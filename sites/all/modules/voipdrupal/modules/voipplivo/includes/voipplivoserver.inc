<?php

// $Id$

/**
 * @file
 * Implementation of the VoipPlivoServer class
 */


/**
 * File dependencies
 */

foreach (array('plivo.php', 'voipplivo.inc') as $file) {
  require_once(dirname(__FILE__) . DIRECTORY_SEPARATOR . $file);
}

module_load_include('inc', 'voip', 'includes/voipserver');
module_load_include('inc', 'voipcall', 'voipcall');


/**
 * Class definitions
 */

class VoipPlivoServer extends VoipServer {

  /*
   * Constructors
   */

  function __construct() {
    $id = 'plivo';
    $name = 'Plivo';
    $config_form = 'voipplivo_admin_form';
    parent::__construct($id, $name, $config_form);
  }


  /*
   * Public methods
   */

  /**
   * Implementation of VoipServer() API method
   */

  /*
   * API methods
   */

  /**
   * Implementation of the VoipServer dial() API method
   */
  function dial($voipcall, $server_config = NULL) {

    $rc = FALSE;
    voip_error_reset();

    if (!$server_config) {
      $server_config = $this->getConfig();
    }

    // Plivo configuration
    $api_version = 'v0.1';
    $rest_api_url = $server_config['voipplivo_restapi_url'];
    $account_sid = $server_config['voipplivo_account_sid'];
    $auth_token = $server_config['voipplivo_auth_token'];
	
	$caller_number = ($voipcall->getCallerNumber())
      ? $voipcall->getCallerNumber()
      : variable_get('voipcall_cid_number', NULL);
    $dest_number = $voipcall->getDestNumber();

   // (re)start the session associated with the call
    $voip_session = VoipSession::getSessionByNumber($caller_number, $dest_number);
    if ($voip_session) {
      $voip_session->resetTimer();
	   //we must preserve cid
	  $cid = $voip_session->getCid();
	  //load existing call
	  $voipcall = VoipCall::load($cid);
    }
    else {
      $voip_session = new VoipSession();
      $voip_session->setOriginNumber($caller_number);
      $voip_session->setDestinationNumber($dest_number);
	  
	  // Update call variables
      $voipcall->setSource('drupal');
      $voipcall->setDirection(VoipCall::OUTBOUND);
	  $voipcall->save();
      $cid = $voipcall->getCid();
	  $voip_session->setCid($cid);
    }
    $voip_session->save();

    # Define Channel Variable - http://wiki.freeswitch.org/wiki/Channel_Variables
    $extra_dial_string = "bridge_early_media=true,hangup_after_bridge=true";

    $menu_path = 'voip/plivo/callhandler';
    $response_url = $menu_path . '/process_outbound_calls/' . $cid;
    $call_handler_url = url($response_url, array('absolute' => TRUE));
    $response_url = $menu_path . '/process_hangup/' . $cid;
    $status_callback_url = url($response_url, array('absolute' => TRUE));

    $gateways = $server_config['voipplivo_call_gateways'];
    $gateway_codecs = $server_config['voipplivo_call_gateway_codec'];
    $gateway_timeouts = $server_config['voipplivo_call_gateway_timeouts'];
    $gateway_retries = $server_config['voipplivo_call_gateway_retries'];

    $vars = array(
      'From' => $caller_number,
      # Caller Id
      'To' => $dest_number,
      # User Number to Call
      'Gateways' => $gateways,
      # Gateway string to try dialing our separated by comma. First in list will be tried first
      'GatewayCodecs' => $gateway_codecs,
      # Codec string as needed by FS for each gateway separated by comma
      'GatewayTimeouts' => $gateway_timeouts,
      # Seconds to timeout in string for each gateway separated by comma
      'GatewayRetries' => $gateway_retries,
      # Retry String for Gateways separated by comma, on how many times each gateway should be retried
      'ExtraDialString' => $extra_dial_string,
      'AnswerUrl' => $call_handler_url,
      //TODO: Check that hangup_url works
      'HangupUrl' => $status_callback_url,
      //TODO: Whats the purpose of ringing URLs? Is it optional?
      //'RingUrl' => "http://127.0.0.1:5000/ringing/"
    );

    // Instantiate a new Plivo Rest Client
    $client = new PlivoRestClient($rest_api_url, $account_sid, $auth_token, $api_version);
    $response = $client->call($vars);

    // update call based on response
    if ($response->IsError) {
      // differentiate between processing errors and higher-level errors
      $plivo_error_code = (string) $response->HttpStatus;
      switch ($plivo_error_code) {
        case '401': // wrong auth token and auth sid or if you your ip is not allowed in ALLOWED_IPS
          $error_msg = t('Wrong auth token and auth sid or ip is not allowed.');
          $voipcall->setErrorMessage($error_msg);
          $voipcall->setCallStatus(VoipCall::ERROR);
          $voipcall->save();
          break;
        default: // processing error
          $plivo_error_msg = $response->ErrorMessage;
          $msg = "Processing failure. Please contact your system's administrator. Plivo error @plivo_code: @plivo_msg";
          $params = array(
            '@plivo_code' => $plivo_error_code,
            '@plivo_msg' => $plivo_error_msg
          );
          $voipcall->report_error('voipplivo', $msg, $params);
          break;
      }
      $rc = FALSE;
    }
    else {
      $rc = TRUE;
    }

    return $rc;
  }

  /**
   * Implementation of the VoipServer send_text() API method
   */
  function send_text($text, $voipcall, $reply = FALSE, $server_config = NULL) {
    $rc = FALSE;
    voip_error_reset();

    // determine from/to numbers
    if ($reply) {
      $to = $voipcall->getCallerNumber();
      $from = $voipcall->getDestNumber();
      if (!isset($from)) {
        $voipcall->report_error('voipplivo', "Attempt to send a text message reply with no caller number.");
        return FALSE;
      }
    }
    else {
      $to = $voipcall->getDestNumber();
      $from = ($voipcall->getCallerNumber())
        ? $voipcall->getCallerNumber()
        : variable_get('voipcall_cid_number', NULL);
    }

    // (re)start the session associated with the call
    $voip_session = VoipSession::getSessionByNumber($from, $to);
    if ($voip_session) {
      $voip_session->resetTimer();
	  $cid = $voip_session->getCid();
	  //load existing call
	  $voipcall = VoipCall::load($cid);
    }
    else {
      $voip_session = new VoipSession();
      $voip_session->setOriginNumber($from);
      $voip_session->setDestinationNumber($to);
	  
	  // update call variables
      $voipcall->setSource('drupal');
      $voipcall->setDirection(VoipCall::OUTBOUND);
      $voipcall->setCurrentChannel('text');
      $voipcall->setCurrentNetwork('sms');
	  $voipcall->save();
      $cid = $voipcall->getCid();
	  $voip_session->setCid($cid);
    }

    $voip_session->save();

    // send the sms
    if (voipscript_use_sms_framework()) {
      // use SMS Framework to send SMS message if user enabled this option
      voipscript_send_sms_framework($to, $text);
      return TRUE;
    }
    // else use VoIP Drupal:
    // Plivo doesn't support SMS yet
    return FALSE;
  }

  /**
   * Implementation of the VoipServer hangup() API method
   */
  function hangup($voipcall, $server_config = NULL) {
    if (voip_debug()) {
      $id = $voipcall->getCallId();
      $status = $voipcall->getCallStatus();
      watchdog('voipplivo', "in hangup() with call id: $id and status: $status");
    }
    $rc = FALSE;
    voip_error_reset();

    if (!$server_config) {
      $server_config = $this->getConfig();
    }

    // Plivo configuration
    $api_version = 'v0.1';
    $rest_api_url = $server_config['voipplivo_restapi_url'];
    $account_sid = $server_config['voipplivo_account_sid'];
    $auth_token = $server_config['voipplivo_auth_token'];

    // Instantiate a new Plivo Rest Client
    $client = new PlivoRestClient($rest_api_url, $account_sid, $auth_token, $api_version);

    $call_id = $voipcall->getCallId();
    if (!$call_id) {
      $msg = "Attempt to hangup a Plivo call (cid = @cid) without a call id";
      $params = array('@cid' => $voipcall->getCid());
      $voipcall->report_error('voipplivo', $msg, $params);
      $rc = FALSE;
    }
    else {
      //$plivo_path = "/$api_version/Accounts/$account_sid/Calls/$call_id";
      $vars = array(
        'CallUUID' => $call_id, # Request UUID to hangup call
      );

      $response = $client->hangup_call($vars);

      // update call based on response
      if ($response->IsError) {
        $msg = "Plivo hangup command failed: @error";
        $params = array('@error' => $response->ErrorMessage);
        $voipcall->report_error('voipplivo', $msg, $params);
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
   * Implementation of the VoipServer text_handler() API method
   */
  function text_handler($text_content, $origin, $destination, $time, $network, $server_name) {
    $menu_path = 'voip/plivo/callhandler';
    $request_url = $menu_path . '/process_inbound_text/';
    $url = url($request_url, array('absolute' => TRUE));

    $server_config = $this->getConfig();
    $vars = array(
      'AccountSid' => $server_config['voipplivo_account_sid'],
      'SmsSid' => $todo,
      'From' => $origin,
      'To' => $destination,
      'Body' => $text_content,
      'Direction' => 'inbound',
      'Channel' => 'offline_text'
    );

    //url-ify the data for the POST
    foreach ($vars as $key => $value) {
      $fields_string .= $key . '=' . urlencode($value) . '&';
    }
    $fields_string = rtrim($fields_string, '&');

    //open connection
    $ch = curl_init();

    //set the url, number of POST vars, POST data
    curl_setopt($ch, CURLOPT_URL, $url);
    curl_setopt($ch, CURLOPT_POST, count($vars));
    curl_setopt($ch, CURLOPT_POSTFIELDS, $fields_string);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);

    //execute post
    $result = curl_exec($ch);

    //close connection
    curl_close($ch);
  }

  /**
   * Implementation of the VoipServer ping() API method
   */
  function ping($server_config = NULL) {

    if (!$server_config) {
      $server_config = $this->getConfig();
    }

    // Plivo configuration
    $api_version = 'v0.1';
    $rest_api_url = $server_config['voipplivo_restapi_url'];
    $account_sid = $server_config['voipplivo_account_sid'];
    $auth_token = $server_config['voipplivo_auth_token'];

    // Instantiate a new Plivo Rest Client
    try {
      $client = new PlivoRestClient($rest_api_url, $account_sid, $auth_token, $api_version);

      // Request a reload configuration as a way to test the server connectivity
      voip_error_reset();
      $vars = array();
      $response = $client->reload_config($vars);

      if ($response->IsError) {
        voip_error("Plivo command Ping failed: " . $response->ErrorMessage);
        return FALSE;
      }
      return TRUE;
    } catch (Exception $e) {
      voip_error($e->getMessage());
      return FALSE;
    }
  }

  /**
   * Private methods
   */
// TODO:  private static function _get_available_voices() {
  static function _get_available_voices() {
    // Note: check http://festvox.org/voicedemos.html for demos of the different voices
    $voices = array();
    $voices['slt'] = array(
      'language' => 'en', 'voice' => 'woman',
      'description' => t('Slt (female voice in American English)')
    );
    $voices['rms'] = array(
      'language' => 'en', 'voice' => 'man',
      'description' => t('Rms (male voice in American English)')
    );
    $voices['awb'] = array(
      'language' => 'en2', 'voice' => 'man',
      'description' => t('Awb (male voice in Scottish English)')
    );
    $voices['kal'] = array(
      'language' => 'en-us', 'voice' => 'man',
      'description' => t('Kal (male voice in American English)')
    );
    return $voices;
  }
}

