<?php

abstract class DrupalBlockBase {
  
  var $info;
  var $status;
  var $region;
  var $weight;
  var $cache;
  static $BlockPool;
  
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
  
  static function listBlocks() {
    static $r;
    
    if (!isset($r)) {
      $r = array();
      foreach (array_keys(DrupalBlockBase::$BlockPool) as $key) {
        $r[$key] = DrupalBlockBase::$BlockPool[$key]->info();
      }
    }
    return $r;
  }
  
  static function register($key, $block) {
    if (!isset(DrupalBlockBase::$BlockPool)) {
      DrupalBlockBase::$BlockPool = array();
    }
    DrupalBlockBase::$BlockPool[$key] = $block;
  }
  
  static function unregister($key, $block) {
    unset(DrupalBlockBase::$BlockPool[$key]);
  }
  // handles save, configure, view
  static function dispatch($key, $method, $edit) {
    if (isset(DrupalBlockBase::$BlockPool[$key])) {
      switch ($method) {
        case 'configure':
        case 'view':
          return DrupalBlockBase::$BlockPool[$key]->$method();
        case 'save':
          return DrupalBlockBase::$BlockPool[$key]->$method($edit);
      }
    }
  }

  // this method is optional
  function configure() {}
  function save($edit) {}
}
