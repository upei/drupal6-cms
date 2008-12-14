<?php 
	$bucket = _get_bucket(); 
	if($bucket == "home" || $bucket == "avc"){$searchstyle="padding-right:15px;width:976px;background-image:url(/home/sites/all/themes/newsflash/images/market/". $bucket ."/bkgrd_search.gif);";}else{$searchstyle="width:1000px;";}
?>
<div align="center">
<div style="<?php print $searchstyle; ?>">
<div align = "right" id="google_search_box">
<form method="GET" target="FlyFrame" action="http://websearch.cs.upei.ca/search">
   <input type="text" name="q" size="32" maxlength="256" value="" />
   <input type="submit" name="btnG" value="Search UPEI" />
   <input type="hidden" name="site" value="default_collection" />
   <input type="hidden" name="client" value="default_frontend" />
   <input type="hidden" name="output" value="xml_no_dtd" />
   <input type="hidden" name="proxystylesheet" value="default_frontend" />
   <input type="hidden" name="filter" value="p" />
   <input type="hidden" name="getfields" value="*" />
</form>
</div>
</div>
    </div>
