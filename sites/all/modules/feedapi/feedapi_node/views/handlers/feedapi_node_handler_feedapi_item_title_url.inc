<?php
// $Id: feedapi_node_handler_feedapi_item_title_url.inc,v 1.1.2.2 2008/10/09 06:43:31 aronnovak Exp $

/**
 * Field handler to provide title links to drupal nodes
 *
 * @ingroup views_field_handlers
 */
class feedapi_node_handler_feedapi_item_title_url extends views_handler_field {
  
  function query() {
    $this->ensure_my_table();
    $this->query->add_field('node', 'title', 'item_title');
    $this->query->add_field('feedapi_node_item', 'url', 'original_item_url');
    $this->add_additional_fields();
  }
  
  function render($values) {
    return l(check_plain($values->item_title), $values->original_item_url, array('html' => TRUE));
  }

}
