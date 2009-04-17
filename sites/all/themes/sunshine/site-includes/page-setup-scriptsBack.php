<script type="text/javascript" src="/misc/swfobject.js"></script>

  <script type="text/javascript"><?php /* Needed to avoid Flash of Unstyle Content in IE */ ?> </script>
  <?php if (theme_get_setting('sunshine_width')) { ?>
    <style type="text/css">
    /*#page {
      width : <?php print theme_get_setting('sunshine_fixedwidth') ?>px;
    }*/
    </style>
  <?php } else { ?>
    <style type="text/css">
    /*#page {
      width: 95%;
    }*/
    </style>
  <?php }  ?>
  <!-- Removed Theme call of width, and hard coded 1000px; -->
  <style type="text/css">
    #page {width: 1000px;}
    </style>
  <?php //if ($left_sidebar_width = theme_get_setting('sunshine_leftsidebarwidth')) { ?>
    <style type="text/css">
    body.sidebar-left #main {
      margin-left: -1<?php //print $left_sidebar_width ?>px;
    }
    body.sidebars #main {
      margin-left: -1<?php //print $left_sidebar_width ?>px;
    }
    body.sidebar-left #squeeze {
      margin-left: 1<?php //print $left_sidebar_width ?>px;
    }
    body.sidebars #squeeze {
      margin-left: 1<?php //print $left_sidebar_width ?>px;
    }
    </style>
  <?php //}  ?>
  <?php //if ($right_sidebar_width = theme_get_setting('sunshine_rightsidebarwidth')) { ?>
    <style type="text/css">
    body.sidebar-right #main {
      margin-right: -1<?php //print $right_sidebar_width ?>px;
    }
    body.sidebars #main {
      margin-right: -1<?php //print $right_sidebar_width ?>px;
    }
    body.sidebar-right #squeeze {
      margin-right: 1<?php //print $right_sidebar_width ?>px;
    }
    body.sidebars #squeeze {
      margin-right: 1<?php //print $right_sidebar_width ?>px;
    }
    </style>
  <?php //}  ?>
  <?php //if (theme_get_setting('sunshine_fontfamily')) { ?>
    <!-- Remove Theme call of font-family and hardcoded into page -->
	<style type="text/css">
    body {
      font-family : Arial, Verdana, sans-serif;<?php //print theme_get_setting('sunshine_fontfamily') ?>;
    }
    </style>
  <?php //}  ?>
  <?php //if (theme_get_setting('sunshine_fontfamily') == 'Custom') { ?>
    <?php //if (theme_get_setting('sunshine_customfont')) { ?>
      <style type="text/css">
      /*body {
        font-family : <?php print theme_get_setting('sunshine_customfont') ?>;
      }*/
      </style>
    <?php //}  ?>
  <?php //}  ?>
  <?php if (theme_get_setting('sunshine_iepngfix')) { ?>
<!--[if lte IE 6]>
<script type="text/javascript"> 
    $(document).ready(function(){ 
        $(document).pngFix(); 
    }); 
</script> 
<![endif]-->
  <?php } ?>
  <?php //if (theme_get_setting('sunshine_usecustomlogosize')) { ?>
    <style type="text/css">
    /*img#logo {
      width : <?php print theme_get_setting('sunshine_logowidth') ?>px;
      height: <?php print theme_get_setting('sunshine_logoheight') ?>px;
    }*/
    </style>
  <?php //}  ?>