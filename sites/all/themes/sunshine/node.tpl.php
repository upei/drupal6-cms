<div class="node<?= ($is_front || $type == 'landingpage') ? "-front" : "" ?> node-<?=$type?><?php if ($sticky) { print " sticky"; } ?><?php if (!$status) { print " node-unpublished"; } ?>">
  <? if (!$is_front): ?>
  <div class="right">
    <?php if ($links): ?>
    <fieldset>
      <legend>Useful Links</legend>
      <div class="links"><?php print $links; ?></div>
    </fieldset>
    <?php endif; ?>
  </div>
  <? endif; ?>
  <div class="content">
    <? if ($page == 0): ?>
    <h2 class="title"><a href="<?=$node_url?>"><?=$title?></a></h2>
    <? endif; ?>
    <div class="body">
      <?= ($body) ? $body : $content ?>
    </div>
    <div class="clear-block clear"></div>
    <?php if (!$is_front && $type != 'landingpage' && !$view && array_key_exists(DRUPAL_AUTHENTICATED_RID, $user->roles)): ?>
    <div class="date"><? if (date('jFY', $changed) != date('jFY', $created)): ?> Updated on <?php print date('l, j F, Y.', $changed); endif; ?>
    Created on <?php print date('l, j F, Y', $created); ?>.</div>
    <?php endif; ?>
  </div>
  <div class="clear-block clear"></div>

</div>
