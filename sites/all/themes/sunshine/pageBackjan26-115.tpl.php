<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="<?php print $language->language ?>" xml:lang="<?php print $language->language ?>">
<head>
  <title><?php print $head_title ?></title>
  <link rel="apple-touch-icon shortcut icon" type="image/png" href="http://upei.ca/misc/upei-favicon.png" />
  
  <?php print $head ?>
  <?php print $styles ?>
<style type="text/css">@import "<?php print base_path() . path_to_theme() ?>/css/general_style.css";</style>
<?php /* includes the sub-banner code */ include 'mods/subbanners.php'; ?>
<style type="text/css">@import "/css/sunshine.css";<?php  //print _import_override_css_files(); ?></style>
<script type="text/javascript" src="/misc/swfobject.js"></script>


  
  <?php print $scripts ?>
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

<?php if ($suckerfish) { ?>
    <?php if (theme_get_setting('sunshine_suckerfish')) { ?>
<!--[if lte IE 6]>
<script type="text/javascript" src="<?php print $GLOBALS['base_url']."/"; print $directory; ?>/js/suckerfish.js"></script>
<![endif]-->
    <?php }  ?>
  <?php } ?>
  <script type="text/javascript" src="<?php print $GLOBALS['base_url']."/"; print $directory; ?>/js/pickstyle.js"></script>
</head>
<body<?php print phptemplate_body_class($sidebar_left, $sidebar_right); ?>>

<!-- Added January 22nd 2009 by shawn to add the new full cross section to the top of the page-->
<div style="width:100%;height:52px;">
	<div style="width:1000px;margin:5px auto;">
	<a href="/home"><img style="float:left;margin-left:10px;margin-top:2px;" src="/banner/other/UPEI-Horizontal-Logo_200.jpg"></a>
	<div style="float:right;padding:0px 10px 0px 0px;">
	
	<ul class="links-menu links" id="navlist">
<!--<li class=" first"><a href="http://www.upei.ca">UPEI Home</a></li>-->
<li class=""><a href="http://www.upei.ca/futurestudents">Future Students</a></li>
<li class=""><a href="http://www.upei.ca/currentstudents">Current Students</a></li>
<li class=""><a href="http://www.upei.ca/alumni">Alumni &amp; Friends</a></li>
<li class=""><a href="http://www.upei.ca/futurestudents/parentsandfamily">Parents &amp; Family</a></li>
<li class=""><a href="http://www.upei.ca/staff_faculty">Staff &amp; Faculty</a></li>
<li class=" last"><a href="http://www.upei.ca/home/contactpage">Contact UPEI</a></li>
</ul>     
	</div>
	
	
<script language="javascript">
function ExecuteQuickLink(){
	window.location.href = document.frmQuickLinks.sltURL.value;
}
</script>
<?php // include "mods/google.php";?>

<form style="font-size:0.9em;margin:7px 5px 0px 0px;float:right;" name="frmQuickLinks">
<select name="sltURL" onchange="ExecuteQuickLink();">
	<option value="http://upei.ca/home">--- Quick Links ---</option>
	<option value="https://secure.upei.ca/cls/dropbox/SpringTime.html">Second Semester 2008-09 Timetable</option>
	<option value="http://welcome.upei.ca/news/">News &amp; Events</option>
	<option value="http://upei.ca/staff_faculty/search">Search Faculty &amp; Staff</option>
	<option value="http://www.upei.ca/registrar/">Registrar's Office</option>
	<option value="http://upei.ca/studentservices/award/entering-upei">Scholarships</option>
	<option value="http://www.upei.ca/futurestudents/tuition">Tuition</option>
	<option value="http://upei.ca/internationalization">Internationalization</option>
	<option value="http://www.upei.ca/bookstore">Bookstore</option>
	<option value="http://www.upei.ca/residence">Residences</option>
	<option value="http://www.upei.ca/conference">Conference Services</option>
	<option value="http://cms.upei.ca/home/research_institutes_and_centres">Institutes &amp; Centres</option>
	<option value="http://cms.upei.ca/home/safety">Campus Safety</option>
</select>
</form>
	</div>

</div>
<!-- End Top Section-->
  <div id="page">
	<?php //Suckerfish statement moved to here Dec 2008?>
	<?php if ($suckerfish): ?>
        <!-- <div style="clear:both"></div> -->
        <!--  -->
		<div id="suckerfishmenu" class="clear-block"> <?php print $suckerfish; ?> </div>
      <?php endif; ?>
    <div id="middlecontainer">
<!-- dave did this and he's very sorry--> 
<!--
<?php if($bucket != "home" && $bucket != "avc"){?><h1 class="title"><?php print $title ?></h1> <?php }?> 
-->
<?php //include "mods/google.php";?>
<?php if ($sidebar_left) { ?>
        <div id="sidebar-left"><?php print $sidebar_left ?> </div>
      <?php } ?>
      <div id="main">
        <div id="squeeze">
          <?php if (theme_get_setting('sunshine_breadcrumb')): ?>
            <?php if ($breadcrumb): ?>
              <div id="breadcrumb"> <?php print $breadcrumb; ?> </div>
            <?php endif; ?>
          <?php endif; ?>
          <?php if ($mission) { ?>
            <div id="mission"><?php print $mission ?></div>
          <?php } ?>
          <div id="squeeze-content">
            <div id="inner-content">
             <?php if ($content_top):?>
                <div id="content-top"><?php print $content_top; ?></div>
              <?php endif; ?>
			<!--  
         <?php if($bucket == "home" || $bucket == "avc"){?><h1 class="title"><?php print $title ?></h1><?php }?>
              -->
			  <div class="tabs"><?php print $tabs ?></div>
              <?php print $help ?>
              <?php if ($show_messages) { print $messages; } ?>
 <?php
      $section1count = 0;
      if ($user1)  { $section1count++; }
      if ($user2)  { $section1count++; }
      if ($user3)  { $section1count++; }
    ?>
    <?php if ($section1count): ?>
      <?php $section1width = 'width' . floor(99 / $section1count); ?>
      <div class="clear-block clr" id="section1">
        <div class="sections">
          <?php if ($user1): ?>
            <div class="section <?php echo $section1width ?>"><?php print $user1; ?></div>
          <?php endif; ?>
          <?php if ($user2): ?>
            <div class="section <?php echo $section1width ?>"><?php print $user2; ?></div>
          <?php endif; ?>
          <?php if ($user3): ?>
            <div class="section <?php echo $section1width ?>"><?php print $user3; ?></div>
          <?php endif; ?>
        </div>
        <div style="clear:both"></div>
      </div><!-- /section1 -->
<?php endif; ?>
              <?php print $feed_icons; ?>
              
			  <?php
      $section2count = 0;
      if ($user4)  { $section2count++; }
      if ($user5)  { $section2count++; }
      if ($user6)  { $section2count++; }
    ?>
    <?php if ($section2count): ?>
      <?php $section2width = 'width' . floor(99 / $section2count); ?>
      <div class="clear-block clr" id="section2">
        <div class="sections">
          <?php if ($user4): ?>
            <div class="section <?php echo $section2width ?>"><?php print $user4; ?></div>
          <?php endif; ?>
          <?php if ($user5): ?>
            <div class="section <?php echo $section2width ?>"><?php print $user5; ?></div>
          <?php endif; ?>
          <?php if ($user6): ?>
            <div class="section <?php echo $section2width ?>"><?php print $user6; ?></div>
          <?php endif; ?>
        </div>
        <div style="clear:both"></div>
      </div><!-- /section2 -->
    <?php endif; ?>
<?php print $content; ?>			  
<?php if ($content_bottom): ?>
                <div id="content-bottom"><?php print $content_bottom; ?></div>
              <?php endif; ?>
            </div><!-- /inner-content -->
          </div><!-- /squeeze-content -->
        </div><!-- /squeeze -->
      </div><!-- /main -->
      <?php if ($sidebar_right) { ?>
        <div id="sidebar-right"><?php print $sidebar_right ?> </div>
      <?php } ?>
    </div><!-- /middle-container -->
    <div style="clear:both"></div>
     </div> <!-- /page -->
    
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
 

</body>
</html>
