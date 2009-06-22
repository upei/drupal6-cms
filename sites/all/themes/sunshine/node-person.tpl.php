<div class="node node-person node-<?=$type?><?php if ($sticky) { print " sticky"; } ?><?php if (!$status) { print " node-unpublished"; } ?>">
  <? if ($page == 0): ?>
  <? if ($content): ?>
  <h2 class="title"><a href="<?=$node_url?>"><?=$title?></a></h2>
  <? else: ?>
  <h2 class="title"><?=$title?></h2>
  <? endif; ?>
  <? endif; ?>
  <div class="right">
    <fieldset class="contact-infomation">
      <div class="field field-field-faculty-member-photo" style="float: right;">
        <?=$field_faculty_photo[0]['view']?>
      </div>
      <legend>Contact Information</legend>
      <div class="field field-field-title">
        <span class="label">Title</span>
        <span class="value"><?=$field_title[0]['safe']?></span>
      </div>
      <?php if ($field_faculty_status): ?>
      <div class="field field-field-faculty-status">
        <span class="label">Faculty Status</span>
        <span class="value"><?=$field_faculty_status[0]['safe']?></span>
      </div>
      <?php endif; ?>
      <?php if ($field_education): ?>
      <div class="field field-field-education">
        <span class="label">Education</span>
        <span class="value"><?=$field_education[0]['safe']?></span>
      </div>
      <?php endif; ?>
      <div class="field field-field-department">
        <span class="label">Department</span>
        <span class="value"><?=$field_department[0]['safe']?></span>
      </div>
      <div class="field field-field-office">
        <span class="label">Office</span>
        <span class="value"><?=$field_office[0]['safe']?></span>
      </div>
      <div class="field field-field-email">
        <span class="label">Email</span>
        <span class="value"><?=$field_email[0]['safe']?></span>
      </div>
      <div class="field field-field-phone">
        <span class="label">Phone</span>
        <span class="value"><?=$field_phone[0]['value']?></span>
      </div>
      <?php if ($field_fax): ?>
      <div class="field field-field-fax">
        <span class="label">Fax</span>
        <span class="value"><?=$field_fax[0]['safe']?></span>
      </div>
      <?php endif; ?>
      <?php if ($field_link): ?>
      <div class="field field-field-link">
        <span class="label">Link</span>
        <span class="value"><?=$field_link[0]['safe']?></span>
      </div>
      <?php endif; ?>
    </fieldset>
    <?php if ($links && !$view): ?>
    <fieldset>
      <legend>Useful Links</legend>
      <div class="links"><?php print $links; ?></div>
    </fieldset>
    <?php endif; ?>
  </div>
  <div class="content">
    <? if (!$view): ?>
    <div class="body">
      <?= $content ?>
    </div>
    <? endif; ?>
    <?php if (!$is_front && $type != 'landingpage' && !$view): ?>
    <div class="clear-block clear"></div>
    <div class="date"><? if (date('jFY', $changed) != date('jFY', $created)): ?> Updated on <?php print date('l, j F, Y.', $changed); endif; ?>
    Created on <?php print date('l, j F, Y', $created); ?>.</div>
    <?php endif; ?>
  </div>
</div>
