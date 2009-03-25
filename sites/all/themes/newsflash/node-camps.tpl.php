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

  <div class="content">

  
  <?php echo $node->content['body']['#value'];?>
  
  <fieldset class="fieldgroup group-camp-information">
  <legend>Camp Information</legend>
  <?php echo  "<strong>" .  $node->content['group_camp_information']['group']['field_camp_category']['field']['#title'] . ": </strong>" . $node->field_camp_category[0]['view'] ; ?><br />
  <?php echo  "<strong>Ages: </strong>" . $node->field_age_from[0]['view'] . " - " . $node->field_age_to[0]['view'] ;?>  <br />
  <?php 
  
  
	$startmonth = date("F", strtotime($node->field_camp_date_start[0]['value']));
    $finishmonth = date("F", strtotime($node->field_camp_date_finish[0]['value']));
    $starttime = date("g:i a", strtotime($node->field_camp_date_start[0]['value']));
    $finishtime = date("g:i a", strtotime($node->field_camp_date_finish[0]['value']));

  
  	if($startmonth == $finishmonth){
        $campdate = date("F j", strtotime($node->field_camp_date_start[0]['value'])) . " - " . date("j", strtotime($node->field_camp_date_finish[0]['value']));
      }else{
        $campdate = date("F j", strtotime($node->field_camp_date_start[0]['value'])) . " - " . date("F j", strtotime($node->field_camp_date_finish[0]['value']));
      }
  	echo "<strong>Camp Date: </strong>" . $campdate . "<br />";
  	echo "<strong>Camp Time: </strong>" . $starttime . " - " . $finishtime;
	
  ?>
  </fieldset>
  
  <?php echo $node->content['group_contact_information']['#children']; ?>
  <?php echo $node->content['group_admin_info']['#children']; ?>
  </div>
 
 
 <div class="clear-block clear"></div>

  <?php if ($links): ?>
    <div class="links"><?php print $links; ?></div>
  <?php endif; ?>

</div>
