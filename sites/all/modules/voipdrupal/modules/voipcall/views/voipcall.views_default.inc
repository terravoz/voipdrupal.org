<?php

/**
 * @file
 *  Provide sample VoIP all log table.
 */

/**
 * Implements hook_views_default_views().
 */
function voipcall_views_default_views() {
  $views = array();

  $view = new view;
  $view->name = 'voipcall';
  $view->description = 'VoIP call log';
  $view->tag = '';
  $view->view_php = '';
  $view->base_table = 'voipcall';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('relationships', array(
    'uid' => array(
      'label' => 'user',
      'required' => 0,
      'id' => 'uid',
      'table' => 'voipcall',
      'field' => 'uid',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('fields', array(
    'cid' => array(
      'label' => 'CID',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'set_precision' => FALSE,
      'precision' => 0,
      'decimal' => '.',
      'separator' => ',',
      'prefix' => '',
      'suffix' => '',
      'exclude' => 0,
      'id' => 'cid',
      'table' => 'voipcall',
      'field' => 'cid',
      'relationship' => 'none',
    ),
    'start_time' => array(
      'label' => 'Start time',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'date_format' => 'small',
      'custom_date_format' => '',
      'exclude' => 0,
      'id' => 'start_time',
      'table' => 'voipcall',
      'field' => 'start_time',
      'relationship' => 'none',
    ),
    'name' => array(
      'label' => 'User',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_user' => 1,
      'overwrite_anonymous' => 0,
      'anonymous_text' => '',
      'exclude' => 0,
      'id' => 'name',
      'table' => 'users',
      'field' => 'name',
      'relationship' => 'uid',
    ),
    'caller_name' => array(
      'label' => 'Caller name',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'exclude' => 0,
      'id' => 'caller_name',
      'table' => 'voipcall',
      'field' => 'caller_name',
      'relationship' => 'none',
    ),
    'caller_number' => array(
      'label' => 'Caller number',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'exclude' => 0,
      'id' => 'caller_number',
      'table' => 'voipcall',
      'field' => 'caller_number',
      'relationship' => 'none',
    ),
    'dest_name' => array(
      'label' => 'Destination name',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'exclude' => 0,
      'id' => 'dest_name',
      'table' => 'voipcall',
      'field' => 'dest_name',
      'relationship' => 'none',
    ),
    'dest_number' => array(
      'label' => 'Destination number',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'exclude' => 0,
      'id' => 'dest_number',
      'table' => 'voipcall',
      'field' => 'dest_number',
      'relationship' => 'none',
    ),
    'nothing' => array(
      'label' => 'Other',
      'alter' => array(
        'text' => 'See more',
        'make_link' => 1,
        'path' => 'voipcall/[cid]',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'exclude' => 0,
      'id' => 'nothing',
      'table' => 'views',
      'field' => 'nothing',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'perm',
    'perm' => 'administer voip drupal framework',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('title', 'VoIP Call Log');
  $handler->override_option('items_per_page', 50);
  $handler->override_option('use_pager', '1');
  $handler->override_option('style_plugin', 'table');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'asc',
    'columns' => array(
      'call_channel' => 'call_channel',
      'call_network' => 'call_network',
      'caller_name' => 'caller_name',
      'caller_number' => 'caller_number',
      'dest_name' => 'dest_name',
      'dest_number' => 'dest_number',
      'direction' => 'direction',
      'duration' => 'duration',
      'start_time' => 'start_time',
      'status' => 'status',
    ),
    'info' => array(
      'call_channel' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'call_network' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'caller_name' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'caller_number' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'dest_name' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'dest_number' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'direction' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'duration' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'start_time' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'status' => array(
        'sortable' => 1,
        'separator' => '',
      ),
    ),
    'default' => '-1',
  ));
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->override_option('path', 'admin/voip/call/log');
  $handler->override_option('menu', array(
    'type' => 'normal',
    'title' => 'VoIP Call Log',
    'description' => '',
    'weight' => '0',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));


  $views[$view->name] = $view;

  return $views;
}
