<?php
if($row->node_data_field_game_date_field_third_label_value){
	$output = $row->node_data_field_game_date_field_third_label_value;
}else{
	if(!$output){
		$GameDate = $row->node_data_field_game_date_field_game_date_value;
		$output = date("g:i a", strtotime($GameDate));
	}
}
if($row->node_data_field_game_date_field_result_value){$output .= "&nbsp;&nbsp;" . $row->node_data_field_game_date_field_result_value;}
if($row->node_data_field_game_date_field_exhibition_value == "yes"){$output = "* " . $output;}

echo $output;
//echo print_r($row) 
?>