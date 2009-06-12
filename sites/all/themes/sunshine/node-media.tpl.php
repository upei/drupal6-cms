<div class="node-media node<?php if ($sticky) { print " sticky"; } ?><?php if (!$status) { print " node-unpublished"; } ?>">
  <div class="left">
    <div class="field field-field-image"><?= $field_image[0]['view']?></div>
    <div class="field field-field-pull-quote"><?= $field_pull_quote[0]['view']?></div>
  </div>
  <div class="right">
    <?php if ($links): ?>
    <fieldset>
      <legend>Useful Links</legend>
      <div class="links">
        <ul class="links">
          <li class="first last">
          <a href="<?=base_path()?>media">Return to Media Releases</a>
          </li>
        </ul>
      </div>
      <div class="links"><?php print $links; ?></div>
    </fieldset>
    <?php endif; ?>
    <fieldset>
      <legend>Contact Information</legend>
      <div class="field field-field-contact-name">
        <span class="label">Contact Person:</span>
        <span class="value"><?=$field_contact_name[0]['view']?></span>
      </div>
      <div class="field field-field-department">
        <span class="label">Department:</span>
        <span class="value"><?=$field_department[0]['view']?></span>
      </div>
      <div class="field field-field-phone">
        <span class="label">Phone:</span>
        <span class="value"><?=$field_phone[0]['view']?></span>
      </div>
    </fieldset>
  </div>
  <div class="content">
    <? if ($page == 0): ?>
    <h2 class="title"><a href="<?=$node_url?>"><?=$title?></a></h2>
    <? endif; ?>
    <div class="date">Posted on <?php print date('l, j F, Y'); ?></div>
    <div class="body">
    <?php
      // filter out unneccessary p tags
      print preg_replace(
        array("/<p>(&nbsp;| )*<\/p>/"),
        array(''),
        $body); ?>
    </div>
  </div>
  <div class="clear-block clear"></div>

</div>
