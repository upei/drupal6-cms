
<?php include '02.050-left-sidebar.php'; ?>
<!-- dave did this and he's very sorry--> 
<?php include '02.110-breadcrumb.php'; ?>
<?php include '02.120-mission.php'; ?>
<?php include '02.130-page-top.php'; ?>
<div style="clear:both"></div>
<?
	$aURI = explode("/", request_uri());
	if($aURI[1] == "home" && !$aURI[2]){$DisplayTitle = "<a class=\"homenewstitle\" href=\"http://www.upei.ca/news\">". $title ."</a>";}else{$DisplayTitle = $title;}
?>
<h1 class="title"><?php print $DisplayTitle ?></h1>
<?php print $help ?>
<?php if ($show_messages) { print $messages; } ?>
<?php include '02.200-sections.php'; ?>
<div style="clear:both"></div>
<?php include '02.300-content.php'; ?>
<div style="clear:both"></div>
<?php include '02.400-sections.php'; ?>
<div style="clear:both"></div>
<?php include '02.410-page-bottom.php'; ?>
<div style="clear:both"></div>
<div class="clear-block clr" id="links-section">
  <?php include '02.420-bottom-links.php'; ?>
</div><!-- /bottom links -->
<div style="clear:both"></div>
<? include '02.450-right-sidebar.php'; ?>
