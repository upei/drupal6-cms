<div class="node-<?=$type?> node<?php if ($sticky) { print " sticky"; } ?><?php if (!$status) { print " node-unpublished"; } ?>">
  <div class="left">
    <div class="field field-field-photo"><?= $field_photo[0]['view']?></div>
    <div class="field field-field-pull-quote"><?= $field_pull_quote[0]['view']?></div>
  </div>
  <div class="right">
    <fieldset>
      <legend>Useful Links</legend>
      <div class="links">
        <ul class="links">
          <li class="first last">
            <a href="<?=base_path()?>blogs">Return to Blogs</a>
          </li>
        </ul>
      </div>
    <?php if ($links): ?>
      <div class="links"><?php print $links; ?></div>
    <?php endif; ?>
    </fieldset>
  </div>
  <div class="content">
    <? if ($page == 0): ?>
    <h2 class="title"><a href="<?=$node_url?>"><?=$title?></a></h2>
    <? endif; ?>
    <div class="date">Posted on <?php print date('l, j F, Y', $created); ?></div>
    <div class="body">
    <?php
      // filter out unneccessary p tags
      print preg_replace(
        array("/<p>(&nbsp;| )*<\/p>/"),
        array(''),
        $content); ?>
    </div>
  </div>
  <div class="clear-block clear"></div>
</div>
