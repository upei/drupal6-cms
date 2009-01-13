<?php
// $Id: print_mail.admin.inc,v 1.1.2.2 2008/08/21 22:03:40 jcnventura Exp $

/**
 * @file
 * Contains the administrative functions of the send by e-mail module.
 *
 * This file is included by the send by e-mail module, and includes the
 * settings form.
 */

/**
 * Menu callback for the send by e-mail module settings form.
 *
 * @ingroup forms
 */
function print_mail_settings() {
  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Send by e-mail options'),
  );

  $form['settings']['print_mail_link_pos'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Send by e-mail link'),
    '#default_value' => variable_get('print_mail_link_pos', array(PRINT_MAIL_LINK_POS_DEFAULT => PRINT_MAIL_LINK_POS_DEFAULT)),
    '#options' => array('link' => t('Links area'), 'corner' => t('Content corner')),
    '#description' => t('Choose the location of the link(s) to the send by e-mail page. The Links area is usually below the node content, whereas the Content corner is placed in the upper-right corner of the node content. Unselect all options to disable the link. Even if the link is disabled, you can still send a node by e-mail by going to !path/nid where nid is the numeric id of the node.', array('!path' => PRINTMAIL_PATH)),
  );

  $form['settings']['adv_link'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced link options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['settings']['adv_link']['print_mail_show_link'] = array(
    '#type' => 'radios',
    '#title' => t('Link style'),
    '#default_value' => variable_get('print_mail_show_link', PRINT_MAIL_SHOW_LINK_DEFAULT),
    '#options' => array(1 => t('Text only'), 2 => t('Icon only'), 3 => t('Icon and Text')),
    '#description' => t('Select the visual style of the link.'),
  );

  $form['settings']['adv_link']['print_mail_node_link_visibility'] = array(
    '#type' => 'radios',
    '#title' => t('Link visibility'),
    '#default_value' => variable_get('print_mail_node_link_visibility', PRINT_MAIL_NODE_LINK_VISIBILITY_DEFAULT),
    '#options' => array(t('Show on every page except the listed pages.'), t('Show on only the listed pages.')),
  );

  $form['settings']['adv_link']['print_mail_node_link_pages'] = array(
    '#type' => 'textarea',
    '#default_value' => variable_get('print_mail_node_link_pages', PRINT_MAIL_NODE_LINK_PAGES_DEFAULT),
    '#rows' => 3,
    '#description' => t("Enter one page per line as Drupal paths. The '*' character is a wildcard. Example paths are %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page.", array('%blog' => 'blog', '%blog-wildcard' => 'blog/*', '%front' => '<front>')),
  );

  $form['settings']['adv_link']['print_mail_link_class'] = array(
    '#type' => 'textfield',
    '#title' => t('Link class'),
    '#default_value' => variable_get('print_mail_link_class', PRINT_MAIL_LINK_CLASS_DEFAULT),
    '#size' => 60,
    '#maxlength' => 250,
    '#description' => t('This can be used by themers to change the link style or by jQuery modules to open in a new window (e.g. greybox or thickbox). Multiple classes can be specified, separated by spaces.'),
  );

  $form['settings']['adv_link']['print_mail_sys_link_visibility'] = array(
    '#type' => 'radios',
    '#title' => t('Show link in system (non-content) pages'),
    '#default_value' => variable_get('print_mail_sys_link_visibility', PRINT_MAIL_SYS_LINK_VISIBILITY_DEFAULT),
    '#options' => array(t('Show on every page except the listed pages.'), t('Show on only the listed pages.')),
  );

  $form['settings']['adv_link']['print_mail_sys_link_pages'] = array(
    '#type' => 'textarea',
    '#default_value' => variable_get('print_mail_sys_link_pages', PRINT_MAIL_SYS_LINK_PAGES_DEFAULT),
    '#rows' => 3,
    '#description' => t('Setting this option will add a send by-email link on pages created by Drupal or the enabled modules.') .'<br />'.
                      t("Enter one page per line as Drupal paths. The '*' character is a wildcard. Example paths are %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page.", array('%blog' => 'blog', '%blog-wildcard' => 'blog/*', '%front' => '<front>')),
  );

  $form['settings']['print_mail_book_link'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show link in book nodes'),
    '#default_value' => variable_get('print_mail_book_link', PRINT_MAIL_BOOK_LINK_DEFAULT),
    '#description' => t('Activate this to add a send by e-mail link in book nodes. Requires the (core) book module.'),
  );

  $form['settings']['print_mail_hourly_threshold'] = array(
    '#type' => 'select',
    '#title' => t('Hourly threshold'),
    '#default_value' => variable_get('print_mail_hourly_threshold', PRINT_MAIL_HOURLY_THRESHOLD),
    '#options' => drupal_map_assoc(array(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 30, 40, 50)),
    '#description' => t('The maximum number of e-mails a user can send per hour.'),
  );

  $form['settings']['print_mail_teaser_default'] = array(
    '#type' => 'checkbox',
    '#title' => t('Send only the teaser'),
    '#default_value' => variable_get('print_mail_teaser_default', PRINT_MAIL_TEASER_DEFAULT_DEFAULT),
    '#description' => t("If selected, the default choice will be to send only the node's teaser instead of the full content."),
  );

  $form['settings']['print_mail_teaser_choice'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable teaser/full mode choice'),
    '#default_value' => variable_get('print_mail_teaser_choice', PRINT_MAIL_TEASER_CHOICE_DEFAULT),
    '#description' => t('If checked, the user will be able to choose between sending the full content or only the teaser at send time.'),
  );

  return system_settings_form($form);
}
