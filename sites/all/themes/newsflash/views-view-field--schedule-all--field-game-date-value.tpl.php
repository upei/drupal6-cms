<?php
$GameDate = date($row->node_data_field_game_date_field_game_date_value);
$Display = date("F j, Y", strtotime($GameDate));


if($row->node_data_field_game_date_field_first_label_value){
	$output = $row->node_data_field_game_date_field_first_label_value;
}else{
	$output = $Display;
}

echo $output;

?>
