<?php

/**
 * @file
 * hook_file and imagefield_crop file functions.
 */
function imagefield_crop_file_insert($file) {
  // we copy the file as is, for quality cropping.
  if ((isset($file->field['widget']) &&
       $file->field['widget']['module'] == 'imagefield_crop') &&
      imagefield_file_is_image($file)) {
    $newfile = drupal_clone($file);
    file_copy($newfile->filepath, imagefield_crop_file_admin_crop_display_path($newfile));
  }
}

function imagefield_crop_file_update(&$file) {
  // update admin thumbnail
  imagefield_file_insert($file);

  // flush imagecache
  module_invoke('imagecache', 'image_flush', $file->filepath);

  // update timestamp, see http://drupal.org/node/353405
  $file->timestamp = REQUEST_TIME;
  drupal_write_record('files', $file, 'fid');
}

function imagefield_crop_file_delete($file) {
  // delete admin thumbnail.
  if (imagefield_file_is_image($file))
    file_delete(imagefield_crop_file_admin_crop_display_path($file));
}

// create the path to the file to be used for displaying the crop interface.
function imagefield_crop_file_admin_crop_display_path($file) {
  $file = (object)$file;
  return $file->filepath .'.crop_display.jpg';
}

// Original file to crop from
function imagefield_crop_file_admin_original_path($file) {
  // the displayed and original are the same. Yay Jcrop!
  $original_path = imagefield_crop_file_admin_crop_display_path($file);
  if (!file_exists($original_path)) {
    // orig file does not exist, use what we have as original
    file_copy($file['filepath'], $original_path);
  }
  return $original_path;
}
