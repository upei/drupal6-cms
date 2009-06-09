<div id="footer-absolute">
<div id="footer-background"></div>
<div id="footer-placeholder"></div>
</div>

<?php if ($footer) { ?>
  <div id="footer-region"><?php print $footer?></div>
<?php } ?>

<div id="footer-message">
<?php if ($footer_message)
  		print $footer_message;

$bucket = _get_bucket();
if($bucket != "home" && $bucket != "avc"){
	//print "<img style=\"position:relative;top:16px;\" src=\"/css/images/leaf_rust_gold.jpg\">";
}
$date = date('Y');
print "<br />University of Prince Edward Island, 550 University Avenue, Charlottetown, PE, Canada C1A 4P3<br />
&copy; $date | University of Prince Edward Island | All Rights Reserved ";
?>		

</div>

