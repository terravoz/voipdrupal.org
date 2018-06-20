<?php
// $Id$

/**
 * @file
 * A FileField extension to allow uploading audio files by recording them in Nanogong
 */

/**
 * Implementation of hook_filefield_source_info().
 */
function filefield_source_recorder_info() {
  $source['recorder'] = array(
    'name' => t('Audio Recorder'),
    'label' => t('Audio Recorder'),
    'description' => t('Record audio using Nanogong audio recorder.'),
    'process' => 'filefield_source_recorder_process',
    'value' => 'filefield_source_recorder_value',
    'weight' => 3,
  );
  return $source;
}

/**
 * Implementation of hook_theme().
 */
function filefield_source_recorder_theme() {
  return array(
    'filefield_source_recorder_element' => array(
      'arguments' => array('element' => NULL),
      'file' => 'sources/recorder.inc',
    ),
  );
}

/**
 * A #process callback to extend the filefield_widget element type.
 */
function filefield_source_recorder_process($element, $edit, &$form_state, $form) {
  $field = content_fields($element['#field_name'], $element['#type_name']);

  $element['filefield_recorder'] = array(
    '#theme' => 'filefield_source_recorder_element',
    '#weight' => 100.5,
    '#access' => empty($element['fid']['#value']),
  );

  $path = _filefield_source_recorder_directory($field['widget']);
  $description = t('Record audio using Nanogong audio recorder.');

  $validators = $element['#upload_validators'];
  if (isset($validators['filefield_validate_size'])) {
      unset($validators['filefield_validate_size']);
  }
  //$description .= '<br />' . filefield_sources_element_validation_help($validators);
  
  $element['filefield_recorder']['#description'] = $description;
 
  $element['filefield_recorder']['recorder'] = array(
    '#type' => 'submit',
    '#value' => $recorder_message ? t('Refresh') : t('recorder'),
    '#submit' => array('node_form_submit_build_node'),
    '#ahah' => array(
       'path' => 'filefield/ahah/'. $element['#type_name'] .'/'. $element['#field_name'] .'/'. $element['#delta'],
       'wrapper' => $element['#id'] .'-ahah-wrapper',
       'method' => 'replace',
       'effect' => 'fade',
    ),
  );
  
  $element['filefield_recorder']['rec'] = array(
    '#value' => audiorecorderfield_recorder_nanogong($element, $field['widget'])
  );

  return $element;
}

/**
 * A #filefield_value_callback function.
 */
function filefield_source_recorder_value($element, &$item) {
  if (!empty($item['filefield_recorder']['filename'])) {
    $field = content_fields($element['#field_name'], $element['#type_name']);
    $recorder_path = _filefield_source_recorder_directory($field['widget']);
    $filepath = $recorder_path . '/' . $item['filefield_recorder']['filename'];

    // Clean up the file name extensions and transliterate.
    $original_filepath = $filepath;
    $new_filepath = filefield_sources_clean_filename($filepath);
    rename($filepath, $new_filepath);
    $filepath = $new_filepath;

    // Run all the normal validations, minus file size restrictions.
    $validators = $element['#upload_validators'];
    if (isset($validators['filefield_validate_size'])) {
      unset($validators['filefield_validate_size']);
    }

    // Save the file to the new location.
    if ($file = field_file_save_file($filepath, $validators, filefield_widget_file_path($field))) {
      $item = array_merge($item, $file);

      // Delete the original file if "moving" the file instead of copying.
      if (empty($field['widget']['filefield_source_recorder_mode']) || $field['widget']['filefield_source_recorder_mode'] !== 'copy') {
        @unlink($filepath);
      }
    }

    // Restore the original file name if the file still exists.
    if (file_exists($filepath) && $filepath != $original_filepath) {
      rename($filepath, $original_filepath);
    }
  }

  $item['filefield_recorder']['filename'] = '';
}

/**
 * Theme the output of the autocomplete field.
 */
function theme_filefield_source_recorder_element($element) {
 
  $output = $element['recorder_message']['#value'];
  $output .= $element['rec']['#value'];
  $element['#type'] = 'item';
  return '<div class="filefield-source filefield-source-recorder clear-block">' . theme('form_element', $element, $output) . '</div>';
}

function _filefield_source_recorder_directory($field, $account = NULL) {
  $account = isset($account) ? $account : $GLOBALS['user'];  
  $path = $field['filefield_source_recorder_path'];
  $absolute = !empty($field['filefield_source_recorder_absolute']);

  // Replace user level tokens.
  // Node level tokens require a lot of complexity like temporary storage
  // locations when values don't exist. See the filefield_paths module.
  if (module_exists('token')) {
    $path = token_replace($path, 'user', $account);
  }

  return $absolute ? $path : file_directory_path() . '/' . $path;
}
