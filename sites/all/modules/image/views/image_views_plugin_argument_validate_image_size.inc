<?php
// $Id: image_views_plugin_argument_validate_image_size.inc,v 1.1 2009/01/13 10:10:41 drewish Exp $

/**
 * @file
 * Views validation plugin for Image size argument.
 */

/**
 * Defines a new validator, Image size.
 * Validates passed image size argument and can restrict which image sizes
 * can be passed.
 */
class image_views_plugin_argument_validate_image_size extends views_plugin_argument_validate {
  var $image_sizes = array();

  function init(&$view, &$argument, $id = NULL) {
    parent::init($view, $argument, $id);
    $this->image_sizes = image_get_sizes();
  }

  function validate_form(&$form, &$form_state) {
    $image_size_options = array();
    foreach ($this->image_sizes as $key => $size) {
      $image_size_options[$key] = $size['label'];
    }

    $form['image_size'] = array(
      '#title' => t('Image sizes'),
      '#type' => 'select',
      '#required' => TRUE,
      '#multiple' => TRUE,
      '#options' => $image_size_options,
      '#default_value' => $this->get_argument(),
      '#description' => t('Which image sizes are allowed to be passed through this argument.'),
      '#process' => array('views_process_dependency'),
      '#dependency' => array('edit-options-validate-type' => array($this->id)),
    );
  }

  function get_argument() {
    return isset($this->argument->options['image_size']) ? $this->argument->options['image_size'] : array_keys($this->image_sizes);
  }
  
  function validate_argument($argument) {
    return $this->argument->options['image_size'][$argument];
  }
}

