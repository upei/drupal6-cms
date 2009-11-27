<div class="node-media node<?php if ($sticky) { print " sticky"; } ?><?php if (!$status) { print " node-unpublished"; } ?>">
  <div class="left">
    <div class="field field-field_news_image"><?= $field_news_image[0]['view']?></div>
    <div class="field field-field_news_image-data-title"><?= $field_news_image[0]['data']['title']?></div>
    <?php if ($field_pull_quote[0]['view']): ?>
    <div class="field field-field-pull-quote"><?= $field_pull_quote[0]['view']?></div>
    <?php endif; ?>
  </div>
  <div class="right">   
<!-- 
<fieldset>
      <legend>Useful Links</legend>
      <div class="links">
        <ul class="links">
          <li class="first last">
          <a href="<?=base_path()?>media">Return to Media Releases</a>
          </li>
        </ul>
      </div>
    <?php if ($links): ?>
      <div class="links"><?php print $links; ?></div>
    <?php endif; ?>
    </fieldset>
-->

<? if($field_contact_name[0]['value'] || $field_department[0]['value'] || $field_phone[0]['value'] || $field_email[0]['value']){?>
    <fieldset style="margin:0px 0px 0px 10px;">
      <legend>Contact Information</legend>
<?php if($field_contact_name[0]['value']){?>     
 <div class="field field-field-contact-name">
        <span class="label">Contact Person:</span>
        <span class="value"><?=$field_contact_name[0]['view']?></span>
      </div>
 <?}?>

<?php
if($field_department[0]['value']){?>
      <div class="field field-field-department">
        <span class="label">Department:</span>
        <span class="value"><?=$field_department[0]['view']?></span>
      </div>
<?}?>
<?php if($field_phone[0]['value']){?>
      <div class="field field-field-phone">
        <span class="label">Phone:</span>
        <span class="value"><?=$field_phone[0]['view']?></span>
      </div>
 <?}?>
<?php if ($field_email[0]['value']){ ?>
      <div class="field field-field-email">
        <span class="label">Email:</span>
        <span class="value"><?= $field_email[0]['safe']?></span>
      </div>
      <?php } ?>
    </fieldset>
<?php }?>
  </div>
  <div class="content">
    <? if ($page == 0): ?>
    <h2 class="title"><a href="<?=$node_url?>"><?=$title?></a></h2>
    <? endif; ?>
   <? /* <div class="date">Posted on <?php print date('l, j F Y', $created); ?></div> */?>
    <div class="field field-field-image"><?= $field_image[1]['view'] ?></div>
    <div class="field field-field-image-data-title"><?= $field_image[1]['data']['title'] ?></div>
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
