<?php
// $Id: node.tpl.php,v 1.00 2008/03/03 12:00:00 jaburns Exp $

if ($page != 0 ) {

/* IF YOU DO NOT WISH PAGING, DELETE ALL PHP BELOW */
$page_content = spliti('<br class="mobi" />', $content );
$nums         = count($page_content);

$offset  = ( isset($_GET['p']) AND is_numeric($_GET['p']) AND $_GET['p'] < $nums ) ? $_GET['p'] : 0; 

$content  = "\n". mobi_fix($page_content[$offset]) ."\n";
$content .= '<p>'. t('Page ') . ($offset+1) . t(' of ') . $nums .'</p>';

if ( $offset+1 < $nums ) {
$content .= '<p>'. 
    l(t('Next'), 'node/'.$node->nid, array('query' => 'p='. ($offset+1), 'attributes' => array('accesskey' => 6)) )
     .'</p>';
}

}
// REMOVE EVERYTHING ABOVE
?>
  <div class="node<?php if ($sticky) { print " sticky"; } ?><?php if (!$status) { print " node-unpublished"; } ?>">
    <?php if ($picture) {
      print $picture;
    }
    ?>
    <?php if ($page == 0) { ?><h2 class="title"><a href="<?php print $node_url?>"><?php print $title?></a></h2><?php }; ?>
    
      <?php if ($submitted): ?>
        <span class="submitted"><?php print $submitted; ?></span>
      <?php endif; ?>
 
    <div class="content"><?php print $content; ?></div>
    
       
    <?php if ($taxonomy AND $page != 0 )  { ?>
        <div class="taxonomy">Posted in: <?php print $terms?></div>
    <?php }; ?>
    
    <?php if ($links && $teaser): ?>
    <div class="links"> 
    <?php print l("Read more", "node/$node->nid", array('attributes' => 
    array('title' => "Read more on $node->title")) ); ?> &raquo;</div>
    <?php endif; ?>
  </div>