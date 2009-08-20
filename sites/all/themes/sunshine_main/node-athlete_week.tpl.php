<div class="node<?php if ($sticky) { print " sticky"; } ?><?php if (!$status) { print " node-unpublished"; } ?>">
  <?php if ($picture) { print $picture; }?>

  <?php if ($page == 0) { ?>
    <?php if ($title) { ?>
      <h2 class="title"><a href="<?php print $node_url?>"><?php print $title?></a></h2>
    <?php }; ?>
  <?php }; ?>

  <?php if ($terms) { ?>
    <span class="submitted"><?php print $submitted?></span> <span class="taxonomy"><?php print $terms?></span>
  <?php }; ?>

  <div class="content"><?php print $content?></div>
  <div class="clear-block clear"></div>
  <p align="right"><a href="/athletics/aotw/list">See past <em>Athlete of the Week</em> winners</a></p>
  <?php if ($links): ?>
    <div class="links"><?php print $links; ?></div>
  <?php endif; ?>

</div>
