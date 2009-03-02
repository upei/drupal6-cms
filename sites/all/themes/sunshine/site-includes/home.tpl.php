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
      $section1count = 3;
      // if ($user1)  { $section1count++; }
      // if ($user2)  { $section1count++; }
      // if ($user3)  { $section1count++; }
    ?>
    <?php if ($section1count): ?>
      <?php $section1width = 'width' . floor(99 / $section1count); ?>
      <div class="clear-block clr" id="section1">
        <div class="sections">
          <?php if ($user1): ?>
            <div class="section user1-<?=$section1width?>"><?php print $user1; ?></div>
          <?php endif; ?>
          <?php if ($user2): ?>
            <div class="section user2-<?=$section1width?>"><?php print $user2; ?></div>
          <?php endif; ?>
          <?php if ($user3): ?>
            <div class="section user3-<?=$section1width?>"><?php print $user3; ?></div>
          <?php endif; ?>
        </div>
        <div style="clear:both"></div>
      </div><!-- /section1 -->
<?php endif; ?>
              <?php print $feed_icons; ?>
              
			  <?php
      $section2count = 2;
      // if ($user4)  { $section2count++; }
      // if ($user5)  { $section2count++; }
      // if ($user6)  { $section2count++; }
    ?>
    <?php if ($section2count): ?>
      <?php $section2width = 'width' . floor(99 / $section2count); ?>
      <div class="clear-block clr" id="section2">
        <div class="sections">
          <?php if ($user4): ?>
            <div class="section user1-<?php echo $section2width ?>"><?php print $user4; ?></div>
          <?php endif; ?>
          <?php if ($user5): ?>
            <div class="section user2-<?php echo $section2width ?>"><?php print $user5; ?></div>
          <?php endif; ?>
          <?php if ($user6): ?>
            <div class="section user3-<?php echo $section2width ?>"><?php print $user6; ?></div>
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
    <? include 'right-sidebar.php'; ?>
    </div><!-- /middle-container -->
    <div style="clear:both"></div>
     </div> <!-- /page -->

