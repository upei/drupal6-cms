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

<?
	$aURI = explode("/", request_uri());
	if($aURI[1] == "home" && !$aURI[2]){$DisplayTitle = "<a style=\"font-weight:normal;color:#666666;text-decoration:underline;\" href=\"http://www.upei.ca/news\">". $title ."</a>";}else{$DisplayTitle = $title;}
?>		  
<h1 class="title"><?php print $DisplayTitle ?></h1>
              
			  <div class="tabs"><?php print $tabs ?></div>
              <?php print $help ?>
              <?php if ($show_messages) { print $messages; } ?>
 <?php
      $section1count = 2;
      // if ($user1)  { $section1count++; }
      // if ($user2)  { $section1count++; }
      // if ($user3)  { $section1count++; }
    ?>
    <?php if ($section1count): ?>
      <?php $section1width = 'width' . floor(99 / $section1count); ?>
      <div class="clear-block clr" id="section1">
        <div class="sections">
          <?php if ($user1): ?>
            <div class="section user1n-<?=$section1width?>"><?php print $user1; ?></div>
          <?php endif; ?>
          <?php if ($user2): ?>
            <div class="section user2n-<?=$section1width?>"><?php print $user2; ?></div>
          <?php endif; ?>
          <?php if ($user3): ?>
            <div class="section user3n-<?=$section1width?>"><?php print $user3; ?></div>
          <?php endif; ?>
        </div>
        <div style="clear:both"></div>
      </div><!-- /section1 -->
<?php endif; ?>
              <?php print $feed_icons; ?>
              
			  <?php
      $section2count = 3;
      // if ($user4)  { $section2count++; }
      // if ($user5)  { $section2count++; }
      // if ($user6)  { $section2count++; }
    ?>
    <?php if ($section2count): ?>
      <?php $section2width = 'width' . floor(99 / $section2count); ?>
      <div class="clear-block clr" id="section2" style="margin-top: 10px; padding-top: 10px; border-top: 1px solid #eee;">
        <div class="sections">
          <?php if ($user4): ?>
            <div class="section user4n-<?php echo $section2width ?>"><?php print $user4; ?></div>
          <?php endif; ?>
          <?php if ($user5): ?>
            <div class="section user5n-<?php echo $section2width ?>"><?php print $user5; ?></div>
          <?php endif; ?>
          <?php if ($user6): ?>
            <div class="section user6n-<?php echo $section2width ?>"><?php print $user6; ?></div>
          <?php endif; ?>
        </div>
        <div style="clear:both"></div>
      </div><!-- /section2 -->
    <?php endif; ?>
<?php print $content; ?>			 
<?php if ($content_bottom): ?>
                <div id="content-bottom"><?php print $content_bottom; ?></div>
              <?php endif; ?>
          			  <?php
                $section3count = 6;
                // if ($user4)  { $section2count++; }
                // if ($user5)  { $section2count++; }
                // if ($user6)  { $section2count++; }
              ?>
              <?php if ($section3count): ?>
                <?php $section3width = 'width' . floor(99 / $section3count); ?>
                <div class="clear-block clr" id="links-section">
                  <div class="sections">
                    <?php if ($links1): ?>
                      <div class="section links1-<?php echo $section3width ?>"><?php print $links1; ?></div>
                    <?php endif; ?>
                    <?php if ($links2): ?>
                      <div class="section links2-<?php echo $section3width ?>"><?php print $links2; ?></div>
                    <?php endif; ?>
                    <?php if ($links3): ?>
                      <div class="section links3-<?php echo $section3width ?>"><?php print $links3; ?></div>
                    <?php endif; ?>
                    <?php if ($links4): ?>
                      <div class="section links4-<?php echo $section3width ?>"><?php print $links4; ?></div>
                    <?php endif; ?>
                    <?php if ($links5): ?>
                      <div class="section links5-<?php echo $section3width ?>"><?php print $links5; ?></div>
                    <?php endif; ?>
                    <?php if ($links6): ?>
                      <div class="section links6-<?php echo $section3width ?>"><?php print $links6; ?></div>
                    <?php endif; ?>
                  </div>
                  <div style="clear:both"></div>
                </div><!-- /section2 -->
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

