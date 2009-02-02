<?php
// $Id: image_views_handler_filter_image_size.inc,v 1.1 2009/01/13 10:10:41 drewish Exp $

/**
 * @file
 * Views handler for Image Size filter.
 */

/**
 * Filter by Image Size.
 */
class image_views_handler_filter_image_size extends views_handler_filter_in_operator {
  function get_value_options() {
    if (!isset($this->value_options)) {
      foreach (image_get_sizes() as $key => $size) {
        $options[$key] = $size['label'];
      }
      $this->value_options = $options;
    }
  }
}

