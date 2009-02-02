<?php
// $Id: image_views_handler_field_image_size.inc,v 1.1 2009/01/13 10:10:41 drewish Exp $

/**
 * @file
 * Views handler for Image size field.
 */

/**
 * Renders the human-readable equivelant of a given Image size
 * or an empty string in case of an invalid image size.
 */
class image_views_handler_field_image_size extends views_handler_field {
  var $image_sizes = array();

  function init(&$view, $options) {
    parent::init($view, $options);
    
    $this->image_sizes = image_get_sizes();
  }

  function render($values) {
    $image_size = $values->{$this->field_alias};

    if (!empty($image_size) && isset($this->image_sizes[$image_size])) {
      return check_plain($this->image_sizes[$image_size]['label']);
    }

    return '';
  }
}

