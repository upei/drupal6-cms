<div class="node-page node<?php if ($sticky) { print " sticky"; } ?><?php if (!$status) { print " node-unpublished"; } ?>">
  <div class="right">
    <?php if ($links): ?>
    <fieldset>
      <legend>Useful Links</legend>
      <div class="links"><?php print $links; ?></div>
    </fieldset>
    <?php endif; ?>
  </div>
  <div class="content">
    <? if ($page == 0): ?>
    <h2 class="title"><a href="<?=$node_url?>"><?=$title?></a></h2>
    <? endif; ?>
    <div class="body">
      <?= $body ?>
    </div>
    <?php if (!$is_front): ?>
    <div class="date">Updated on <?php print date('l, j F, Y', $changed); ?></div>
    <?php endif; ?>
  </div>
  <div class="clear-block clear"></div>

</div>
