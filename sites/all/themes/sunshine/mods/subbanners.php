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

function _get_banner() {
	$url_part = _get_sections();
	$mypath = "/var/www-d6/docroot";
	for($len = count($url_part); $len >= 1; $len--) {
		$url = array_slice($url_part, 0, $len);
		$file_name = '/banner/' . join('_', $url) . '.jpg';
		if (is_file($mypath . $file_name)) {
			return $file_name;
		}
	}
	return "/banner/default.jpg";
}

function _import_override_css_files() {
	$url_part = _get_sections();
	$mypath = "/var/www-d6/docroot";
  $output = '';
	for($len = 1; $len <= count($url_part); $len++) {
		$url = array_slice($url_part, 0, $len);
		$file_name = '/css/' . join('_', $url) . '.css';
		if (is_file($mypath . $file_name)) {
			$output .= '<style type="text/css">@import url("' . $file_name . "\");</style>\n";
		}
/*
    $file_name = '/css/' . join('_', $url) . '-ie.css';
    if (is_file($mypath . $file_name)) {
      $output .= <<<EOF
<!--[if lte IE 6]>
<style type="text/css">@import url("$file_name");</style>
<![endif]-->
EOF;
    }
*/
  } 
	return $output;
}
