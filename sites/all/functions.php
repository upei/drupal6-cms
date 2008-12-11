<?php

function _get_bucket() {
  $site = split('/', request_uri());
  return $site[1];
}

function _get_sections() {
  $site = array_slice(split('/', request_uri()), 1);
  if ($site[2] == 'admin') {
    return array($site[1]);
  }
  else {
    return array_filter($site, create_function('$a', 'return !empty($a);'));
  }
}

