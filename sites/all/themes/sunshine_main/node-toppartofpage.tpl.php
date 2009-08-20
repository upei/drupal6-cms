<div class="node<?php if ($sticky) { print " sticky"; } ?><?php if (!$status) { print " node-unpublished"; } ?>">
  <?php if ($picture) { print $picture; }?>


  <div class="content"><?php print $content?></div>
  <div class="clear-block clear"></div>

  <?php if ($links): ?>
    <div class="links"><?php print $links; ?></div>
  <?php endif; ?>

</div>
