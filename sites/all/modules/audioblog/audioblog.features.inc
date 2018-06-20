<?php

/**
 * Implementation of hook_node_info().
 */
function audioblog_node_info() {
  $items = array(
    'audioblog' => array(
      'name' => t('Audio Blog'),
      'module' => 'features',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}
