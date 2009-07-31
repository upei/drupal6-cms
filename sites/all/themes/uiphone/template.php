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
  // add title to breadcrumb
  $icon = uiphone_get_menu_icon($_REQUEST['q']);
  $vars['breadcrumb'] .= '<span class="nav-title"><span class="nav-title-icon">'.$icon.'</span><span class="nav-title-text">'.$vars['title'].'</span></span>';
}

function uiphone_get_menu_icon($path) {
  // get menu icon for path
  $result = db_query(db_rewrite_sql("SELECT nid FROM {node} WHERE title='%s'"), $path);
  if ($node = db_fetch_object($result)) {
    $node = node_load($node->nid);
    $img = '<img src="' . url($node->field_icon[0]['filepath']) . '" width="32" height="32" alt="'. $node->title . '"/>';
    // $img = l($img, $path, array('html' => TRUE));
    return $img;
  }
  else {
    return '';
  }
}

function phptemplate_breadcrumb($breadcrumb) {
  static $icons = NULL;
  $dirty = FALSE;
  $icons = cache_get('uiphone_breadcrumb_icons');
  if ($icons) {
    $icons = $icons->data;
  }
  else {
    $icons = array();
  }
  
  // deal with home icon
  if ($breadcrumb && !isset($icons['/'])) {
    $icons['/'] = array(
      'path' => '/',
      'icon' => '<img src="' . url(path_to_theme() . '/images/nav/home.png') . '" width="41" height="32" />',
    );
  }
  // add home icon
  $result = '<span class="nav-home">' . l($icons['/']['icon'], '', array('html' => TRUE)) . '</span>';
  unset($breadcrumb[0]);
  // separator
  $sep = '<img src="'.url(path_to_theme() . '/images/nav/sep.png').'" width="10" height="32" alt="separator" />';
  $result .= '<span class="nav-item">';
  foreach ($breadcrumb as $value) {
    // wrap a span around the breadcrumb
    // grep the icon paths from breadcrumb
    if (!isset($icons[$value])) {
      $dirty = TRUE;
      $matches = NULL;
      if (preg_match('#<a href="([^"]+)"#', $value, $matches)) {
        // rip the path out if it is local
        $path = $matches[1];
        if (!preg_match('#^http://#', $path)) {
          $path = substr($path, strlen(base_path()));
          $path = $path ? $path : '/';
        }
        $icons[$value] = array(
          'path' => $path,
          'icon' => uiphone_get_menu_icon($path),
        );
      }
    }
    // embed the path
    $result .= $icons[$value]['icon'] . $value . $sep ;
  }
  $result .= '</span>';
  // add the help icon
  // $result .= '<span class="nav-help">'
  //     . l('<img src="'.url(path_to_theme() . '/images/nav/help.png').'" width="32" height="32" alt="Help" />', 'help', array('html'=>TRUE))
  //     . '</span>';
  // save cache
  if ($dirty) {
    cache_set('uiphone_breadcrumb_icons', $icons);
  }
  return $result;
}
