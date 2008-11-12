<?php
// $Id: fckeditor.user.inc,v 1.1.2.12 2008/10/15 12:04:48 wwalc Exp $
/**
 * FCKeditor - The text editor for Internet - http://www.fckeditor.net
 * Copyright (C) 2003-2008 Frederico Caldeira Knabben
 *
 * == BEGIN LICENSE ==
 *
 * Licensed under the terms of any of the following licenses at your
 * choice:
 *
 *  - GNU General Public License Version 2 or later (the "GPL")
 *    http://www.gnu.org/licenses/gpl.html
 *
 *  - GNU Lesser General Public License Version 2.1 or later (the "LGPL")
 *    http://www.gnu.org/licenses/lgpl.html
 *
 *  - Mozilla Public License Version 1.1 or later (the "MPL")
 *    http://www.mozilla.org/MPL/MPL-1.1.html
 *
 * == END LICENSE ==
 *
 * @file
 * FCKeditor Module for Drupal 6.x
 *
 * This module allows Drupal to replace textarea fields with FCKeditor.
 *
 * This HTML text editor brings to the web many of the powerful functionalities
 * of known desktop editors like Word. It's really  lightweight and doesn't
 * require any kind of installation on the client computer.
 */

function fckeditor_user_delegate($type, $edit, &$user, $category = NULL) {
  if ($type == 'form' && $category == 'account' && user_access('access fckeditor')) {
    module_load_include('lib.inc', 'fckeditor');

    $profile = fckeditor_user_get_profile($user);
    $toolbar_options = fckeditor_load_toolbar_options();
    $skin_options = fckeditor_load_skin_options();
    $lang_options = fckeditor_load_lang_options();

    // because the settings are saved as strings we need to test for the string 'true'
    if ($profile->settings['allow_user_conf'] == 't') {
      $form['fckeditor'] = array(
        '#type' => 'fieldset',
        '#title' => t('Rich text editor settings'),
        '#weight' => 10,
        '#collapsible' => TRUE,
        '#collapsed' => TRUE
      );

      $form['fckeditor']['fckeditor_default'] = array(
        '#type' => 'radios',
        '#title' => t('Default state'),
        '#default_value' => isset($user->fckeditor_default) ? $user->fckeditor_default : (isset($profile->settings['default']) ? $profile->settings['default'] : 'f'),
        '#options' => array(
          't' => t('Enabled'),
          'f' => t('Disabled')
        ),
        '#description' => t('Should rich-text editing be enabled or disabled by default in textarea fields? If disabled, rich text editor may still be enabled using toggle or popup window.'),
      );

      $form['fckeditor']['fckeditor_show_toggle'] = array(
        '#type' => 'radios',
        '#title' => t('Show disable/enable rich text editor toggle'),
        '#default_value' => isset($user->fckeditor_show_toggle) ? $user->fckeditor_show_toggle : (isset($profile->settings['show_toggle']) ? $profile->settings['show_toggle'] : 't'),
        '#options' => array(
          't' => t('Yes'),
          'f' => t('No')
        ),
        '#description' => t('Whether or not to show the disable/enable rich text editor toggle below the textarea. Works only if FCKeditor is not running a popup window (see below).'),
      );

      if (user_access('administer fckeditor')) {
        $form['fckeditor']['fckeditor_show_fieldnamehint'] = array(
          '#type' => 'radios',
          '#title' => t('Show field name hint below each rich text editor'),
          '#default_value' => !empty($user->fckeditor_show_fieldnamehint) ? $user->fckeditor_show_fieldnamehint : 't',
          '#options' => array(
            't' => t('Yes'),
            'f' => t('No')
          ),
        );
      }

      $form['fckeditor']['fckeditor_popup'] = array(
        '#type' => 'radios',
        '#title' => t('Use FCKeditor in a popup window'),
        '#default_value' => isset($user->fckeditor_popup) ? $user->fckeditor_popup : (isset($profile->settings['popup']) ? $profile->settings['popup'] : 'f'),
        '#options' => array(
          'f' => t('No'),
          't' => t('Yes')
        ),
        '#description' => t('If this option is enabled a link to a popup window will be used instead of a textarea replace.'),
      );

      $form['fckeditor']['fckeditor_skin'] = array(
        '#type' => 'select',
        '#title' => t('Skin'),
        '#default_value' => isset($user->fckeditor_skin) ? $user->fckeditor_skin : (isset($profile->settings['skin']) ? $profile->settings['skin'] : 'default'),
        '#options' => $skin_options,
        '#description' => t('Choose a FCKeditor skin.'),
      );

      $form['fckeditor']['fckeditor_toolbar'] = array(
        '#type' => 'select',
        '#title' => t('Toolbar'),
        '#default_value' => isset($user->fckeditor_toolbar) ? $user->fckeditor_toolbar : (isset($profile->settings['toolbar']) ? $profile->settings['toolbar'] : 'default'),
        '#options' => $toolbar_options,
        '#description' => t('Choose a FCKeditor toolbar set.'),
      );

      $form['fckeditor']['fckeditor_expand'] = array(
        '#type' => 'select',
        '#title' => t('Start the toolbar expanded'),
        '#default_value' => isset($user->fckeditor_expand) ? $user->fckeditor_expand : (isset($profile->settings['expand']) ? $profile->settings['expand'] : 't'),
        '#options' => array(
          't' => t('Expanded'),
          'f' => t('Collapsed')
        ),
        '#description' => t('The toolbar start expanded or collapsed.'),
      );

      $form['fckeditor']['fckeditor_width'] = array(
        '#type' => 'textfield',
        '#title' => t('Width'),
        '#default_value' => isset($user->fckeditor_width) ? $user->fckeditor_width : (isset($profile->settings['width']) ? $profile->settings['width'] : '100%'),
        '#description' => t('Width in pixels or percent. Example: 400 or 100%.'),
        '#size' => 40,
        '#maxlength' => 128,
      );

      $form['fckeditor']['fckeditor_lang'] = array(
        '#type' => 'select',
        '#title' => t('Language'),
        '#default_value' => isset($user->fckeditor_lang) ? $user->fckeditor_lang : (isset($profile->settings['lang']) ? $profile->settings['lang'] : 'en'),
        '#options' => $lang_options,
        '#description' => t('The language for the FCKeditor interface.')
      );

      $form['fckeditor']['fckeditor_auto_lang'] = array(
        '#type' => 'radios',
        '#title' => t('Auto-detect language'),
        '#default_value' => isset($user->fckeditor_auto_lang) ? $user->fckeditor_auto_lang : (isset($profile->settings['auto_lang']) ? $profile->settings['auto_lang'] : 't'),
        '#options' => array(
          't' => t('Yes'),
          'f' => t('No')
        ),
        '#description' => t('Use auto detect user language feature.')
      );

      return array('fckeditor' => $form);
    }
  }

  if ($type == 'validate') {
    if (isset($edit['fckeditor_default'], $edit['fckeditor_popup']) && $edit['fckeditor_default'] == 't' && $edit['fckeditor_popup'] == 't') {
      form_set_error('fckeditor_popup', t('If FCKeditor is enabled by default, popup window must be disabled.'));
    }

    if (isset($edit['fckeditor_show_toggle'], $edit['fckeditor_popup']) && $edit['fckeditor_show_toggle'] == 't' && $edit['fckeditor_popup'] == 't') {
      form_set_error('fckeditor_popup', t('If toggle is enabled, popup window must be disabled.'));
    }

    if (isset($edit['fckeditor_width']) && !preg_match('/^\d+%?$/', $edit['fckeditor_width'])) {
      form_set_error('fckeditor_width', t('Enter valid width. Example: 400 or 100%.'));
    }
  }

  return NULL;
}