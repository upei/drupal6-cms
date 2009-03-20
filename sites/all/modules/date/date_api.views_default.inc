<?php
//$Id: date_api.views_default.inc,v 1.1.2.1 2008/06/13 13:50:04 karens Exp $
function date_api_views_default_views() {
 
$view = new view;
$view->name = 'date_browser';
$view->description = 'Browse through nodes by year, month, day, or week. Date browser attachment adds back/next navigation to the top of the page.';
$view->tag = 'Date';
$view->view_php = '';
$view->base_table = 'node';
$view->is_cacheable = '0';
$view->api_version = 2;
$view->disabled = TRUE; /* Edit this to true to make a default view disabled initially */
$handler = $view->new_display('default', 'Defaults', 'default');
$handler->override_option('fields', array(
  'title' => array(
    'id' => 'title',
    'table' => 'node',
    'field' => 'title',
    'label' => 'Title',
    'relationship' => 'none',
    'link_to_node' => 1,
  ),
  'changed' => array(
    'label' => 'Updated date',
    'date_format' => 'small',
    'custom_date_format' => '',
    'exclude' => 0,
    'id' => 'changed',
    'table' => 'node',
    'field' => 'changed',
    'relationship' => 'none',
  ),
));
$handler->override_option('arguments', array(
  'date_argument' => array(
    'default_action' => 'default',
    'style_plugin' => 'default_summary',
    'style_options' => array(),
    'wildcard' => 'all',
    'wildcard_substitution' => 'All',
    'title' => '',
    'default_argument_type' => 'date',
    'default_argument' => '',
    'validate_type' => 'none',
    'validate_fail' => 'not found',
    'date_fields' => array(
      'node.changed' => 'node.changed',
    ),
    'date_method' => 'OR',
    'granularity' => 'month',
    'id' => 'date_argument',
    'table' => 'node',
    'field' => 'date_argument',
    'relationship' => 'none',
    'default_argument_user' => 0,
    'default_argument_fixed' => '',
    'default_argument_php' => '',
    'validate_argument_node_type' => array(
      'page' => 0,
      'story' => 0,
    ),
    'validate_argument_node_access' => 0,
    'validate_argument_nid_type' => 'nid',
    'validate_argument_vocabulary' => array(
    ),
    'validate_argument_type' => 'tid',
    'validate_argument_php' => '',
  ),
));
$handler->override_option('filters', array(
  'type' => array(
    'id' => 'type',
    'table' => 'node',
    'field' => 'type',
    'operator' => 'in',
    'value' => array(
      'test' => 'test',
    ),
    'group' => 0,
    'exposed' => FALSE,
    'expose' => array(
      'operator' => FALSE,
      'label' => '',
    ),
    'relationship' => 'none',
  ),
));
$handler->override_option('access', array(
  'type' => 'none',
  'role' => array(),
  'perm' => '',
));
$handler->override_option('items_per_page', 0);
$handler->override_option('use_pager', '1');
$handler = $view->new_display('page', 'Page', 'page');
$handler->override_option('use_pager', '1');
$handler->override_option('row_plugin', 'node');
$handler->override_option('row_options', array(
  'teaser' => 1,
  'links' => 1,
));
$handler->override_option('path', 'date_browser');
$handler->override_option('menu', array(
  'type' => 'none',
  'title' => '',
  'weight' => 0,
));
$handler->override_option('tab_options', array(
  'type' => 'none',
  'title' => '',
  'weight' => 0,
));
$handler = $view->new_display('date_nav', 'Date browser', 'date_nav_1');
$handler->override_option('style_plugin', 'date_nav');
$handler->override_option('displays', array(
  'page' => 'page',
  'default' => 0,
));

  $views[$view->name] = $view;
  return $views;
}