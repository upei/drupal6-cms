<?php
// $Id: print.pages.inc,v 1.1.2.29 2008/09/10 08:13:05 jcnventura Exp $

/**
 * @file
 * Contains the functions to generate Printer-friendly pages.
 *
 * This file is included by the core PF module, and includes all the
 * functions necessary to generate a PF version of the original page
 * in HTML format.
 */

/**
 * Generate an HTML version of the printer-friendly page
 *
 * @see print_controller()
 * @see _print_get_template()
 */
function print_controller_html() {
  $args = func_get_args();
  // Remove the print/ prefix
  $path = implode('/', $args);
  $cid = isset($_GET['comment']) ? $_GET['comment'] : NULL;

  $print = print_controller($path, $cid);
  $node = $print['node'];
  include_once(_print_get_template('html', $print['type']));
}

/**
 * Select the print generator function based on the page type
 *
 * Depending on the type of node, this functions chooses the appropriate
 * generator function.
 *
 * @param $path
 *   path of the original page
 * @param $cid
 *   comment ID of the individual comment to be rendered
 * @param $teaser
 *   if set to TRUE, outputs only the node's teaser
 * @param $message
 *   optional sender's message (used by the send e-mail module)
 * @return
 *   array with the fields to be used in the template
 * @see _print_generate_node()
 * @see _print_generate_path()
 * @see _print_generate_book()
 */
function print_controller($path, $cid, $teaser = FALSE, $message = NULL) {
  if (!is_numeric($path)) {
    // Indirect call with print/alias
    // If there is a path alias with these arguments, generate a printer-friendly version for it
    $path = drupal_get_normal_path($path);
    $ret = preg_match('!^node/(.*)!i', $path, $matches);
    if ($ret == 1) {
      $path = $matches[1];
    }
  }
  $parts = explode('/', $path);
  if (is_numeric($parts[0])) {
    $print = _print_generate_node($path, $cid, $teaser, $message);
  }
  else {
    $ret = preg_match('!^book/export/html/(.*)!i', $path, $matches);
    if ($ret == 1) {
      // This is a book PF page link, handle trough the book handling functions
      $print = _print_generate_book($matches[1], $teaser, $message);
    }
    else {
      // If no content node was found, handle the page printing with the 'printable' engine
      $print = _print_generate_path($path, $teaser, $message);
    }
  }

  return $print;
}

/**
 * Generates a robots meta tag to tell them what they may index
 *
 * @return
 *   string with the meta robots tag
 */
function _print_robots_meta_generator() {
  $print_robots_noindex = variable_get('print_robots_noindex', PRINT_ROBOTS_NOINDEX_DEFAULT);
  $print_robots_nofollow = variable_get('print_robots_nofollow', PRINT_ROBOTS_NOFOLLOW_DEFAULT);
  $print_robots_noarchive = variable_get('print_robots_noarchive', PRINT_ROBOTS_NOARCHIVE_DEFAULT);
  $robots_meta = array();

  if (!empty($print_robots_noindex)) {
    $robots_meta[] = 'noindex';
  }
  if (!empty($print_robots_nofollow)) {
    $robots_meta[] = 'nofollow';
  }
  if (!empty($print_robots_noarchive)) {
    $robots_meta[] = 'noarchive';
  }

  if (count($robots_meta) > 0) {
    $robots_meta = implode(', ', $robots_meta);
    $robots_meta = "<meta name='robots' content='$robots_meta' />\n";
  }
  else {
    $robots_meta = '';
  }

  return $robots_meta;
}

/**
 * Post-processor that fills the array for the template with common details
 *
 * @param $node
 *   generated node with a printer-friendly node body
 * @param $message
 *   optional sender's message (used by the send e-mail module)
 * @param $cid
 *   id of current comment being generated (NULL when not generating
 *   an individual comment)
 * @return
 *   array with the fields to be used in the template
 */
function _print_var_generator($node, $message = NULL, $cid = NULL) {
  global $base_url, $language;

  $path = empty($node->nid) ? $node->path : "node/$node->nid";

  $themed = theme('print_text');

  // print module settings
  $print_css = variable_get('print_css', PRINT_CSS_DEFAULT);
  $print_urls = variable_get('print_urls', PRINT_URLS_DEFAULT);
  $print_logo_options = variable_get('print_logo_options', PRINT_LOGO_OPTIONS_DEFAULT);
  $print_logo_url = variable_get('print_logo_url', PRINT_LOGO_URL_DEFAULT);
  $print_html_sendtoprinter = variable_get('print_html_sendtoprinter', PRINT_HTML_SENDTOPRINTER_DEFAULT);
  $print_sourceurl_enabled = variable_get('print_sourceurl_enabled', PRINT_SOURCEURL_ENABLED_DEFAULT);
  $print_sourceurl_forcenode = variable_get('print_sourceurl_forcenode', PRINT_SOURCEURL_FORCENODE_DEFAULT);
  $print_sourceurl_date = variable_get('print_sourceurl_date', PRINT_SOURCEURL_DATE_DEFAULT);
  $print_footer_options = variable_get('print_footer_options', PRINT_FOOTER_OPTIONS_DEFAULT);
  $print_footer_user = variable_get('print_footer_user', PRINT_FOOTER_USER_DEFAULT);

  $print['language'] = $language->language;
  $print['title'] = $node->title;
  $print['head'] = drupal_get_html_head();
  $print['scripts'] = drupal_get_js();
  $print['robots_meta'] = _print_robots_meta_generator();
  $print['url'] = url($path, array('absolute' => TRUE));
  $print['base_href'] = "<base href='". $print['url'] ."' />\n";
  $print['favicon'] = theme_get_setting('toggle_favicon') ? "<link rel='shortcut icon' href='". theme_get_setting('favicon') ."' type='image/x-icon' />\n" : '';

  if (!empty($print_css)) {
    $replace_pairs = array('%b' => base_path(), '%t' => path_to_theme());
    $user_css = strip_tags(strtr($print_css, $replace_pairs));
  }
  else {
    drupal_add_css(drupal_get_path('module', 'print') .'/css/print.css');
  }
  $drupal_css = drupal_add_css();
  foreach ($drupal_css as $key => $types) {
    // Unset the theme's CSS
    $drupal_css[$key]['theme'] = array();
  }

  // If we are sending a message via e-mail, the CSS must be embedded
  if (!empty($message)) {
    $style = '';
    $css_files = array();
    foreach ($drupal_css as $types) {
      foreach ($types as $values) {
        $css_files = array_merge($css_files, array_keys($values));
      }
    }
    if (!empty($print_css)) {
      // Convert to a local path, by removing the base_path
      $pattern = '!^'. base_path() .'!';
      $css_files[] = preg_replace($pattern, '', $user_css);
    }
    foreach ($css_files as $filename) {
      $res = file_get_contents($filename, TRUE);
      if ($res != FALSE) {
        $style .= $res;
      }
    }
    $print['css'] = "<style type='text/css' media='all'>$style</style>\n";
  }
  else {
    $print['css'] = drupal_get_css($drupal_css);
    if (!empty($print_css)) {
      $print['css'] .= "<link type='text/css' rel='stylesheet' media='all' href='$user_css' />\n";
    }
  }

  $print['sendtoprinter'] = $print_html_sendtoprinter ? ' onload="window.print();"' : '';

  switch ($print_logo_options) {
    case 0: // none
      $logo_url = 0;
      break;
    case 1: // theme's
      $logo_url = theme_get_setting('logo');
      break;
    case 2: // user-specifed
      $logo_url = strip_tags($print_logo_url);
      break;
  }
  $print['logo'] = $logo_url ? "<img class='print-logo' src='$logo_url' alt='' />\n" : '';

  switch ($print_footer_options) {
    case 0: // none
      $footer = '';
      break;
    case 1: // theme's
      $footer = filter_xss_admin(variable_get('site_footer', FALSE)) ."\n". theme('blocks', 'footer');
      $logo_url = theme_get_setting('logo');
      break;
    case 2: // user-specifed
      $footer = $print_footer_user;
      break;
  }
  $print['footer_message'] = $footer;

  $published_site = variable_get('site_name', 0);
  if ($published_site) {
    $published = (empty($themed['published'])) ? t('Published on %site_name', array('%site_name' => $published_site)) : ($themed['published'] .' '. $published_site);
    $print['site_name'] = $published .' ('. l($base_url, $base_url) .')';
  }
  else {
    $print['site_name'] = '';
  }

  if ($print_sourceurl_enabled == 1) {
    /* Grab and format the src URL */
    if (empty($print_sourceurl_forcenode)) {
      $url = $print['url'];
    }
    else {
      $url = $base_url .'/'. (((bool)variable_get('clean_url', '0')) ? '' : '?q=') . $path;
    }
    if ($cid) {
      $url .= '#comment-$cid';
    }
    $retrieved_date = format_date(time(), 'small');
    $retrieved = (empty($themed['retrieved'])) ? t('retrieved on %date', array('%date' => $retrieved_date)) : ($themed['retrieved'] .' '. $retrieved_date);
    $print['printdate'] = $print_sourceurl_date ? " ($retrieved)" : '';

    $source_url = (empty($themed['sourceURL'])) ? t('Source URL') : $themed['sourceURL'];
    $print['source_url'] = '<strong>'. $source_url . $print['printdate'] .':</strong> '. l($url, $url);
  }
  else {
    $print['source_url'] = '';
  }

  if (isset($node->type)) {
    $node_type = $node->type;

    if (theme_get_setting("toggle_node_info_$node_type")) {
      $by_author = ($node->name ? $node->name : variable_get('anonymous', t('Anonymous')));
      $by = (empty($themed['by'])) ? t('By %author', array('%author' => $by_author)) : ($themed['by'] .' '. $by_author);
      $print['submitted'] = $by;

      $created_datetime = format_date($node->created, 'small');
      $created = (empty($themed['created'])) ? t('Created %date', array('%date' => $created_datetime)) : ($themed['created'] .' '. $created_datetime);
      $print['created'] = $created;
    }
    else {
      $print['submitted'] = '';
      $print['created'] = '';
    }

    $print['type'] = $node->type;
  }
  else {
    $print['submitted'] = '';
    $print['created'] = '';
    $print['type'] = '';
  }

  menu_set_active_item($path);
  $breadcrumb = drupal_get_breadcrumb();
  if (!empty($breadcrumb)) {
    $breadcrumb[] = menu_get_active_title();
    $print['breadcrumb'] = implode(' > ', $breadcrumb);
  }
  else {
    $print['breadcrumb'] = '';
  }

  // Display the collected links at the bottom of the page. Code once taken from Kjartan Mannes' project.module
  $print['pfp_links'] = '';
  if (!empty($print_urls)) {
    $urls = _print_friendly_urls();
    $max = count($urls);
    $pfp_links = '';
    if ($max) {
      for ($i = 0; $i < $max; $i++) {
        $pfp_links .= '['. ($i + 1) .'] '. $urls[$i] ."<br />\n";
      }
      $links = (empty($themed['links'])) ? t('Links') : $themed['links'];
      $print['pfp_links'] = "<p><strong>$links:</strong><br />$pfp_links</p>";
    }
  }

  if (module_exists('taxonomy')) {
    $terms = taxonomy_link('taxonomy terms', $node);
    $print['taxonomy'] = theme('links', $terms);
  }

  $print['content'] = $node->body;
  $print['node'] = $node;
  $print['message'] = $message;

  return $print;
}

/**
 * Callback function for the preg_replace_callback for URL-capable patterns
 *
 * Manipulate URLs to make them absolute in the URLs list, and to add a
 * [n] footnote marker.
 *
 * @param $matches
 *   array with the matched tag patterns, usually <a...>+text+</a>
 * @return
 *   tag with re-written URL and when appropriate the [n] index to the
 *   URL list
 */
function _print_rewrite_urls($matches) {
  global $base_url, $base_root;

  // Get value of Printer-friendly URLs setting
  $print_urls = variable_get('print_urls', PRINT_URLS_DEFAULT);

  // first, split the html into the different tag attributes
  $pattern = '!\s*(\w+\s*=\s*"(?:\\\"|[^"])*")\s*|\s*(\w+\s*=\s*\'(?:\\\\\'|[^\'])*\')\s*|\s*(\w+\s*=\s*\w+)\s*|\s+!';
  $attribs = preg_split($pattern, $matches[1], -1, PREG_SPLIT_NO_EMPTY | PREG_SPLIT_DELIM_CAPTURE);
  foreach ($attribs as $key => $value) {
    $attribs[$key] = preg_replace('!(\w)\s*=\s*(.*)!', '$1=$2', $value);
  }

  $size = count($attribs);
  for ($i=1; $i < $size; $i++) {
    // If the attribute is href or src, we may need to rewrite the URL in the value
    if (preg_match('!^(?:href|src)\s*?=(.*)!i', $attribs[$i], $urls) > 0) {
      $url = trim($urls[1], " \t\n\r\0\x0B\"'");

      if (strpos($url, '://') || preg_match('!^mailto:.*?@.*?\..*?$!iu', $url)) {
        // URL is absolute, do nothing
        $newurl = urldecode($url);
      }
      else {
        if ($url[0] == '#') {
          // URL is an anchor tag
          if (!empty($print_urls)) {
            $path = explode('/', $_GET['q']);
            unset($path[0]);
            $path = implode('/', $path);
            if (is_numeric($path)) {
              $path = "node/$path";
            }
            // Printer-friendly URLs is on, so we need to make it absolute
            $newurl = url($path, array('fragment' => substr(urldecode($url), 1), 'absolute' => TRUE));
          }
          // Because base href is the original page, change the link to
          // still be usable inside the print page
          $matches[1] = str_replace($url, $_GET['q'] . $url, $matches[1]);
        }
        else {
          // URL is relative, convert it into absolute URL
          if ($url[0] == '/') {
            // If it starts with '/' just append it to the server name
            $newurl = $base_root .'/'. trim(urldecode($url), '/');
          }
          elseif (preg_match('!^(?:index.php)?\?q=!i', $url)) {
            // If it starts with ?q=, just prepend with the base URL
            $newurl = $base_url .'/'. trim(urldecode($url), '/');
          }
          else {
            $newurl = url(trim(urldecode($url), '/'), array('absolute' => TRUE));
          }
          $matches[1] = str_replace($url, $newurl, $matches[1]);
        }
      }
    }
  }

  $ret = '<'. $matches[1] .'>';
  if (count($matches) == 4) {
    $ret .= $matches[2] . $matches[3];
    if ((!empty($print_urls)) && (isset($newurl))) {
      $ret .= ' <span class="print-footnote">['. _print_friendly_urls(trim(stripslashes($newurl))) .']</span>';
    }
  }

  return $ret;
}

/**
 * Auxiliary function to store the Printer-friendly URLs list as static.
 *
 * @param $url
 *   absolute URL to be inserted in the list
 * @return
 *   list of URLs previously stored if $url is 0, or the current count
 *   otherwise.
 */
function _print_friendly_urls($url = 0) {
  static $urls = array();
  if ($url) {
    $url_idx = array_search($url, $urls);
    if ($url_idx !== FALSE) {
      return ($url_idx + 1);
    }
    else {
      $urls[] = $url;
      return count($urls);
    }
  }
  $ret = $urls;
  $urls = array();
  return $ret;
}

/**
 * Choose most appropriate template
 *
 * Auxiliary function to resolve the most appropriate template trying to find
 * a content specific template in the theme or module dir before falling back
 * on a generic template also in those dirs.
 *
 * @param format
 *   format of the PF page being rendered (html, pdf, etc.)
 * @param $type
 *   name of the node type being rendered in a PF page
 * @return
 *   filename of the most suitable template
 */
function _print_get_template($format = NULL, $type = NULL) {
  $filenames = array();
  // First try to find a template defined both for the format and then the type
  if (!empty($format) && !empty($type)) {
    $filenames[] = "print_$format.node-$type.tpl.php";
  }
  // Then only for the format
  if (!empty($format)) {
    $filenames[] = "print_$format.tpl.php";
  }
  // If the node type is known, then try to find that type's template file
  if (!empty($type)) {
    $filenames[] = "print.node-$type.tpl.php";
  }
  // Finally search for a generic template file
  $filenames[] = 'print.tpl.php';

  foreach ($filenames as $value) {
    // First in the theme directory
    $file = drupal_get_path('theme', $GLOBALS['theme_key']) .'/'. $value;
    if (file_exists($file)) {
      return $file;
    }
    // Then in the module directory
    $file = drupal_get_path('module', 'print') .'/'. $value;
    if (file_exists($file)) {
      return $file;
    }
  }
}

/**
 * Prepare a Printer-friendly-ready node body for content nodes
 *
 * @param $nid
 *   node ID of the node to be rendered into a printer-friendly page
 * @param $cid
 *   comment ID of the individual comment to be rendered
 * @param $teaser
 *   if set to TRUE, outputs only the node's teaser
 * @param $message
 *   optional sender's message (used by the send e-mail module)
 * @return
 *   filled array ready to be used in the template
 */
function _print_generate_node($nid, $cid = NULL, $teaser = FALSE, $message = NULL) {
  // We can take a node id
  $node = node_load(array('nid' => $nid));
  if (!node_access('view', $node)) {
    // Access is denied
    return drupal_access_denied();
  }
  drupal_set_title($node->title);

  //alert other modules that we are generating a printer-friendly page, so they can choose to show/hide info
  $node->printing = TRUE;
  // Turn off Pagination by the Paging module
  unset($node->pages);
  unset($node->page_count);

  if ($teaser) {
    unset($node->body);
  }
  else {
    unset($node->teaser);
  }
  $node = (object)$node;
  if ($cid === NULL) {
    // Adapted (simplified) version of node_view for Drupal 5.x
    //Render the node content
    $node = node_build_content($node, $teaser, TRUE);
    // Disable fivestar widget output
    unset($node->content['fivestar_widget']);
    // Disable service links module output
    unset($node->content['service_links']);

    $node->body = drupal_render($node->content);
    //TODO the following was part of the fix for http://drupal.org/node/254863
    //check if it is reproducible and find the exact condition which
    //triggered it
    //$node->body = html_entity_decode($node->body);
  }

  $print_comments = variable_get('print_comments', PRINT_COMMENTS_DEFAULT);

  if (function_exists('comment_render') && (($cid != NULL) || ($print_comments))) {
    //Print only the requested comment (or if $cid is NULL, all of them)
    $comments = comment_render($node, $cid);

    //Remove the comment forms
    $comments = preg_replace('!<form.*?id="comment-.*?">.*?</form>!sim', '', $comments);
    //Remove the 'Post new comment' title
    $comments = preg_replace('!<h2.*?>Post new comment</h2>!', '', $comments);
    //Remove the comment title hyperlink
    $comments = preg_replace('!(<h3.*?>)(<a.*?>)(.*?)</a>(</h3>)!', '$1$3$4', $comments);
    //Remove the comment author link
    $pattern = '!(<span class="submitted">)(.*?)<a.*?>(.*?)</a>(</span>)!sim';
    if (preg_match($pattern, $comments)) {
      $comments = preg_replace($pattern , '$1$2$3$4', $comments);
    }
    //Remove the comment links
    $comments = preg_replace('!\s*<ul class="links">.*?</ul>!sim', '', $comments);
    if ($cid != NULL) {
      // Single comment requested, output only the comment
      unset($node->body);
    }
    $node->body .= $comments;
  }

  node_invoke_nodeapi($node, 'alter', FALSE, TRUE);

  // Convert the a href elements
  $pattern = '!<(a\s[^>]*?)>(.*?)(</a>)!is';
  $node->body = preg_replace_callback($pattern, '_print_rewrite_urls', $node->body);

  init_theme();

  $print = _print_var_generator($node, $message, $cid);

  return $print;
}

/**
 * Prepare a Printer-friendly-ready node body for non-content pages
 *
 * @param $path
 *   path of the node to be rendered into a printer-friendly page
 * @param $teaser
 *   if set to TRUE, outputs only the node's teaser
 * @param $message
 *   optional sender's message (used by the send e-mail module)
 * @return
 *   filled array ready to be used in the template
 */
function _print_generate_path($path, $teaser = FALSE, $message = NULL) {
  $path = drupal_get_normal_path($path);

  menu_set_active_item($path);
  // Adapted from index.php.
  $node = new stdClass();
  $node->body = menu_execute_active_handler($path);
  $node->title = drupal_get_title();
  $node->path = $path;

  // It may happen that a drupal_not_found is called in the above call
  if (preg_match('/404 Not Found/', drupal_get_headers()) == 1) {
    return;
  }

  if (is_int($node->body)) {
    switch ($node->body) {
      case MENU_NOT_FOUND:
        return drupal_not_found();
        break;
      case MENU_ACCESS_DENIED:
        return drupal_access_denied();
        break;
    }
  }

  // Delete any links area
  $node->body = preg_replace('!\s*<div class="links">.*?</div>!sim', '', $node->body);

  // Convert the a href elements
  $pattern = '!<(a\s[^>]*?)>(.*?)(</a>)!is';
  $node->body = preg_replace_callback($pattern, '_print_rewrite_urls', $node->body);

  init_theme();

  $print = _print_var_generator($node, $message);

  return $print;
}


/**
 * Prepare a Printer-friendly-ready node body for book pages
 *
 * @param $nid
 *   node ID of the node to be rendered into a printer-friendly page
 * @param $teaser
 *   if set to TRUE, outputs only the node's teaser
 * @param $message
 *   optional sender's message (used by the send e-mail module)
 * @return
 *   filled array ready to be used in the template
 */
function _print_generate_book($nid, $teaser = FALSE, $message = NULL) {
  $node = node_load(array('nid' => $nid));
  if (!node_access('view', $node) || (!user_access('access printer-friendly version'))) {
    // Access is denied
    return drupal_access_denied();
  }

  $tree = book_menu_subtree_data($node->book);
  $node->body = book_export_traverse($tree, 'book_node_export');

  // Convert the a href elements
  $pattern = '!<(a\s[^>]*?)>(.*?)(</a>)!is';
  $node->body = preg_replace_callback($pattern, '_print_rewrite_urls', $node->body);

  init_theme();

  $print = _print_var_generator($node, $message);
  // The title is already displayed by the book_recurse, so avoid duplication
  $print['title'] = '';

  return $print;
}
