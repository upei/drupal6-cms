<?php if (array_key_exists(DRUPAL_AUTHENTICATED_RID, user_roles())): ?>
<?php if ($administration_panel): ?>
<div id="admin-panel">
  <?php print $administration_panel; ?>
  <div class="clear-block"></div>
</div>
<?php endif; ?>
<?php endif; ?>
