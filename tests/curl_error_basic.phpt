--TEST--
curl_winssl_error() function - basic test for curl_winssl_error using a fake url
--CREDITS--
Mattijs Hoitink mattijshoitink@gmail.com
#Testfest Utrecht 2009
--SKIPIF--
<?php

if (!extension_loaded("curl_winssl")) die("skip\n");

$url = "fakeURL";
$ip = gethostbyname($url);
if ($ip != $url) die("skip 'fakeURL' resolves to $ip\n");

?>
--FILE--
<?php
/*
 * Prototype:     string curl_winssl_error(resource $ch)
 * Description:   Returns a clear text error message for the last cURL operation.
 * Source:        ext/curl/interface.c
 * Documentation: http://wiki.php.net/qa/temp/ext/curl
 */
 
// Fake URL to trigger an error
$url = "fakeURL";

echo "== Testing curl_winssl_error with a fake URL ==\n";

// cURL handler
$ch = curl_winssl_init($url);
curl_winssl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);

curl_winssl_exec($ch);
var_dump(curl_winssl_error($ch));
curl_winssl_close($ch);

?>
--EXPECTF--
== Testing curl_winssl_error with a fake URL ==
string(%d) "%sfakeURL%S"
