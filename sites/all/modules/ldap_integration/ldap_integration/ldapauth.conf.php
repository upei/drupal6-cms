<?php
// $Id: ldapauth.conf.php,v 1.2.4.3 2008/09/16 15:58:58 miglius Exp $

/**
 * @file
 * ldapauth module configuration options.
 */

/**
 * Transform the login name to something understood by the server.
 */
function ldapauth_transform_login_name($login_name) {
  return $login_name;
}

/**
 * Let users in (or not) according to some attributes' values
 * (and maybe some other reasons).
 */
function ldapauth_user_filter(&$attributes) {
  // Uncomment one of the next lines to see how the argument array looks like.
  // print_r($attributes);
  // watchdog('ldapauth', t('Debug: ') . print_r($attributes, TRUE));

  // Example: don't allow in users with no homeDirectory set.
  // return isset($attributes['homeDirectory'][0]) && $attributes['homedirectory'][0];

  return TRUE;
}

