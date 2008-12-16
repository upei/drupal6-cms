<?php
// $Id: views_bonus_plugin_style_export.inc,v 1.3 2008/12/06 17:10:47 neclimdul Exp $
/**
 * @file
 * Plugin include file for export style plugin.
 */

/**
 * Generalized style plugin for export plugins.
 */
class views_bonus_plugin_style_export extends views_plugin_style {
  function init(&$view, &$display, $options = NULL) {
    parent::init(&$view, &$display, $options = NULL);
  }

  function attach_to($display_id, $path, $title) {
    $url_options = array('html' => true);
    $input = $this->view->get_exposed_input();
    if ($input) {
      $url_options['query'] = $input;
    }
    $image = theme('image', $this->feed_image);
    $this->view->feed_icon .= l($image, $path, $url_options);
  }
}
