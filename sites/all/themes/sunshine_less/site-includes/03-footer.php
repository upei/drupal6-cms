<?php if ($links1 || $links2 || $links3 || $links4 || $links5 || $links6): ?>
<div class="clear-block clr" id="links-section">                                                                        
  <?php include '02.420-bottom-links.php'; ?>
</div><!-- /bottom links -->
<?php endif; ?>

<?php if ($footer) { ?>
  <div id="footer-region"><?php print $footer?></div>
<?php } ?>

<div id="footer-message">
<?php if ($footer_message)
  		print $footer_message;
?>		
</div>

