<?php
// $Id: charts.views.inc,v 1.3 2009/05/12 20:05:50 brmassa Exp $
/**
 * @author Bruno Massa http://drupal.org/user/67164
 * @file
 * Views integration with Charts.
 */

/**
* Implementation of hook_views_plugins().
*
* Define charts style for Views.
*/
function charts_views_plugins() {
  // Views support is only possible if Views Calc module is enabled. It
  // is responsible for turn the Views values into a aggregates.
  if (!module_exists('views_calc')) {
    return;
  }

  return array(
    'module' => 'charts',
    'style'  => array(     // Declare the charts style plugin
      'chart' => array(
        'handler'         => 'charts_plugin_style_chart',
        'help'            => t('Displays the content in several Chart styles.'),
        'path'            => drupal_get_path('module', 'charts') .'/views',
        'parent'          => 'parent',
        'title'           => t('Chart'),
        'type'            => 'normal',
        'uses fields'     => TRUE,
        'uses options'    => TRUE,
        'uses row plugin' => FALSE,
      ),
    )
  );
}
