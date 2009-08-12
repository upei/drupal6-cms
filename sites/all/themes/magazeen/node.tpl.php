<?php
// $Id: node.tpl.php,v 1.7.2.2 2009/05/04 07:31:23 zinv Exp $

/**
 * @file node.tpl.php
 *
 * Theme implementation to display a node.
 *
 * Available variables:
 * - $title: the (sanitized) title of the node.
 * - $content: Node body or teaser depending on $teaser flag.
 * - $picture: The authors picture of the node output from
 *   theme_user_picture().
 * - $date: Formatted creation date (use $created to reformat with
 *   format_date()).
 * - $links: Themed links like "Read more", "Add new comment", etc. output
 *   from theme_links().
 * - $name: Themed username of node author output from theme_user().
 * - $node_url: Direct url of the current node.
 * - $terms: the themed list of taxonomy term links output from theme_links().
 * - $submitted: themed submission information output from
 *   theme_node_submitted().
 *
 * Other variables:
 * - $node: Full node object. Contains data that may not be safe.
 * - $type: Node type, i.e. story, page, blog, etc.
 * - $comment_count: Number of comments attached to the node.
 * - $uid: User ID of the node author.
 * - $created: Time the node was published formatted in Unix timestamp.
 * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in
 *   teaser listings.
 * - $id: Position of the node. Increments each time it's output.
 *
 * Node status variables:
 * - $teaser: Flag for the teaser state.
 * - $page: Flag for the full page state.
 * - $promote: Flag for front page promotion state.
 * - $sticky: Flags for sticky post setting.
 * - $status: Flag for published status.
 * - $comment: State of comment settings for the node.
 * - $readmore: Flags true if the teaser content of the node cannot hold the
 *   main body content.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 *
 * @see template_preprocess()
 * @see template_preprocess_node()
 */
?>

<div id="node-<?php print $node->nid; ?>" class="node <?php print $node_classes; ?>"><div class="node-inner">

  <div class="post-meta clearfix">
    <h2 class="post-title left">
      <a href="<?php print $node_url; ?>" title="<?php print $title ?>"><?php print $title; ?></a>
    </h2>

    <?php if ($unpublished): ?>
      <div class="unpublished"><?php print t('Unpublished'); ?></div>
    <?php endif; ?>

    <p class="post-info right">
      <?php if ($submitted): ?>
        <?php print $submitted; ?>
      <?php endif; ?>
    </p>  
  </div>

  <div class="post-box">
    <div class="post">
      <?php if ($teaser): ?>
        <?php if (!$page && isset($comment_link)): ?>
          <div class="comment-count">
            <?php print $comment_link; ?>
          </div>
        <?php endif; ?>
      <?php endif; ?>
      <?php print $picture; ?>
      <?php print $content; ?>
      <?php print $links; ?>
    </div>
    <?php if ($teaser): ?>
      <div class="post-footer clearfix">
        <?php if (!$page && isset($node_read_more)): ?>
          <div class="continue-reading">
            <?php print $node_read_more; ?>
          </div>
        <?php endif; ?>
        <div class="category-menu">
          <?php if ($terms): ?>
            <?php print $terms; ?>
          <?php endif; ?>
        </div>
      </div>
    <?php endif; ?>
  </div>

</div></div> <!-- /node-inner, /node -->