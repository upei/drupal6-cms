<?php
// $Id: image_views_handler_argument_image_size.inc,v 1.1 2009/01/13 10:10:41 drewish Exp $

/**
 * @file
 * Views argument handler for Image size argument.
 */

/**
 * Argument handler for Image size. It converts given image size argument to
 * its human-readable name.
 */
class image_views_handler_argument_image_size extends views_handler_argument_string {
  /**
   * Get the human-readable label for the image size.
   */
  function title() {
    $image_sizes = image_get_sizes();
    return check_plain($image_sizes[$this->argument]['label']);
  }
}

