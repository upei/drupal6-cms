<?php
// $Id: twocol_stacked.inc,v 1.1 2008/07/23 21:14:29 merlinofchaos Exp $

/**
 * Implementation of hook_panels_layouts().
 */
function panels_twocol_stacked_panels_layouts() {
  $items['twocol_stacked'] = array(
    'title' => t('Two column stacked'),
    'icon' => 'twocol_stacked.png',
    'theme' => 'panels_twocol_stacked',
    'css' => 'twocol_stacked.css',
    'panels' => array(
      'top' => t('Top'),
      'left' => t('Left side'),
      'right' => t('Right side'),
      'bottom' => t('Bottom')
    ),
  );

  return $items;
}
