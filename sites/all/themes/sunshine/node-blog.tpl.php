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
            <a href="<?=base_path()?>blogs/external">More Blog Posts</a><br />
            <a href="<?=base_path()?>blogs/internal">Research Milieu</a>
          </li>
        </ul>
      </div>
    <!--
    <?php if ($links): ?>
      <div class="links"><?php print $links; ?></div>
    <?php endif; ?>
    -->
    </fieldset>
  </div>
  <div class="content">
    <? if ($page == 0): ?>
    <h2 class="title"><a href="<?=$node_url?>"><?=$title?></a></h2>
    <? endif; ?>
    <div class="date">Posted on <?php print date('l, j F Y', $created); ?>
<div style="display: block; float: right;">
<!-- AddThis Button BEGIN -->
<a href="http://www.addthis.com/bookmark.php?v=250&pub=xa-4a5b85f028866018" onmouseover="return addthis_open(this, '', '[URL]', '[TITLE]')" onmouseout="addthis_close()" onclick="return addthis_sendto()"><img style="margin: 0;" src="http://s7.addthis.com/static/btn/lg-share-en.gif" width="125" height="16" alt="Bookmark and Share" style="border:0"/></a><script type="text/javascript" src="http://s7.addthis.com/js/250/addthis_widget.js?pub=xa-4a5b85f028866018"></script>
<!-- AddThis Button END -->
</div>
</div>
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
