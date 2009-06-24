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
      <?php if ($field_title && $field_title[0]['value']): ?>
      <div class="field field-field-title">
        <span class="label">Title</span>
        <span class="value"><?=$field_title[0]['safe']?></span>
      </div>
      <?endif;?>
      <?php if ($field_faculty_status && $field_faculty_status[0]['value']): ?>
      <div class="field field-field-faculty-status">
        <span class="label">Faculty Status</span>
        <span class="value"><?=$field_faculty_status[0]['safe']?></span>
      </div>
      <?php endif; ?>
      <?php if ($field_education && $field_education[0]['value']): ?>
      <div class="field field-field-education">
        <span class="label">Education</span>
        <span class="value"><?=$field_education[0]['safe']?></span>
      </div>
      <?php endif; ?>
      <?php if ($field_department && $field_department[0]['value']): ?>
      <div class="field field-field-department">
        <span class="label">Department</span>
        <span class="value"><?=$field_department[0]['safe']?></span>
      </div>
      <?php endif; ?>
      <?php if ($field_office && $field_office[0]['value']): ?>
      <div class="field field-field-office">
        <span class="label">Office</span>
        <span class="value"><?=$field_office[0]['safe']?></span>
      </div>
      <?php endif; ?>
      <?php if ($field_email && $field_email[0]['email']): ?>
      <div class="field field-field-email">
        <span class="label">Email</span>
        <span class="value"><?=$field_email[0]['safe']?></span>
      </div>
      <?php endif; ?>
      <?php if ($field_phone && $field_phone[0]['value']): ?>
      <div class="field field-field-phone">
        <span class="label">Phone</span>
        <span class="value"><?=$field_phone[0]['value']?></span>
      </div>
      <?php endif; ?>
      <?php if ($field_fax && $field_fax[0]['value']): ?>
      <div class="field field-field-fax">
        <span class="label">Fax</span>
        <span class="value"><?=$field_fax[0]['value']?></span>
      </div>
      <?php endif; ?>
      <?php if ($field_link && $field_link[0]['url']): ?>
      <div class="field field-field-link">
        <span class="label">Link</span>
        <span class="value"><?=$field_link[0]['view']?></span>
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
  </div>
</div>
