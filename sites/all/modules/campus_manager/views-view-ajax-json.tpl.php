<?php

drupal_set_header('Content-type: text/javascript; charset=utf-8');
$final = array();
foreach ($rows as $row) {
  $final[] = unserialize($row);
}
print json_encode($final);
exit;