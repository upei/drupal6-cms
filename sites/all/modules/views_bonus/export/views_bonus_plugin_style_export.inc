<?php
// $Id: views_bonus_plugin_style_export.inc,v 1.8 2009/07/07 07:59:40 neclimdul Exp $
/**
 * @file
 * Plugin include file for export style plugin.
 */

/**
 * Generalized style plugin for export plugins.
 *
 * @ingroup views_style_plugins
 */
class views_bonus_plugin_style_export extends views_plugin_style {

  /**
   * Set options fields and default values.
   *
   * @return
   * An array of options information.
   */
  function option_definition() {
    $options = parent::option_definition();

    $options['filename'] = array(
      'default' => $this->feed_file,
      'translatable' => FALSE,
    );
    $options['attach_text'] = array(
      'default' => $this->feed_text,
      'translatable' => TRUE,
    );
    return $options;
  }

  /**
   * Options form mini callback.
   *
   * @param $form
   * Form array to add additional fields to.
   * @param $form_state
   * State of the form.
   * @return
   * None.
   */
  function options_form(&$form, &$form_state) {
    $form['attach_text'] = array(
      '#type' => 'textfield',
      '#title' => t('Attach text'),
      '#default_value' => $this->options['attach_text'],
      '#description' => t('This text is used in building the feed link. By default it is the "alt" text for the feed image.'),
    );
    $form['provide_file'] = array(
      '#type' => 'checkbox',
      '#title' => t('Provide as file'),
      '#default_value' => $this->options['provide_file'],
      '#description' => t('By deselecting this, the xml file will be provided as a feed instead of a file for download.'),
    );
    $form['filename'] = array(
      '#type' => 'textfield',
      '#title' => t('Filename'),
      '#default_value' => $this->options['filename'],
      '#description' => t('The filename that will be suggested to the browser for downloading purposes. %view will be replaced with the view name.'),
      '#process' => array('views_process_dependency'),
      '#dependency' => array(
        'edit-style-options-provide-file' => array(TRUE),
      ),
    );
  }

  /**
   * Attach this view to another display as a feed.
   *
   * Provide basic functionality for all export style views like attaching a
   * feed image link.
   */
  function attach_to($display_id, $path, $title) {
    $types = array(
     'views_bonus_plugin_style_export_csv' => 'csv',
     'views_bonus_plugin_style_export_doc' => 'doc',
     'views_bonus_plugin_style_export_txt' => 'txt',
     'views_bonus_plugin_style_export_xml' => 'xml',
    );
    $type = $types[get_class($this)];
    $theme_pattern = array(
      'views_bonus_export_feed_icon__' . $this->view->name . '__' . $display_id . '__' . $type,
      'views_bonus_export_feed_icon__' . $this->view->name . '__' . $display_id,
      'views_bonus_export_feed_icon__' . $this->view->name . '__' . $type,
      'views_bonus_export_feed_icon__' . $display_id . '__' . $type,
      'views_bonus_export_feed_icon__' . $display_id,
      'views_bonus_export_feed_icon__' . $type,
      'views_bonus_export_feed_icon',
    );
    $this->view->feed_icon .= theme($theme_pattern,
      $this->feed_image,
      $this->view->get_url(NULL, $path),
      $this->view->get_exposed_input(),
      $this->options['attach_text']
    );
  }
}
