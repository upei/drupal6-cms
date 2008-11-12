<?php
// $Id: fckeditor.lib.inc,v 1.1.2.5 2008/09/22 20:21:21 hass Exp $
/**
 * FCKeditor - The text editor for Internet - http://www.fckeditor.net
 * Copyright (C) 2003-2008 Frederico Caldeira Knabben
 *
 * == BEGIN LICENSE ==
 *
 * Licensed under the terms of any of the following licenses at your
 * choice:
 *
 *  - GNU General Public License Version 2 or later (the "GPL")
 *    http://www.gnu.org/licenses/gpl.html
 *
 *  - GNU Lesser General Public License Version 2.1 or later (the "LGPL")
 *    http://www.gnu.org/licenses/lgpl.html
 *
 *  - Mozilla Public License Version 1.1 or later (the "MPL")
 *    http://www.mozilla.org/MPL/MPL-1.1.html
 *
 * == END LICENSE ==
 *
 * @file
 * FCKeditor Module for Drupal 6.x
 *
 * This module allows Drupal to replace textarea fields with FCKeditor.
 *
 * This HTML text editor brings to the web many of the powerful functionalities
 * of known desktop editors like Word. It's really  lightweight and doesn't
 * require any kind of installation on the client computer.
 */

/**
 * Guess the absolute server path to the document root
 * Usually it should return $_SERVER['DOCUMENT_ROOT']
 *
 * @todo Improve me!!
 * Returns absolute path or false on failure
 *
 * @return string|boolean
 */
function fckeditor_get_document_root_full_path() {
  $found=0;
  $index_dir  = realpath(dirname($_SERVER['SCRIPT_FILENAME'])); // {/dir1/dir2/home/drupal}/index.php
  if (getcwd() == $index_dir) {
    $found++;
  }
  $drupal_dir = base_path();
  $index_dir  = str_replace('\\', "/", $index_dir);
  $drupal_dir = str_replace('\\', "/", $drupal_dir);
  $document_root_dir   = $index_dir .'/'. str_repeat('../', substr_count($drupal_dir, '/')-1);
  $document_root_dir   = realpath($document_root_dir);
  $document_root_dir   = rtrim($document_root_dir, '/\\');
  if ($document_root_dir == $_SERVER['DOCUMENT_ROOT']) {
    $found++;
  }
  $document_root_dir   = str_replace('\\', '/', $document_root_dir);

  if ($document_root_dir != '') {
    $found++;
  }
  if (file_exists($document_root_dir)) {
    $found++;
  }
  if (file_exists($document_root_dir . base_path() .'includes/bootstrap.inc')) {
    $found++;
  }

  if ($found >= 3) {
    return $document_root_dir;
  }
  else{
    return FALSE;
  }
}

/**
 * Emulates the asp Server.mapPath function.
 * Given an url path return the physical directory that it corresponds to.
 *
 * Returns absolute path or false on failure
 *
 * @param string $path
 * @return @return string|boolean
 */
function fckeditor_resolve_url($path) {
  if (function_exists('apache_lookup_uri')) {
    $info = @apache_lookup_uri($path);
    if (!$info) {
      return FALSE;
    }
    return $info->filename . $info->path_info ;
  }

  $document_root = fckeditor_get_document_root_full_path();
  if ($document_root !== FALSE) {
    return $document_root . $path;
  }

  return FALSE;
}

function fckeditor_load_toolbar_options() {
  $arr = array();
  $module_drupal_path = drupal_get_path('module', 'fckeditor');
  $editor_local_path  = fckeditor_path(TRUE);
  $fckconfig_js = $editor_local_path .'/fckconfig.js';
  $fckeditor_config_js = $module_drupal_path .'/fckeditor.config.js';
  if (file_exists($fckconfig_js) && is_readable($fckconfig_js)) {
    $fp = @fopen($fckconfig_js, "r");
    if ($fp) {
      while (!feof($fp)) {
        $line = fgets($fp, 1024);
        $matches = array();
        if (preg_match('/FCKConfig\.ToolbarSets\[("|\')(.*?)\\1\]/i', $line, $matches)) {
          $arr[$matches[2]] = drupal_ucfirst($matches[2]);
        }
      }
      fclose($fp);
    }
  }
  if (file_exists($fckeditor_config_js) && is_readable($fckeditor_config_js)) {
    $fp = @fopen($fckeditor_config_js, "r");
    if ($fp) {
      while (!feof($fp)) {
        $line = fgets($fp, 1024);
        $matches = array();
        if (preg_match('/FCKConfig\.ToolbarSets\[("|\')(.*?)\\1\]/i', $line, $matches)) {
          $arr[$matches[2]] = drupal_ucfirst($matches[2]);
        }
      }
      fclose($fp);
    }
  }

  //oops, we have no information about toolbars, let's use hardcoded array
  if (empty($arr)) {
    $arr = array(
      'Basic' => 'Basic',
      'Default' => 'Default',
    );
  }
  asort($arr);

  return $arr;
}

function fckeditor_load_skin_options() {
  $arr = array();
  $editor_local_path  = fckeditor_path(TRUE);
  $skin_dir     = $editor_local_path .'/editor/skins';
  if (is_dir($skin_dir)) {
    $dh = @opendir($skin_dir);
    if (FALSE !== $dh) {
      while (($file = readdir($dh)) !== FALSE ) {
        if (in_array($file, array(".", "..", "CVS", ".svn"))) {
          continue;
        }
        if (is_dir($skin_dir . DIRECTORY_SEPARATOR . $file)) {
          $arr[$file] = drupal_ucfirst($file);
        }
      }
      closedir( $dh );
    }
  }

  //oops, we have no information about skins, let's use only default
  if (empty($arr)) {
    $arr = array(
      'default' => 'Default',
    );
  }
  asort($arr);

  return $arr;
}

function fckeditor_load_lang_options() {
  $arr = array();
  $editor_local_path  = fckeditor_path(TRUE);
  $lang_dir     = $editor_local_path .'/editor/lang';
  if (is_dir($lang_dir)) {
    $dh = @opendir($lang_dir);
    if (FALSE !== $dh ) {
      while (($file = readdir($dh)) !== FALSE) {
        if (in_array($file, array(".", "..", "CVS", ".svn"))) {
          continue;
        }
        $matches = array();
        if (is_file($lang_dir . DIRECTORY_SEPARATOR . $file) && preg_match('/^(.*?)\.js$/', $file, $matches)) {
          $lang = $matches[1];
          $arr[$lang] = drupal_strtoupper($lang);
        }
      }
      closedir( $dh );
    }
  }

  //oops, we have no information about languages, let's use those available in FCKeditor 2.4.3
  if (empty($arr)) {
    $arr = array(
      'af' => 'Afrikaans',
      'ar' => 'Arabic',
      'bg' => 'Bulgarian',
      'bn' => 'Bengali/Bangla',
      'bs' => 'Bosnian',
      'ca' => 'Catalan',
      'cs' => 'Czech',
      'da' => 'Danish',
      'de' => 'German',
      'el' => 'Greek',
      'en' => 'English',
      'en-au' => 'English (Australia)',
      'en-ca' => 'English (Canadian)',
      'en-uk' => 'English (United Kingdom)',
      'eo' => 'Esperanto',
      'es' => 'Spanish',
      'et' => 'Estonian',
      'eu' => 'Basque',
      'fa' => 'Persian',
      'fi' => 'Finnish',
      'fo' => 'Faroese',
      'fr' => 'French',
      'gl' => 'Galician',
      'he' => 'Hebrew',
      'hi' => 'Hindi',
      'hr' => 'Croatian',
      'hu' => 'Hungarian',
      'it' => 'Italian',
      'ja' => 'Japanese',
      'km' => 'Khmer',
      'ko' => 'Korean',
      'lt' => 'Lithuanian',
      'lv' => 'Latvian',
      'mn' => 'Mongolian',
      'ms' => 'Malay',
      'nb' => 'Norwegian Bokmal',
      'nl' => 'Dutch',
      'no' => 'Norwegian',
      'pl' => 'Polish',
      'pt' => 'Portuguese (Portugal)',
      'pt-br' => 'Portuguese (Brazil)',
      'ro' => 'Romanian',
      'ru' => 'Russian',
      'sk' => 'Slovak',
      'sl' => 'Slovenian',
      'sr' => 'Serbian (Cyrillic)',
      'sr-latn' => 'Serbian (Latin)',
      'sv' => 'Swedish',
      'th' => 'Thai',
      'tr' => 'Turkish',
      'uk' => 'Ukrainian',
      'vi' => 'Vietnamese',
      'zh' => 'Chinese Traditional',
      'zh-cn' => 'Chinese Simplified',
    );
  }

  asort($arr);

  return $arr;
}
