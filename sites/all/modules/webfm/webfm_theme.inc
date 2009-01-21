<?php
// $Id: webfm_theme.inc,v 1.3 2008/12/02 17:53:50 robmilne Exp $
/**
 * Displays file attachments in table
 */
function theme_webfm_attachments($files) {
  global $base_url;
  $header = array(t('Attachment'));
  if($enable_date = variable_get('webfm_attach_date', '')) {
	  array_push($header, t('Date'));
  }
  if($enable_size = variable_get('webfm_attach_size', '')) {
	  array_push($header, t('Size'));
  }
  $rows = array();
  foreach ($files as $file) {
    // 0 =inline : 1 = attach
    $icon_path = $base_url.'/'.variable_get('webfm_icon_dir', '').'/'._webfm_get_icon($file->e);
	  $description = '';
    if(variable_get('webfm_attach_desc', '') && !empty($file->fdesc)) {
      $description = '<div class="att-fdesc">'.$file->fdesc.'</div>';
	  }
  	$filename = $file->ftitle ? $file->ftitle : $file->n;
  	if(variable_get('webfm_attach_new_window', '')) {
      $href = array(
        'data' => l('<img src="'.$icon_path.'" alt="[file]" title="Download '.$filename .'"/> ', 'webfm_send/'.$file->id.'/1',
        array('attributes' => array('title' => 'Download '.$filename,'target' => '_blank'), 'html' => TRUE))
        .l($filename, 'webfm_send/'.$file->id, array('attributes' => array('title' => 'Open '.$filename, 'target' => '_blank')))
        .$description, 'class' => 'att-title'
      );
    } else {
      $href = array(
        'data' => l('<img src="'.$icon_path.'" alt="[file]" title="Download '.$filename .'"/> ', 'webfm_send/'.$file->id.'/1',
        array('attributes' => array('title' => 'Download '.$filename), 'html' => TRUE))
        .l($filename, 'webfm_send/'.$file->id, array('attributes' => array('title' => 'Open '.$filename)))
        .$description, 'class' => 'att-title'
      );
    }

    $row = array();
    array_push($row, $href);
    if($enable_date) {
      $time = $file->fcreatedate ? date(webfm_get_date_format(), $file->fcreatedate) : date(webfm_get_date_format(),  @filemtime($file->p . '/'. $file->n));
      array_push($row, array('data' => $time, 'class' => 'att-time'));
    }
    if($enable_size) {
      array_push($row, array('data' => format_size($file->s), 'class' => 'att-size'));
    }
    array_push($rows, $row);
  }
  if (count($rows)) {
    return theme('table', $header, $rows, array('class' => 'webfm-attach-list'));
  }
}
