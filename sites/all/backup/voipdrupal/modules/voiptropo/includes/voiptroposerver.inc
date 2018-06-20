<?php

// $Id$

/**
 * @file
 * Implementation of the VoiptropoServer class
 */


/**
 * File dependencies
 */

module_load_include('inc', 'voip', 'includes/voipserver');
module_load_include('inc', 'voipcall', 'voipcall');


/**
 * Class definitions
 */
        
class VoipTropoServer extends VoipServer {

  /*
   * Constructors
   */

  function __construct() {
    $id = 'tropo';
    $name = 'Tropo';
    $config_form = 'voiptropo_admin_form';
    parent::__construct($id, $name, $config_form);
  }


  /*
   * Public methods
   */

  static function getVoicesList() {
    $voices_available = self::_get_available_voices();
    $list = array();
    foreach ($voices_available as $id => $voice) {
      $list[$id] = $voice['description'];
    }
    asort($list);
    return $list;
  }

  /**
   * Returns the Tropo id associated with the given $voice and $language
   */
  static function getVoiceId($voice, $language) {
    $voices = VoipTropoServer::_get_available_voices();
    foreach ($voices as $key => $voice_array) {
      if ($voice_array['language'] == $language && $voice_array['voice'] == $voice) {
        return $key;
      }
    }
    return NULL;
  }
  
  /**
   * Returns the Tropo Voice Region id associated with the given $voice and $language
   */
  static function getVoiceRegionId($voice, $language) {
    $voices = VoipTropoServer::_get_available_voices();
    foreach ($voices as $key => $voice_array) {
      if ($voice_array['language'] == $language && $voice_array['voice'] == $voice) {
        return $voice_array['language'].'-'.$voice_array['region'];
      }
    }
    return NULL;
  }

  /**
   * Implementation of VoipServer() API method
   */
  function getDefaultLanguage() {
    $server_config = $this->getConfig();
    $voice_id = $server_config['voiptropo_voice_id'];
    $voices_available = self::_get_available_voices();
    $voice_descriptor = $voices_available[$voice_id];
    $voice = $voice_descriptor['language'];
    return $voice;
  }

  /**
   * Implementation of VoipServer() API method
   */
  function getDefaultVoice() {
    $server_config = $this->getConfig();
    $voice_id = $server_config['voiptropo_voice_id'];
    return $voice_id;
  }


  /*
   * API methods
   */

  /**
   * Implementation of the VoipServer dial() API method
   */
  function dial($voipcall, $server_config=NULL) {

    voip_error_reset();

    if (!$server_config) {
      $server_config = $this->getConfig();
    }

    // tropo configuration
    $username = $server_config['voiptropo_account_username'];
    $password = $server_config['voiptropo_account_password'];
    $token = $server_config['voiptropo_voice_token'];

    // Update call variables
    $voipcall->setSource('drupal');
    $voipcall->setDirection(VoipCall::OUTBOUND);
    
    // save the call in order to get generate an nid
    $voipcall->save();

    // Instantiate a new tropo Rest Client
    $client = new SessionAPI();
    $caller_number = ($voipcall->getCallerNumber())
                       ? $voipcall->getCallerNumber()
                       : variable_get('voipcall_cid_number', NULL);
    $voipcall->setCallerNumber($caller_number);                   
    $dest_number = $voipcall->getDestNumber();
   
    //$menu_path = 'voip/tropo/callhandler';
    $call_nid = $voipcall->getCid();
  
    $vars = array(
      'action' => 'create',
      'username' => $username,
      'password' => $password,
      'caller_number' => $caller_number,
      'dest_number' => $dest_number,
      'tropo_action' => 'process_outbound_calls',
      'call_nid' => $call_nid,
    );

    //TODO: TZ:What is this?
    // Handle answering machine options
    /*if($voipcall->getCheckMachine() == TRUE) {
    // TODO: do we need to implement tropo's 'hangup on machine' option here?
      // Note: adding any value in here -- even 'Continue' -- adds a 5 sec delay
      //       to the call. To prevent that, 'IfMachine' has to be NULL
      $vars['IfMachine'] = 'Continue'; 
    }
    */
    try {
      $response = $client->createSession($token, $vars);
    }
    catch (Exception $e) {
      $msg = "Processing failure. Please contact your system's administrator.";
      $voipcall->report_error('voiptropo', $msg);
      //$voipcall->setErrorMessage($error_msg);
      $voipcall->setCallStatus(VoipCall::ERROR);
      $voipcall->save();
      return FALSE;
    }
    // Else: 
    $voipcall->save();
    watchdog('voiptropo', 'new call: ' . print_r($voipcall, TRUE));
    return TRUE;
  }


  /**
   * Implementation of the VoipServer hangup() API method
   */
  function hangup($voipcall, $server_config=NULL) {
   $id = $voipcall->getCallId();
   $status = $voipcall->getCallStatus();
   watchdog('voiptropo', "in hangup() with call id: $id and status: $status");

    $rc = FALSE;
    voip_error_reset();

    if (!$server_config) {
      $server_config = $this->getConfig();
    }

    // tropo configuration
    $username = $server_config['voiptropo_account_username'];
    $password = $server_config['voiptropo_account_password'];
    $token = $server_config['voiptropo_voice_token'];

    // Instantiate a new Tropo Event API
    $client=new EventAPI($username, $password);

    $call_id = $voipcall->getCallId();
    if (!$call_id) {
      $msg = "Attempt to hangup a tropo call (nid = @nid) without a call id";
      $params = array('@nid' => $voipcall->getCid());
      $voipcall->report_error('voiptropo', $msg, $params);
      $rc = FALSE;
    }
    else {
      $event = 'hangup';
      try {
        $client->sendEvent($call_id, $event);
        $voipcall->setHangupReason(VoipCall::HANGUP_API_REQUEST);
        $voipcall->save();
        $rc = TRUE;
      }
      catch (Exception $e) {
        $msg = "tropo hangup command failed: @error";
        $params = array('@error' => $e->getMessage());
        $voipcall->report_error('voiptropo', $msg, $params);
      }
    }

    return $rc;
  }


  /**
   * Implementation of the VoipServer ping() API method
   */
  function ping($server_config=NULL) {
 
    // tropo configuration
    $username = $server_config['voiptropo_account_username'];
    $password = $server_config['voiptropo_account_password'];

    // Instantiate a new tropo Rest Client
    $provisioning=new ProvisioningAPI($username, $password);

    voip_error_reset();    
    try{
      // Request a list of applications as a way to test the server connectivity
      $response = $provisioning->viewApplications();
    }
    catch (Exception $e) {
      voip_error("Tropo command Ping failed: " . $e->getMessage());
      return FALSE;
    }
   
    return TRUE;
  }

  private static function _get_available_voices() {
    $voices = array();
    $voices['carmen'] = array(
      'language' => 'es', 'region' => 'es', 'voice' => 'woman', 
      'description' => t('female voice in Castilian Spanish'));
    $voices['jorge'] = array(
      'language' => 'es', 'region' => 'es', 'voice' => 'man', 
      'description' => t('male voice in Castilian Spanish'));
    $voices['florence'] = array(
      'language' => 'fr', 'region' => 'fr', 'voice' => 'woman', 
      'description' => t('female voice in French'));
    $voices['bernard'] = array(
      'language' => 'fr', 'region' => 'fr', 'voice' => 'man', 
      'description' => t('male voice in French'));
    $voices['allison'] = array(
      'language' => 'en', 'region' => 'us', 'voice' => 'woman', 
      'description' => t('female voice in US English'));
    $voices['dave'] = array(
      'language' => 'en', 'region' => 'us', 'voice' => 'man', 
      'description' => t('male voice in US English'));
    $voices['kate'] = array(
      'language' => 'en', 'region' => 'gb', 'voice' => 'woman', 
      'description' => t('female voice in British English'));
    $voices['simon'] = array(
      'language' => 'en', 'region' => 'gb', 'voice' => 'man', 
      'description' => t('male voice in British English'));
    $voices['katrin'] = array(
      'language' => 'de', 'region' => 'de', 'voice' => 'woman', 
      'description' => t('female voice in German'));
    $voices['stefan'] = array(
      'language' => 'de', 'region' => 'de', 'voice' => 'man', 
      'description' => t('male voice in German'));
    $voices['paola'] = array(
      'language' => 'it', 'region' => 'it', 'voice' => 'woman', 
      'description' => t('female voice in Italian'));
    $voices['luca'] = array(
      'language' => 'it', 'region' => 'it', 'voice' => 'man', 
      'description' => t('male voice in Italian'));
    $voices['saskia'] = array(
      'language' => 'nl', 'region' => 'nl', 'voice' => 'woman', 
      'description' => t('female voice in Dutch'));
    $voices['willem'] = array(
      'language' => 'nl', 'region' => 'nl', 'voice' => 'man', 
      'description' => t('male voice in Dutch'));
    $voices['soledad'] = array(
      'language' => 'es', 'region' => 'mx', 'voice' => 'woman', 
      'description' => t('female voice in Mexican Spanish'));
    $voices['carlos'] = array(
      'language' => 'es', 'region' => 'mx', 'voice' => 'man', 
      'description' => t('male voice in Mexican Spanish'));
    $voices['zosia'] = array(
      'language' => 'pl', 'region' => 'pl', 'voice' => 'woman', 
      'description' => t('female voice in Polish'));
    $voices['krzysztof'] = array(
      'language' => 'pl', 'region' => 'pl', 'voice' => 'man', 
      'description' => t('male voice in Polish'));
    return $voices;
  }
}
