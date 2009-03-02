<?php 
if($row->node_data_field_game_date_field_championship_label_value){
	$output = $row->node_data_field_game_date_field_championship_label_value;
}else{
	if($row->node_data_field_opponent_field_opponent_value){
		if($row->node_data_field_home_away_field_home_away_value == "home"){
			$output = "<img src=\"/athletics/files/athletics/sm_" . $row->node_data_field_opponent_field_opponent_value . ".gif\">";
			$output .= "&nbsp;&nbsp;<img style=\"border:none;\" src=\"/athletics/files/athletics/vs.gif\">&nbsp;&nbsp;";
			$output .= "<img src=\"/athletics/files/athletics/sm_upei.gif\">";
		}else{
			$output = "<img src=\"/athletics/files/athletics/sm_upei.gif\">";
			$output .= "&nbsp;&nbsp;<img style=\"border:none;\" src=\"/athletics/files/athletics/vs.gif\">&nbsp;&nbsp;";
			$output .= "<img src=\"/athletics/files/athletics/sm_" . $row->node_data_field_opponent_field_opponent_value . ".gif\">";
		}
		
		
	}
}
	
	echo $output;
?>

