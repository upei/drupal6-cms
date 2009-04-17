<?php

//$output = "";
$site = explode("/", request_uri());

switch ($output){
  case "Financial Management":
    $strDisplay = "financial";
  break;
  case "Human Resources":
    $strDisplay = "humanresources";
  break;
  case "Strategic Planning":
    $strDisplay = "strategic";
  break;
  case "Marketing and Sales":
    $strDisplay = "marketing";
  break;
  case "Management and Operations":
    $strDisplay = "operations";
  break;

}
$avar = str_replace(" ", "%20", $output);

//print_r($row);
echo "<a href=\"/$site[1]/course/list/$strDisplay\">" . $output . "</a>";

//print_r($row);
?>
