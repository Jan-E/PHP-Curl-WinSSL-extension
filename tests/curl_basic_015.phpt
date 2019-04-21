--TEST--
Test curl_winssl_init() function with $url parameter defined
--CREDITS--
Jean-Marc Fontaine <jmf@durcommefaire.net>
--SKIPIF--
<?php if (!extension_loaded("curl_winssl")) exit("skip curl_winssl extension not loaded"); ?>
--FILE--
<?php
  $url = 'https://example.org/'; 
  $ch  = curl_winssl_init($url);
  var_dump($url == curl_winssl_getinfo($ch, CURLINFO_EFFECTIVE_URL));
?>
===DONE===
--EXPECTF--
bool(true)
===DONE===
