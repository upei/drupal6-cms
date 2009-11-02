<?php
// $Id: fusioncharts.inc,v 1.10.2.1 2009/07/14 02:40:43 brmassa Exp $
/**
 * @author Bruno Massa http://drupal.org/user/67164
 * @file
 * Use FusionCharts on your site.
 */

/**
 * Create the values object using FusionCharts
 *
 * @param $type
 *   String. The data type. It can be 'category', 'set' or 'trendline'
 * @param $data
 *   Array. The data to be converted to XML
 * @param $options
 *   Array (optional). Data options
 * @return
 *   Array, the XML array
 */
function _fusioncharts_values($type, $data, $options = array()) {
  switch ($type) {
    case 'category':
      $attr         = 'label';
      $global_type  = 'categories';
    break;
    case 'set':
      $attr         = 'value';
      $global_type  = 'dataSet';
    break;
    case 'trendline':
      $attr         = 'value';
      $global_type  = 'trendlines';
    break;
  }

  // Create each value.
  $values = array();
  while (list(, $value) = each($data)) {
    if (is_array($value)) {
      $values[] = array('key' => $type, 'attributes' => $value);
    }
    else {
      $values[] = array('key' => $type, 'attributes' => array($attr => $value));
    }
  }

  // Create the XML array
  if (empty($options['no_wrap'])) {
    return array(
      'key'         => $global_type,
      'value'       => $values,
      'attributes'  => $options
    );
  }
  else {
    return $values;
  }
}

/**
 * Convert all Chart-level data.
 *
 * @param &$chart
 *   Array. The array that will be converted into a string for FusionCharts
 * @param &$data
 *   Array. The raw data.
 * @return
 *   String. The string presentation of series data
 */
function _fusioncharts_chart(&$chart, &$data) {
  $chart['attributes']['bgColor'] = $data['#color']['background'];
  if (isset($data['#title'])) {
    $chart['attributes']['caption'] = $data['#title'];
  }
  $chart['attributes']['animation'] = '0';
}

/**
 * Implementation of hook_charts_render().
 *
 * Its a Charts module hook. It transform the data into a HTML chart.
 *
 * @param &$data
 *   Array. The
 */
function _fusioncharts_charts_render(&$data) {
  // Convert the chat TYPE into the FusionCharts way.
  // Since its a requirement to build the chart on Google, if the value
  // was not found, return nothing and stop the execution.
  $options = array(
    'line2D'  => 'MSLine.swf',
    'hbar2D'  => 'MSBar2D.swf',
    'hbar3D'  => 'MSBar3D.swf',
    'vbar2D'  => 'MSColumn2D.swf',
    'vbar3D'  => 'MSColumn3D.swf',
    'pie2D'   => 'Pie2D.swf',
    'pie3D'   => 'Pie3D.swf',
  );
  if (empty($options[$data['#type']])) {
    return t('This type is not possible using %chartplugin',
      array('%chartplugin' => 'FusionCharts'));
  }
  $file = file_create_url('fusioncharts') .'/'. $options[$data['#type']];

  // Convert the chat SIZE into the FusionCharts way.
  // Since its a requirement to build the chart on Google, if the value
  // was not found, return nothing and stop the execution.
  if (empty($data['#width']) or empty($data['#height'])) {
    return '';
  }
  $width  = $data['#width'];
  $height = $data['#height'];

  $chart = array(
    'key'   => 'chart',
    'value' => array()
  );

  if ($message = _fusioncharts_chart($chart, $data)) {
    return $message;
  }

  $series = '_fusioncharts_series';
  if ($data['#type'] == 'pie2D' or $data['#type'] == 'pie3D') {
    $series = '_fusioncharts_series_single';
  }
  if ($message = $series($chart, $data)) {
    return $message;
  }

  $chart =  '&dataXML='. str_replace('"', "'", format_xml_elements(array($chart)));

  // Its the HTML tag to include the chart
  return <<<FUSIONCHARTS
<object classid="clsid:d27cdb6e-ae6d-11cf-96b8-444553540000" width="$width" height="$height">
  <param name="allowScriptAccess" value="always" />
  <param name="movie" value="$file" />
  <param name="FlashVars" value="&chartWidth=$width&chartHeight=$height$chart" />
  <param name="quality" value="high" />
  <embed src="$file" flashVars="&chartWidth=$width&chartHeight=$height$chart" width="$width" height="$height" type="application/x-shockwave-flash" pluginspage="http://www.macromedia.com/go/getflashplayer" />
</object>
FUSIONCHARTS;
}

/**
 * Convert all Series-level data.
 *
 * @param &$chart
 *   Array. The array that will be converted into a string for FusionCharts
 * @param &$data
 *   Array. The raw data.
 * @return
 *   String. The string presentation of series data
 */
function _fusioncharts_series(&$chart, &$data) {
  // Convert the chat DATA into the FusionCharts way.
  // Since its a requirement to build the chart on FusionCharts, if the value
  // was not found, return nothing and stop the execution.
  foreach (element_children($data) as $series) {
    $series_data = array();
    foreach (element_children($data[$series]) as $values) {
      $serie_data = array(
        'value' => $data[$series][$values]['#value']
      );
      if (isset($data[$series][$values]['#label'])) {
        $serie_data['label'] = $data[$series][$values]['#label'];
      }
      $series_data[] = $serie_data;
    }

    if (isset($data['#color'][$series])) {
      $options['color'] = substr($data['#color'][$series], 1);
    }

    $chart['value'][] = _fusioncharts_values('set', $series_data, $options);

    foreach (element_children($data[$series]) as $values) {
      $value_labels_temp[] = empty($data[$series][$value]['#label']) ? NULL : $data[$series][$value]['#label'];
    }

    // X labels
    $value_labels = array();
    $toogle = FALSE;
    foreach (array_keys($series_data) as $value) {
      if (empty($data[$series][$value]['#label'])) {
        $value_labels[] = '';
        $toogle = TRUE;
      }
      else {
        $value_labels[] = $data[$series][$value]['#label'];
        $toogle = TRUE;
      }
    }
    if (!empty($toogle) and empty($chart['categories'])) {
      $chart['value'][] = _fusioncharts_values('category', $value_labels);
      $chart['categories'] = TRUE;
    }
  }
}

/**
 * Convert all Series-level data.
 *
 * @param &$chart
 *   Array. The array that will be converted into a string for FusionCharts
 * @param &$data
 *   Array. The raw data.
 * @return
 *   String. The string presentation of series data
 */
function _fusioncharts_series_single(&$chart, &$data) {
  // Convert the chat DATA into the FusionCharts way.
  // Since its a requirement to build the chart on FusionCharts, if the value
  // was not found, return nothing and stop the execution.
  foreach (element_children($data) as $series) {
    if (!empty($toogle)) {
      continue;
    }
    $toogle = TRUE;

    foreach (element_children($data[$series]) as $values) {
      $value_labels_temp[] = empty($data[$series][$value]['#label']) ? NULL : $data[$series][$value]['#label'];

      if (is_array($data[$series][$values])) {
        $series_data[] = array(
          'value' => $data[$series][$values]['#value'],
          'label' => $data[$series][$values]['#label'],
          'color' => trim($data['#color'][$values])
        );
      }
      else {
        $series_data[] = array(
          'value' => $data[$series][$values],
        );
      }
    }

    $options['no_wrap'] = TRUE;
    $options['label'] = TRUE;
    foreach (_fusioncharts_values('set', $series_data, $options) as $set) {
      $chart['value'][] = $set;
    }

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
      $chart['value'][] = _fusioncharts_values('category', $value_labels);
    }
  }
}
