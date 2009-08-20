<div class="node<?php if ($sticky) { print " sticky"; } ?><?php if (!$status) { print " node-unpublished"; } ?>">
  <?php if ($picture) { print $picture; }?>

  <?php if ($page == 0) { ?>
    <?php if ($title) { ?>
      <h2 class="title"><a href="<?php print $node_url?>"><?php print $title?></a></h2>
    <?php }; ?>
  <?php }; ?>

  <?php if ($terms) { ?>
    <!--<span class="submitted"><?php print $submitted?></span>--> <span class="taxonomy"><?php print $terms?></span>
  <?php }; ?>
<!-- AddThis Button BEGIN -->
<script type="text/javascript">var addthis_pub="upei";</script>
<a href="http://www.addthis.com/bookmark.php" onmouseover="return addthis_open(this, '', '[URL]', '[TITLE]')" onmouseout="addthis_close()" onclick="return addthis_sendto()"><img src="http://s7.addthis.com/static/btn/lg-share-en.gif" width="125" height="16" border="0" alt="Bookmark and Share" style="border:0"/></a><script type="text/javascript" src="http://s7.addthis.com/js/152/addthis_widget.js"></script>
<!-- AddThis Button END -->

<?php if ($page == 0) { ?>
    <?php if ($title) { ?>
      <h2 class="title"><a href="<?php print $node_url?>"><?php print $title?></a></h2>
    <?php }; ?>
  <?php }; ?>

  <div class="content">
 <?
 if($field_award_process[0][view]){$award_process = "<strong>Award Process: </strong>" . $field_award_process[0][view];}
 $award_type = $field_award_type[0][view];
 $student_status = $field_award_student_status[0][view];
 $award_criteria = $field_award_criteria[0][view];
 $award_description = $field_award_description[0][view];
 //$award_process = $field_award_process[0][view];
 $award_name = $field_award_name[0][view];
 if ($field_award_maximum[0][view]) {$award_maximum = $field_award_maximum[0][view];}else {$award_maximum = "Consult Criteria for Information";}
 $award_occasion = $field_award_occasion[0][view];
 if ($field_award_faculty[0][view]) {$award_faculty = $field_award_faculty[0][view];}else {$award_faculty = "No Restrictions by Faculty";}
 if ($field_award_major[0][view]) {$award_major =  $field_award_major[0][view];}else {$award_major = "No Restrictions by Major";}
 if ($field_award_deadline[0][view]) {$award_deadline =  $field_award_deadline[0][view];} else {$award_deadline = "N/A";}
 if (preg_match('|^http://|', $field_award_app_link[0][view])){$award_app_link =  "<a href=\"" . $field_award_app_link[0][view] . "\">Application Form</a>";} 
 else if (!empty($field_award_app_link[0]['view'])) { $award_app_link = $field_award_app_link[0]['view']; }
 else {$award_app_link = "No Application Form";}
print $field_responsibility[0]['label_text'];
  ?>

 
<table  style="width:100%;margin:10px;"> 
  <!--<tr>
  	<td width="50%"><strong>Award Process:</strong> <?print $award_process; ?></td>
  </tr>-->
  <tr>
  	<td width="50%"><strong>Award Maximum:</strong> <? print $award_maximum; ?></td>
	<td width="50%"><strong>Award Occasion:</strong> <? print $award_occasion; ?></td>
  </tr>
  <tr>
        <td width="50%"><strong>Award Deadline:</strong> <? print $award_deadline; ?></td>
        <td width="50%"><? print $award_app_link; ?></td>
  </tr>
 <tr>
        <td width="50%"><strong>Award Faculty:</strong> <? print $award_faculty; ?></td>
        <td width="50%"><strong>Award Major:</strong> <? print $award_major; ?></td>
  </tr>
 <tr>
         <td width="50%"><strong>Award Type:</strong> <? print $award_type; ?></td>
         <td width="50%"><strong>Student Status:</strong> <? print $student_status; ?></td>
   </tr>

  </table>
 <table style="width:100%;">
  <tr>
        <td width="50%"><strong>Award Criteria:</strong> <?print $award_criteria; ?></td>
  </tr>
  <tr>
	<td style="padding-top:10px;"><? print $award_process; ?></td>
  </tr>
</table>
<h2><a href="http://cms.upei.ca/studentservices/award/entering-upei">Return to UPEI Scholarship main List</a> </h2>
  </div>
  <div class="clear-block clear"></div>


</div>
