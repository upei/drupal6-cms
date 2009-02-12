<?php 
	//$bucket = _get_bucket(); 
	//if($bucket == "home"){$searchstyle="padding-right:15px;width:976px;background-image:url(/home/sites/all/themes/sunshine/images/market/home/bkgrd_search.gif);";}else{$searchstyle="width:1000px;";}
?>

<form style="float:right;" method="get" target="FlyFrame" action="http://websearch.cs.upei.ca/search">
   <input type="text" name="q" size="32" maxlength="256" value="" />
   <input type="submit" name="btnG" value="Search UPEI" />
   <input type="hidden" name="site" value="default_collection" />
   <input type="hidden" name="client" value="default_frontend" />
   <input type="hidden" name="output" value="xml_no_dtd" />
   <input type="hidden" name="proxystylesheet" value="default_frontend" />
   <input type="hidden" name="filter" value="p" />
   <input type="hidden" name="getfields" value="*" />
</form>

