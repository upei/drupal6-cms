<?php
// $Id: page.tpl.php,v 1.9.2.2 2009/05/04 07:31:23 zinv Exp $

/**
 * @file page.tpl.php
 *
 * Theme implementation to display a single Drupal page.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $css: An array of CSS files for the current page.
 * - $directory: The directory the theme is located in, e.g. themes/garland or
 *   themes/garland/minelli.
 * - $is_front: TRUE if the current page is the front page. Used to toggle the mission statement.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Page metadata:
 * - $language: (object) The language the site is being displayed in.
 *   $language->language contains its textual representation.
 *   $language->dir contains the language direction. It will either be 'ltr' or 'rtl'.
 * - $head_title: A modified version of the page title, for use in the TITLE tag.
 * - $head: Markup for the HEAD section (including meta tags, keyword tags, and
 *   so on).
 * - $styles: Style tags necessary to import all CSS files for the page.
 * - $scripts: Script tags necessary to load the JavaScript files and settings
 *   for the page.
 * - $body_classes: A set of CSS classes for the BODY tag. This contains flags
 *   indicating the current layout (multiple columns, single column), the current
 *   path, whether the user is logged in, and so on.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 * - $mission: The text of the site mission, empty when display has been disabled
 *   in theme settings.
 *
 * Navigation:
 * - $search_box: HTML to display the search box, empty if search has been disabled.
 * - $primary_links (array): An array containing primary navigation links for the
 *   site, if they have been configured.
 * - $secondary_links (array): An array containing secondary navigation links for
 *   the site, if they have been configured.
 *
 * Page content (in order of occurrance in the default page.tpl.php):
 * - $left: The HTML for the left sidebar.
 *
 * - $breadcrumb: The breadcrumb trail for the current page.
 * - $title: The page title, for use in the actual HTML content.
 * - $help: Dynamic help text, mostly for admin pages.
 * - $messages: HTML for status and error messages. Should be displayed prominently.
 * - $tabs: Tabs linking to any sub-pages beneath the current page (e.g., the view
 *   and edit tabs when displaying a node).
 *
 * - $content: The main content of the current Drupal page.
 *
 * - $right: The HTML for the right sidebar.
 *
 * Footer/closing data:
 * - $feed_icons: A string of all feed icons for the current page.
 * - $footer_message: The footer message as defined in the admin settings.
 * - $footer : The footer region.
 * - $closure: Final closing markup from any modules that have altered the page.
 *   This variable should always be output last, after all other dynamic content.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 */
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="<?php print $language->language ?>" xml:lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">

<head>
  <title><?php print $head_title ?></title>
  <?php print $head ?>
  <?php print $styles ?> 
</head>

<body class="<?php print $body_classes ?>">

  <div id="header"><div class="container clearfix">

    <?php if ($logo or $site_name or $site_slogan): ?>
      <div id="logo">
        <?php if ($logo): ?>
          <div id="logo-title"><a href="<?php print $base_path; ?>" title="<?php print t('Home'); ?>" rel="home"><img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" id="logo-image" /></a></div>
        <?php endif; ?>

        <?php if ($site_slogan): ?>
          <div id="site-slogan"><?php print $site_slogan; ?></div>
        <?php endif; ?>

        <?php if ($site_name): ?>
          <?php if ($is_front): ?>
            <h1 id="site-name">
              <a href="<?php print $base_path; ?>" title="<?php print t('Home'); ?>" rel="home">
                <?php print $site_name; ?>
              </a>
            </h1>
          <?php else: ?>
            <div id="site-name">
              <strong> <a href="<?php print $base_path; ?>" title="<?php print t('Home'); ?>" rel="home">
                <?php print $site_name; ?>
              </a></strong>
            </div>
          <?php endif; ?>
        <?php endif; ?>
      </div> <!-- /#logo -->
    <?php endif; ?>

    <?php if ($search_box): ?>
      <?php print $search_box; ?>
    <?php endif; ?>
			
  </div></div><!-- /.container, /#header -->

  <?php if ($primary_links or $feed_icons): ?>
    <div id="navigation"><div class="container clearfix">

      <?php if ($primary_links): ?>
          <?php print theme('links', $primary_links, $attributes = array('class' => 'pages')); ?>
      <?php endif; ?>

      <?php if ($feed_icons): ?>
        <div id="rss">
          <?php print $feed_icons ?>
        </div><!-- /#rss -->
      <?php endif; ?>

    </div></div><!-- /.container, /#navigation -->
  <?php endif; ?>

	<?php if ($dock or $mission): ?>
		<div id="dock"><div class="dock-back container clearfix">

      <?php if ($mission): ?>
        <div id="mission"> 
          <?php print $mission; ?>
        </div><!-- /#mission -->
      <?php endif; ?>
				
    	<?php print $dock; ?>

		</div></div><!-- /.dock-back, /#dock  -->
	<?php endif; ?>

  <div id="page" class="clearfix"><div class="container">

    <div class="main-content left">

      <?php if ($breadcrumb or $title or $tabs or $messages): ?>
        <div id="content-header">
          <?php print $messages; ?>
          <?php print $breadcrumb; ?>
          <?php if ($title): ?>
            <?php if (!$node): ?>
              <h1 class="title"><?php print $title; ?></h1>
            <?php endif; ?>
          <?php endif; ?>
          <?php if ($tabs): ?>
          <div class="tabs"><?php print $tabs; ?></div>
            <?php endif; ?>
        </div> <!-- /#content-header -->
      <?php endif; ?>

      <div id="content"><div id="content-inner">
        <?php if ($help): ?>
          <?php print $help; ?>
        <?php endif; ?>

        <div id="content-area">
          <?php print $content; ?>
        </div>
      </div></div> <!-- /#content-inner, /#content -->
      
    </div><!-- /.main-content -->
			
    <?php if ($right): ?>
      <div class="sidebar right">
        <?php print $right; ?>
      </div><!-- /.sidebar -->
    <?php endif; ?>

  </div></div><!-- /.container, /#page-->

  <?php if ($footerleft or $footerright): ?>
    <div id="footer"><div class="container footer-divider clearfix">	    

      <?php if ($footerleft): ?>
        <div class="footer-left">
          <?php print $footerleft; ?>
        </div><!-- /.footer-left -->
      <?php endif; ?>

      <?php if ($footerright): ?>
        <div class="footer-right">
          <?php print $footerright; ?>
        </div><!-- /.footer-right -->
      <?php endif; ?>

    </div></div><!--/.footer-divider, /#footer -->
	<?php endif; ?>

  <?php if ($footer_message): ?>
    <div id="footer-message"><div class="container clearfix">
      <?php print $footer_message; ?>		
    </div></div><!-- /.container, /#footer-message -->
  <?php endif; ?>

  <?php print $scripts ?>
	<?php print $closure ?>

</body>
</html>