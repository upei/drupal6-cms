<?php include 'mods/doctype.php'; ?>
<html xmlns="http://www.w3.org/1999/xhtml" xmlns:u="http://upei.ca/xml/extensions" lang="<?php print $language->language ?>" xml:lang="<?php print $language->language ?>">
<head>
  <title><?= $_SERVER['REQUEST_URI']=='/home/' ? "University of Prince Edward Island" : variable_get('site_name', '') . ' ' . variable_get('site_slogan', '') . " | University of Prince Edward Island" ?></title>
  <link rel="apple-touch-icon shortcut icon" type="image/png" href="http://upei.ca/misc/upei-favicon.png" />
  <?php print $head ?>
  <?php print $scripts ?>
  <?php print $styles ?>
<style type="text/css">@import url("<?php print base_path() . path_to_theme() ?>/css/general_style.css");</style>
<style type="text/css">@import url("/css/sunshine.css");</style>
<?php print _import_override_css_files(); ?>
<?php include 'site-includes/page-setup-scripts.php'; ?>
<style type="text/css">@import url('/misc/ui-theme/ui.generated.css');</style>
<?php if ($suckerfish) { ?>
  <?php if (theme_get_setting('sunshine_suckerfish')) { ?>
<!--[if lte IE 6]>
<script type="text/javascript" src="<?php print $GLOBALS['base_url']."/"; print $directory; ?>/js/suckerfish.js"></script>
<![endif]-->
	<?php } ?>
<?php } ?>
</head>
<body<?php print phptemplate_body_class($sidebar_left, $sidebar_right); ?>>
<? if (function_exists('_print_additional_info')) {
  _print_additional_info();
}?>
<?php include "site-includes/00-primarynav.php"; ?>
<?php include "site-includes/01-topsection.php"; ?>
<?php include 'site-includes/02-page.tpl.php'; ?>
<?php print $closure ?>
<?php include 'site-includes/03-footer.php'; ?>
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
