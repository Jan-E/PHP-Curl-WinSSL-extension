--TEST--
Check http2 connection with winssl
--SKIPIF--
<?php 
if (!extension_loaded("curl_winssl")) {
	die('skip - curl_winssl extension not available in this build'); 
}
if(substr(PHP_OS, 0, 3) != 'WIN' )
  die("skip for windows only");
?>
--FILE--
<?php
function getSslHeader($url) {
	$ch = curl_winssl_init();
	curl_winssl_setopt($ch, CURLOPT_SSL_VERIFYPEER, true);
	curl_winssl_setopt($ch, CURLOPT_HEADER, true);
	/* get us the resource without a body! */
	curl_winssl_setopt($ch, CURLOPT_NOBODY, true );
	curl_winssl_setopt($ch, CURLOPT_URL, $url);
	curl_winssl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
	$result = curl_winssl_exec($ch);
	curl_winssl_close($ch);
	return $result;
}
$result = getSslHeader('https://nghttp2.org/');
//	HTTP/2 200
//	date: Mon, 22 Apr 2019 19:55:56 GMT
//	content-type: text/html; charset=utf-8
//	vary: Accept-Encoding
//	strict-transport-security: max-age=31536000; includeSubDomains; preload
//	via: 1.1 google
//	alt-svc: quic=":443"; ma=2592000; v="46,44,43,39"
if (stripos($result, 'HTTP/2 200') === false) {
	echo $result;
} else {
	echo "HTTP/2 200\n";
}
?>
DONE
--EXPECTF--
HTTP/2 200
DONE
