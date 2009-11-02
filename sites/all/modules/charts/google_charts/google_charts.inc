<?php
// $Id: google_charts.inc,v 1.18 2009/05/15 04:48:24 brmassa Exp $
/**
 * @author Bruno Massa http://drupal.org/user/67164
 * @file
 * Use Google Charts on your site.
 */

function _google_charts($type) {
  $types = array(
    'line2D'  => array('legend' => TRUE, 'typecode' => 'lc', 'value_attributes' => FALSE),
    'hbar2D'  => array('legend' => TRUE, 'typecode' => 'bhg', 'value_attributes' => FALSE),
    'vbar2D'  => array('legend' => TRUE, 'typecode' => 'bvg', 'value_attributes' => FALSE),
    'pie2D'   => array('legend' => FALSE, 'typecode' => 'p', 'value_attributes' => TRUE),
    'pie3D'   => array('legend' => FALSE, 'typecode' => 'p3', 'value_attributes' => TRUE),
    'venn'    => array('legend' => TRUE, 'typecode' => 'v', 'value_attributes' => FALSE),
    'scatter' => array('legend' => FALSE, 'typecode' => 's', 'value_attributes' => FALSE),
  );
  return $types[$type];
}

/**
 * Convert all Chart-level data.
 *
 * @param &$chart
 *   Array. The array that will be converted into a string for Google Charts
 * @param &$data
 *   Array. The raw data.
 * @return
 *   String. The string presentation of series data
 */
function _google_charts_chart(&$chart, &$data) {
  // Convert the chat TYPE into the Google Chart way.
  // Since its a requirement to build the chart on Google, if the value
  // was not found, return nothing and stop the execution.
  $options = _google_charts($data['#type']);
  if (empty($options['typecode'])) {
    return t('This type is not possible using %chartplugin',
      array('%chartplugin' => 'Google Chart'));
  }
  if ($data['#type'] == 'pie2D' and count(element_children($data)) > 1) {
    $chart[] = 'cht=pc';
  }
  else {
    $chart[] = 'cht='. $options['typecode'];
  }

  // Convert the chat SIZE into the Google Chart way.
  // Since its a requirement to build the chart on Google, if the value
  // was not found, return nothing and stop the execution.
  if (empty($data['#width']) or empty($data['#height'])) {
    return t('Height and Width are required');
  }
  $chart[] = 'chs='. $data['#width'] .'x'. $data['#height'];

  // Add Title and Description to the chart
  if (!empty($data['#title'])) {
    $chart[] = 'chtt='. $data['#title'];
  }

  // Chart background color. Since the default color
  // is white (#ffffff), only different colors are considered
  if (!empty($data['#color']['background']) and $data['#color']['background'] != '#ffffff') {
    $chart[] = 'chf=bg,s,'. substr($data['#color']['background'], 1);
  }

  return;
}

/**
 * Encode the Chart data into a Alphanumeric code, follwing the
 * Google Chart API instruction. Its needed because there is a
 * size limmit to URL strings. So we reduce the amount of characters.
 *
 * It basicly uses a scale of 61 levels to represent each chart
 * value. If a more precise scale is needed, see
 * _google_charts_codingextended(), which produces a 4000 levels,
 * but also a bigger URL string.
 *
 * @param $data
 *   Array. A series of numeric data values
 * @return
 *   String. The string presentation of series data
 */
function _google_charts_data_codingsimple($value, $max) {
  // Set the list of characters and the size of the list
  $simple = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789';
  $simple_len = drupal_strlen($simple) - 1;

  if ($value >= 0) {
    return $simple[round($simple_len * $value / $max)];
  }
  else {
    return  '_';
  }
}

/**
 * Implementation of hook_charts_render().
 *
 * Its a Charts module hook. It transform the data into a HTML chart.
 *
 * @param &$data
 *   Array. The
 */
function _google_charts_render(&$data) {
  $chart = array();
  if ($message = _google_charts_chart($chart, $data)) {
    return $message;
  }

  // Convert the chat DATA into the Google Chart way.
  // Since its a requirement to build the chart on Google, if the value
  // was not found, return nothing and stop the execution.
  if ($message = _google_charts_series($chart, $data)) {
    return $message;
  }

  // If its all ok, build the HTML img tag
  return '<img src="http://chart.apis.google.com/chart?'. implode('&amp;', $chart) .'" />';
}

/**
 * Convert all Series-level data.
 *
 * @param &$chart
 *   Array. The array that will be converted into a string for Google Charts
 * @param &$data
 *   Array. The raw data.
 * @return
 *   String. The string presentation of series data
 */
function _google_charts_series(&$chart, &$data) {
  $options = _google_charts($data['#type']);

  // The final output is going to be build
  $chart_data = '';

  $value_labels = array();

  // For each chart value, encode it
  // Note: Underscore represents a missing value
  foreach (element_children($data) as $series) {
    // Include a series separator
    if (!empty($chart_data)) {
      $chart_data .= ',';
    }

    // Get only the numeric values from the series
    $series_data = _charts_series_values($data[$series]);

    // Get the highest value on the series, to be a reference point
    $max = max($series_data);

    // Value labels: temporary array.
    $value_labels_temp = array();

    // For each series of data, scan it
    foreach (array_keys($series_data) as $value) {
      $svalue = &$data[$series][$value];
      $chart_data .= _google_charts_data_codingsimple($series_data[$value], $max);

      $value_labels_temp[] = empty($svalue['#label']) ? NULL : $svalue['#label'];

      // Get the highlight points
      if (!empty($svalue['#highlight'])
          or ($data['#type'] == 'scatter' and ($series % 2 == 0))) {
        $highlight[] = 't'. $svalue['#label'] .','.
          (empty($svalue['#color']) ? substr($data[$series]['#color'], 1) : substr($svalue['#color'], 1)) .','.
          $series .','.
          $value .','.
          (empty($svalue['#size']) ? 10 : $svalue['#size']);
      }

      if ($options['value_attributes']
          or ($data['#type'] == 'scatter' and ($series % 2 == 0))) {
        // Series legends
        $value_labels[] = empty($svalue['#label']) ? NULL : $svalue['#label'];
      }
    }

    // Value labels
    if (!empty($value_labels_temp)) {
      $value_labels += $value_labels_temp;
    }

    if (empty($options['value_attributes'])) {
      // Series legends
      $legends[] = empty($data[$series]['#legend']) ? NULL : $data[$series]['#legend'];

      // Series colors
      $colors[] = empty($data[$series]['#color']) ? NULL : substr($data[$series]['#color'], 1);
    }
  }

  // Return the series of data
  if (empty($chart_data)) {
    return t('No enough data to create a chart.');
  }

   // Insert data
  $chart[] = 'chd=s:'. $chart_data;

  // Insert series color
  if (!empty($colors)) {
    $chart[] = 'chco='. implode(',', $colors);
  }

  // Insert values labels
  if (!empty($value_labels)) {
    $chart[] = 'chl='. implode('|', $value_labels);
  }


  // Insert multiple series tag
  if ($options['legend'] and !empty($legends)) {
    $chart[] = 'chdl='. implode('|', $legends);
  }

  // Insert values labels
  if (!empty($highlight)) {
    $chart[] = 'chm='. implode('|', $highlight);
  }

  return;
}
