<?php if ($user1 || $user2 || $user3): ?>
<div class="clear-block clr" id="section1">
  <div class="sections">
    <?php if ($user1): ?>
      <div class="section user1"><?php print $user1; ?></div>
    <?php endif; ?>
    <?php if ($user2): ?>
      <div class="section user2"><?php print $user2; ?></div>
    <?php endif; ?>
    <?php if ($user3): ?>
      <div class="section user3"><?php print $user3; ?></div>
    <?php endif; ?>
  </div>
</div><!-- /section1 -->

<!--<div style="margin:0px auto;margin-top:30px;border-bottom:1px solid #cccccc;width:900px;"></div>-->
<?php endif; ?>
