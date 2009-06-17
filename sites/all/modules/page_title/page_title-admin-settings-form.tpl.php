<?php
$rows = array();

foreach (element_children($form['pattern']) as $key) {
  $title = array(
    '#type' => 'item',
    '#title' => $form['pattern'][$key]['#title'],
    '#required' => $form['pattern'][$key]['#required'],
  );
  unset($form['pattern'][$key]['#title']);

  $row = array(
    drupal_render($title),
    drupal_render($form['scope'][$key]),
    drupal_render($form['pattern'][$key]),
    isset($form['showfield'][$key .'_showfield']) ? drupal_render($form['showfield'][$key .'_showfield']) : '',
  );

  $rows[] = $row;
}

print theme('table', array(t('Page Type'), t('Token Scope'), t('Pattern'), t('Show Field')), $rows);

print drupal_render($form);
