<?php

abstract class WICache {
	
	public abstract function setExpiryTime($seconds);
	// return null if no cache exists, or is expired
	public abstract function get($key);
	// should not write to cache if it's not expired.
	public abstract function put($key, $value);
	// invalidate the cache
	public abstract function invalidate($key);
}

class WIFileCache extends WICache {
	
	private $cacheDirectory_;

	var $expiryTime = 1800; // in seconds
	
	public function __construct($cacheDirectory) {
		$this->cacheDirectory_ = $cacheDirectory;
	}
	
	private function getCacheFilename($key) {
		return $this->cacheDirectory_ . '/' . $key . '.cache';
	}
	
	public function setExpiryTime($seconds) {
		$this->expiryTime = $seconds;
	}
	
	public function get($key) {
		// get the file name
		$filename = $this->getCacheFilename($key);
		
		// if the file does not exist, return null
		if (!file_exists($filename)) {
			return NULL;
		}
		
		// if the file is expired, invalidate it and return null
		if (time() - filemtime($filename) > $this->expiryTime) {
			$this->invalidate($key);
			return NULL;
		}
		
		$this->obtainLock($filename, LOCK_SH);
		
		// read the file
		$content = file_get_contents($filename);
		
		// unlock the file
		$this->releaseLock($filename);
		
		// return the content
		return $content;
	}
	
	private function obtainLock($filename, $type) {
		$filename = $filename . '.lck';
		if (file_exists($filename))
			$fh = fopen($filename, 'r');
		else
			$fh = fopen($filename, 'w');

		if (!flock($fh, $type)) {
			// unable to lock
			error_log('Unable to obtain lock: ' . $filename);
		}
	}
	
	private function releaseLock($filename) {
		$filename = $filename . '.lck';
		if (file_exists($filename))
			$fh = fopen($filename, 'r');
		else
			$fh = fopen($filename, 'w');
		
		if (!flock($fh, LOCK_UN)) {
			// unable to lock
			error_log('Unable to release lock: ' . $filename);
		}
		
		@unlink($filename);
	}
	
	public function put($key, $value) {
		// get the file name
		$filename = $this->getCacheFilename($key);
		
		// if the file does exist, return false
		if (file_exists($filename) && time() - filemtime($filename) <= $this->expiryTime) {
			return false;
		}
		
		// lock the file
		$this->obtainLock($filename, LOCK_EX);
		
		// write the file
		file_put_contents($filename, $value);
		
		// unlock the file
		$this->releaseLock($filename);
		
		// true
		return true;
	}
	
	public function invalidate($key) {
		$filename = $this->getCacheFilename($key);
		$this->obtainLock($filename, LOCK_EX);
		@unlink($filename);
		$this->releaseLock($filename);
	}
	
}
