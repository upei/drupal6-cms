<?php
// $Id: page.tpl.php,v 1.00 2008/03/03 12:00:00 jaburns Exp $
?><?php print $dtd ?>
<html xmlns="http://www.w3.org/1999/xhtml" lang="<?php print $language->language ?>" xml:lang="<?php print $language->language ?>">

<head>
<meta name="viewport" content="width=device-width,user-scalable=no" />
<link rel="apple-touch-icon" href="/sites/upei.ca.m/files/images/upei-touch-logo.png" />
<title>UPEI</title>
  <?php 
  print $head;
  print $styles;
  print $scripts;
  print $head_extra;
  ?>
</head>

<body>

<?php if ($logo OR $site_name OR $site_slogan) { ?>
<div id="header">
<!--
  <?php if ($logo) { ?>
  <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>"><img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" /></a>
  <?php } ?>
-->
  <?php if ($site_name) { ?>
  <h1 class="site-name"><a accesskey="0" href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>"><?php print $site_name; ?></a></h1>
  <?php } ?>
  <?php if ($site_slogan) { ?>
  <div class="site-slogan"><?php print $site_slogan; ?></div>
  <?php } ?>
</div>
<?php } ?>

<?php if ($mission) { ?>
  <div id="mission"><?php print $mission; ?></div>
<?php } ?>


<?php if ($mobi_links != '' AND $primary_links) { ?>
<div id="mobi_links">
    <?php print $mobi_links; ?>
</div>
 <?php } ?>

<?php if ($left) { ?>
<div id="sidebar-left">
  <?php print $left; ?>
</div>
<?php } ?>

<?php if ($header) { ?>
  <div id="header_block"><?php print $header; ?></div>
<?php } ?>

<div id="main">
  
  <?php if ($title) { ?>
  <h1 class="title"><?php print $title; ?></h1>
  <?php } ?>
  
  <?php if ($tabs) { ?>
    <!-- <div class="tabs"><?php print $tabs; ?></div> -->
  <?php } ?>

  <?php if ( $pre_content ) { print $pre_content; } ?>
  
  <?php if ($show_messages) { print $messages; } ?>

  <?php /* print $help */ ?>
  <?php print $content ?>
  <?php /* print $feed_icons */ ?>

</div>

<?php if ($right) { ?>
<div id="sidebar-right">
  <?php print $right; ?>
</div>
<?php } ?>

<!--<?php print $breadcrumb ?>-->

<div id="footer">
<div align="center"><?php
    $date = date('Y');
    print "University of Prince Edward Island, 550 University Avenue, Charlottetown, PE, Canada C1A 4P3<br />
    &copy; $date | University of Prince Edward Island | All Rights Reserved ";
?></div>
<?php if ($footer) { ?>
 <?php print $footer_message; ?>
  <?php print $footer; ?>
<?php } ?>
</div>

<?php print $closure; ?>

</body>
</html>
