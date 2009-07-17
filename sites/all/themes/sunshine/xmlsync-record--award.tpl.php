<div class="node node-<?=$node->type?>">
 <div id="awardtable">
 <h2 style="margin-left:10px;"><?=x($data,'/data/name')?></h2>
 	
 <table border="1" cellspacing="0">
 <tr height="14">
 <th colspan="2" style="border:none;text-align:right;background-color:#e8e8e8;">
 	<!-- AddThis Button BEGIN -->
	<script type="text/javascript">var addthis_pub="upei";</script>
	<a href="http://www.addthis.com/bookmark.php" onmouseover="return addthis_open(this, '', '[URL]', '[TITLE]')" onmouseout="addthis_close()" onclick="return addthis_sendto()"><img src="http://s7.addthis.com/static/btn/lg-share-en.gif" width="125" height="16" border="0" alt="Bookmark and Share" style="border:0"/></a><script type="text/javascript" src="http://s7.addthis.com/js/152/addthis_widget.js"></script>
	<!-- AddThis Button END -->
 </th>
 </tr>
 <tr>
 	<td style="width:200px;"><strong>Award Maximum:</strong></td>
  <td><?=x($data, '/data/maximum-amount') ?
         x($data,'/data/maximum-amount') : t('To Be Determined')?></td>
 </tr>
 
 <tr>
 	<td><strong>Award Occasion:</strong></td>
	<td><?=x($data,'/data/occasion')?></td>
 </tr>
  <tr>
 	<td><strong>Award Deadline:</strong></td>
  <td><?=x($data,'/data/deadline') ?
         x($data,'/data/deadline') : t('No Deadline')?></td>
 </tr>
  <tr>
 	<td><strong>Application Form:</strong></td>
  <td><?=x($data,'/data/application-form-link') ?
         l(t('Application Form'), x($data,'/data/application-form-link')) : t('No Application Form')?></td>
 </tr>
  <tr>
 	<td><strong>Award Faculty:</strong></td>
  <td><?=x($data,'/data/faculty/name') ?
         x($data,'/data/faculty/name') : t('No Restrictions by Faculty')?></td>
 </tr>
  <tr>
 	<td><strong>Award Major:</strong></td>
  <td><?=x($data,'/data/major/name') ?
         x($data,'/data/major/name') : t('No Restrictions by Major')?></td>
 </tr>
  <tr>
 	<td><strong>Award Type:</strong></td>
	<td><?=x($data,'/data/type')?></td>
 </tr>
  <tr>
 	<td><strong>Student Status:</strong> </td>
	<td><?=x($data,'/data/student-status')?></td>
 </tr>
  <tr>
 	<td valign="top"><strong>Award Criteria:</strong></td>
	<td><?=x($data,'/data/criteria')?></td>
 </tr>
 <tr>
 	<td><strong>Award Process: </strong></td>
	<td><?=x($data,'/data/process')?></td>
 </tr>
 </table>
 </div>
<h2><a href="http://cms.upei.ca/studentservices/award/totalyear/">Return to UPEI Scholarship main List</a> </h2>
  </div>
  <div class="clear-block clear"></div>
</div>
