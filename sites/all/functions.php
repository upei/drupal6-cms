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

$GLOBALS['wi_cache'] = new WIFileCache(UPEI_CACHE_DIR);

function wicache_get_contents($url) {
  global $wi_cache;
  $cache =& $wi_cache;
  $cache->setExpiryTime(UPEI_CACHE_EXPIRE);
  $content = $cache->get(sha1($url));
  if (!$content) {
    $content = file_get_contents($url);
    $cache->put(sha1($url), $content);
  }
  return $content;
}
