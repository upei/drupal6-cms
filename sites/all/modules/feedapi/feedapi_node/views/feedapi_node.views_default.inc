<?php
// $Id: feedapi_node.views_default.inc,v 1.1.2.1 2008/10/01 08:55:47 aronnovak Exp $
/**
 * @file
 * FeedAPI Node Views - Default Views
 */

/**
 * Implementation of hook_views_default_views().
 */
function feedapi_node_views_default_views() {
  // feeds overview page
  $view = new view;
  $view->name = 'feeds';
  $view->description = t('Show a listing of all feed items for a feed');
  $view->tag = t('default');
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = '0';
  $view->api_version = 2;
  $view->disabled = FALSE;
  $view->display = array();

  $display = new views_display;
  $display->id = 'default';
  $display->display_title = t('Defaults');
  $display->display_plugin = 'default';
  $display->position = '1';
  $display->display_options = array(
    'style_plugin' => 'default',
    'style_options' =>
    array(
    ),
    'row_plugin' => 'node',
    'row_options' =>
    array(
      'teaser' => 1,
      'links' => 1,
    ),
    'relationships' =>
    array(
    ),
    'fields' =>
    array(
    ),
    'sorts' =>
    array(
      'created' =>
      array(
        'order' => 'DESC',
        'granularity' => 'second',
        'id' => 'created',
        'table' => 'node',
        'field' => 'created',
        'sortorder' => 'desc',
        'relationship' => 'none',
      ),
    ),
    'arguments' =>
    array(
      'feed_nid' => array(
        'default_action' => 'ignore',
        'style_plugin' => 'default_summary',
        'style_options' => array(),
        'wildcard' => 'all',
        'wildcard_substitution' => 'All',
        'title' => '%1',
        'default_argument_type' => 'fixed',
        'default_argument' => '',
        'validate_type' => 'node',
        'validate_fail' => 'not found',
        'break_phrase' => 0,
        'not' => 0,
        'id' => 'feed_nid',
        'table' => 'feedapi_node_item_feed',
        'field' => 'feed_nid',
        'relationship' => 'none',
        'default_options_div_prefix' => '',
        'default_argument_user' => 0,
        'default_argument_fixed' => '',
        'default_argument_php' => '',
        'validate_argument_node_type' => array(
          'blog' => 0,
          'bookmark' => 0,
          'feedapi_node' => 0,
          'feed_item' => 0,
          'page' => 0,
          'story' => 0,
        ),
        'validate_argument_node_access' => 1,
        'validate_argument_nid_type' => 'nid',
        'validate_argument_vocabulary' => array(
          '1' => 0,
        ),
        'validate_argument_type' => 'tid',
        'validate_argument_php' => '',
        ),
    ),
    'filters' =>
    array(
      'status' =>
      array(
        'id' => 'status',
        'table' => 'node',
        'field' => 'status',
        'operator' => '=',
        'value' => '1',
        'group' => 0,
        'exposed' => FALSE,
        'expose' =>
        array(
          'operator' => FALSE,
          'label' => '',
        ),
      ),
    ),
    'items_per_page' => 10,
    'use_pager' => '1',
    'pager_element' => 0,
    'title' => t('Feed items'),
    'header' => '',
    'header_format' => '1',
    'footer' => '',
    'footer_format' => '1',
    'empty' => t('No feed items found.'),
    'empty_format' => '1',
  );
  $view->display['default'] = $display;

  $display = new views_display;
  $display->id = 'page';
  $display->display_title = t('Page');
  $display->display_plugin = 'page';
  $display->position = '2';
  $display->display_options = array(
    'defaults' =>
    array(
      'access' => TRUE,
      'title' => TRUE,
      'header' => TRUE,
      'header_format' => TRUE,
      'header_empty' => TRUE,
      'footer' => TRUE,
      'footer_format' => TRUE,
      'footer_empty' => TRUE,
      'empty' => TRUE,
      'empty_format' => TRUE,
      'items_per_page' => TRUE,
      'offset' => TRUE,
      'use_pager' => TRUE,
      'pager_element' => TRUE,
      'link_display' => TRUE,
      'php_arg_code' => TRUE,
      'exposed_options' => TRUE,
      'style_plugin' => TRUE,
      'style_options' => TRUE,
      'row_plugin' => TRUE,
      'row_options' => TRUE,
      'relationships' => TRUE,
      'fields' => TRUE,
      'sorts' => TRUE,
      'arguments' => TRUE,
      'filters' => TRUE,
      'use_ajax' => TRUE,
      'distinct' => TRUE,
    ),
    'relationships' =>
    array(
    ),
    'fields' =>
    array(
    ),
    'sorts' =>
    array(
    ),
    'arguments' =>
    array(
    ),
    'filters' =>
    array(
    ),
    'path' => 'feed-item',
  );
  $view->display['page'] = $display;

  $views[$view->name] = $view;
  return $views;
}


