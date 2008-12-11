<?php
// $Id: image_attach.views.inc,v 1.3 2008/10/20 23:52:48 drewish Exp $

/**
 * Implementation of hook_views_data().
 */
function image_attach_views_data() {
  // Basic table information.
  $data = array();

  // Define the base group of this table. Fields that don't
  // have a group defined will go into this field by default.
  $data['image_attach']['table']['group']  = t('Image attach');

  // For other base tables, explain how we join
  // LEFT is the default, but let's be explicit
  $data['image_attach']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid',
      'field' => 'nid',
      'type' => 'LEFT',
    ),
  );

  // changed field
  $data['image_attach']['iid'] = array(
    'title' => t('Attached image'), // The item it appears as on the UI,
    'field' => array(
      'handler' => 'image_attach_views_handler_field_iid',
      'click sortable' => TRUE,
    ),
    'help' => t('An image attached to a node.'),
  );

  return $data;
}

