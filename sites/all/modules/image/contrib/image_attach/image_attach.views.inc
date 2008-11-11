<?php
// $Id: image_attach.views.inc,v 1.1 2008/06/16 18:06:01 drewish Exp $

/**
 * Implementation of hook_views_tables().
 */
function image_attach_views_tables() {
  $tables['image_attach'] = array(
    'name' => 'image_attach',
    'join' => array(
      'left' => array(
        'table' => 'node',
        'field' => 'nid'
      ),
      'right' => array(
        'field' => 'nid'
      ),
    ),
    'fields' => array(
      'iid' => array(
        'name' => t('Image Attach: Display Image'),
        'handler' => array(
          'image_attach_views_handler_field_iid' => t('Image'),
          'image_attach_views_handler_field_iid_link_node' => t('Image with link to attaching node'),
          'image_attach_views_handler_field_iid_link_image' => t('Image with link to attached image'),
        ),
        'option' => array(
          '#type' => 'select',
          '#options' => 'image_views_handler_filter_image_size',
        ),
        'sortable' => FALSE,
      ),
    ),
    'filters' => array(
      'iid' => array(
        'name' => t('Image Attach: Attached image'),
        'operator' => array('=' => t('Exists')),
        'list' => 'views_handler_operator_yesno',
        'list-type' => 'select',
        'handler' => 'image_attach_views_handler_filter_iid_exist',
        'help' => t('Filter by whether or not the node has an attached image.'),
      ),
    ),
  );

  return $tables;
}

/**
 * Views handler for displaying the image.
 */
function image_attach_views_handler_field_iid($field_info, $field_data, $value, $data) {
  if ($value) {
    $image = node_load($value);
    return image_display($image, $field_data['options']);
  }
}

/**
 * Views handler for displaying the image in a link to the image node that attaches the image.
 */
function image_attach_views_handler_field_iid_link_node($field_info, $field_data, $value, $data) {
  if ($value) {
    $image = node_load($value);
    return l(image_display($image, $field_data['options']), 'node/'. $data->nid, array(), NULL, NULL, FALSE, TRUE);
  }
}

/**
 * Views handler for displaying the image in a link to the attached image.
 */
function image_attach_views_handler_field_iid_link_image($field_info, $field_data, $value, $data) {
  if ($value) {
    $image = node_load($value);
    return l(image_display($image, $field_data['options']), 'node/'. $value, array(), NULL, NULL, FALSE, TRUE);
  }
}

/**
 * Views handler for filtering whether or not the node has an attached image.
 */
function image_attach_views_handler_filter_iid_exist($op, $filter, $filterdata, &$query) {
  switch ($op) {
    case 'handler':
      $query->ensure_table('image_attach');
      if ($filter['value']) {
        $query->add_where('image_attach.iid');
      }
      else {
        $query->add_where('ISNULL(image_attach.iid)');
      }
      break;
  }
}