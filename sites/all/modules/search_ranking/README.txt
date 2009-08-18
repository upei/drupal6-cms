Search Ranking 6.x

Project Page: http://drupal.org/project/search_ranking
Issue Queue: http://drupal.org/project/issues/search_ranking

Summer of Code 2008: http://drupal.org/node/10906

About:
This module was created for the Drupal CMS as part of a Google Summer of Code
2008 project.  This module allows Drupal 6.x users to take advantage of a 
new feature that will be available in Drupal 7.x (thanks to douggreen) that
enables search results to be scored differently based on a number of ranking
factors.

This module overrides the default search provided by node.module.  Site
administrators who are looking to use this on an existing website will not
have to worry about users with bookmarked search pages getting 404 errors because it seemlessly overrides the search behavior provided by node.module
while extending the ranking factors by providing hook_ranking().

Todo:

- Override the default node search with this module. [DONE]
- Provide implementations of hook_ranking from node_search(). [DONE]
- Write simpletest coverage.
- Provide AHAH search results on admin settings page to provide a preview
  of how changing ranking settings will change result ranking.
- Provide implementations of hook_ranking() for the following.
  - Sticky (nodes marked as sticky receive higher score) [DONE]
  - Promoted (nodes marked as promoted receive higher score) [DONE]
  - Relevancy (number of keywords present in the node/comments) [DONE]
  - Recency (the currentness of the node) [DONE]
  - Comments (how many comments the node has)
  - Statistics (how many visits the node has)
  - Average Vote Score (votingapi/fivestar)
  - Total Votes (votingapi/fivestar)