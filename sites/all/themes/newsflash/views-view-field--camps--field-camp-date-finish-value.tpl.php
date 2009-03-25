<?php

$aDate = date($row->node_data_field_camp_date_start_field_camp_date_finish_value);
if($aDate){$output = date("F j", strtotime($aDate));}


echo $output;
//print_r($row);
?>
