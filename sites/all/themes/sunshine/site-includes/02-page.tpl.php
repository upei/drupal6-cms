
<?php include '02.050-left-sidebar.php'; ?>
<div id="middlecontainer">
<!-- dave did this and he's very sorry--> 
  <div id="main">
    <div id="squeeze">
      <?php include '02.110-breadcrumb.php'; ?>
      <?php include '02.120-mission.php'; ?>
      <div id="squeeze-content">
        <div id="inner-content">
          <?php include '02.130-page-top.php'; ?>
          <?
          	$aURI = explode("/", request_uri());
          	if($aURI[1] == "home" && !$aURI[2]){$DisplayTitle = "<a class=\"homenewstitle\" href=\"http://www.upei.ca/news\">". $title ."</a>";}else{$DisplayTitle = $title;}
          ?>
          <h1 class="title"><?php print $DisplayTitle ?></h1>
        

          <?php print $help ?>
          <?php if ($show_messages) { print $messages; } ?>
          <?php include '02.200-sections.php'; ?>
          <?php include '02.300-content.php'; ?>
          <?php include '02.400-sections.php'; ?>
          <?php include '02.410-page-bottom.php'; ?>
          <?php if (_get_bucket() != 'home'): ?>
            <div class="clear-block clr" id="links-section">
            <div class="sections">
              <?php include '02.420-bottom-links.php'; ?>
            </div><!-- /bottom links -->
            <div style="clear:both"></div>
          <? endif; ?>
        </div><!-- /inner-content -->
      </div><!-- /squeeze-content -->
    </div><!-- /squeeze -->
  </div><!-- /main -->
</div><!-- /middle-container -->
<? include '02.450-right-sidebar.php'; ?>
