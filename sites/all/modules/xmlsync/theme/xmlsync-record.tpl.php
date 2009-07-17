<?
// $Id: xmlsync-record.tpl.php,v 1.1 2009/07/17 14:28:10 gzfelix Exp $
?>
<div class="xmlsync-record">
  <div class="xmlsync-record-description">
    <?=$record->entity_description?>
  </div>
  <pre class="xmlsync-record-data">
    <?=htmlentities($record->data)?>
  </pre>
</div>
