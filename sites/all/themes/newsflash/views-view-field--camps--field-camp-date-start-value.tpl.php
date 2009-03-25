<?php
$startdate =  date($row->node_data_field_camp_date_start_field_camp_date_start_value);
$finishdate = date($row->node_data_field_camp_date_start_field_camp_date_finish_value);


if($startdate){
$startmonth = date("F", strtotime($startdate));
$finishmonth = date("F", strtotime($finishdate));



if($startmonth == $finishmonth){
  $output = date("F j", strtotime($startdate)) . " - " .  date("j", strtotime($finishdate)) ;
}else{
   $output = date("F j", strtotime($startdate)) . " - " .  date("F j", strtotime($finishdate)) ;
}

}
//echo $startmonth;
//echo $finishmonth;

echo $output;
//print_r($row);
?>
