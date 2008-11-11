<?php
// $Id: feedapi_handler_feedapi_title_nid.inc,v 1.1.2.1 2008/10/01 19:14:13 aronnovak Exp $

/**
 * Field handler to provide title links
 *
 * @ingroup views_field_handlers
 */
class feedapi_handler_feedapi_title_nid extends views_handler_field {
  
  function query() {
    $this->ensure_my_table();
    $this->query->add_field('node', 'title', 'feed_title');
    $this->query->add_field('node', 'nid', 'feed_nid');
    $this->add_additional_fields();
  }
  
  function render($values) {
    return l(check_plain($values->feed_title), 'node/'. $values->feed_nid);
  }

}
