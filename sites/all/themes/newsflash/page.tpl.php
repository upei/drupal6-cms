<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="<?php print $language->language ?>" xml:lang="<?php print $language->language ?>">
<head>
  <title><?php print $head_title ?></title>
  <?php print $head ?>
  <?php print $styles ?>
  <?php print $scripts ?>
  <script type="text/javascript"><?php /* Needed to avoid Flash of Unstyle Content in IE */ ?> </script>
  <?php if (theme_get_setting('newsflash_width')) { ?>
    <style type="text/css">
    #page {
      width : <?php print theme_get_setting('newsflash_fixedwidth') ?>px;
    }
    </style>
  <?php } else { ?>
    <style type="text/css">
    #page {
      width: 95%;
    }
    </style>
  <?php }  ?>
  <?php if ($left_sidebar_width = theme_get_setting('newsflash_leftsidebarwidth')) { ?>
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
  <?php if ($right_sidebar_width = theme_get_setting('newsflash_rightsidebarwidth')) { ?>
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
  <?php if (theme_get_setting('newsflash_fontfamily')) { ?>
    <style type="text/css">
    body {
      font-family : <?php print theme_get_setting('newsflash_fontfamily') ?>;
    }
    </style>
  <?php }  ?>
  <?php if (theme_get_setting('newsflash_fontfamily') == 'Custom') { ?>
    <?php if (theme_get_setting('newsflash_customfont')) { ?>
      <style type="text/css">
      body {
        font-family : <?php print theme_get_setting('newsflash_customfont') ?>;
      }
      </style>
    <?php }  ?>
  <?php }  ?>
  <?php if (theme_get_setting('newsflash_iepngfix')) { ?>
<!--[if lte IE 6]>
<script type="text/javascript"> 
    $(document).ready(function(){ 
        $(document).pngFix(); 
    }); 
</script> 
<![endif]-->
  <?php } ?>
  <?php if (theme_get_setting('newsflash_usecustomlogosize')) { ?>
    <style type="text/css">
    img#logo {
      width : <?php print theme_get_setting('newsflash_logowidth') ?>px;
      height: <?php print theme_get_setting('newsflash_logoheight') ?>px;
    }
    </style>
  <?php }  ?>
<!--[if IE]>
<style type="text/css" media="all">@import "<?php print base_path() . path_to_theme() ?>/css/ie.css";</style>
<![endif]-->
  <?php if ($suckerfish) { ?>
    <?php if (theme_get_setting('newsflash_suckerfish')) { ?>
<!--[if lte IE 6]>
<script type="text/javascript" src="<?php print $GLOBALS['base_url']."/"; print $directory; ?>/js/suckerfish.js"></script>
<![endif]-->
    <?php }  ?>
  <?php } ?>
  <script type="text/javascript" src="<?php print $GLOBALS['base_url']."/"; print $directory; ?>/js/pickstyle.js"></script>
</head>
<body<?php print phptemplate_body_class($sidebar_left, $sidebar_right); ?>>
  <div id="page">
    <div id="header" class="clear-block">
      <div id="logo-title">
        <?php if ($logo): ?>
          <?php if (theme_get_setting('newsflash_themelogo')) { ?>
            <?php $logo_path = base_path() . path_to_theme() . "/images/" . get_newsflash_style() . "/logo.png"; ?>
            <a href="<?php print $base_path; ?>" title="<?php print t('Home'); ?>"> <img src="<?php print $logo_path; ?>" alt="<?php print t('Home'); ?>" id="logo" /> </a>
          <?php } else { ?>
            <a href="<?php print $base_path; ?>" title="<?php print t('Home'); ?>"> <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" id="logo" /> </a>
          <?php } ?>
        <?php endif; ?>
      </div><!-- /logo-title -->
      <div id="name-and-slogan">
        <?php if ($site_name): ?>
          <h1 class='site-name'> <a href="<?php print $base_path ?>" title="<?php print t('Home'); ?>"> <?php print $site_name; ?> </a> </h1>
        <?php endif; ?>
        <?php if ($site_slogan): ?>
          <div class='site-slogan'> <?php print $site_slogan; ?> </div>
        <?php endif; ?>
      </div><!-- /name-and-slogan -->
      <?php if ($header): ?>
        <div style="clear:both"></div>
        <?php print $header; ?>
      <?php endif; ?>
      <?php print $search_box; ?>
      <?php if (isset($primary_links) || isset($secondary_links)) { ?>
        <div id="primarymenu">
        <?php if (isset($primary_links)) : ?>
          <?php print theme('links', $primary_links, array('class' => 'links primary-links')) ?>
        <?php endif; ?>
        <?php if (isset($secondary_links)) : ?>
          <?php print theme('links', $secondary_links, array('class' => 'links secondary-links')) ?> 
        <?php endif; ?>
        </div>
      <?php } ?>
      <?php if ($suckerfish): ?>
        <div style="clear:both"></div>
        <div id="suckerfishmenu" class="clear-block"> <?php print $suckerfish; ?> </div>
      <?php endif; ?>
    </div><!-- /header -->
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
    <div id="middlecontainer">
      <?php if ($sidebar_left) { ?>
        <div id="sidebar-left"><?php print $sidebar_left ?> </div>
      <?php } ?>
      <div id="main">
        <div id="squeeze">
          <?php if (theme_get_setting('newsflash_breadcrumb')): ?>
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
              <h1 class="title"><?php print $title ?></h1>
              <div class="tabs"><?php print $tabs ?></div>
              <?php print $help ?>
              <?php if ($show_messages) { print $messages; } ?>
              <?php print $content; ?> 
              <?php print $feed_icons; ?>
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
    <div id="footer">
      <?php if ($footer_region) { ?>
        <div id="footer-region"><?php print $footer_region?></div>
      <?php } ?>
      <?php if ($footer_message) { ?>
        <div id="footer-message"><?php print $footer_message ?></div>
      <?php } ?>
      <br />
      <?php $logo_path = base_path() . path_to_theme() . "/images/" . get_newsflash_style(); ?>
      <a href="http://www.roopletheme.com" title="RoopleTheme!"><img src="<?php print $logo_path . '/RoopleThemeLogo.png'; ?>" alt="RoopleTheme!"/></a>
    </div><!-- /footer -->
  <div style="clear:both"></div>
  <?php print $closure ?>
  </div> <!-- /page -->
</body>
</html>
