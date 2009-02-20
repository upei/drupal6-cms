<?php include 'mods/doctype.php'; ?>
<html xmlns="http://www.w3.org/1999/xhtml" xmlns:u="http://upei.ca/xml/extensions" lang="<?php print $language->language ?>" xml:lang="<?php print $language->language ?>">
<head>
  <title><?php print "University of Prince Edward Island" //$head_title ?></title>
  <link rel="apple-touch-icon shortcut icon" type="image/png" href="http://upei.ca/misc/upei-favicon.png" />
  
  <?php print $head ?>
  <?php print $scripts ?>
  <?php print $styles ?>
<style type="text/css">@import "<?php print base_path() . path_to_theme() ?>/css/general_style.css";</style>
<?php /* includes the sub-banner code */ include 'mods/subbanners.php'; ?>
<style type="text/css">@import "/css/sunshine.css";</style>
<?php print _import_override_css_files(); ?>
<script type="text/javascript" src="/misc/swfobject.js"></script>


  
  <script type="text/javascript"><?php /* Needed to avoid Flash of Unstyle Content in IE */ ?> </script>
  <?php if (theme_get_setting('sunshine_width')) { ?>
    <style type="text/css">
    #page {
      width : <?php print theme_get_setting('sunshine_fixedwidth') ?>px;
    }
    </style>
  <?php } else { ?>
    <style type="text/css">
    #page {
      width: 95%;
    }
    </style>
  <?php }  ?>
  <?php if ($left_sidebar_width = theme_get_setting('sunshine_leftsidebarwidth')) { ?>
    <style type="text/css">
    body.sidebar-left #main {
      margin-left: -<?php print $left_sidebar_width ?>px;
    }
    body.sidebars #main {
      margin-left: -<?php print $left_sidebar_width ?>px;
    }
    body.sidebar-left #squeeze {
      margin-left: <?php print $left_sidebar_width ?>px;
    }
    body.sidebars #squeeze {
      margin-left: <?php print $left_sidebar_width ?>px;
    }
    #sidebar-left {
      width: <?php print $left_sidebar_width ?>px;
    }
    </style>
  <?php }  ?>
  <?php if ($right_sidebar_width = theme_get_setting('sunshine_rightsidebarwidth')) { ?>
    <style type="text/css">
    body.sidebar-right #main {
      margin-right: -<?php print $right_sidebar_width ?>px;
    }
    body.sidebars #main {
      margin-right: -<?php print $right_sidebar_width ?>px;
    }
    body.sidebar-right #squeeze {
      margin-right: <?php print $right_sidebar_width ?>px;
    }
    body.sidebars #squeeze {
      margin-right: <?php print $right_sidebar_width ?>px;
    }
    #sidebar-right {
      width: <?php print $right_sidebar_width ?>px;
    }
    </style>
  <?php }  ?>
  <?php if (theme_get_setting('sunshine_fontfamily')) { ?>
    <style type="text/css">
    body {
      font-family : <?php print theme_get_setting('sunshine_fontfamily') ?>;
    }
    </style>
  <?php }  ?>
  <?php if (theme_get_setting('sunshine_fontfamily') == 'Custom') { ?>
    <?php if (theme_get_setting('sunshine_customfont')) { ?>
      <style type="text/css">
      body {
        font-family : <?php print theme_get_setting('sunshine_customfont') ?>;
      }
      </style>
    <?php }  ?>
  <?php }  ?>
  <?php if (theme_get_setting('sunshine_iepngfix')) { ?>
<!--[if lte IE 6]>
<script type="text/javascript"> 
    $(document).ready(function(){ 
        $(document).pngFix(); 
    }); 
</script> 
<![endif]-->
  <?php } ?>
  <?php if (theme_get_setting('sunshine_usecustomlogosize')) { ?>
    <style type="text/css">
    img#logo {
      width : <?php print theme_get_setting('sunshine_logowidth') ?>px;
      height: <?php print theme_get_setting('sunshine_logoheight') ?>px;
    }
    </style>
  <?php }  ?>
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
<!-- Added January 22nd 2009 by shawn to add the new full cross section to the top of the page-->
<div style="width:100%;height:52px;">
	<div style="width:1000px;margin:5px auto;">
	<a href="/home"><img style="float:left;margin-left:10px;margin-top:2px;" src="/banner/other/UPEI-Horizontal-Logo_200.jpg" alt="UPEI Logo" /></a>
	<div style="float:right;padding:0px 10px 0px 0px;">
	
	<ul class="links-menu links" id="navlist">
<!--<li class=" first"><a href="http://www.upei.ca">UPEI Home</a></li>-->
<li class=""><a href="http://www.upei.ca/futurestudents">Future Students</a></li>
<li class=""><a href="http://www.upei.ca/currentstudents">Current Students</a></li>
<li class=""><a href="http://www.upei.ca/alumni">Alumni &amp; Friends</a></li>
<li class=""><a href="http://www.upei.ca/futurestudents/parentsandfamily">Parents &amp; Family</a></li>
<li class=""><a href="http://www.upei.ca/staff_faculty">Staff &amp; Faculty</a></li>
<li class=" last"><a href="http://www.upei.ca/home/contactpage">Contacts</a></li>
</ul>     
	</div>
	
<div style="margin-top:5px;width:706px;float:right;border:0px solid #cccccc;">
<?php include "mods/google.php";?>

<!--
<script language="javascript">
function ExecuteQuickLink(){
	window.location.href = document.frmQuickLinks.sltURL.value;
}
</script>
<form style="float:left;font-size:1.1em;margin:2px 0px 0px 0px;" name="frmQuickLinks">
<select name="sltURL" onchange="ExecuteQuickLink();">
	<option value="http://upei.ca/home"> - Campus Links - </option>
	<option value="https://secure.upei.ca/cls/dropbox/SpringTime.html">Second Semester 2008-09 Timetable</option>
	<option value="http://welcome.upei.ca/news/">News &amp; Events</option>
	<option value="http://upei.ca/staff_faculty/search">Search Faculty &amp; Staff</option>
	<option value="http://www.upei.ca/registrar/">Registrar's Office</option>
	<option value="http://www.upei.ca/futurestudents/tuition">Tuition</option>
	<option value="http://www.upei.ca/bookstore">Bookstore</option>
	<option value="http://www.upei.ca/residence">Residences</option>
	<option value="http://cms.upei.ca/home/research_institutes_and_centres">Institutes &amp; Centres</option>
	<option value="http://cms.upei.ca/home/safety">Campus Safety</option>
</select>
</form>
-->
</div>
</div>
</div>
<!-- End Top Section-->
<?
if (_get_bucket() == 'home') {
  include ('site-includes/home.tpl.php');
}
else {
  include ('site-includes/second.tpl.php');
}
?>

	<div id="footer"  style="width:100%;background-color:#e8e8e8;" >
      <?php if ($footer_region) { ?>
        <div id="footer-region"><?php print $footer_region?></div>
      <?php } ?>
      <?php if ($footer_message) { ?>
        <div id="footer-message">
		<?php 
		$bucket = _get_bucket();
		if($bucket != "home" && $bucket != "avc"){
			print "<img style=\"position:relative;top:16px;\" src=\"/css/images/leaf_rust_gold.jpg\">";
		}
		print $footer_message;
		$date = date('Y');
		print "<br />University of Prince Edward Island, 550 University Avenue, Charlottetown, PE, Canada C1A 4P3<br />
		&copy; $date | University of Prince Edward Island | All Rights Reserved ";

?>		

		</div>
      <?php } ?>
      <?php $logo_path = base_path() . path_to_theme() . "/images/" . get_sunshine_style(); ?>
    </div><!-- /footer -->
  <div style="clear:both"></div>
  <?php print $closure ?>

<?php if ( $_SERVER['REMOTE_ADDR'] == '137.149.3.48' || $_SERVER['REMOTE_ADDR'] == '137.149.3.28') {
  $_ga = 'UA-7323270-1';
}
else {
  $_ga = 'UA-7323270-2';
} ?>
<!-- google analytics/quancast code. -->
<script type="text/javascript">
var gaJsHost = (("https:" == document.location.protocol) ? "https://ssl." : "http://www.");
document.write(unescape("%3Cscript src='" + gaJsHost + "google-analytics.com/ga.js' type='text/javascript'%3E%3C/script%3E"));
</script>
<script type="text/javascript">
try {
var pageTracker = _gat._getTracker("<?=$_ga?>");
pageTracker._trackPageview();
} catch(err) {}</script>
<!-- Start Quantcast tag -->
<script type="text/javascript">
_qoptions={
qacct:"p-73x8TBYuYZv9-"
};
</script>
<script type="text/javascript" src="http://edge.quantserve.com/quant.js"></script>
<noscript>
<img src="http://pixel.quantserve.com/pixel/p-73x8TBYuYZv9-.gif" style="display: none;" border="0" height="1" width="1" alt="Quantcast"/>
</noscript>
<!-- End Quantcast tag -->
</body>
</html>
