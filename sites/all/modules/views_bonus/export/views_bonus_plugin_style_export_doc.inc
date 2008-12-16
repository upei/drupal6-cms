<?php
// $Id: views_bonus_plugin_style_export_doc.inc,v 1.3 2008/12/06 17:10:47 neclimdul Exp $
/**
 * @file
 * Plugin include file for export style plugin.
 */

/**
 * Generalized style plugin for export plugins.
 */
class views_bonus_plugin_style_export_doc extends views_bonus_plugin_style_export {
  function init(&$view, &$display, $options = NULL) {
    parent::init(&$view, &$display, $options = NULL);
    $this->feed_image = drupal_get_path('module', 'views_bonus_export') . '/images/doc.png';
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['filename'] = array(
      'default' => 'view-%view.doc',
      'translatable' => FALSE,
    );

    return $options;
  }

  function options_form(&$form, &$form_state) {
    $form['filename'] = array(
      '#type' => 'textfield',
      '#title' => t('CSV filename'),
      '#default_value' => $this->options['filename'],
      '#description' => t('The filename that will be suggested to the browser for downloading purposes. %view will be replaced with the view name.'),
      '#process' => array('views_process_dependency'),
      '#dependency' => array('edit-style-options-override' => array(FALSE)),
    );
  }
}
