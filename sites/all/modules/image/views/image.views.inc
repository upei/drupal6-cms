<?php
// $Id: image.views.inc,v 1.1 2009/01/13 10:10:41 drewish Exp $

/**
 * @file
 * Views integration with Image module.
 */

/**
 * Implementation of hook_views_data().
 */
function image_views_data() {
  $data = array();

  // Add {image} table data, using {node} and {files} as possible base tables.
  $data['image']['table']['group'] = t('Image');
  $data['image']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid',
      'field' => 'nid',
    ),
    'files' => array(
      'left_field' => 'fid',
      'field' => 'fid',
    ),
  );

  $data['image']['image_size'] = array(
    'title' => t('Image size'),
    'help' => t('Image size'),
    'field' => array(
      'handler' => 'image_views_handler_field_image_size',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'image_views_handler_argument_image_size',
      'parent' => 'views_handler_argument_string',
    ),
    'filter' => array(
      'handler' => 'image_views_handler_filter_image_size',
    ),
  );

  $data['image']['nid'] = array(
    'title' => t('Image'),
    'help' => t('The rendered image of an Image node.'),
    'field' => array(
      'handler' => 'image_views_handler_field_image',
    ),
  );

  return $data;
}

/**
 * Implementation of hook_views_data_alter().
 */
function image_views_data_alter(&$data) {
  $data['node']['image_files'] = array(
    'group' => t('Image'),
    'relationship' => array(
      'title' => t('Files'),
      'label' => t('Image files'),
      'help' => t('Add a relationship to gain access to files data for files uploaded by image.module. Note that this relationship will cause duplicate nodes by the number of image sizes for the given node.'),
      'relationship table' => 'image',
      'relationship field' => 'fid',
      'base' => 'files',
      'field' => 'fid',
      'handler' => 'image_views_handler_relationship',
    ),
  );
  
  $data['files']['image_node'] = array(
    'group' => t('Image'),
    'relationship' => array(
      'title' => t('Node'),
      'label' => t('Image node'),
      'help' => t('Add a relationship to gain access to the node of the image files uploaded by image.module.'),
      'relationship table' => 'image',
      'relationship field' => 'nid',
      'base' => 'node',
      'field' => 'nid',
      'handler' => 'image_views_handler_relationship',
    ),
  );
}

/**
 * Implementation of hook_views_handlers().
 */
function image_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'image') .'/views',
    ),
    'handlers' => array(
      'image_views_handler_field_image' => array(
        'parent' => 'views_handler_field',
      ),
      'image_views_handler_field_image_size' => array(
        'parent' => 'views_handler_field',
      ),
      'image_views_handler_argument_image_size' => array(
        'parent' => 'views_handler_argument_string',
      ),
      'image_views_handler_filter_image_size' => array(
        'parent' => 'views_handler_filter_in_operator',
      ),
      'image_views_handler_relationship' => array(
        'parent' => 'views_handler_relationship',
      ),
    ),
  );
}

/**
 * Implementation of hook_views_plugins().
 */
function image_views_plugins() {
  return array(
    'module' => 'views', // This just tells our themes are elsewhere.
    'argument validator' => array(
      'image_size' => array(
        'title' => t('Image size'),
        'handler' => 'image_views_plugin_argument_validate_image_size',
        'path' => drupal_get_path('module', 'image') . '/views',
      ),
    ),
  );
}

