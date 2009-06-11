<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="<?php  print $print['language'] ?>" xml:lang="<?php  print $print['language'] ?>">
  <head>
    <title><?php  print $print['title'] ?></title>
    <?php  print $print['head'] ?>
    <?php  print $print['scripts'] ?>
    <?php  print $print['robots_meta'] ?>
    <?php  print $print['base_href'] ?>
    <?php  print $print['favicon'] ?>
    <?php  print $print['css'] ?>
	<link type="text/css" rel="stylesheet" media="all" href="/news/sites/all/themes/sunshine/css/print.css?E" />
  </head>
  <body<?php  print $print['sendtoprinter'] ?>>
    <?php if (!empty($print['message'])) print '<div class="print-message">'. $print['message'] .'</div><p />' ?>
    <!-- <div class="print-logo"><?php  print $print['logo'] ?></div> -->
    <!-- <div class="print-site_name"><?php  print $print['site_name'] ?></div> -->
    <p />
    <!-- <div class="print-breadcrumb"><?php  print $print['breadcrumb'] ?></div> -->
    <div class="bannersection">
		<div class="print-bannerimage"><img src="/banner/other/lhlogo.jpg"></div>
		<div class="print-address"></div>
	</div>
	<p />
    <div class="all-content">
	<h1 class="print-title"><?php  print $print['title'] ?></h1>
    <div class="print-info">
		<div class="print-submitted"><?php  print $print['submitted'] ?></div>
    	<? $print['created'] = str_replace("Created", "", $print['created']);?>
		<div class="print-created"><?php  print $print['created'] ?></div>
	</div>
	
	<? $print['content'] = str_replace("<p>&nbsp;</p>", "", $print['content']);?>
	<? $print['content'] = strip_tags($print['content'], '<p><a><em><strong>');?>
	<div class="print-content">	<?php  print $print['content'] ?></div>
	</div>
    
	
	<!-- <div class="print-taxonomy"><?php print $print['taxonomy'] ?></div>
    <div class="print-footer"><?php  print $print['footer_message'] ?></div> -->
    <hr class="print-hr" />
    <div class="print-source_url"><?php  //print $print['source_url'] ?></div>
    <div class="print-links"><?php  //print $print['pfp_links'] ?></div>
  </body>
</html>
