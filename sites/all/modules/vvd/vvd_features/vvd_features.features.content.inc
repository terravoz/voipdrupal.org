<?php

/**
 * Implementation of hook_content_default_fields().
 */
function vvd_features_content_default_fields() {
  $fields = array();

  // Exported field: field_vvd_editor
  $fields['vvd-field_vvd_editor'] = array(
    'field_name' => 'field_vvd_editor',
    'type_name' => 'vvd',
    'display_settings' => array(
      'label' => array(
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'vvd_workspace',
    'required' => '0',
    'multiple' => '0',
    'module' => 'vvd',
    'active' => '1',
    'widget' => array(
      'default_value' => array(
        '0' => '',
      ),
      'default_value_php' => NULL,
      'label' => 'VVD Workspace',
      'weight' => '-4',
      'description' => '',
      'type' => 'vvd_widget',
      'module' => 'vvd',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('VVD Workspace');

  return $fields;
}
