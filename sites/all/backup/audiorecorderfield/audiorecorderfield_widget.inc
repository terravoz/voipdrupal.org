<?php
// $Id:

/**
 * @file
 * audiorecorderfield widget hooks and callbacks.
 */

/**
 * Implementation of CCK's hook_widget_settings($op = 'form').
 */
function audiorecorderfield_widget_settings_form($widget) {
  $form = module_invoke('filefield', 'widget_settings', 'form', $widget);

  $form['file_extensions'] = array(
    '#type' => 'textfield',
    '#title' => t('Permitted upload file extensions'),
    '#default_value' => is_string($widget['file_extensions']) ? $widget['file_extensions'] :'mp3 wav',
    '#size' => 64,
    '#description' => t('Extensions a user can upload to this field. Separate extensions with a space and do not include the leading dot. Leaving this blank will allow users to upload a file with any extension.'),
    '#weight' => 1,
  );
  
  return $form;
}

/**
 * Implementation of CCK's hook_widget_settings($op = 'save').
 */
function audiorecorderfield_widget_settings_save($widget) {
  $filefield_settings = module_invoke('filefield', 'widget_settings', 'save', $widget);
  return $filefield_settings;
}

/**
 * Element #value_callback function.
 */
function audiorecorderfield_widget_value($element, $edit = FALSE) {
  $field = filefield_widget_value($element, $edit);
  
  return $field;
}

/**
 * FormAPI theme function. Theme the output of an image field.
 */
function theme_audiorecorderfield_widget($element) {
  
  $z=theme('form_element', $element, $element['#children']);
  
  return $z;
}

/**
 * Process an individual element.
 *
 * Build the form element. When creating a form using FAPI #process,
 * note that $element['#value'] is already set.
 *
 * The $fields array is in $form['#field_info'][$element['#field_name']].
 */
function audiorecorderfield_widget_process($element, $edit, $form_state, $form) {
  $field = $form['#field_info'][$element['#field_name']];
  $field_key = $element['#columns'][0];
  $fid=$element['#value'][$field_key];

  //TODO: Add support for more recording applets (ListenUp,...)
  //TODO: Add hook_audiofield_recorders to allow other modules to add more recorder applets.
  $element['applet'] = array(
    '#required' => $element['#required'],
    '#value' => audiorecorderfield_recorder_nanogong($element, $field['widget'])
  );
     
  // this would be the hidden field the applet would insert the newly uploaded file fid to.
  $element[$field_key] = array(
    '#type' => 'hidden',
    '#title' => t($field['widget']['label']),
    '#required' => $element['#required'],
    '#default_value' => isset($fid) ? $fid : "",
  );

  return $element;
}

/*
 * NanoGong recorder applet
 */
function audiorecorderfield_recorder_nanogong($element, $widget) {
    
    // The widget is being presented, so apply the JavaScript.
    drupal_add_js(drupal_get_path('module', 'audiorecorderfield') . '/js/audiorecorder_nanogong.js');
    $field_name=str_replace('field_', '', $element['#field_name']);
    //Change "_" into "-"
    $field_name=str_replace('_', '-', $field_name);
    
    //TODO: Load options here (width, height,MaxDuration...)
    /*$width = isset($widget['player_width'])?$widget['recorder_width']:300;
    $height = isset($widget['player_height'])? $widget['recorder_height']:100;
    */
    //Nanogong configuration http://gong.ust.hk/nanogong/info_config.html
    $config = '<param name="ShowSaveButton" value="false" />'; //Disable Save button
    $config .= '<param name="ShowTime" value="true" /> '; //Show Time
    $config .= '<param name="ShowSpeedButton" value="false" /> '; //Disable speed button
    $config .= '<param name="MaxDuration" value="1200" /> '; //Set MaxDuration to maximum (20 minutes)
    
    if (!empty($element['#value']['filepath'])) {
        $info = pathinfo($element['#value']['filename']);
        $button_op='Remove';
        $class_suffix='player';
        $audiofile=file_create_url($element['#value']['filepath']);
        $op=$info['extension'];
        if ($op=='wav') {
          //Load existing file in Nanogong
          $audio_url = '<param name="SoundFileURL" value="' . $audiofile . '"/>';
          $config .= '<param name="ShowRecordButton" value="false" /> '; //Disable Record button  
          $width='82px';
        }
        else {
          $output = '<div id="nanogong-' . $field_name . '-' . $element['#delta'] . '-wrapper">' . audiofield_get_player($audiofile, $op) . '</div>';
        }
    }
    else {
        $op='wav';
        $button_op='Upload';
        $class_suffix='recorder';
        $width='113px';
    }
    
    //Display Nanogong applet only if there is no file or uploaded file is wav
    if ($op=='wav') {
        //Add css
        drupal_add_css(drupal_get_path('module', 'audiorecorderfield') . '/css/audiorecorderfield.css');
        //Nanogong Applet
        $output = '<div class="nanogong-' . $class_suffix . '" id="nanogong-' . $field_name . '-' . $element['#delta'] . '-wrapper"><applet id="nanogong-' . $field_name . '-' . $element['#delta'] . '" archive="' . base_path() . drupal_get_path('module', 'audiorecorderfield') . '/recorders/nanogong.jar" 
            code="gong.NanoGong" width="' . $width . '" height="40">
            ' . $config . '
            ' . $audio_url . '
            </applet></div>';
    }
    //Upload/Remove button
    $output .= '<div><input id="nanogong-button-' . $field_name . '-' . $element['#delta'] . '" type="button" value="' . $button_op . '" onclick="submitVoice(\'' . $field_name . '\',' . $element['#delta'] . ')" /></div>';
    
    return $output;
}
