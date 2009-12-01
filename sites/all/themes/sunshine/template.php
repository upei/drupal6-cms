<?php
// $Id$

function sunshine_build_css_cache($css_files) {
  $data = '';

  // Create the css/ within the files folder.
  $csspath = file_create_path('css');
  $orgpath = drupal_get_path('theme', 'sunshine') . '/css/';
  
  file_check_directory($csspath, FILE_CREATE_DIRECTORY);

  // Build aggregate CSS file.
  foreach ($css_files as $key => $file) {
    $contents = drupal_load_stylesheet($orgpath . $file, TRUE);
    // Return the path to where this CSS file originated from.
    $base = base_path() . $orgpath;
    _drupal_build_css_path(NULL, $base);
    // Prefix all paths within this CSS file, ignoring external and absolute paths.
    $data .= preg_replace_callback('/url\([\'"]?(?![a-z]+:|\/+)([^\'")]+)[\'"]?\)/i', '_drupal_build_css_path', $contents);
  }

  // Per the W3C specification at http://www.w3.org/TR/REC-CSS2/cascade.html#at-import,
  // @import rules must proceed any other style, so we move those to the top.
  $regexp = '/@import[^;]+;/i';
  preg_match_all($regexp, $data, $matches);
  $data = preg_replace($regexp, '', $data);
  $data = implode('', $matches[0]) . $data;
  $checksum = md5($data);
  $filename_cache = 'sunshine.cache.css';
  // Create the CSS file.
  if ((!file_exists($csspath.'/'.$filename_cache)) || (md5(file_get_contents($csspath.'/'.$filename_cache)) != $checksum)) {
    // drupal_set_message('Sunshine CSS cache has been rebuilt.');
    file_save_data($data, $csspath .'/'. $filename_cache, FILE_EXISTS_REPLACE);
  }

  return $csspath .'/'. $filename_cache;
}

function _get_override_css_files() {
  $url_part = _get_sections();
	$mypath = "/var/www-d6/docroot";
  $files = array();
  // FIXME temporary hack for avc development
  if (_get_bucket() == 'avc') {
    return array('/css/avc-sunshine.css');
  }
	for($len = 1; $len <= count($url_part); $len++) {

		$url = array_slice($url_part, 0, $len);
		$file_name = '/css/' . join('_', $url) . '.css';
		if (is_file($mypath . $file_name)) {
      $output .= '<link rel="stylesheet" type="text/css" href="' . $file_name . "\" />\n";
			$files[] = $file_name;
		}
  }
	return $files;
}

function _import_override_css_files($merge = array()) {
  $files = array_merge($merge, _get_override_css_files());
  $output = '<style type="text/css">' . "\n";
  foreach ($files as $filename) {
    $output .= "\t@import url(\"$filename\");\n";
  }
  $output .= "</style>\n";
  return $output;
}

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

/* order is important here */

$css_files = array(
  // base
  '000-base.css',
  
  // header and sidebars
  '003-suckerfish.css',
  '005-admin-navigation.css',
  '010-primary-navigation.css',
  '020-header.css',
  '030-sidebar.css',
  
  // sections
  '100-sections.css',
  
  // pages
  '200-pages.css',
  '210-page-top.css',
  '220-content-top.css',
  '230-content.css',
  '240-inner-sidebars.css',
  '250-content-bottom.css',
  '260-page-bottom.css',
  
  // links and footer
  '300-bottom-links.css',
  '310-footer.css',

  // javascript library
  '800-widgets.css',
  '810-scrollable.css',
  
  // special css
  '901-faqs.css',
  '902-buttons.css',
  '903-home-page-selector.css',
  '904-front-page-story.css',
  '905-front-page-gallery.css',
  '906-front-page-news-tabs.css',
  '907-views-nav-buttons.css',
  '908-zoom.css',
  '910-tooltip.css',
  '911-event-timeline.css',
  '912-section_efg.css',
  '920-node.css',
  '923-node-media.css',
  '925-node-person.css',
  '930-node-form.css',
  '990-misc.css',

  'sunshine.css',
  
  // jquery-ui
  'ui-theme/ui.core.css',
  'ui-theme/ui.theme.css',
  'ui-theme/ui.resizable.css',
  'ui-theme/ui.dialog.css',
  );

// aggregate sunshine css files
$base_css = sunshine_build_css_cache($css_files);
drupal_add_css($base_css, 'theme', 'all', false);

// scripts that are added to theme
$scripts = array(
  'js/tools.scrollable.min.js',
  'js/tools.tooltip.min.js',
  'js/tools.expose.min.js',
  'js/sunshine.js',
);

foreach ($scripts as $script) drupal_add_js( drupal_get_path('theme', 'sunshine') . '/' . $script, 'theme', 'footer');
drupal_add_js('misc/sifr/jquery.swfobject.min.js', 'theme', 'footer', false, true);
drupal_add_js('misc/sifr/jquery.sifr.min.js', 'theme', 'footer', false, true);
drupal_add_js('misc/fancyzoom.min.js', 'theme', 'header', false, true);

if (theme_get_setting('sunshine_iepngfix')) {
   drupal_add_js(drupal_get_path('theme', 'sunshine') . '/js/jquery.pngFix.js', 'theme');
}

if (theme_get_setting('sunshine_uselocalcontent'))
{
   $local_content = drupal_get_path('theme', 'sunshine') . '/' . theme_get_setting('sunshine_localcontentfile');
	 if (file_exists($local_content)) {
	    drupal_add_css($local_content, 'theme');
	 }
}

$javascript = <<<END
$(function () {
  if ($.hasFlashPlayer) {
    $('.header-title').sifr({
      offsetTop: 3,
      textColor: '#7A2424',
      font:'minionpro',
      path:'/misc/sifr'
    });
  }
});
END;
drupal_add_js($javascript, 'inline', 'footer', false, false);

/* XXX add rss feed to home page. this is a workaround.  */
if (function_exists('_get_bucket')) {
switch (_get_bucket()) {
case 'home':
case 'news':
  $_rss_feed = '<link rel="alternate" type="application/rss+xml" title="UPEI Media Releases" href="http://www.upei.ca/news/media/feed" />';
  if (function_exists('drupal_add_html_head')) {
    drupal_add_html_head($_rss_feed); // drupal 7
  }
  else {
    drupal_set_html_head($_rss_feed); // drupal 6
  }
}
}
/* END */

function sunshine_preprocess_block(&$vars) {
  $subject = db_result(db_query("SELECT title from {blocks} where bid=%d", $vars['block']->bid));
  if($subject) {
    $vars['block']->subject = $subject;
  }
}

function sunshine_preprocess_page(&$vars) {
  $page_classes = array();
  // add front
  if ($vars['is_front']) {
    $page_classes[] = 'page-front';
  }
  else {
    $page_classes[] = 'page-not-front';
  }

  // add node type and nid to page_classes
  if ($vars['node']) {
    $page_classes[] = 'page-' . $vars['node']->type;
    $page_classes[] = 'page-nid-' . $vars['node']->nid;
  }

  // add view-id to page_classes
  $view = views_get_page_view();
  if ($view) {
    $view_name = strtolower(preg_replace('/[^A-Za-z0-9-]/', '-', $view->view->name));
    $view_id = strtolower(preg_replace('/[^A-Za-z0-9-]/', '-', $view->display->id));
    $page_classes[] = 'page-view-' . $view_name;
    $page_classes[] = 'page-view-' . $view_name . '-' . $view_id;
  }

  $page_classes = array_filter($page_classes);
  $vars['page_classes'] = implode(' ', $page_classes);
}

function sunshine_simplenews_scheduler_title($title, $edition_no) {
  return $title;
}
