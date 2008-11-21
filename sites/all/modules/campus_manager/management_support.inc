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
  
  function definition() {
    return array(
      'info' => $this->info,
      'status' => $this->status,
      'region' => $this->region,
      'weight' => $this->weight,
      );
  }

  // this method is optional
  function configure() {}
  function save($edit) {}
}
