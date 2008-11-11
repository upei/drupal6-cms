<?php
// $Id: onecol.inc,v 1.1 2008/07/23 21:14:28 merlinofchaos Exp $

/**
 * implementation of hook_panels_layouts()
 */
function panels_onecol_panels_layouts() {
  $items['onecol'] = array(
    'title' => t('Single column'),
    'icon' => 'onecol.png',
    'theme' => 'panels_onecol',
    'css' => 'onecol.css',
    'panels' => array('middle' => t('Middle column')),
  );

  return $items;
}
