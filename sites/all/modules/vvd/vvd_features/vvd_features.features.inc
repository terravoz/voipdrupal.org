<?php

/**
 * Implementation of hook_node_info().
 */
function vvd_features_node_info() {
  $items = array(
    'vvd' => array(
      'name' => t('VVD Workspace'),
      'module' => 'features',
      'description' => t('Visual VoIP Script Workspace'),
      'has_title' => '1',
      'title_label' => t('Workspace title'),
      'has_body' => '0',
      'body_label' => '',
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}

/**
 * Implementation of hook_views_api().
 */
function vvd_features_views_api() {
  return array(
    'api' => '2',
  );
}
