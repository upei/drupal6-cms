<?php
// $Id: openflashchart.inc,v 1.9 2009/05/15 05:30:53 brmassa Exp $
/**
 * @author Bruno Massa http://drupal.org/user/67164
 * @file
 * Use Open Flash Chart on your site.
 */

/**
 * Convert all Chart-level data.
 *
 * @param &$chart
 *   Object. The Open Flash Chart object
 * @param &$data
 *   Array. The raw data.
 */
function _openflashchart_chart(&$chart, &$data) {
  $chart->set_title($data['#title']);
  $chart->set_width($data['#width']);
  $chart->set_height($data['#height']);
  $chart->set_bg_colour($data['#color']['#background']);
}

/**
 * Implementation of hook_charts_render().
 *
 * Its a Charts module hook. It transform the data into a HTML chart.
 *
 * @param &$data
 *   Array. The
 */
function _openflashchart_charts_render(&$data) {
  $chart = new open_flash_chart_api();

  if ($error = _openflashchart_chart($chart, $data)) {
    return $error;
  }

  if ($error = _openflashchart_series($chart, $data)) {
    return $error;
  }

  return $chart->render();
}

/**
 * Convert all Series-level data.
 *
 * @param &$chart
 *   Object. The Open Flash Chart object
 * @param &$data
 *   Array. The raw data.
 */
function _openflashchart_series(&$chart, &$data) {
  foreach (element_children($data) as $series) {
    // Get the color
    $color = empty($data[$series]['#color']) ? '' : $data[$series]['#color'];

    switch ($data['#type']) {
      case 'line2D':
        $chart->line(1, $color);
        break;

      case 'vbar2D':
        $chart->bar(75, $color);
        break;

      case 'vbar3D':
        $chart->bar_3D(75, $color);
        break;

      case 'pie2D':
        $chart->pie(75, '#000000', 'font-size: 12px;');
        break;

      default:
        return t('This type is not possible using %chartplugin',
          array('%chartplugin' => 'Open Flash Chart'));
    }

    // Insert a new series of values
    if ($data['#type'] != 'pie2D') {
      _openflashchart_series_generic($chart, $data, $series);
    }
    elseif (empty($series)) {
      _openflashchart_series_pie($chart, $data, $series);
    }
  }
}

function _openflashchart_series_generic(&$chart, &$data, $series) {
  static $max;

  // Get only the numeric values from the series
  $series_data = _charts_series_values($data[$series]);

  $chart->set_data($series_data);

  // Get the highest value on the series, to be a reference point
  $max = $max < max($series_data) ? max($series_data) : $max;

  // Y labels
  $chart->set_y_max($max);

  // X labels
  $value_labels = array();
  $toogle = FALSE;
  foreach (array_keys($series_data) as $value) {
    if (empty($data[$series][$value]['#label'])) {
      $value_labels[] = '';
    }
    else {
      $value_labels[] = $data[$series][$value]['#label'];
      $toogle = TRUE;
    }
  }
  if (!empty($toogle)) {
    $chart->set_x_labels($value_labels);
  }
}

function _openflashchart_series_pie(&$chart, &$data, $series) {
  // Get only the numeric values from the series
  $series_data = _charts_series_values($data[$series]);

  if (empty($series)) {
    // Pieces labels
    $value_labels = array();
    foreach (array_keys($series_data) as $value) {
      if (empty($data[$series][$value]['#label'])) {
        $value_labels[] = '';
      }
      else {
        $value_labels[] = $data[$series][$value]['#label'];
      }

      $color[] = $data[$series][$value]['#color'];
    }

    $chart->pie_values($series_data, $value_labels, array());

    $chart->pie_slice_colours($color);
  }
}
