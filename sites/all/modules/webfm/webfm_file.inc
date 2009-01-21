<?php
/* $Id: webfm_file.inc,v 1.11 2008/10/15 17:16:56 robmilne Exp $ */

/**
 * webfm_mkdir -called from the ajax action - switch case 'mkdir':
 *
 * @param string $source - the source directory path
 * @param string $dest - the destination directory name
 *
 * @ret string   -name of directory if created
 *      FALSE    -if unsuccessful
 */
function webfm_mkdir($source, $dest, $rename = FALSE, &$error){
  $mkdir_path = ($source.'/'.$dest);
  if (!is_dir($mkdir_path)) {
    if(@mkdir($mkdir_path)) {
      chmod($mkdir_path, 0775);
      if (!is_writable($mkdir_path))
        $error = t('The directory ').$mkdir_path.t(' is not writable');
      else
        return $mkdir_path;
    }
  } else if($rename == TRUE) {
    $count = 0;
    while(is_dir($munge_path = ($mkdir_path.'_'.$count))){
      $count++;
    }
    if(@mkdir($munge_path)) {
      chmod($munge_path, 0775);
      if (!is_writable($munge_path))
        $error = t('The directory ').$munge_path.t(' is not writable');
      else
        return $munge_path;
    } else {
      $error = t('mkdir for ').$munge_path.t(' failed');
    }
  } else {
    $error = t('The directory ').$mkdir_path.t(' already exists');
  }
  return FALSE;
}

/**
 * webfm_rename -called from the ajax action - switch case 'rename':
 *
 * @param string  $source - the source directory path
 * @param string  $dest - the destination directory name
 * @param bool    $uid - user id
 * @param string &$err_arr - ref to error array for client feedback
 *
 * @ret   bool   -true if the directory/file is renamed and file record(s)
 *                updated if dir/file under db control
 */
function webfm_rename($source, $dest, $uid, &$err_arr) {
  $dest_temp = $dest.'~'; //handle possible case problem
  //File
  //if target is a file and new name isn't already used...
  if(is_file($source) && !is_file($dest)) {
    $file_o = webfm_get_file_record('', $source);
    //if we are admin or owner of target file...
    if($uid == 1 ||
       ($file_o && ($uid == $file_o->uid)) ||
       ($file_o && webfm_file_mod_access($file_o))) {
      //check validity of new file name
      $file = new stdClass();
      $file->filename = basename($dest);
      $file->filepath = $source;
      $file->filesize = 0; //avoid fail for size - we're interested in extensions
      if(webfm_enum_validate($file, $err_arr) === FALSE) {
        //illegal file extension
        $err_arr[] = t('Invalid name');
        return FALSE;
      }
      //if file is not read-only...rename
      if(@rename($source, $dest_temp)) {
        if(!@rename($dest_temp, $dest)) {
          @rename($dest_temp, $source);
          $err_arr[] = t('rename ').basename($source).t(' fail');
          return FALSE;
        }
      } else {
        $err_arr[] = basename($source).t(' read-only');
        return FALSE;
      }
    } else {
      $err_arr[] = t('permission denied');
      return FALSE;
    }
    return(webfm_rename_db_file($source, $dest, $err_arr));
  }

  //Directory
  //if target is a directory, new name is a unique path and we are an admin...
  else if(is_dir($source) && !is_dir($dest) && ($uid == 1)) {
    //if the target isn't read-only
    if(@rename($source, $dest_temp)) {
      //directory rename is OK, back out, rename db files and rename dir again
      @rename($dest_temp, $source);
      if(webfm_rename_db_dir_recur($source, $dest, TRUE, $err_arr)) {
        @rename($source, $dest_temp);
        @rename($dest_temp, $dest);
      } else {
        $err_arr[] = t('webfm_rename_db_dir_recur error - db may be corrupted');
        drupal_set_message(t('webfm_rename_db_dir_recur error - db may be corrupted'), error);
        return FALSE;
      }
      return TRUE;
    } else {
      $err_arr[] = $source.' read-only';
      return FALSE;
    }
  }

  $err_arr[] = 'rename '.array_pop(explode('/', $source)).' to '.array_pop(explode('/', $dest)).' fail';

  return FALSE;
}

function webfm_rename_db_file($source, $dest, &$err_arr) {
  if($fid = webfm_get_fid($source)) {
    if(!webfm_dbupdate_file($fid, $dest)) {
      $err_arr[] = t('webfm_dbupdate_file error - fid: ').$fid;
      return FALSE;
    }
  }
  return TRUE;
}

function webfm_rename_db_dir_recur($source, $dest, $ret, &$err_arr) {
  if($handle = opendir($source)) {
    while(($file = readdir($handle)) !== FALSE) {
      if($file != '.' && $file != '..') {
        $source_item  = $source.'/'.$file;
        $dest_item = $dest.'/'.$file;
        if(is_file($source_item)) {
          if(!(webfm_rename_db_file($source_item, $dest_item, $err_arr)))
            $ret = FALSE;
        } elseif(is_dir($source_item)) {
          $ret = webfm_rename_db_dir_recur($source_item, $dest_item, $ret, $err_arr);
        }
      }
    }
    closedir($handle);
  }
  return $ret;
}

/**
 * webfm_delete_dir_recur - called from the ajax action - switch case 'delete':
 *
 * @param string $source - the source directory path
 * @param bool   $ret - return value seed
 * @param string &$err_arr - ref to error array for client feedback
 *
 * @ret   bool   -true if the directory or file is deleted and all file records updated
 */
function webfm_delete_dir_recur($source, $ret, &$err_arr) {
  if($handle = opendir($source)) {
    while(($file = readdir($handle)) !== FALSE) {
      if($file != '.' && $file != '..') {
        $source_item  = $source.'/'.$file;
        if(is_file($source_item)) {
          if(!(webfm_delete_file($source_item, $error))) {
            $err_arr[] = $error;
            $ret = FALSE;
          }
        } elseif (is_dir($source_item)) {
          webfm_delete_dir_recur($source_item, $ret, $err_arr);
        }
      }
    }
    closedir($handle);
  } else {
    $err_arr[] = t('Unable to opendir ').$source;
    return FALSE;
  }
  if(($retn = rmdir($source)) == FALSE)
    $err_arr[] = t('Unable to rmdir ').$source;
  return ($retn == TRUE && $ret == TRUE);
}

function webfm_delete_file($source, &$error) {
  $file = webfm_get_file_record('', $source);
  if(@unlink($source)) {
    if($file && (!webfm_dbdelete_file($file->fid))) {
      $error = t('webfm_dbdelete_file() fail for ').$source;
      return FALSE;
    }
  } else if(file_exists($source)) {
    $error = $source.t(' could not be deleted');
    return FALSE;
  }
  return TRUE;
}

/**
 * Move a directory or file and update database
 *
 * @param string  $source - the source directory path
 * @param string  $dest - the destination directory name
 * @param bool    $uid - uid of user making move request
 * @param string &$err_arr - ref to error array for client feedback
 *
 * @ret   bool   -true if any directory change (used to switch client cache)
 *
 */
function webfm_move($source, $dest, $uid, &$err_arr) {
  $dest .= '/' . strrev(substr(strrev($source), 0, strpos(strrev($source), '/')));
  return(webfm_rename($source, $dest, $uid, $err_arr));
}

/**
 * webfm_insert_file - inserts a file into the webfm_file table
 *
 * @param string  $path - path relative to drupal root
 * @param string &$err_arr - ref to error array for client feedback
 *
 * @return bool - TRUE if query executed successfully, otherwise FALSE
 */
function webfm_insert_file($path, &$err_arr){
  if(!webfm_get_fid($path)) {
    $file = new stdClass();
    $file->filepath = $path;
    if(webfm_enum_validate($file, $err_arr)) {
      if(($ret = webfm_dbinsert_file($file, $err)) === FALSE) {
        $err_arr[] = $err;
      }
      return $ret;
    }
  } else {
    $err_arr[] = $path .t(' already in db');
  }
  return FALSE;
}

/**
 * webfm_insert_dir - inserts files into the webfm_file table
 *
 * @param string  $path - path relative to drupal root
 * @param bool    $recur - flag to indicate if recursive operation into sub-dirs
 * @param string &$err_arr - ref to error array for client feedback
 *
 * @return obj - contains error flag and count of successful and failed inserts
 */
function webfm_insert_dir($path, $recur, &$err_arr){
  $result = new stdClass();
  $result->cnt = 0;
  $result->errcnt = 0;
  if($handle = opendir($path)) {
    $bl = array('.', '..', '.svn', '.htaccess');
    while(false !== ($file = readdir($handle))) {
      if(!in_array(strtolower($file), $bl)){
        $file_path = $path.'/'.$file;
        if(is_file($file_path)) {
          // file
          if(webfm_insert_file($file_path, $err_arr)) {
            $result->cnt++;
          } else {
            $result->errcnt++;
          }
        } else if($recur && is_dir($file_path)) {
          $nest_result = webfm_insert_dir($file_path, $recur, $err_arr);
          $result->cnt += $nest_result->cnt;
          $result->errcnt += $nest_result->errcnt;
        }
      }
    }
    closedir($handle);
  } else {
    $err_arr[] = t('Cannot open dir ').$path;
  }
  return $result;
}
?>
