<?php
  			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			// Created Novem 2008 to allow different banners for sub-sites @@
			// 
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
  			//Get the URL parts
			//Get how many levels are in the URL Bucket Name starting at [1]
			//Make the base path for the banners.
			//See if there is a folder for the sub sections
			//If it exists, pop in the banner from the sub folder
			//Else use the default bucket banner
			$url_part = explode("/", request_uri());
			$aCount = count($url_part);
			$bucket = $url_part[1];
			$mypath = "/var/www/drupal/cms/current/sites/upei.ca." . $bucket . "/themes/newsflash/images/banners/";
			for($x = 2; $x < $aCount; $x++){
				$mypath .= $url_part[$x] . "/";
			}
			$flag = 0;
			while($flag == 0 && $aCount > 2){
				$mypath  = ChopPath($mypath);
				$val = is_dir($mypath);
				if($val){
					$flag = 1;
					if($url_part[2]){ 
						$headerstyle = GetBanner(1, $mypath, $bucket);
					}else{
						$headerstyle = GetBanner(0, $mypath, $bucket);
					}
				}else{
					$mypath = str_replace($url_part[$aCount - 1] . "/", "", $mypath);
					$aCount = $aCount - 1;
					$headerstyle = GetBanner(0, $mypath, $bucket);
				}
			}
		?>
