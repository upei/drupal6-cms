<?php

require_once('views_plugin_style_ajax.inc');

class views_plugin_style_ajax_json extends views_plugin_style_ajax {

  function options(&$options) {
    parent::options($options);
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
  }

  function render() {
    $output = parent::render();
    drupal_set_header('Content-type: text/javascript; charset=utf-8');
    return drupal_to_js($output);
  }
}

