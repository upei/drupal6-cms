<!DOCTYPE html>
<html>
<head>
  <title><?= $head_title  ?></title>
  <style type="text/css">@import url("<?php print base_path() . path_to_theme() ?>/css/reset.css");</style>
<!--[if IE]><link rel="stylesheet" type="text/css" href="<?php print base_path() . path_to_theme() ?>/css/ie.css" /><![endif]-->
  <?php print $head ?>
  <?php print $styles ?>
<!--[if IE 6]><link rel="stylesheet" type="text/css" href="<?php print base_path() . path_to_theme() ?>/css/ie6fix.css" /><![endif]-->
  <?php print $scripts ?>
  <?php include 'site-includes/page-setup-scripts.php'; ?>
</head>
<body>
<?php if (!empty($admin)) print $admin; ?>
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
<div id="page" class="<?=$is_front ? "page-front" : ""?><?= $node ?" page-$node->type" : ""?><?= $node ? " page-nid-$node->nid" : ""?>">
  <?php include 'site-includes/02-page.tpl.php'; ?>
  <div style="clear:both"></div>
</div>
<?php print $closure ?>
<div id="footer"  class="fullwidthdiv" >
  <?php include 'site-includes/03-footer.php'; ?>
  <div style="clear:both"></div>
</div>
</body>
</html>
