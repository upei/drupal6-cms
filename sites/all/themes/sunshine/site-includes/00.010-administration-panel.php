<?php if (array_key_exists(DRUPAL_AUTHENTICATED_RID, user_roles())): ?>

<div id="administration-panel">
  <?php if ($administration_panel) {
    print $administration_panel;
  }
  ?>
</div>

<?php endif; ?>