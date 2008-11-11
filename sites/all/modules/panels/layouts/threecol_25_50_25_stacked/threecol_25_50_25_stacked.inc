<?php
// $Id: threecol_25_50_25_stacked.inc,v 1.1 2008/07/23 21:14:28 merlinofchaos Exp $

/**
 * Implementation of hook_panels_layouts()
 */
function panels_threecol_25_50_25_stacked_panels_layouts() {
  $items['threecol_25_50_25_stacked'] = array(
    'title' => t('Three column 25/50/25 stacked'),
    'icon' => 'threecol_25_50_25_stacked.png',
    'theme' => 'panels_threecol_25_50_25_stacked',
    'css' => 'threecol_25_50_25_stacked.css',
    'panels' => array(
      'top' => t('Top'),
      'left' => t('Left side'),
      'middle' => t('Middle column'),
      'right' => t('Right side'),
      'bottom' => t('Bottom'),
    ),
  );

  return $items;
}
