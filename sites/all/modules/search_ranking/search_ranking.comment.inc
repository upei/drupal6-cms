<?php

$ranking['comments'] = array(
  'title' => t('Number of Comments'),
  'score' => '(2.0 - 2.0 / (1.0 + MAX(c.comment_count) * %f))',
  'arguments' => array(variable_get('node_cron_comments_scale', 0.0)),
  'join' => 'LEFT JOIN {node_comment_statistics} c ON c.nid = i.sid'
);