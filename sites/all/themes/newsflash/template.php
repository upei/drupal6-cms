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
if (is_null(theme_get_setting('newsflash_style'))) {
  global $theme_key;
  // Save default theme settings
  $defaults = array(
    'newsflash_style' => 'blue',
    'newsflash_width' => 0,
	'newsflash_fixedwidth' => '850',
    'newsflash_breadcrumb' => 0,
	'newsflash_iepngfix' => 0,
    'newsflash_themelogo' => 0,
	'newsflash_fontfamily' => 0,
    'newsflash_customfont' => '',
    'newsflash_uselocalcontent' => 0,
    'newsflash_localcontentfile' => '',
    'newsflash_leftsidebarwidth' => '210',
    'newsflash_rightsidebarwidth' => '210',
    'newsflash_suckerfish' => 0,
    'newsflash_usecustomlogosize' => 0,
    'newsflash_logowidth' => '100',
    'newsflash_logoheight' => '100',
  );

  variable_set(
    str_replace('/', '_', 'theme_'. $theme_key .'_settings'),
    array_merge(theme_get_settings($theme_key), $defaults)
  );
  // Force refresh of Drupal internals
  theme_get_setting('', TRUE);
}

function get_newsflash_style() {
  $style = theme_get_setting('newsflash_style');
  if (!$style)
  {
    $style = 'blue';
  }
  if (isset($_COOKIE["newsflashstyle"])) {
    $style = $_COOKIE["newsflashstyle"];
  }
  return $style;
}

$style = get_newsflash_style();
drupal_add_css(drupal_get_path('theme', 'newsflash') . '/css/' . $style . '.css', 'theme');

if (theme_get_setting('newsflash_iepngfix')) {
   drupal_add_js(drupal_get_path('theme', 'newsflash') . '/js/jquery.pngFix.js', 'theme');
}

if (theme_get_setting('newsflash_suckerfish')) {
   drupal_add_css(drupal_get_path('theme', 'newsflash') . '/css/suckerfish_'  . $style . '.css', 'theme');
}

if (theme_get_setting('newsflash_uselocalcontent'))
{
   $local_content = drupal_get_path('theme', 'newsflash') . '/' . theme_get_setting('newsflash_localcontentfile');
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
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// following 2 functions are used in conjunction with the page.tpl.php file
// This allows the use of sub-banners on sub sections of websites.
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
                        function ChopPath($mypath){
	                                //Get rid of any white space on the right of the URL
	                                //Get the string Length of the path
	                                //If the URL has a ? at the end of it, code will display 2 // replace it with 1 /
	                                $mypath = rtrim($mypath);
	                                $url_len = strlen($mypath);
		                        $LastChars = substr($mypath, $url_len - 2, $url_len);
		                          if ($LastChars == "//"){$mypath = str_replace("//", "/", $mypath);}
	                              return $mypath;
                        }
                        function GetBanner($var, $mypath, $bucket){
                        // Get the proper banner
                       // if $var = 0 get the default banner
                       // if $var = 1 get a sub banner based on its path
                       switch ($var){
                                 case 0:
                                          $aPath = base_path() . path_to_theme() . "/images/";
                                 break;

																																																																									                                        case 1:
																																																																														                                                //Since absolute path is used to see if the directory exists
																																																																																				                                                //Switch to the Drupal system path
                   // $mypath = str_replace("/var/www/drupal/cms/current/sites/upei.ca." . $bucket . "/themes/newsflash", base_path() . path_to_theme() , $mypath);
		 $mypath = "/var/www/drupal/cms/current/sites/upei.ca." . $bucket . "/themes/newsflash";
		 $aPath = $mypath;
																																																																																																						                                        break;
																																																																																																											                                }
																																																																																																															                                $finalstyle = "#header {background: #ffffff url(" . $aPath . "graphic.jpg) 0 0 no-repeat;height: 110px;}";
																																																																																																																			                                return $finalstyle;
																																																																																																																							                        }
																																																																																																																										//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

