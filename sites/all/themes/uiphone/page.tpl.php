<?php
// $Id$
?>
<!DOCTYPE html>
<html>
<head>
<title><?= $head_title?></title>
<meta name="viewport" content="width=device-width, minimum-scale=1.0, maximum-scale=1.0">
<link rel="apple-touch-icon" href="<?= $logo ?>" />
<link type="text/css" rel="stylesheet" media="screen" href="<?=base_path() . path_to_theme()?>/css/iphone.css" />
  <?php 
  print $head;
  print $styles;
  print $head_extra;
  ?>
<?php print $scripts; ?>
</head>
<body>
<?php if (!$is_front): ?>
<div class="nav"><? print $breadcrumb; ?></div>
<?php endif;?>
<div class="header">
  <?php print $header; ?>
</div>
<div class="content">  
  <?php if ($messages): ?>
  <div class="rounded">
    <?php print $messages; ?>
  </div>
  <?php endif; ?>
  <?php /* print $help */ ?>
  <?php print $content ?>
  <?php /* print $feed_icons */ ?>
</div>
<div style="clear:both;"></div>
<div id="footer">
  <?php print $footer_message; ?>
  <?php print $footer; ?>
</div>
</body>
</html>
