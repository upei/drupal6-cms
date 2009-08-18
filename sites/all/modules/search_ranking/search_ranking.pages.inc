<?php
// $Id: search_ranking.pages.inc,v 1.4 2008/07/06 09:24:10 blucches Exp $

/**
 * @file
 * User page callbacks for search_ranking module.
 */
 
/**
 * More or less a copy of search_view().
 */
function search_ranking_view($type = 'search_ranking') {
  // Search form submits with POST but redirects to GET. This way we can keep
  // the search query URL clean as a whistle:
  // search/type/keyword+keyword
  if (!isset($_POST['form_id'])) {
    if ($type == '') {
      // Note: search/search_ranking can not be a default tab because it would
      // take on the path of its parent (search). It would prevent remembering
      // keywords when switching tabs. This is why we drupal_goto to it from
      // the parent instead.
      drupal_goto('search/node');
    }
    
    // Override the normal search for $type = 'node'
    $type = 'search_ranking';
    
    $keys = search_get_keys();
    // Only perform search if there is non-whitespace search term:
    $results = '';
    if (trim($keys)) {
      // Log the search keys:
      watchdog('search', '%keys (@type).', array('%keys' => $keys, '@type' => module_invoke($type, 'search', 'name')), WATCHDOG_NOTICE, l(t('results'), 'search/'. $type .'/'. $keys));

      // Collect the search results:
      $results = search_data($keys, $type);

      if ($results) {
        $results = theme('box', t('Search results'), $results);
      }
      else {
        $results = theme('box', t('Your search yielded no results'), search_help('search#noresults', drupal_help_arg()));
      }
    }

    // Construct the search form.
    $output = drupal_get_form('search_form', NULL, $keys, 'node');
    $output .= $results;

    return $output;
  }

  return drupal_get_form('search_form', NULL, empty($keys) ? '' : $keys, $type);
}