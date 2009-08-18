<?php
// Inverse law that maps the highest view count on the site to 1 and 0 to 0.
$ranking['statistics'] = array(
  'title' => t('Number of Visits'),
  'score' => '(2.0 - 2.0 / (1.0 + MAX(nc.totalcount) * %f))',
  'arguments' => array(variable_get('node_cron_views_scale', 0.0)),
  'join' => 'LEFT JOIN {node_counter} nc ON nc.nid = i.sid',
);
