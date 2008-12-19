<?php
// $Id: template.php,v 1.00 2008/03/03 12:00:00 jaburns Exp $

/**
 * Sets the body-tag class attribute.
 *
 * Adds 'sidebar-left', 'sidebar-right' or 'sidebars' classes as needed.
 */
function phptemplate_body_class($left, $right) {
  if ($left != '' && $right != '') {
    $class = 'sidebars';
  }
  else {
    if ($left != '') {
      $class = 'sidebar-left';
    }
    if ($right != '') {
      $class = 'sidebar-right';
    }
  }

  if (isset($class)) {
    print ' class="'. $class .'"';
  }
}


function phptemplate_links($links = array(), $attributes = array('class' => 'links'))
{
$delimiter = " | ";
// Display the left cap of the 'button bar'
//print "[";
$link_count = count($links);
$current = 1;
$output = '';
if ( is_array($links) ){
foreach ( $links as $lnk ) {
    // Print the link
    //print_r($lnk); //Array ( [title] => TITLE [href] => # [attributes] => Array ( ) )
    $output .= l($lnk['title'], $lnk['href'], $lnk['attributes']);
        // Only print the delimiter if not the last link
    if ( $current < $link_count ) {
        $output .= $delimiter;
    }
    $current++;
}

$output .= '';
} else {
$output = $links;
}
return $output;
}

/* NOTE SURE WHAT THIS DOES */
function phptemplate_filter_tips_more_info() {
  return '';
}

/**
 * Return a themed breadcrumb trail.
 *
 * @param $breadcrumb
 *   An array containing the breadcrumb links.
 * @return a string containing the breadcrumb output.
 */
function phptemplate_breadcrumb($breadcrumb) {
  if (!empty($breadcrumb)) {
    return '<div class="breadcrumb">'. implode(' &#187; ', $breadcrumb) .'</div>';
  }
}

/**
 * Allow themable wrapping of all comments.
 */
 
/* NOTE SURE WHAT THIS DOES */
function phptemplate_comment_wrapper($content, $node) {
/*
  if (!$content || $node->type == 'forum') {
    return '<div id="comments">'. $content .'</div>';
  }
  else {
    return '<div id="comments"><h2 class="comments">'. t('Comments') .'</h2>'. $content .'</div>';
  }
*/  
  return '';
  
}

/**
 * Override or insert PHPTemplate variables into the templates.
 */
function phptemplate_preprocess_page(&$vars) {

$mime_types = array 
    (
    'application/vnd.wap.xhtml+xml',
    'application/xhtml+xml',
    'text/html'
    );
    
$mime_dtds = array
    (
    '<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE html PUBLIC "-//WAPFORUM//DTD XHTML Mobile 1.2//EN" 
    "http://www.openmobilealliance.org/tech/DTD/xhtml-mobile11.dtd"> '."\n",
    '<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" 
    "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">'."\n",
    '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML Basic 1.0//EN" 
    "http://www.w3.org/TR/xhtml-basic/xhtml-basic10.dtd">'
    );

if ( !isset($_SERVER["HTTP_ACCEPT"]) OR empty($_SERVER["HTTP_ACCEPT"]) OR stripos($_SERVER['REQUEST_URI'], 'admin') !== FALSE ) {
    $my_dtd = 2;
} elseif ( stristr($_SERVER["HTTP_ACCEPT"], $mime_types[0]) ) {
    $my_dtd = 0;
} elseif ( stristr($_SERVER["HTTP_ACCEPT"], $mime_types[1]) ) {
    $my_dtd = 1;
} else {
    $my_dtd = 2;
}
$my_dtd = 2;

$vars['dtd']     = $mime_dtds[$my_dtd];
$vars['head']    = ($my_dtd != 2 ) ? str_replace('text/html', $mime_types[$my_dtd], $vars['head']) : $vars['head'];
$vars['styles']  = ( stripos($_SERVER['REQUEST_URI'], 'admin') !== FALSE ) ? $vars['styles'] : 
                    '<link type="text/css" rel="stylesheet" media="all" href="'. base_path() . path_to_theme() .'/mobi.css" />'."\n";
$vars['head_extra'] = '<link rel="alternate" media="handheld" href="http://'.  $_SERVER['HTTP_HOST'] . $_SERVER['REQUEST_URI'] .'" />'."\n";
$vars['scripts'] = ( stripos($_SERVER['REQUEST_URI'], 'admin') !== FALSE ) ? $vars['scripts'] : '';

$new_links = array();
$new_link = array();
$blah = $vars['primary_links']; // CHANGE TO MENU OF CHOICE

$i = 1;
foreach ($blah as $menu_item => $menu_value) {
    $new_links [$menu_item] = array('attributes' => array('accesskey' => $i));
    $new_link [$menu_item] = $menu_value;
    $i++;
}

$att = array_merge_recursive($new_links, $new_link);

$m_l = '';
foreach ($att as $lmenu => $latts){
    $m_l .= "\n" . l( $latts['title'], $latts['href'], array('attributes' => $latts['attributes']) ) .' | ';
}

$vars['mobi_links'] = rtrim($m_l, ' | ');
#$vars['content'] = '<pre>'. print_r($_SERVER, true) .'</pre>';


  drupal_set_header('Content-Type: '. $mime_types[$my_dtd] .'; charset=utf-8');
  drupal_set_header("Expires: " . date("D, d M Y H:i:s", time() + 60 * 60 * 24 * 7) . " GMT");
  drupal_set_header("Cache-Control: Public");
}

/**
 * Returns the rendered local tasks. The default implementation renders
 * them as tabs. Overridden to split the secondary tasks.
 *
 * @ingroup themeable
 */
 

/* NOTE SURE WHAT THIS DOES */
function phptemplate_menu_local_tasks() {
  return menu_primary_local_tasks();
}

/* NOTE SURE WHAT THIS DOES */
function phptemplate_comment_submitted($comment) {
  return t('!datetime — !username',
    array(
      '!username' => theme('username', $comment),
      '!datetime' => format_date($comment->timestamp)
    ));
}
/* NOTE SURE WHAT THIS DOES */
function phptemplate_node_submitted($node) {
  return t('!datetime — !username',
    array(
      '!username' => theme('username', $node),
      '!datetime' => format_date($node->created),
    ));
}

/* PAGER -> LIMITED FUNCTIONALITY */

function phptemplate_pager($tags = array(), $limit = 5, $element = 0, $parameters = array()) {
  global $pager_total, $pager_page_array;
  $output = '';
  
  $page_of = (!$node) ? ' '. $pager_page_array[$element] + 1 .' / '. $pager_total[$element] .' ' : '';

  if ($pager_total[$element] > 1) {
    $output .= '<div class="pager">';
    $output .= theme('pager_previous', ($tags[1] ? $tags[1] : t('<<')), $limit, $element, 1, $parameters) ." \n";
    $output .= $page_of;
    $output .= theme('pager_next', ($tags[3] ? $tags[3] : t('>>')), $limit, $element, 1, $parameters) ." \n";
    $output .= '</div>';
    
    // THIS SHOULD EQUAL THE HTML EQUIVILANT OF t()s ABOVE
    $output = str_replace('>&lt;&lt;', ' accesskey="7" title="previous"><<', $output);
    $output = str_replace('>&gt;&gt;', ' accesskey="9" title="next">>>', $output);  
    return $output;
  }
}

//~ Make code XHTML compatible
function mobi_fix($buffer) {

/**
 * This segment is based on htmlcorrector module was made by Steven Wittens <unconed@drop.org>
 */
 
  $nonesting = array('li', 'p');
  // Single use tags in HTML4
  $singleuse = array('base', 'meta', 'link', 'hr', 'br', 'param', 'img', 'area', 'input', 'col', 'frame', 'go');
  // Properly entify angles
  $text = preg_replace('!<([^a-zA-Z/])!', '&lt;\1', $buffer);
  // Splits tags from text
  $split = preg_split('/<([^>]+?)>/', $text, -1, PREG_SPLIT_DELIM_CAPTURE);
  // Note: PHP ensures the array consists of alternating delimiters and literals
  // and begins and ends with a literal (inserting $null as required).
  $tag = false; // Odd/even counter. Tag or no tag.
  $stack = array();
  $output = '';
  foreach ($split as $value) {
    // HTML tag
    if ($tag) {
      list($tagname) = explode(' ', strtolower($value), 2);
      // Closing tag
      if ($tagname{0} == '/') {
        $tagname = substr($tagname, 1);
        if (!in_array($tagname, $singleuse)) {
          // See if we have other tags lingering first, and close them
          while (($stack[0] != $tagname) && count($stack)) {
            $output .= '</'. array_shift($stack) .'>';
          }
          // If the tag was not found, just leave it out;
          if (count($stack)) {
            $output .= '</'. array_shift($stack) .'>';
          }
        }
      }
      // Opening tag
      else {
        // See if we have an identical tag already open and close it if desired.
        if (count($stack) && ($stack[0] == $tagname) && in_array($stack[0], $nonesting)) {
          $output .= '</'. array_shift($stack) .'>';
        }
        // Push non-single-use tags onto the stack
        if (!in_array($tagname, $singleuse)) {
          array_unshift($stack, $tagname);
        }
        // Add trailing slash to single-use tags as per X(HT)ML.
        else {
          $value = rtrim($value, ' /') . ' /';
        }
        $output .= '<'. $value .'>';
      }
    }
    else {
      // Passthrough
      $output .= $value;
    }
    $tag = !$tag;
  }
  // Close remaining tags
  while (count($stack) > 0) {
    $output .= '</'. array_shift($stack) .'>';
  }
  return str_replace (array('<p></p>'), array(''), $output );
}
