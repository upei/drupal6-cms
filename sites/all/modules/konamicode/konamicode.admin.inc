<?php
// $Id: konamicode.admin.inc,v 1.1 2009/05/11 14:25:32 robloach Exp $

/**
 * @file
 * Provides the administration settings for the Konami Code module.
 */

/**
 * Menu callback; The administration settings for the Konami Code.
 */
function konamicode_admin_settings() {
  $form['konamicode_destination'] = array(
    '#type' => 'textfield',
    '#title' => t('Destination'),
    '#description' => t('When people enter the <a href="@konamicode">Konami Code</a>, redirect them to the given URL. This can either be an internal or external path.', array('@konamicode' => 'http://en.wikipedia.org/wiki/Konami_code')),
    '#default_value' => variable_get('konamicode_destination', ''),
  );
  return system_settings_form($form);
}
