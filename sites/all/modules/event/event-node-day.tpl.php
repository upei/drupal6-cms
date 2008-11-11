<?php
// $Id: event-node-day.tpl.php,v 1.6 2008/10/26 18:55:25 killes Exp $

/**
 * @file event-node-day.tpl.php
 * Display an event in the day view.
 *
 * Available variables:
 * - $zebra: Either "even" or "odd", depending on the position of the event in the calendar.
 * - $links: Links added at the bottom of the event.
 * - $teaser: Teaser of the event, sanitized.
 * - $node_type: Node type
 * - $show_calendar_link: If a link to all the events of this type should be shown.
 * - $calendar_link: Link to the calendar for all events of this type
 * - $node_title_unsafe: Unfiltered event title, use only in l() functions
 * - $node_title_safe: Sanitized version of the title
 * - $node_link: URL to the event's detail page 
 * - $show_start: If the start date should be shown
 * - $show_end: If the end date should be shown
 * - $start_date: The unformatted start date
 * - $end_date: The unformatted end date
 * - $start_date_utc: The unformatted start date (UTC)
 * - $end_date_utc: The unformatted end date (UTC)
 * - $start_date_formatted: The formatted start date, according to the chosen settings
 * - $end_date_formatted: The formatted end date, according to the chosen settings
 *
 * @see template_preprocess_event_node_day()
 */
?>
<div class="event dayview vevent <?php print $zebra ?> ">
  <?php if ($show_calendar_link) { ?>
    <div class="type"> <?php print l("($node_type)", $calendar_link, array('attributes' => array('title' => t('limit view to events of this type')))) ?> </div>
  <?php } ?>
  <div class="title summary"><?php print l($node_title_unsafe, $node_link, array('attributes' => array('title' => t('view this event'))))?></div>
  <?php if ($show_start) { ?>
    <div class="start dtstart" title="<?php print event_format_date($start_date_utc, 'custom', "Y-m-d\TH:i:s\Z") ?>"><?php print t('Start: ') . $start_date_formatted ?></div>
  <?php } ?>
   <?php if ($show_end) { ?>
     <div class="end dtend" title="<?php print event_format_date($end_date_utc, 'custom', "Y-m-d\TH:i:s\Z") ?>"><?php print t('End: ') . $end_date_formatted ?></div>
  <?php } ?>

  <div class="content description"><?php print $teaser ?></div>
  <div class="links"><?php print $links ?></div>
</div>
