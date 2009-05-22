<?php if (array_key_exists(DRUPAL_AUTHENTICATED_RID, user_roles())): ?>
<?php if ($administration_panel): ?>
<div id="administration-panel">
    <?php print $administration_panel; ?>
</div>
<?php endif; ?>
<?php endif; ?>