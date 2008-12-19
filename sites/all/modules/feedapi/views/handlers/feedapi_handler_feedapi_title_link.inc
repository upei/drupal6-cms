<?php
// $Id: feedapi_handler_feedapi_title_link.inc,v 1.1.2.2 2008/10/24 20:14:38 alexb Exp $

/**
 * Field handler to provide title links to drupal nodes
 *
 * @ingroup views_field_handlers
 */
class feedapi_handler_feedapi_title_link extends views_handler_field {
  
  function query() {
    $this->ensure_my_table();
    $this->query->add_field('node', 'title', 'feed_title');
    $this->query->add_field('feedapi_standalone', 'link', 'feed_link');
    $this->query->add_field('feedapi_standalone', 'url', 'feed_url');
  }
  
  function render($values) {
    if ($values->feed_link) {
      return l(check_plain($values->feed_title), $values->feed_link, array('html' => TRUE));
    }
    else {
      return l(check_plain($values->feed_title), $values->feed_url, array('html' => TRUE));
    }
  }
}
