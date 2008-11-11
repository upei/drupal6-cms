<?php
// $Id: ldapdata.conf.php,v 1.5.2.3 2008/09/16 15:58:58 miglius Exp $

/**
 * @file
 * ldapdata module configuration options.
 */

/**
 * WARNING: if you change this, then you WANT to set attribute mapping
 * to read-only. Otherwise, odd stuff WILL happen. Seriously!!!!!!
 */
function ldapdata_attribute_filter(&$attributes) {
  // Uncomment one of the next lines to see how the argument array looks like.
  // print_r($attributes);
  // watchdog('ldapdata', t('Debug: ') . print_r($attributes, TRUE));

  // Example:
  //   Say the attrribute emailAddress is stored like
  //   whatever#jdoe@example.com . You obviously will want
  //   Drupal to have it as jdoe@example.com, so you do this:
  //$attributes['emailAddress'][0] = preg_replace('/[^#]+#([^#])/', '$1', $attributes['emailAddress'][0]);

  return $attributes;
}

/**
 * Edit this list so that all attributes that you might wish to show
 *  are included. You may then enable/disable attributes in the Admin page.
 *
 * The left hand element indicates the LDAP attribute name.
 *
 * The 1st right hand elements in the array determine how the attribute and
 * its value are displayed. The first element may be 'text' or 'url'.
 */
function ldapdata_attributes() {
  return array(
    'givenName' => array('text', 'textfield', t('First Name'), 64, 64),
    'sn'        => array('text', 'textfield', t('Last Name'), 64, 64), // aka Surname.
    'cn'        => array('text', 'textfield', t('Common Name'), 64, 64),
    //'homePage'  => array('url', 'textfield', t('Other web pages'), 64, 64),
    'mail'      => array('text', 'textfield', t('Email'), 64, 64)
  );
}

