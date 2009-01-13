<?php

class views_plugin_display_ajax_page extends views_plugin_display_page {

  function uses_breadcrumb() { return FALSE; }
  function get_style_type() { return 'ajax'; }

  /**
   * Feeds do not go through the normal page theming mechanism. Instead, they
   * go through their own little theme function and then return NULL so that
   * Drupal believes that the page has already rendered itself...which it has.
   */
  function execute() {
    $output = $this->view->render();
    if (empty($output)) {
      drupal_set_header('HTTP/1.1 404 Not Found');
    }
    print $output;
  }

  function preview() {
    return '<pre>' . check_plain($this->view->render()) . '</pre>';
  }

  /**
   * Instead of going through the standard views_view.tpl.php, delegate this
   * to the style handler.
   */
  function render() {
    return $this->view->style_plugin->render($this->view->result);
  }

}
