--TEST--
Test curl_winssl_error() & curl_winssl_errno() function with problematic proxy
--CREDITS--
TestFest 2009 - AFUP - Perrick Penet <perrick@noparking.net>
--SKIPIF--
<?php
	if (!extension_loaded("curl")) print "skip";
	$addr = "www.".uniqid().".".uniqid();
	if (gethostbyname($addr) != $addr) {
		print "skip catch all dns";
	}
?>
--FILE--
<?php

$url = "http://www.example.org";
$ch = curl_winssl_init();
curl_winssl_setopt($ch, CURLOPT_PROXY, uniqid().":".uniqid());
curl_winssl_setopt($ch, CURLOPT_URL, $url);

curl_winssl_exec($ch);
var_dump(curl_winssl_error($ch));
var_dump(curl_winssl_errno($ch));
curl_winssl_close($ch);


?>
--EXPECTF--
string(%d) "%r(Couldn't resolve proxy|Could not resolve proxy:|Could not resolve host:|Could not resolve:|Unsupported proxy syntax in)%r %s"
int(5)
