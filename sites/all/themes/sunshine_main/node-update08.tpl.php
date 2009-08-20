<div class="node<?php if ($sticky) { print " sticky"; } ?><?php if (!$status) { print " node-unpublished"; } ?>">
  <?php if ($picture) { print $picture; }?>

  <?php if ($page == 0) { ?>
    <?php if ($title) { ?>
     <!--  <h2 class="title"><a href="<?php print $node_url?>"><?php print $title?></a></h2> -->
	  
    <?php }; ?>
  <?php }; ?>
	
	
<div id="presup08nav"> 
<img src="/president/files/president/08_index.jpg">
<table border="0" style="position:relative;left:10px;width:518px;" align="center">
<tr>
	<td><a href="/president/update08/" id="current">Home</a></td>
	<td><a href="/president/update08/revitalize-campus">Revitalize Campus</a></td>
	<td><a href="/president/update08/engage-community">Engage Community</a></td>
	<td><a href="/president/update08/celebrate-success">Celebrate Success</a></td>
</tr>
<tr>
	<td><a href="/president/update08/build-spirit-and-teamwork">Build Spirit & Teamwork</a></td>
	<td><a href="/president/update08/discover-learn">Discover & Learn</a></td>
	<td><a href="/president/update08/make-a-difference">Make a Difference</a></td>
	<td><a href="/president/update08/define-future">Define the future</a></td>
</tr>
</table>
<img src="/president/files/president/menugrade.jpg">
</div>
  <div class="content"><?php print $content?></div>
  <div class="clear-block clear"></div>

  <?php if ($links): ?>
    <div class="links"><?php print $links; ?></div>
  <?php endif; ?>

</div>
