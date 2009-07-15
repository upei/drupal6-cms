<!DOCTYPE html>
<html>
<head>
  <title><?= $_SERVER['REQUEST_URI'] == '/home/' ? 'University of Prince Edward Island' : $head_title . ' | University of Prince Edward Island' ?></title>
  <link rel="apple-touch-icon shortcut icon" type="image/png" href="http://upei.ca/misc/upei-favicon.png" />
  <style type="text/css">@import url("<?php print base_path() . path_to_theme() ?>/css/reset.css");</style>
<!--[if IE]><link rel="stylesheet" type="text/css" href="<?php print base_path() . path_to_theme() ?>/css/ie.css" /><![endif]-->
  <?php print $head ?>
  <?php print $styles ?>
<!--[if IE 6]><link rel="stylesheet" type="text/css" href="<?php print base_path() . path_to_theme() ?>/css/ie6fix.css" /><![endif]-->
  <?php print _import_override_css_files(array("/css/sunshine.css"/*, "/misc/ui-theme/ui.generated.css"*/)); ?>
  <?php print $scripts ?>
  <?php include 'site-includes/page-setup-scripts.php'; ?>
</head>
<body>
<? if (function_exists('_print_additional_info')) {
  _print_additional_info();
}?>
<?php include 'site-includes/00.010-administration-panel.php'; ?>
<div id="primary-navigation">
  <?php include "site-includes/00-primarynav.php"; ?>
</div>
<!-- Start Top Section -->
<div id="header">
  <?php include "site-includes/01-header.php"; ?>
  <div style="clear:both"></div>
</div>
<?php include 'site-includes/02.100-suckerfish.php'; ?>
<div id="page" class="<?=$is_front ? "page-front " : ""?>page-<?=$node->type?>">
  <?php include 'site-includes/02-page.tpl.php'; ?>
  <div style="clear:both"></div>
</div>
<?php print $closure ?>
<div id="footer"  class="fullwidthdiv" >
  <?php include 'site-includes/03-footer.php'; ?>
  <div style="clear:both"></div>
</div>
<?php 
	if ( $_SERVER['REMOTE_ADDR'] == '137.149.3.48' || $_SERVER['REMOTE_ADDR'] == '137.149.3.28') {
  		$_ga = 'UA-7323270-1';
	}else {
  		$_ga = 'UA-7323270-2';
	} 
	include ('site-includes/04-quantcast.php');
?>
</body>
</html>
