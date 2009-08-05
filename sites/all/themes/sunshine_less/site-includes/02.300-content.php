<?php if ($content_top):?>
   <div id="content-top"><?php print $content_top; ?></div>
<?php endif; ?>
<?php if ($sidebar_inner_left): ?>
<div id="sidebar-inner-left">
  <? print $sidebar_inner_left; ?>
</div>
<?php endif; ?>
<?php if ($sidebar_inner_right): ?>
<div id="sidebar-inner-right">
  <? print $sidebar_inner_right; ?>
</div>
<?php endif; ?>
<div id="real-content" class="<? if ($sidebar_inner_left && $sidebar_inner_right) { print 'narrow'; } else if ( $sidebar_inner_left || $sidebar_inner_right) { print 'normal'; } else { print 'wide'; }?>">
<div class="tabs"><?php print $tabs ?></div>
<?php if ($content): ?>
<div id="content">
  <?php print $content; ?>
</div>
<?php endif; ?>
</div>
<?php print $feed_icons; ?>
<?php if ($content_bottom): ?>
<div id="content-bottom" style="clear:both;"><?php print $content_bottom; ?></div>
<?php endif; ?>              
