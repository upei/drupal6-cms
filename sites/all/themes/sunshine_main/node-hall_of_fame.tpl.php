<div class="node<?php if ($sticky) { print " sticky"; } ?><?php if (!$status) { print " node-unpublished"; } ?>">
  <?php if ($picture) { print $picture; }?>

  <?php if ($page == 0) { ?>
    <?php if ($title) { ?>
      <h2 class="title"><a href="<?php print $node_url?>"><?php print $title?></a></h2>
    <?php }; ?>
  <?php }; ?>

  <?php if ($terms) { ?>
    <span class="submitted"><?php print $submitted?></span> <span class="taxonomy"><?php print $terms?></span>
  <?php }; ?>

  <?php
 $Inducted = $field_year_inducted[0][value];
 $SchoolYear = $field_school_year[0][value];
 $Italics = $field_italics[0][value];
  ?>
  
  <div class="content"><?php //print $content?>
  	<div style="font-size:16px;background-image:url(/athletics/files/athletics/hof_medal.jpg);width:203;height:203px;float:right;font-weight:bold;">
	<table style="width:203px;height:203px;">
	<tr>
		<td align="center" valign="middle">
		<?php print $Inducted; ?><br />Inductee
		</td>
	</tr>
	</table>
	</div>
	
	<?php if($SchoolYear){print $SchoolYear . "<br /><br />";} ?>
	<?php if($Italics){print "<em>" . $Italics . "</em><br /><br />";} ?>
	<?php print $body ?>
  
  </div>
  <div class="clear-block clear"></div>

  <?php if ($links): ?>
    <div class="links"><?php print $links; ?></div>
  <?php endif; ?>

</div>
