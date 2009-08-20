 <?
 //Strip the HTML away from the variables and strtodate the date variable
  $sDate = $field_game_date[0][view];
  $sDate = str_replace("<span class=\"date-display-single\">", "", $sDate);
  $sDate = str_replace("</span>", "", $sDate);
  $sDate = strtotime("$sDate");

 
 
 //Final list of Variables to use in code
 $PantherSport = $field_panther_sport[0][value];
 $PantherSportView = MakePantherSportView($PantherSport);
 $HomeAway = $field_home_away[0][value];
 $Exhibition = $field_exhibition[0][view];
 $Time = date("g:i a", $sDate);
 $Date = date("l, F j, Y", $sDate);
 $Opponent = $field_opponent[0][value];
 $Link =  $field_link[0][view];
 $StoryImage = $field_image[0][view]; 
 $Result = $field_result[0][view]; 
 
 $Label1 = $field_home_away[0][view];
 $Label2 = $field_championship_label[0][view];
 $Label3 = $field_third_label[0][value];
 
 
 function MakePantherSportView($PSport){
 	switch ($PSport){
		case "msoccer": $ret = "Men's Soccer"; break;
		case "wsoccer": $ret = "Women's Soccer"; break;
		case "wrugby": $ret = "Women's Rugby"; break;
		case "fieldhockey": $ret = "Women's Field Hockey"; break;
		case "mbball": $ret = "Men's Basketball"; break;
		case "wbball": $ret = "Women's Basketball"; break;
		case "mhockey": $ret = "Men's Hockey"; break;
		case "whockey": $ret = "Women's Hockey"; break;
		case "wvolleyball": $ret = "Women's Volleyball"; break;
	}
	
	return $ret;
 }
 
 ?>

 

 <div class="node<?php if ($sticky) { print " sticky"; } ?><?php if (!$status) { print " node-unpublished"; } ?>">
  <?php if ($picture) { print $picture; }?>

  <?php if ($page == 0) { ?>
    <?php if ($title) { ?>
      <h2 class="title"><a href="<?php print $node_url?>"><?php print $title ?></a></h2>
	 
    <?php }; ?>
  <?php }; ?>

  <?php if ($terms) { ?>
    <span class="submitted"><?php print $submitted?></span> <span class="taxonomy"><?php print $terms?></span>
  <?php }; ?>

  <div class="content">
 <div class="gamespecs">
 <?php 
 	print "<span style=\"font-size:16px;font-weight:bold;\">UPEI $PantherSportView</span><br />$Date";
	if($Link || $Label3){print "<br />" . $StoryImage;}else{
	
if($HomeAway == "home"){
						print "<table style=\"width:180px;\"><tr><td style=\"padding-left:10px;\" width=\"90\" align=\"center\"><img src=\"/athletics/files/athletics/75_$Opponent.gif\"></td><td align=\"center\" valign=\"middle\"> at </td><td style=\"padding-left:10px;\" width=\"90\" align=\"center\"><img src=\"/athletics/files/athletics/75_upei.gif\"></td></tr></table>";}
					elseif($HomeAway == "away"){
						print "<table style=\"width:180px;\"><tr><td style=\"padding-left:10px;\" width=\"90\" align=\"center\"><img src=\"/athletics/files/athletics/75_upei.gif\"></td><td align=\"center\" valign=\"middle\"> at </td><td style=\"padding-left:10px;\" width=\"90\" align=\"center\"><img src=\"/athletics/files/athletics/75_$Opponent.gif\"></td></tr></table>";}
	}
	echo "<div class=\"gamespecsbottom\">";
	if($Label3){print $Label3 . "&nbsp;&nbsp;" . $Result;}elseif($Link){print "Final: $Link $Result";}else{print "Game Time $Time";}
	echo "</div>";
?>
 </div>
<? print $body; ?>
  
  </div>
  <div class="clear-block clear"></div>

  <?php if ($links): ?>
    <div class="links"><?php print $links; ?></div>
  <?php endif; ?>

</div>
