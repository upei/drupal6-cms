<?php

abstract class DrupalBlockBase {
  
  var $info;
  var $status;
  var $region;
  var $weight;
  var $cache;
  
  function __construct($info, $status, $region, $weight) {
    $this->info = $info;
    $this->status = $status;
    $this->region = $region;
    $this->weight = $weight;
  }
  
  abstract function view(); // this method is required
  
  function info() {
    return array(
      'info' => $this->info,
      'status' => $this->status,
      'region' => $this->region,
      'weight' => $this->weight,
      );
  }
  
  static function listBlocks($blocks) {
      $list = array();
      foreach ($blocks as $key => $value) {
          $list[$key] = $value->info();
      }
      return $list;
  }

  // this method is optional
  function configure() {}
  function save($edit) {}
}
