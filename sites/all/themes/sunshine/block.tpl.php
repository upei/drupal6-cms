<div class="block block-<?php print $block->module; ?>" id="block-<?php print $block->module; ?>-<?php print $block->delta; ?>">
<?php if ($block->subject) { ?><h2 class="title"><?php
if (module_hook('pathfilter','filter')) {
  print module_invoke('pathfilter', 'filter', 'process', 0, -1, html_entity_decode($block->subject));
}
else {
  print html_entity_decode($block->subject);
}
?></h2><?php } ?>
  <?php if ($block->content) { ?><div class="content"><?php print $block->content; ?></div><?php } ?>
</div>
