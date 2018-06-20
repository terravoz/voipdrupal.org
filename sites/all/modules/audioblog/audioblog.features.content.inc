<?php

/**
 * Implementation of hook_content_default_fields().
 */
function audioblog_content_default_fields() {
  $fields = array();

  // Exported field: field_audioblog_recording
  $fields['audioblog-field_audioblog_recording'] = array(
    'field_name' => 'field_audioblog_recording',
    'type_name' => 'audioblog',
    'display_settings' => array(
      'label' => array(
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'audiofield_embedded',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'audiofield_embedded',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'audiofield_embedded',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'audiofield_embedded',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'filefield',
    'required' => '0',
    'multiple' => '0',
    'module' => 'filefield',
    'active' => '1',
    'list_field' => '0',
    'list_default' => 1,
    'description_field' => '0',
    'widget' => array(
      'file_extensions' => 'mp3 wav',
      'file_path' => '',
      'progress_indicator' => 'bar',
      'max_filesize_per_file' => '',
      'max_filesize_per_node' => '',
      'label' => 'Audio',
      'weight' => '31',
      'description' => '',
      'type' => 'audiorecorderfield_widget',
      'module' => 'audiorecorderfield',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Audio');

  return $fields;
}
