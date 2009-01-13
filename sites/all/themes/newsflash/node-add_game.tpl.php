 <?
 //Strip the HTML away from the variables and strtodate the date variable
  $sDate = $field_game_date[0][view];
  $sDate = str_replace("<span class=\"date-display-single\">", "", $sDate);
  $sDate = str_replace("</span>", "", $sDate);
  $sDate = strtotime("$sDate");

 
 
 //Final list of Variables to use in code
 $PantherSport = $field_panther_sport[0][view];
 $PantherSportValue = $field_panther_sport[0][value];
 $HomeAway = $field_home_away[0][view];
 $Exhibition = $field_exhibition[0][view];
 $Time = date("g:i a", $sDate);
 $Date = date("l, F j, Y", $sDate);
 $Opponent = $field_opponent[0][view];
 $Link =  $field_link[0][view];
 $StoryImage = $field_image[0][view]; 
 
 $Label1 = $field_home_away[0][view];
 $Label2 = $field_championship_label[0][view];
 $Label3 = $field_third_label[0][view];
 
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
 	print "<span style=\"font-size:16px;font-weight:bold;\">UPEI $PantherSport</span><br />$Date";
	if($Link || $Label3){print "<br />" . $StoryImage;}else{
		/*if($HomeAway == "Home"){print "<br /><img src=\"/athletics/files/athletics/$Opponent.gif\"> at <img src=\"/athletics/files/athletics/UPEI.gif\">";}elseif($HomeAway == "Away"){print "<br /><img src=\"/athletics/files/athletics/UPEI.gif\"> at <img src=\"/athletics/files/athletics/$Opponent.gif\">";}*/
if($HomeAway == "Home"){
						print "<table style=\"width:180px;\"><tr><td style=\"padding-left:10px;\" width=\"90\" align=\"center\"><img src=\"/athletics/files/athletics/$Opponent.gif\"></td><td align=\"center\" valign=\"middle\"> at </td><td style=\"padding-left:10px;\" width=\"90\" align=\"center\"><img src=\"/athletics/files/athletics/UPEI.gif\"></td></tr></table>";}
					elseif($HomeAway == "Away"){
						print "<table style=\"width:180px;\"><tr><td style=\"padding-left:10px;\" width=\"90\" align=\"center\"><img src=\"/athletics/files/athletics/UPEI.gif\"></td><td align=\"center\" valign=\"middle\"> at </td><td style=\"padding-left:10px;\" width=\"90\" align=\"center\"><img src=\"/athletics/files/athletics/$Opponent.gif\"></td></tr></table>";}
	}
	
	if($Label3){print "<br />" . $Label3;}elseif($Link){print "<br />$Link";}else{print "<br />$Time";}
?>
 </div>
<? print $body; ?>
  
  </div>
  <div class="clear-block clear"></div>

  <?php if ($links): ?>
    <div class="links"><?php print $links; ?></div>
  <?php endif; ?>

</div>