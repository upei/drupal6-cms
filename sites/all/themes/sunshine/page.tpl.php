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
<script type="text/javascript"><?php /* Needed to avoid Flash of Unstyle Content in IE */ ?> </script>
<script type="text/javascript" src="/misc/swfobject.js"></script>
<!--[if lte IE 6]>
<script type="text/javascript"> 
    $(document).ready(function(){ 
        $(document).pngFix(); 
    }); 
</script> 
<![endif]-->

<!--[if IE]>
<style type="text/css" media="all">@import "<?php print base_path() . path_to_theme() ?>/css/ie.css";</style>
<![endif]-->
<style type="text/css">@import url('/misc/ui-theme/ui.generated.css');</style>
<?php if ($suckerfish) { ?>
    <?php if (theme_get_setting('sunshine_suckerfish')) { ?>
<!--[if lte IE 6]>
<script type="text/javascript" src="<?php print $GLOBALS['base_url']."/"; print $directory; ?>/js/suckerfish.js"></script>
<![endif]-->
	<?php }  ?>
<?php } ?>
</head>
<body<?php print phptemplate_body_class($sidebar_left, $sidebar_right); ?>>

<?php include "site-includes/00-primarynav.php"; ?>
<?php include "site-includes/01-topsection.php"; ?>
<?
	if (_get_bucket() == 'home') {
		include ('site-includes/02-home.tpl.php');
	}else {
  		include ('site-includes/02-second.tpl.php');
	}
	include ('site-includes/03-footer.php');
?>	
<?php print $closure ?>

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
