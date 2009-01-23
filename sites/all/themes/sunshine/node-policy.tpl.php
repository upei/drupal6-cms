<div class="node<?php if ($sticky) { print " sticky"; } ?><?php if (!$status) { print " node-unpublished"; } ?>">
  <?php if ($picture) { print $picture; }?>

  <?php if ($page == 0) { ?>
    <?php if ($title) { ?>
      <h2 class="title"><a href="<?php print $node_url?>"><?php print $title?></a></h2>
    <?php }; ?>
  <?php }; ?>

  <?php if ($terms) { ?>
    <!--<span class="submitted"><?php print $submitted?></span>--> <span class="taxonomy"><?php print $terms?></span>
  <?php }; ?>

  <div class="content">
 <?
 $policy_unique_id = $field_policy_unique_id[0][view];
 $policy_revision_number = $field_policy_revision_number[0][view];
 $creation_date = $field_creation_date[0][view];
 $version_date = $field_version_date[0][view];
 $policy_review_date = $field_policy_review_date[0][view];
 $authority = $field_authority[0][view];
 $responsibility = $field_responsibility[0][view];
 $document_status =  $field_document_status[0][view];

print $field_responsibility[0]['label_text'];
  ?>

 
  <table border="2" bordercolor="#000000" style="width:100%;">
  <tr>
  	<td width="50%"><strong>Policy Number:</strong> <?print $policy_unique_id; ?></td>
	<td width="50%"><strong>Revision Number:</strong> <?print $policy_revision_number;?></td>
  </tr>
 
  <tr>
  	<td width="50%"><strong>Creation Date:</strong> <?print $creation_date; ?></td>
	<td width="50%"><strong>Version Date:</strong> <?print $version_date; ?></td>
  </tr>
  <tr>
  	<td width="50%"><strong>Authority:</strong> <? print $authority; ?></td>
	<td width="50%"><strong>Responsibility:</strong> <? print $responsibility; ?></td>
  </tr>
   <tr>
  	<td width="50%">&nbsp;<!--<strong>Review Date:</strong> <? print $policy_review_date; ?>--></td>
	<td width="50%"><strong>Document Status:</strong> <? print $document_status; ?></td>
  </tr>
  </table>

  
  <?php

print "<br /><strong>Policy Purpose</strong><br />";
print $node->content['body']['#value'];
print $node->content['files']['#value'];


?>
  </div>
  <div class="clear-block clear"></div>

  <?php if ($links): ?>
    <div class="links"><?php print $links; ?></div>
  <?php endif; ?>

</div>
