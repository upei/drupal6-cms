<div class="clear-block clr" id="links-section">                                                                        
  <?php include '02.420-bottom-links.php'; ?>
</div><!-- /bottom links -->

<?php if ($footer) { ?>
  <div id="footer-region"><?php print $footer?></div>
<?php } ?>

<div id="footer-message">
<?php if ($footer_message)
  		print $footer_message;

$date = date('Y');
print "<br />University of Prince Edward Island, 550 University Avenue, Charlottetown, PE, Canada C1A 4P3<br />
&copy; $date | University of Prince Edward Island | All Rights Reserved ";
?>		

</div>

