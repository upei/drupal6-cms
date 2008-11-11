<?php
// $Id: ldapdata.theme.inc,v 1.1.2.6 2008/10/05 18:46:47 miglius Exp $

/**
 * @file
 * Themes for ldapdata module.
 */

//////////////////////////////////////////////////////////////////////////////
// Theme callbacks

/**
 * Theme function for the admin edit form.
 */
function theme_ldapdata_admin_edit($form) {
  $output = '';
  $rows = array();
  foreach (element_children($form) as $element) {
    if ($element == "ldap_editable_attributes" ) {
      foreach (element_children($form['ldap_editable_attributes']['ldap_attr_table']) as $key) {
        $row = array();
        $row[] = drupal_render($form['ldap_editable_attributes']['ldap_attr_table'][$key]);
        $row[] = drupal_render($form['ldap_editable_attributes']['ro_status'][$key]);
        $row[] = drupal_render($form['ldap_editable_attributes']['rw_status'][$key]);
        $rows[] = $row;
      }
      $form['ldap_editable_attributes']['#children'] = drupal_render($form['ldap_editable_attributes']['ldap_message']);
      $form['ldap_editable_attributes']['#children'] .= theme('table', $form['ldap_editable_attributes']['header']['#value'], $rows);
      $output .= drupal_render($form['ldap_editable_attributes']);
    }
    else {
      $output .= drupal_render($form[$element]);
    }
  }

  $output .= drupal_render($form);

  return $output;
}

/**
 * Theme functon for the LDAP attribute.
 */
function theme_ldapdata_ldap_attribute($value, $type) {
  switch ($type) {
    case 'url':
      $ret = strpos($value, '://') ? $value : "http://$value";
      $ret = "<a href=\"$ret\">$ret</a>";
      break;
    case 'txt':
    default:
      $ret = $value;
      break;
  }

  return $ret;
}

