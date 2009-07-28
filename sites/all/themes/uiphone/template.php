<?php

function phptemplate_preprocess(&$vars) {
  global $user;
  // define some useful variables
  $vars['is_admin'] = in_array('admin', $user->roles);
  $vars['logged_in'] = ($user->uid > 0) ? TRUE : FALSE;
}

function phptemplate_preprocess_page(&$vars) {
  // get rid of all module css unless it's admin menu
  $css =& $vars['css'];
  foreach ($css['all']['module'] as $key => $value) {
    if (!preg_match('/admin_menu/', $key)) {
      unset($css['all']['module'][$key]);
    }
  }
  // get rid of all print css
  unset($css['print']);
  // reset the styles
  $vars['styles'] = drupal_get_css($css);
}
