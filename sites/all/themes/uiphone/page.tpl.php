<?php
// $Id$
?>
<!DOCTYPE html>
<html>
<head>
<title><?= $head_title?></title>
<meta name="viewport" content="width=device-width,user-scalable=no" />
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
<div class="nav">
</div>
<?php endif;?>
<div class="header">
  <?= $header ?>
</div>

<div class="content">  
  <?php /* print $help */ ?>
  <?php print $content ?>
  <?php /* print $feed_icons */ ?>

</div>
<div id="footer">
  <?php print $footer_message; ?>
  <?php print $footer; ?>
</div>
</body>
</html>
