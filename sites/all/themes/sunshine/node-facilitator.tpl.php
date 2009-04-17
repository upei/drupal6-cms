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
    <?php //print_r($node); //$content;
  	echo "<strong>" . $node->field_title[0][value] . "</strong>";
	echo "<p>" . $node->body ."</p>";
	// This will show the list of courses taught by that facilitator.
	echo "<h3>ProfitLearn PEI Workshops that ". $node->title ." delivers:</h3><ul>";
  echo "<ul>";
 
    $sSQL = "SELECT * FROM {node} WHERE type = 'course'";
    $all_courses =  db_query($sSQL);
    $site = explode("/", request_uri() );
    while($anode = db_fetch_object($all_courses)){
        $node_object = node_load($anode->nid);
        $myArray = $node_object->field_facilitator;
        $count = 0;
        foreach($myArray as $value){
          if($node->nid == $node_object->field_facilitator[$count][nid]){
            echo "<li><a href=\"/" . $site[1] ."/node/" . $node_object->nid  . "\">" . $node_object->title . "</a></li>";
          }
          $count++;
        }

    }
  echo "</ul>";

    
    


    //if (in_array()){}
 /* 
	$sSQL = "SELECT * FROM {content_field_facilitator} WHERE field_facilitator_nid = ". $node->vid;
	$ci = db_query($sSQL);
	
	while($anode = db_fetch_object($ci)){
		$node_object = node_load($anode->vid);
		echo "<li>" . $node_object->title . "</li>";
		//db_query("INSERT INTO {blocks_roles} (module, delta, rid)VALUES('%s', '%s', %d)", $block_module, $menu->mid, $roles->rid);
	}
	*/
	echo "</ul>";
  ?>
  </div>
 
 
 <div class="clear-block clear"></div>

  <?php if ($links): ?>
    <div class="links"><?php print $links; ?></div>
  <?php endif; ?>

</div>
