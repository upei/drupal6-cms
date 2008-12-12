 <?php
  //add the style to make the top banner randomly show a different picture
  
  //Generate a Random Number
function _RandomImage(){
  	srand(time());
	$intRandom = (rand()%9);
  
  	switch ($intRandom){
	Case 0:
		$headimage = "graphic10.jpg";
	break;
	Case 1:
		$headimage = "graphic.jpg";
	break;
	Case 2:
	$headimage = "graphic2.jpg";
	break;
	Case 3:
		$headimage = "graphic3.jpg";
	break;
	Case 4:
		$headimage = "graphic4.jpg";
	break;
	Case 5:
		$headimage = "graphic5.jpg";
	break;
	Case 6:
		$headimage = "graphic6.jpg";
	break;
	Case 7:
		$headimage = "graphic7.jpg";
	break;
	Case 8:
		$headimage = "graphic8.jpg";
	break;
	Case 9:
		$headimage = "graphic9.jpg";
	break;
	}
	$_val = "#header{height:126px;background-image: url(/home/sites/all/themes/newsflash/images/market/home/". $headimage .")}";
 	return $_val;
 }
 
 ?>
