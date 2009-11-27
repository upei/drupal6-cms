<?
if($row->node_status == 1){$b = "58ff47"; $c = "bfffb8";}else{$b = "ff6868"; $c = "ffaeae";}

//echo print_r($row);
echo "<div style=\"margin-bottom:5px;background-color:#". $c .";border:1px solid #". $b .";\">" . $output . " - ". date("F j, h:i a", $row->node_created) ." </div>";

?>