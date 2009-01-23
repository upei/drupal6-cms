<?php
// $Id$

function phptemplate_body_class($sidebar_left, $sidebar_right) {
   if ($sidebar_left != '' && $sidebar_right != '') {
     $class = 'sidebars';
   }
   else {
     if ($sidebar_left != '') {
       $class = 'sidebar-left';
     }
     if ($sidebar_right != '') {
       $class = 'sidebar-right';
     }
   }
 
   if (isset($class)) {
     print ' class="'. $class .'"';
}

}
if (is_null(theme_get_setting('sunshine_style'))) {
  global $theme_key;
  // Save default theme settings
  $defaults = array(
    'sunshine_style' => 'blue',
    'sunshine_width' => 0,
	'sunshine_fixedwidth' => '850',
    'sunshine_breadcrumb' => 0,
	'sunshine_iepngfix' => 0,
    'sunshine_themelogo' => 0,
	'sunshine_fontfamily' => 0,
    'sunshine_customfont' => '',
    'sunshine_uselocalcontent' => 0,
    'sunshine_localcontentfile' => '',
    'sunshine_leftsidebarwidth' => '210',
    'sunshine_rightsidebarwidth' => '210',
    'sunshine_suckerfish' => 0,
    'sunshine_usecustomlogosize' => 0,
    'sunshine_logowidth' => '100',
    'sunshine_logoheight' => '100',
  );

  variable_set(
    str_replace('/', '_', 'theme_'. $theme_key .'_settings'),
    array_merge(theme_get_settings($theme_key), $defaults)
  );
  // Force refresh of Drupal internals
  theme_get_setting('', TRUE);
}

function get_sunshine_style() {
  $style = theme_get_setting('sunshine_style');
  if (!$style)
  {
    $style = 'blue';
  }
  if (isset($_COOKIE["sunshinestyle"])) {
    $style = $_COOKIE["sunshinestyle"];
  }
  return $style;
}

$style = get_sunshine_style();
drupal_add_css(drupal_get_path('theme', 'sunshine') . '/css/' . $style . '.css', 'theme');

if (theme_get_setting('sunshine_iepngfix')) {
   drupal_add_js(drupal_get_path('theme', 'sunshine') . '/js/jquery.pngFix.js', 'theme');
}

if (theme_get_setting('sunshine_suckerfish')) {
   drupal_add_css(drupal_get_path('theme', 'sunshine') . '/css/suckerfish_'  . $style . '.css', 'theme');
}

if (theme_get_setting('sunshine_uselocalcontent'))
{
   $local_content = drupal_get_path('theme', 'sunshine') . '/' . theme_get_setting('sunshine_localcontentfile');
	 if (file_exists($local_content)) {
	    drupal_add_css($local_content, 'theme');
	 }
}

function phptemplate_menu_links($links, $attributes = array()) {

  if (!count($links)) {
    return '';
  }
  $level_tmp = explode('-', key($links));
  $level = $level_tmp[0];
  $output = "<ul class=\"links-$level ".$attributes['class']. "\" id=\"".$attributes['id']."\">\n";

  $num_links = count($links);
  $i = 1;

  foreach ($links as $index => $link) {
    $output .= '<li';

    $output .= ' class="';
    if (stristr($index, 'active')) {
      $output .= 'active';
    }
    elseif((drupal_is_front_page()) && ($link['href']=='<front>')){
      $link['attributes']['class'] = 'active';
      $output .= 'active';
    }
    if ($i == 1) {
      $output .= ' first'; }
    if ($i == $num_links) {
      $output .= ' last'; }

    $output .= '"';

    $output .= ">". l($link['title'], $link['href'], $link['attributes'], $link['query'], $link['fragment']) ."</li>\n";

    $i++;
  }
  $output .= '</ul>';
  return $output;
}

function phptemplate_imagefield_admin_thumbnail($item = null) {
  if (is_null($item) || empty($item['filepath'])) {
    return '<!-- link to default admin thumb -->';
  }
  $thumb_path = imagefield_file_admin_thumb_path($item);
  return '<img class="imagefield-admin-thumb" width="150" src="'. file_create_url($item['filepath']) .'" />';
}
