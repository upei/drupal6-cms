<?
$display = str_replace(" ", "-", $output);
$display = strtolower($display);


echo "<a href=\"/avc/news/media/type/". $display ."\">" . $output . "</a>";
?>