<div class="block block-<?php print $block->module; ?>" id="block-<?php print $block->module; ?>-<?php print $block->delta; ?>">
<?php if ($block->subject) { ?><h2 class="title"><?php print $block->subject; ?>
</h2><?php } ?>
  <?php if ($block->content) { ?><div class="content"><?php print $block->content; ?></div><?php } ?>
</div>
