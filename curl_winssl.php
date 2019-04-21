<?php
$br = (php_sapi_name() == "cli")? "":"<br>";
if (function_exists('curl_winssl_init')) {
	$module = 'curl_winssl';
} else {
	$module = 'curl';
}
$functions = get_extension_funcs($module);
echo "Functions available in the extension:$br\n";
foreach($functions as $func) {
    echo $func."$br\n";
}
echo "$br\n";
// https://stackoverflow.com/a/12446906/872051 but with CURLOPT_SSL_VERIFYPEER
function getSslPage($url) {
	if (function_exists('curl_winssl_init')) {
		$ch = curl_winssl_init();
		curl_winssl_setopt($ch, CURLOPT_SSL_VERIFYPEER, true);
		curl_winssl_setopt($ch, CURLOPT_HEADER, false);
		curl_winssl_setopt($ch, CURLOPT_FOLLOWLOCATION, true);
		curl_winssl_setopt($ch, CURLOPT_URL, $url);
		curl_winssl_setopt($ch, CURLOPT_REFERER, $url);
		curl_winssl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
		$result = curl_winssl_exec($ch);
		curl_winssl_close($ch);
		return $result;
	} else {
		$ch = curl_init();
		/* has to be false for curl with OpenSSL */
		curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, true);
		curl_setopt($ch, CURLOPT_HEADER, false);
		curl_setopt($ch, CURLOPT_FOLLOWLOCATION, true);
		curl_setopt($ch, CURLOPT_URL, $url);
		curl_setopt($ch, CURLOPT_REFERER, $url);
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
		$result = curl_exec($ch);
		curl_close($ch);
		return $result;
	}
}
$result = getSslPage('https://example.org/');
echo $result;
?>
