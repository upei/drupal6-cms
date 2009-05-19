  <div id="page">
	<?php //Suckerfish statement moved to here Dec 2008?>
	<?php if ($suckerfish): ?>
        <!-- <div style="clear:both"></div> -->
        <!--  -->
		<div id="suckerfishmenu" class="clear-block"> <?php print $suckerfish; ?> </div>
      <?php endif; ?>
    <div id="middlecontainer">
<!-- dave did this and he's very sorry--> 

<?php //include "mods/google.php";?>
<?php include 'left-sidebar.php'; ?>
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
              <?php if ($page_top):?>
                 <div id="page-top"><?php print $page_top; ?></div>
               <?php endif; ?>

<?
	$aURI = explode("/", request_uri());
	if($aURI[1] == "home" && !$aURI[2]){$DisplayTitle = "<a class=\"homenewstitle\" href=\"http://www.upei.ca/news\">". $title ."</a>";}else{$DisplayTitle = $title;}
?>		  
<h1 class="title"><?php print $DisplayTitle ?></h1>
              
			  <div class="tabs"><?php print $tabs ?></div>
              <?php print $help ?>
              <?php if ($show_messages) { print $messages; } ?>

      <div class="clear-block clr" id="section1">
        <div class="sections">
          <?php if ($user1): ?>
            <div class="section user1"><?php print $user1; ?></div>
          <?php endif; ?>
          <?php if ($user2): ?>
            <div class="section user2"><?php print $user2; ?></div>
          <?php endif; ?>
          <?php if ($user3): ?>
            <div class="section user3"><?php print $user3; ?></div>
          <?php endif; ?>
        </div>
        <div style="clear:both"></div>
      </div><!-- /section1 -->

<?php if ($content_top):?>
   <div id="content-top"><?php print $content_top; ?></div>
 <?php endif; ?>
<?php if ($sidebar_inner_left): ?>
<div id="sidebar-inner-left">
  <? print $sidebar_inner_left; ?>
</div>
<?php endif; ?>
<?php if ($sidebar_inner_right): ?>
<div id="sidebar-inner-right">
  <? print $sidebar_inner_right; ?>
</div>
<?php endif; ?>
<div id="real-content" class="<? if ($sidebar_inner_left && $sidebar_inner_right) { print 'narrow'; } else if ( $sidebar_inner_left || $sidebar_inner_right) { print 'normal'; } else { print 'wide'; }?>">
<?php print $content; ?>
</div>
              <?php print $feed_icons; ?>
              <?php if ($content_bottom): ?>
                              <div id="content-bottom" style="clear:both;"><?php print $content_bottom; ?></div>
                            <?php endif; ?>              
      <div class="clear-block clr" id="section2">
        <div class="sections">
          <?php if ($user4): ?>
            <div class="section user4"><?php print $user4; ?></div>
          <?php endif; ?>
          <?php if ($user5): ?>
            <div class="section user5"><?php print $user5; ?></div>
          <?php endif; ?>
          <?php if ($user6): ?>
            <div class="section user6"><?php print $user6; ?></div>
          <?php endif; ?>
        </div>
        <div style="clear:both"></div>
      </div><!-- /section2 -->

    <?php if ($page_bottom):?>
       <div id="page-bottom"><?php print $page_bottom; ?></div>
     <?php endif; ?>
                <div class="clear-block clr" id="links-section">
                  <div class="sections">
                    <?php include 'bottom-links.php'; ?>
                  <div style="clear:both"></div>
                </div><!-- /bottom links -->
            </div><!-- /inner-content -->
          </div><!-- /squeeze-content -->
        </div><!-- /squeeze -->
      </div><!-- /main -->
   <? include 'right-sidebar.php'; ?>
   </div><!-- /middle-container -->
    <div style="clear:both"></div>
     </div> <!-- /page -->

