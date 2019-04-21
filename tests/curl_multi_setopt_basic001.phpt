--TEST--
curl_winssl_multi_setopt basic test
--SKIPIF--
<?php
if (!extension_loaded("curl_winssl")) {
	    exit("skip curl extension not loaded");
}
$curl_version = curl_winssl_version();
if ($curl_version['version_number'] < 0x071000) {
	    exit("skip: test works only with curl >= 7.16.0");
}
?>
--FILE--
<?php

$mh = curl_winssl_multi_init();
var_dump(curl_winssl_multi_setopt($mh, CURLMOPT_PIPELINING, 0));
var_dump(curl_winssl_multi_setopt($mh, -1, 0));

?>
--EXPECTF--
bool(true)

Warning: curl_winssl_multi_setopt(): Invalid curl multi configuration option in %s on line %d
bool(false)
