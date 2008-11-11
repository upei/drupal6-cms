<?php
// $Id: threecol_25_50_25.inc,v 1.1 2008/07/23 21:14:28 merlinofchaos Exp $

/**
 * implementation of hook_panels_layouts
 */
function panels_threecol_25_50_25_panels_layouts() {
  $items['threecol_25_50_25'] = array(
    'title' => t('Three column 25/50/25'),
    'icon' => 'threecol_25_50_25.png',
    'theme' => 'panels_threecol_25_50_25',
    'theme arguments' => array('id', 'content'),
    'panels' => array(
      'left' => t('Left side'),
      'middle' => t('Middle column'),
      'right' => t('Right side')
    ),
  );

  return $items;
}

