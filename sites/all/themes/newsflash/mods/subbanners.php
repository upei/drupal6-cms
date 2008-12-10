<?php
  			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			// Created Novem 2008 to allow different banners for sub-sites @@
			// 
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
  			//Get the URL parts
			//Get how many levels are in the URL Bucket Name starting at [1]
			//Make the base path for the banners.
			//See if there is a folder for the sub sections
			//If it exists, pop in the banner from the sub folder
			//Else use the default bucket banner
function __banner() {
	$url_part = explode("/", request_uri());
	$mypath = "/var/www-d6/docroot";
	$url_part = array_filter(array_slice($url_part, 1), create_function('$a', 'return !empty($a);'));
	for($len = count($url_part); $len >= 1; $len--) {
		$url = array_slice($url_part, 0, $len);
		$file_name = '/banner/' . join('_', $url) . '.jpg';
		if (is_file($mypath . $file_name)) {
			return $file_name;
		}
	}
	return "/banner/default.jpg";
}
	?>
