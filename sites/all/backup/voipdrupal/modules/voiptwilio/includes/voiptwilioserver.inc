<?php

// $Id$

/**
 * @file
 * Implementation of the VoipTwilioServer class
 */


/**
 * File dependencies
 */

foreach (array('twilio.php', 'voiptwilio.inc') as $file) {
  require_once(dirname(__FILE__) . DIRECTORY_SEPARATOR . $file);
}

module_load_include('inc', 'voip', 'includes/voipserver');
module_load_include('inc', 'voipcall', 'voipcall');


/**
 * Class definitions
 */
        
class VoipTwilioServer extends VoipServer {

  /*
   * Constructors
   */

  function __construct() {
    $id = 'twilio';
    $name = 'Twilio';
    $config_form = 'voiptwilio_admin_form';
    parent::__construct($id, $name, $config_form);
  }


  /*
   * Public methods
   */

  static function getVoicesList(){
    $voices_available = self::_get_available_voices();
    $list = array();
    foreach($voices_available as $id => $voice) {
      $list[$id] = $voice['description'];
    }
    asort($list);
    return $list;
  }

  /**
   * Implementation of VoipServer() API method
   */
  function getDefaultLanguage(){
    $server_config = $this->getConfig();
    $voice_id = $server_config['voiptwilio_voice_id'];
    $voices_available = self::_get_available_voices();
    $voice_descriptor = $voices_available[$voice_id];
    $voice = $voice_descriptor['language'];
    return $voice;
  }

  /**
   * Implementation of VoipServer() API method
   */
  function getDefaultVoice(){
    $server_config = $this->getConfig();
    $voice_id = $server_config['voiptwilio_voice_id'];
    $voices_available = self::_get_available_voices();
    $voice_descriptor = $voices_available[$voice_id];
    $voice = $voice_descriptor['voice'];
    return $voice;
  }


  /*
   * API methods
   */

  /**
   * Implementation of the VoipServer dial() API method
   */
  function dial($voipcall, $server_config=NULL) {

    $rc = FALSE;
    voip_error_reset();

    if(!$server_config) {
      $server_config = $this->getConfig();
    }

    // Twilio configuration
    $api_version = '2010-04-01';
    $account_sid = $server_config['voiptwilio_account_sid'];
    $auth_token = $server_config['voiptwilio_auth_token'];

    // Update call variables
    $voipcall->setSource('drupal');
    $voipcall->setDirection(VoipCall::OUTBOUND);
    
    // save the call in order to get generate an nid
    $voipcall->save();

    // Instantiate a new Twilio Rest Client
    $client = new TwilioRestClient($account_sid, $auth_token);

    // Initiate a new outbound call by POST'ing to the Calls resource
    $twilio_path = "/$api_version/Accounts/$account_sid/Calls";
    $caller_number = ($voipcall->getCallerNumber())
                       ? $voipcall->getCallerNumber()
                       : variable_get('voipcall_cid_number', NULL);
    $dest_number = $voipcall->getDestNumber();

    $menu_path = 'voip/twilio/callhandler';
    $call_nid = $voipcall->getCid();
    $response_url = $menu_path . '/process_outbound_calls/' . $call_nid;
    $call_handler_url = url($response_url, array('absolute' => TRUE));
    $response_url = $menu_path . '/process_hangup/' . $call_nid;
    $status_callback_url = url($response_url, array('absolute' => TRUE));

    $vars = array(
      'Caller' => $caller_number,
      'Called' => $dest_number,
      'Url' => $call_handler_url,
      'Method' => 'POST',
      'StatusCallback' => $status_callback_url,
      'StatusCallbackMethod' => 'POST',
      'SendDigits' => '',  // TODO: shall we encode extra digits with dest_number?
      'Timeout' => 60 // TODO: Set to 15 in order to avoid answering machines?
    );

    // Handle answering machine options
    if($voipcall->getCheckMachine() == TRUE) {
// TODO: do we need to implement Twilio's 'hangup on machine' option here?
      // Note: adding any value in here -- even 'Continue' -- adds a 5 sec delay
      //       to the call. To prevent that, 'IfMachine' has to be NULL
      $vars['IfMachine'] = 'Continue'; 
    }

    $response = $client->request($twilio_path, "POST", $vars);

    // update call based on response
    if($response->IsError){
      // differentiate between processing errors and higher-level errors
      $twilio_error_code = (string)$response->ResponseXml->RestException->Code;
      switch($twilio_error_code){
        // the following codes are listed in
        //   http://www.twilio.com/docs/errors/reference/
        case '13214': // Dial: Invalid callerId value
        case '21210': // Caller phone number not verified
        case '21212': // Invalid Caller Phone Number
          $error_msg = t('Invalid caller id value');
          $voipcall->setErrorMessage($error_msg);
          $voipcall->setCallStatus(VoipCall::ERROR);
          $voipcall->save();
          break;
        case '13223': // Dial: Invalid phone number format
        case '13224': // Dial: Invalid phone number
        case '21211': // Invalid Called Phone Number
        case '21213': // Caller phone number is required
        case '21401': // Invalid Phone Number
          $error_msg = t('Invalid phone number');
          $voipcall->setErrorMessage($error_msg);
          $voipcall->setCallStatus(VoipCall::ERROR);
          $voipcall->save();
          break;
        case '13225': // Dial: Forbidden phone number 
        case '21215': // Account not authorized to call NNN
          $error_msg = t('Forbidden phone number');
          $voipcall->setErrorMessage($error_msg);
          $voipcall->setCallStatus(VoipCall::ERROR);
          $voipcall->save();
          break;
        default: // processing error
          $twilio_error_msg = $response->ErrorMessage;
          $msg = "Processing failure. Please contact your system's administrator. Twilio error @twilio_code: @twilio_msg";
          $params = array('@twilio_code' => $twilio_error_code, 
                          '@twilio_msg' => $twilio_error_msg);
          $voipcall->report_error('voiptwilio', $msg, $params);
          break;
      }
      $rc = FALSE;
    }
    else {
      $rc = TRUE;

      // get the new id and status associated with the call
      $xml = $response->ResponseXml;
      $call_id = (string)$xml->Call->Sid;
      $twilio_call_status = (string)$xml->Call->Status;
      $voipcall->setCallId($call_id);
      $voipcall = voiptwilio_update_call_status($voipcall, $twilio_call_status);
      $voipcall->save();

watchdog('voiptwilio', 'new call: ' . print_r($voipcall, true));
    }

    return $rc;
  }


  /**
   * Implementation of the VoipServer hangup() API method
   */
  function hangup($voipcall, $server_config=NULL) {
$id = $voipcall->getCallId();
$status = $voipcall->getCallStatus();
watchdog('voiptwilio', "in hangup() with call id: $id and status: $status");

    $rc = FALSE;
    voip_error_reset();

    if(!$server_config) {
      $server_config = $this->getConfig();
    }

    // Twilio configuration
    $api_version = '2010-04-01';
    $account_sid = $server_config['voiptwilio_account_sid'];
    $auth_token = $server_config['voiptwilio_auth_token'];

    // Instantiate a new Twilio Rest Client
    $client = new TwilioRestClient($account_sid, $auth_token);

    $call_id = $voipcall->getCallId();
    if(!$call_id){
      $msg = "Attempt to hangup a Twilio call (nid = @nid) without a call id";
      $params = array('@nid' => $voipcall->getCid());
      $voipcall->report_error('voiptwilio', $msg, $params);
      $rc = FALSE;
    }
    else {
      $twilio_path = "/$api_version/Accounts/$account_sid/Calls/$call_id";
      $status = 'completed';
      $vars =    array(
        'Status' => $status,
      );

      $response = $client->request($twilio_path, "POST", $vars);

      // update call based on response
      if($response->IsError){
        $msg = "Twilio hangup command failed: @error";
        $params = array('@error' => $response->ErrorMessage);
        $voipcall->report_error('voiptwilio', $msg, $params);
      }
      else {
        $voipcall->setHangupReason(VoipCall::HANGUP_API_REQUEST);
        $voipcall->save();
        $rc = TRUE;
      }
    }

    return $rc;
  }


  /**
   * Implementation of the VoipServer ping() API method
   */
  function ping($server_config=NULL) {

    if(!$server_config) {
      $server_config = $this->getConfig();
    }

    // Twilio configuration
    $api_version = '2010-04-01';
    $account_sid = $server_config['voiptwilio_account_sid'];
    $auth_token = $server_config['voiptwilio_auth_token'];

    // Instantiate a new Twilio Rest Client
    $client = new TwilioRestClient($account_sid, $auth_token);

    // Request a call log as a way to test the server connectivity
    voip_error_reset();
    $path = "/$api_version/Accounts/$account_sid/Calls";
    $vars = array();
    $response = $client->request($path, "GET", $vars);

    if($response->IsError){
      voip_error("Twilio command Ping failed: " . $response->ErrorMessage);
      return FALSE;
    }
    return TRUE;
  }

  /**
   * Private methods
   */
// TODO:  private static function _get_available_voices() {
static function _get_available_voices() {
    $voices = array();
    $voices['en_man'] = array('language' => 'en', 'voice' => 'man',
                        'description' => t('male voice in English'));
    $voices['en_woman'] = array('language' => 'en', 'voice' => 'woman',
                        'description' => t('female voice in English'));
    $voices['es_man'] = array('language' => 'es', 'voice' => 'man',
                        'description' => t('male voice in Spanish'));
    $voices['es_woman'] = array('language' => 'es', 'voice' => 'woman',
                        'description' => t('female voice in Spanish'));
    $voices['fr_man'] = array('language' => 'fr', 'voice' => 'man',
                        'description' => t('male voice in French'));
    $voices['fr_woman'] = array('language' => 'fr', 'voice' => 'woman',
                        'description' => t('female voice in French'));
    $voices['de_man'] = array('language' => 'de', 'voice' => 'man',
                        'description' => t('male voice in German'));
    $voices['de_woman'] = array('language' => 'de', 'voice' => 'woman',
                        'description' => t('female voice in German'));
    return $voices;
  }

}

