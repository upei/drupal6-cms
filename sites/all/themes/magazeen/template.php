<?php
// $Id: template.php,v 1.6.2.2 2009/05/04 07:31:23 zinv Exp $

/**
 * @file template.php
 * Main template file for Magazeen.
 */

/*
 * Initialize theme settings
 */
if (is_null(theme_get_setting('user_notverified_display'))) {
  global $theme_key;
  // Get node types
  $node_types = node_get_types('names');

  /**
   * The default values for the theme variables. Make sure $defaults exactly
   * matches the $defaults in the theme-settings.php file.
   */

  $defaults = array(
    'comment_title'                         => 'Leave a Response',
    'no_comment_message'                    => 'It\'s quite in here! Why not leave a <a href="#respond">response</a>?',
    'breadcrumb_display'                    => 'yes',
    'breadcrumb_separator'                  => ' › ',
    'breadcrumb_home'                       => 1,
    'breadcrumb_trailing'                   => 0,
    'breadcrumb_title'                      => 0,
    'mission_statement_pages'               => 'home',
    'user_notverified_display'              => 1,
    'search_text'                           => 'Search',
    'search_snippet'                        => 1,
    'search_info_type'                      => 1,
    'search_info_user'                      => 1,
    'search_info_date'                      => 1,
    'search_info_comment'                   => 1,
    'search_info_upload'                    => 1,
    'submitted_by_author_default'           => 1,
    'submitted_by_date_default'             => 1,
    'submitted_by_enable_content_type'      => 0,
    'taxonomy_display_default'              => 'all',
    'taxonomy_format_default'               => 'list',
    'taxonomy_enable_content_type'          => 0,
    'readmore_default'                      => t('Continue Reading'),
    'readmore_title_default'                => t('Read the rest of this posting.'),
    'readmore_enable_content_type'          => 0,
    'readmore_prefix_default'               => '',
    'readmore_suffix_default'               => '',
    'comment_singular_default'              => t('1 comment'),
    'comment_plural_default'                => t('@count comments'),
    'comment_title_default'                 => t('Jump to the first comment of this posting.'),
    'comment_prefix_default'                => '',
    'comment_suffix_default'                => '',
    'comment_new_singular_default'          => t('1 new comment'),
    'comment_new_plural_default'            => t('@count new comments'),
    'comment_new_title_default'             => t('Jump to the first new comment of this posting.'),
    'comment_new_prefix_default'            => '',
    'comment_new_suffix_default'            => '',
    'comment_add_default'                   => t('Leave a comment'),
    'comment_add_title_default'             => t('Leave a new comment to this page.'),
    'comment_add_prefix_default'            => '',
    'comment_add_suffix_default'            => '',
    'comment_node_default'                  => t('Add new comment'),
    'comment_node_title_default'            => t('Share your thoughts and opinions related to this posting.'),
    'comment_node_prefix_default'           => '',
    'comment_node_suffix_default'           => '',
    'comment_enable_content_type'           => 0,
    'front_page_title_display'              => 'title_slogan',
    'page_title_display_custom'             => '',
    'other_page_title_display'              => 'ptitle_slogan',
    'other_page_title_display_custom'       => '',
    'configurable_separator'                => ' | ',
    'meta_keywords'                         => '',
    'meta_description'                      => '',
    'rebuild_registry'                      => 0,
    'block_editing'                         => 1,
  );
    
  // Make the default content-type settings the same as the default theme settings,
  // so we can tell if content-type-specific settings have been altered.
  $defaults = array_merge($defaults, theme_get_settings());

  // Set the default values for content-type-specific settings
  foreach ($node_types as $type => $name) {
    $defaults["submitted_by_author_{$type}"]      = $defaults['submitted_by_author_default'];
    $defaults["submitted_by_date_{$type}"]        = $defaults['submitted_by_date_default'];
    $defaults["taxonomy_display_{$type}"]         = $defaults['taxonomy_display_default'];
    $defaults["taxonomy_format_{$type}"]          = $defaults['taxonomy_format_default'];
    $defaults["readmore_{$type}"]                 = $defaults['readmore_default'];
    $defaults["readmore_title_{$type}"]           = $defaults['readmore_title_default'];
    $defaults["readmore_prefix_{$type}"]          = $defaults['readmore_prefix_default'];
    $defaults["readmore_suffix_{$type}"]          = $defaults['readmore_suffix_default'];
    $defaults["comment_singular_{$type}"]         = $defaults['comment_singular_default'];
    $defaults["comment_plural_{$type}"]           = $defaults['comment_plural_default'];
    $defaults["comment_title_{$type}"]            = $defaults['comment_title_default'];
    $defaults["comment_prefix_{$type}"]           = $defaults['comment_prefix_default'];
    $defaults["comment_suffix_{$type}"]           = $defaults['comment_suffix_default'];
    $defaults["comment_new_singular_{$type}"]     = $defaults['comment_new_singular_default'];
    $defaults["comment_new_plural_{$type}"]       = $defaults['comment_new_plural_default'];
    $defaults["comment_new_title_{$type}"]        = $defaults['comment_new_title_default'];
    $defaults["comment_new_prefix_{$type}"]       = $defaults['comment_new_prefix_default'];
    $defaults["comment_new_suffix_{$type}"]       = $defaults['comment_new_suffix_default'];
    $defaults["comment_add_{$type}"]              = $defaults['comment_add_default'];
    $defaults["comment_add_title_{$type}"]        = $defaults['comment_add_title_default'];
    $defaults["comment_add_prefix_{$type}"]       = $defaults['comment_add_prefix_default'];
    $defaults["comment_add_suffix_{$type}"]       = $defaults['comment_add_suffix_default'];
    $defaults["comment_node_{$type}"]             = $defaults['comment_node_default'];
    $defaults["comment_node_title_{$type}"]       = $defaults['comment_node_title_default'];
    $defaults["comment_node_prefix_{$type}"]      = $defaults['comment_node_prefix_default'];
    $defaults["comment_node_suffix_{$type}"]      = $defaults['comment_node_suffix_default'];
  }

  // Get default theme settings.
  $settings = theme_get_settings($theme_key);

  // If content type-specifc settings are not enabled, reset the values
  if (!$settings['readmore_enable_content_type']) {
    foreach ($node_types as $type => $name) {
      $settings["readmore_{$type}"]                    = $settings['readmore_default'];
      $settings["readmore_title_{$type}"]              = $settings['readmore_title_default'];
      $settings["readmore_prefix_{$type}"]             = $settings['readmore_prefix_default'];
      $settings["readmore_suffix_{$type}"]             = $settings['readmore_suffix_default'];
    }
  }
  if (!$settings['comment_enable_content_type']) {
    foreach ($node_types as $type => $name) {
      $defaults["comment_singular_{$type}"]         = $defaults['comment_singular_default'];
      $defaults["comment_plural_{$type}"]           = $defaults['comment_plural_default'];
      $defaults["comment_title_{$type}"]            = $defaults['comment_title_default'];
      $defaults["comment_prefix_{$type}"]           = $defaults['comment_prefix_default'];
      $defaults["comment_suffix_{$type}"]           = $defaults['comment_suffix_default'];
      $defaults["comment_new_singular_{$type}"]     = $defaults['comment_new_singular_default'];
      $defaults["comment_new_plural_{$type}"]       = $defaults['comment_new_plural_default'];
      $defaults["comment_new_title_{$type}"]        = $defaults['comment_new_title_default'];
      $defaults["comment_new_prefix_{$type}"]       = $defaults['comment_new_prefix_default'];
      $defaults["comment_new_suffix_{$type}"]       = $defaults['comment_new_suffix_default'];
      $defaults["comment_add_{$type}"]              = $defaults['comment_add_default'];
      $defaults["comment_add_title_{$type}"]        = $defaults['comment_add_title_default'];
      $defaults["comment_add_prefix_{$type}"]       = $defaults['comment_add_prefix_default'];
      $defaults["comment_add_suffix_{$type}"]       = $defaults['comment_add_suffix_default'];
      $defaults["comment_node_{$type}"]             = $defaults['comment_node_default'];
      $defaults["comment_node_title_{$type}"]       = $defaults['comment_node_title_default'];
      $defaults["comment_node_prefix_{$type}"]      = $defaults['comment_node_prefix_default'];
      $defaults["comment_node_suffix_{$type}"]      = $defaults['comment_node_suffix_default'];
    }
  }
   
  // Don't save the toggle_node_info_ variables
  if (module_exists('node')) {
    foreach (node_get_types() as $type => $name) {
      unset($settings['toggle_node_info_'. $type]);
    }
  }
  // Save default theme settings
  variable_set(
    str_replace('/', '_', 'theme_'. $theme_key .'_settings'),
    array_merge($defaults, $settings)
  );
  // Force refresh of Drupal internals
  theme_get_setting('', TRUE);
}

/**
 * Modify theme variables
 */

function phptemplate_preprocess_page(&$vars) {
  // Hook into color.module
  if (module_exists('color')) {
    _color_page_alter($vars);
  }
  
  // Add conditional stylesheets.
  if (!module_exists('conditional_styles')) {
    $vars['styles'] .= $vars['conditional_styles'] = variable_get('conditional_styles_' . $GLOBALS['theme'], '');
  }

  // Display mission statement on all pages
  if (theme_get_setting('mission_statement_pages') == 'all') {
    $vars['mission'] = theme_get_setting('mission', false);  
  }
 
  // Set site title, slogan, mission, page title & separator
  $title = t(variable_get('site_name', ''));
  $slogan = t(variable_get('site_slogan', ''));
  $mission = t(variable_get('site_mission', ''));
  $page_title = t(drupal_get_title());
  $title_separator = theme_get_setting('configurable_separator');
  if (drupal_is_front_page()) {                                                // Front page title settings
    switch (theme_get_setting('front_page_title_display')) {
      case 'title_slogan':
        $vars['head_title'] = drupal_set_title($title . $title_separator . $slogan);
        break;
      case 'slogan_title':
        $vars['head_title'] = drupal_set_title($slogan . $title_separator . $title);
        break;
      case 'title_mission':
        $vars['head_title'] = drupal_set_title($title . $title_separator . $mission);
        break;
      case 'custom':
        if (theme_get_setting('page_title_display_custom') !== '') {
          $vars['head_title'] = drupal_set_title(t(theme_get_setting('page_title_display_custom')));
        }
    }
  }
  else {                                                                       // Non-front page title settings
    switch (theme_get_setting('other_page_title_display')) {
      case 'ptitle_slogan':
        $vars['head_title'] = drupal_set_title($page_title . $title_separator . $slogan);
        break;
      case 'ptitle_stitle':
        $vars['head_title'] = drupal_set_title($page_title . $title_separator . $title);
        break;
      case 'ptitle_smission':
        $vars['head_title'] = drupal_set_title($page_title . $title_separator . $mission);
        break;
      case 'ptitle_custom':
        if (theme_get_setting('other_page_title_display_custom') !== '') {
          $vars['head_title'] = drupal_set_title($page_title . $title_separator . t(theme_get_setting('other_page_title_display_custom')));
        }
        break;
      case 'custom':
        if (theme_get_setting('other_page_title_display_custom') !== '') {
          $vars['head_title'] = drupal_set_title(t(theme_get_setting('other_page_title_display_custom')));
        }
    }
  }
  $vars['head_title'] = strip_tags($vars['head_title']);                       // Remove any potential html tags
  
	// Add meta tag on all pages
  if (!module_exists('nodewords')) {
    if (theme_get_setting('meta_keywords') !== '') {
      $keywords = '<meta name="keywords" content="'. theme_get_setting('meta_keywords') .'" />';
      $vars['head'] .= $keywords ."\n";
    } 
    if (theme_get_setting('meta_description') !== '') {
      $keywords = '<meta name="description" content="'. theme_get_setting('meta_description') .'" />';
      $vars['head'] .= $keywords ."\n";
    } 
  }

}

function phptemplate_preprocess_node(&$vars) {
  // Build array of handy node classes
  $node_classes = array();
  $node_classes[] = $vars['zebra'];                                      // Node is odd or even
  $node_classes[] = (!$vars['node']->status) ? 'node-unpublished' : '';  // Node is unpublished
  $node_classes[] = ($vars['sticky']) ? 'sticky' : '';                   // Node is sticky
  $node_classes[] = (isset($vars['node']->teaser)) ? 'teaser' : 'full-node';    // Node is teaser or full-node
  $node_classes[] = 'node-type-'. $vars['node']->type;                   // Node is type-x, e.g., node-type-page
  $node_classes = array_filter($node_classes);                           // Remove empty elements
  $vars['node_classes'] = implode(' ', $node_classes);                   // Implode class list with spaces
  
  // Add node_bottom region content
  $vars['node_bottom'] = theme('blocks', 'node_bottom');

  // Node Theme Settings
  
  // Date & author
  $date = format_date($vars['node']->created, 'medium');                 // Format date as small, medium, or large
  $author = theme('username', $vars['node']);
  $author_only_separator = t('Posted by ');
  $author_date_separator = t(' By ');
  $submitted_by_content_type = (theme_get_setting('submitted_by_enable_content_type') == 1) ? $vars['node']->type : 'default';
  $date_setting = (theme_get_setting('submitted_by_date_'. $submitted_by_content_type) == 1);
  $author_setting = (theme_get_setting('submitted_by_author_'. $submitted_by_content_type) == 1);
  $author_separator = ($date_setting) ? $author_date_separator : $author_only_separator;
  $date_author = ($author_setting) ? '<span>' . $author_separator . $author . '</span>' : '';
  $date_author .= ($date_setting) ? $date : '';
  $vars['submitted'] = $date_author;

  // Taxonomy
  $taxonomy_content_type = (theme_get_setting('taxonomy_enable_content_type') == 1) ? $vars['node']->type : 'default';
  $taxonomy_display = theme_get_setting('taxonomy_display_'. $taxonomy_content_type);
  $taxonomy_format = theme_get_setting('taxonomy_format_'. $taxonomy_content_type);
  if ((module_exists('taxonomy')) && ($taxonomy_display == 'all' || ($taxonomy_display == 'only' && $vars['page']))) {
    $vocabularies = taxonomy_get_vocabularies($vars['node']->type);
    $output = '';
    $vocab_delimiter = '';
    foreach ($vocabularies as $vocabulary) {
      if (theme_get_setting('taxonomy_vocab_display_'. $taxonomy_content_type .'_'. $vocabulary->vid) == 1) {
        $terms = taxonomy_node_get_terms_by_vocabulary($vars['node'], $vocabulary->vid);
        if ($terms) {
          $output .= ($taxonomy_format == 'vocab') ? '<li class="vocab vocab-'. $vocabulary->vid .'"><span class="indicator"></span><span class="vocab-name">'. $vocabulary->name .':</span> <ul class="vocab-list">' : '<span class="indicator"></span>';
          $links = array();
          foreach ($terms as $term) {        
            $links[] = '<li class="vocab-term">'. l($term->name, taxonomy_term_path($term), array('attributes' => array('rel' => 'tag', 'title' => strip_tags($term->description)))) .'</li>';        
          }
          if ($taxonomy_format == 'list') {
            $output .= $vocab_delimiter;    // Add comma between vocabularies
            $vocab_delimiter = ', ';        // Use a comma delimiter after first displayed vocabulary
          }
          $output .= implode(", ", $links);
          $output .= ($taxonomy_format == 'vocab') ? '</ul></li>' : '';
        }
      }
    }
    if ($output != '') {
      $output = '<ul class="taxonomy">'. $output .'</ul>';
    }
    $vars['terms'] = $output;
  }
  else {
    $vars['terms'] = '';
  }
  
  // Node Links
  if (isset($vars['node']->links['node_read_more'])) {
    $node_content_type = (theme_get_setting('readmore_enable_content_type') == 1) ? $vars['node']->type : 'default';
    $vars['node']->links['node_read_more'] = array(
      'title' => _themesettings_link(
      theme_get_setting('readmore_prefix_'. $node_content_type),
      theme_get_setting('readmore_suffix_'. $node_content_type),
      theme_get_setting('readmore_'. $node_content_type),
      'node/'. $vars['node']->nid,
      array(
        'attributes' => array('title' => theme_get_setting('readmore_title_'. $node_content_type)), 
        'query' => NULL, 'fragment' => NULL, 'absolute' => FALSE, 'html' => TRUE
        )
      ),
      'attributes' => array('class' => 'readmore-item'),
      'html' => TRUE,
    );
  }
  if (isset($vars['node']->links['comment_add'])) {
    $node_content_type = (theme_get_setting('comment_enable_content_type') == 1) ? $vars['node']->type : 'default';
    if ($vars['teaser']) {
      $vars['node']->links['comment_add'] = array(
        'title' => _themesettings_link(
        theme_get_setting('comment_add_prefix_'. $node_content_type),
        theme_get_setting('comment_add_suffix_'. $node_content_type),
        theme_get_setting('comment_add_'. $node_content_type),
        "comment/reply/".$vars['node']->nid,
        array(
          'attributes' => array('title' => theme_get_setting('comment_add_title_'. $node_content_type)), 
          'query' => NULL, 'fragment' => 'respond', 'absolute' => FALSE, 'html' => TRUE
          )
        ),
        'attributes' => array('class' => 'comment-add-item'),
        'html' => TRUE,
      );
    }
    else {
      $vars['node']->links['comment_add'] = array(
        'title' => _themesettings_link(
        theme_get_setting('comment_node_prefix_'. $node_content_type),
        theme_get_setting('comment_node_suffix_'. $node_content_type),
        theme_get_setting('comment_node_'. $node_content_type),
        "comment/reply/".$vars['node']->nid,
        array(
          'attributes' => array('title' => theme_get_setting('comment_node_title_'. $node_content_type)), 
          'query' => NULL, 'fragment' => 'comment-form', 'absolute' => FALSE, 'html' => TRUE
          )
        ),
        'attributes' => array('class' => 'comment-node-item'),
        'html' => TRUE,
      );
    }
  }
  if (isset($vars['node']->links['comment_new_comments'])) {
    $node_content_type = (theme_get_setting('comment_enable_content_type') == 1) ? $vars['node']->type : 'default';
    $vars['node']->links['comment_new_comments'] = array(
      'title' => _themesettings_link(
        theme_get_setting('comment_new_prefix_'. $node_content_type),
        theme_get_setting('comment_new_suffix_'. $node_content_type),
        format_plural(
          comment_num_new($vars['node']->nid),
          theme_get_setting('comment_new_singular_'. $node_content_type),
          theme_get_setting('comment_new_plural_'. $node_content_type)
        ),
        "node/".$vars['node']->nid,
        array(
          'attributes' => array('title' => theme_get_setting('comment_new_title_'. $node_content_type)), 
          'query' => NULL, 'fragment' => 'new', 'absolute' => FALSE, 'html' => TRUE
        )
      ),
      'attributes' => array('class' => 'comment-new-item'),
      'html' => TRUE,
    );
  }
  if (isset($vars['node']->links['comment_comments'])) {
    $node_content_type = (theme_get_setting('comment_enable_content_type') == 1) ? $vars['node']->type : 'default';
    $vars['node']->links['comment_comments'] = array(
      'title' => _themesettings_link(
        theme_get_setting('comment_prefix_'. $node_content_type),
        theme_get_setting('comment_suffix_'. $node_content_type),
        format_plural(
          comment_num_all($vars['node']->nid),
          theme_get_setting('comment_singular_'. $node_content_type),
          theme_get_setting('comment_plural_'. $node_content_type)
        ),
        "node/".$vars['node']->nid,
        array(
          'attributes' => array('title' => theme_get_setting('comment_title_'. $node_content_type)), 
          'query' => NULL, 'fragment' => 'comments', 'absolute' => FALSE, 'html' => TRUE
        )
      ),
      'attributes' => array('class' => 'comment-item'),
      'html' => TRUE,
    );
  }
  // Separate out comment and read more link.
  $node = $vars['node'];
      
    if (isset($node->links['comment_comments'])) {
      $vars['comment_link'] = $node->links['comment_comments']['title'];
    }
    elseif (isset($node->links['comment_add'])) {
      $vars['comment_link'] = $node->links['comment_add']['title'];
    }
    if (isset($node->links['node_read_more'])) {
      $vars['node_read_more'] = $node->links['node_read_more']['title'];
    }

    // Delete comment links that are already added above.
    if (isset($node->links)) {
      $links = $node->links;
      if (isset($links['comment_comments'])) {
        unset($links['comment_comments']);
      }
      if (isset($links['comment_add'])) {
        unset($links['comment_add']);
      }
      if (isset($links['node_read_more'])) {
        unset($links['node_read_more']);
      }

        $vars['links'] = theme('links', $links, array('class' => 'links inline'));
      }
}

/**
 * Modify search results based on theme settings.
 */
function phptemplate_preprocess_search_result(&$variables) {
  static $search_zebra = 'even';
  $search_zebra = ($search_zebra == 'even') ? 'odd' : 'even';
  $variables['search_zebra'] = $search_zebra;
  
  $result = $variables['result'];
  $variables['url'] = check_url($result['link']);
  $variables['title'] = check_plain($result['title']);

  // Check for existence. User search does not include snippets.
  $variables['snippet'] = '';
  if (isset($result['snippet']) && theme_get_setting('search_snippet')) {
    $variables['snippet'] = $result['snippet'];
  }
  
  $info = array();
  if (!empty($result['type']) && theme_get_setting('search_info_type')) {
    $info['type'] = check_plain($result['type']);
  }
  if (!empty($result['user']) && theme_get_setting('search_info_user')) {
    $info['user'] = $result['user'];
  }
  if (!empty($result['date']) && theme_get_setting('search_info_date')) {
    $info['date'] = format_date($result['date'], 'small');
  }
  if (isset($result['extra']) && is_array($result['extra'])) {
    // $info = array_merge($info, $result['extra']);  Drupal bug?  [extra] array not keyed with 'comment' & 'upload'
    if (!empty($result['extra'][0]) && theme_get_setting('search_info_comment')) {
      $info['comment'] = $result['extra'][0];
    }
    if (!empty($result['extra'][1]) && theme_get_setting('search_info_upload')) {
      $info['upload'] = $result['extra'][1];
    }
  }

  // Provide separated and grouped meta information.
  $variables['info_split'] = $info;
  $variables['info'] = implode(' - ', $info);

  // Provide alternate search result template.
  $variables['template_files'][] = 'search-result-'. $variables['type'];
}


/**
 * Override or insert variables into the block templates.
 *
 * @param $vars
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("block" in this case.)
 */
function phptemplate_preprocess_block(&$vars, $hook) {
  $block = $vars['block'];

  // Special classes for blocks.
  $classes = array('block');
  $classes[] = 'block-' . $block->module;
  $classes[] = 'region-' . $vars['block_zebra'];
  $classes[] = $vars['zebra'];
  $classes[] = 'region-count-' . $vars['block_id'];
  $classes[] = 'count-' . $vars['id'];

  $vars['edit_links_array'] = array();
  $vars['edit_links'] = '';
  if (theme_get_setting('block_editing') && user_access('administer blocks')) {
    include_once './' . drupal_get_path('theme', 'magazeen') . '/include/template.block-editing.inc';
    zen_preprocess_block_editing($vars, $hook);
    $classes[] = 'with-block-editing';
  }

  // Render block classes.
  $vars['classes'] = implode(' ', $classes);
}

/**
 * Override or insert variables into the comment templates.
 *
 * @param $vars
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("comment" in this case.)
 */
function phptemplate_preprocess_comment(&$vars, $hook) {
  include_once './' . drupal_get_path('theme', 'magazeen') . '/include/template.comment.inc';
  _zen_preprocess_comment($vars, $hook);
}

/**
 * Return a themed breadcrumb trail.
 *
 * @param $breadcrumb
 *   An array containing the breadcrumb links.
 * @return
 *   A string containing the breadcrumb output.
 */

function phptemplate_breadcrumb($breadcrumb) {
  // Determine if we are to display the breadcrumb
  $show_breadcrumb = theme_get_setting('breadcrumb_display');
  if ($show_breadcrumb == 'yes' || $show_breadcrumb == 'admin' && arg(0) == 'admin') {

    // Optionally get rid of the homepage link
    $show_breadcrumb_home = theme_get_setting('breadcrumb_home');
    if (!$show_breadcrumb_home) {
      array_shift($breadcrumb);
    }

    // Return the breadcrumb with separators
    if (!empty($breadcrumb)) {
      $breadcrumb_separator = theme_get_setting('breadcrumb_separator');
      $trailing_separator = (theme_get_setting('breadcrumb_trailing') || theme_get_setting('breadcrumb_title')) ? $breadcrumb_separator : '';
      return '<div class="breadcrumb">' . implode($breadcrumb_separator, $breadcrumb) . "$trailing_separator</div>";
    }
  }
  // Otherwise, return an empty string
  return '';
}

/**
 * Override username theming to display/hide 'not verified' text.
 */
function phptemplate_username($object) {
  if ($object->uid && $object->name) {
    // Shorten the name when it is too long or it will break many tables.
    if (drupal_strlen($object->name) > 20) {
      $name = drupal_substr($object->name, 0, 15) .'...';
    }
    else {
      $name = $object->name;
    }
    if (user_access('access user profiles')) {
      $output = l($name, 'user/'. $object->uid, array('attributes' => array('title' => t('View user profile.'))));
    }
    else {
      $output = check_plain($name);
    }
  }
  else if ($object->name) {
    // Sometimes modules display content composed by people who are
    // not registered members of the site (e.g. mailing list or news
    // aggregator modules). This clause enables modules to display
    // the true author of the content.
    if (!empty($object->homepage)) {
      $output = l($object->name, $object->homepage, array('attributes' => array('rel' => 'nofollow')));
    }
    else {
      $output = check_plain($object->name);
    }
    // Display or hide 'not verified' text
    if (theme_get_setting('user_notverified_display') == 1) {
      $output .= ' ('. t('not verified') .')';
    }
  }
  else {
    $output = variable_get('anonymous', t('Anonymous'));
  }
  return $output;
}

/**
  * Theme override for search form.
  * Paste this in the template.php file of your theme
  * more infos : lullabot.com/articles/modifying-forms-5-and-6
  * Here is where you can modify the selected form
  */

function phptemplate_search_theme_form($form) {
  // this line deactivate the 'search this site' label - you can change/delete this
  unset($form['search_theme_form']['#title']);

  // Set a default value in the search box, you can change 'search' to whatever you want - you can change/delete this
  $search_text = theme_get_setting('search_text');      
  $form['search_theme_form']['#value'] = $search_text;

  // Additionnaly, hide the text when editing - you can change/delete this
  // Remember to change the value 'search' here too if you change it in the previous line
  $form['search_theme_form']['#attributes'] = array('onblur' => "if (this.value == '') {this.value = '" . $search_text . "';}", 'onfocus' => "if (this.value == '" . $search_text . "') {this.value = '';}" );

  // Set the submit button to an image button
  $form['submit'] = array('#id' => 'search-submit','#name' => 'search-submit', '#type' => 'image_button', '#src'  => path_to_theme() .'/images/search.png');    
  
  // Don't change this
  $output .= drupal_render($form);

  return $output;
}

/**
 * Overwrite RSS feed.
 */
function phptemplate_feed_icon($url) {
	$title = t('Subscribe to RSS');
  if ($image = theme('image', drupal_get_path('theme', 'magazeen') . '/images/rss.png', $title, $title)) {
    return '<a href="'. check_url($url) .'" class="feed-icon">'. $image. '</a>';
  }
}

/**
 * Allow themable wrapping of all comments.
 */
function phptemplate_comment_wrapper($content, $node) {
  $comment_count = format_plural($node->comment_count, '1 Comment', '@count Comments');
  $no_comment_message = theme_get_setting('no_comment_message');
  $no_comment .= ($node->comment_count == 0) ? '<div class="comment first odd"><div class="comment-inner clear-block"><p>' . $no_comment_message . '</p></div></div>' : '';
  if (!$content || $node->type == 'forum') {
    return '<div id="comments"><div class="comment-content">'. $content .'</div></div>';
  }
  else {
    return '<div id="comments"><div class="commentlist clearfix"><div class="comment-count"><a href="#comments">'. $comment_count .'</a></div>'. $no_comment . $content .'</div></div>';
  }
}
/**
 * Override or insert variables into the box templates.
 *
 * @param $vars
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("box" in this case.)
 */
function magazeen_preprocess_box(&$vars) {
	if (arg(0) == 'node' || arg(0) == 'comment') {
	$comment_title = theme_get_setting('comment_title');
	$output = '<div class="post-meta clearfix"><h3 id="respond" class="post-title-small left">' . $comment_title . '</h3><p class="post-info right"></p></div>';
		$vars['title'] = $output;
	}
}

/**
 * Implements HOOK_theme().
 * Theme FORM.
 */
function magazeen_theme(&$existing, $type, $theme, $path){
  // Compute the conditional stylesheets.
  if (!module_exists('conditional_styles')) {
    include_once './' . drupal_get_path('theme', 'magazeen') . '/include/template.conditional-styles.inc';
    // _conditional_styles_theme() only needs to be run once.
    if ($theme == 'magazeen') {
      _conditional_styles_theme($existing, $type, $theme, $path);
    }
  }

  // If we are auto-rebuilding the theme registry, warn about the feature.
  // Always display the warning in the admin section, otherwise limit to three
  // warnings per hour.
  if (user_access('administer site configuration') && theme_get_setting('rebuild_registry') && $theme == $GLOBALS['theme'] && (arg(0) == 'admin' || flood_is_allowed($GLOBALS['theme'] . '_rebuild_registry_warning', 3))) {
    flood_register_event($GLOBALS['theme'] . '_rebuild_registry_warning');
    drupal_set_message(t('For easier theme development, the theme registry is being rebuilt on every page request. It is <em>extremely</em> important to <a href="!link">turn off this feature</a> on production websites.', array('!link' => url('admin/build/themes/settings/' . $GLOBALS['theme']))), 'warning', FALSE);
  }

  return array(
    // The form ID.
    'comment_form' => array(
      // Forms always take the form argument.
      'arguments' => array('form' => NULL),
    ),
  );
}

/**
 * Theme override for commment form.
 */
function magazeen_comment_form($form) {
  $output = '';
    foreach (element_children($form) as $key) {
      if (isset($form[$key]) && isset($form[$key]['#type']) && $form[$key]['#type'] == 'textfield') {
        $form[$key]['#comments_element'] = TRUE;
        $form[$key]['#size'] = 40;
      }
    }
    if (isset($form['_author'])) {
      $form['_author']['#type'] = 'markup';
      $form['_author']['#value'] = t('Logged in as !user.', array('!user' => $form['_author']['#value']));
    }

    $form['comment_filter']['comment']['#rows'] = 10;
    unset($form['comment_filter']['comment']['#title']);

  // You can use the normal Form API structure to change things, like so:
  // Change the Username field title to Login ID.
  $form['name']['#title'] = t('Name');
  $form['homepage']['#title'] = t('Website');
  // Make sure you call a drupal_render() on the entire $form to make sure you
  // still output all of the elements (particularly hidden ones needed
  // for the form to function properly.)

  $output .= '<div class="post-box"><div class="post">';
  $output .= drupal_render($form);
  $output .= '</div></div>';

  return $output;
}
  
function phptemplate_form_element($element, $value) {
  if (empty($element['#comments_element'])) {
    return theme_form_element($element, $value);
  }
  else {
    $t = get_t();

    $output = '<div class="form-item container-inline comments-element"';
    if (!empty($element['#id'])) {
      $output .= ' id="'. $element['#id'] .'-wrapper"';
    }
    $output .= ">\n";
    $output .= " $value\n";

    $required = !empty($element['#required']) ? '<span class="form-required" title="'. $t('This field is required.') .'">('. $t('required') .')</span>' : '';

    if (!empty($element['#title'])) {
      $title = $element['#title'];
      if (!empty($element['#id'])) {
        $output .= ' <label for="'. $element['#id'] .'"><small>'. $t('!title !required', array('!title' => filter_xss_admin($title), '!required' => $required)) ."</small></label>\n";
      }
      else {
        $output .= ' <label><small>'. $t('!title !required', array('!title' => filter_xss_admin($title), '!required' => $required)) ."</small></label>\n";
      }
    }
  if (!empty($element['#description'])) {
    $output .= ' <div class="description">'. $element['#description'] ."</div>\n";
  }

    $output .= "</div>\n";

    return $output;
  }
}

/**
 * Creates a link with prefix and suffix text
 *
 * @param $prefix
 *   The text to prefix the link.
 * @param $suffix
 *   The text to suffix the link.
 * @param $text
 *   The text to be enclosed with the anchor tag.
 * @param $path
 *   The Drupal path being linked to, such as "admin/content/node". Can be an external
 *   or internal URL.
 *     - If you provide the full URL, it will be considered an
 *   external URL.
 *     - If you provide only the path (e.g. "admin/content/node"), it is considered an
 *   internal link. In this case, it must be a system URL as the url() function
 *   will generate the alias.
 * @param $options
 *   An associative array that contains the following other arrays and values
 *     @param $attributes
 *       An associative array of HTML attributes to apply to the anchor tag.
 *     @param $query
 *       A query string to append to the link.
 *     @param $fragment
 *       A fragment identifier (named anchor) to append to the link.
 *     @param $absolute
 *       Whether to force the output to be an absolute link (beginning with http:).
 *       Useful for links that will be displayed outside the site, such as in an RSS
 *       feed.
 *     @param $html
 *       Whether the title is HTML or not (plain text)
 * @return
 *   an HTML string containing a link to the given path.
 */
function _themesettings_link($prefix, $suffix, $text, $path, $options) {
  return $prefix . (($text) ? l($text, $path, $options) : '') . $suffix;
}