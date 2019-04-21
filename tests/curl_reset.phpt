--TEST--
Test curl_winssl_reset
--SKIPIF--
<?php if (!extension_loaded("curl_winssl")) print "skip";
if (!function_exists("curl_winssl_reset")) exit("skip curl_winssl_reset doesn't exists (require libcurl >= 7.12.1)");
?>
--FILE--
<?php

$test_file = tempnam(sys_get_temp_dir(), 'php-curl-test');
$log_file = tempnam(sys_get_temp_dir(), 'php-curl-test');

$fp = fopen($log_file, 'w+');
fwrite($fp, "test");
fclose($fp);

$testfile_fp = fopen($test_file, 'w+');

$ch = curl_winssl_init();
curl_winssl_setopt($ch, CURLOPT_FILE, $testfile_fp);
curl_winssl_setopt($ch, CURLOPT_URL, 'file://' . $log_file);
curl_winssl_exec($ch);

curl_winssl_reset($ch);
curl_winssl_setopt($ch, CURLOPT_URL, 'file://' . $log_file);
curl_winssl_exec($ch);

curl_winssl_close($ch);

fclose($testfile_fp);

echo file_get_contents($test_file);

// cleanup
unlink($test_file);
unlink($log_file);

?>

===DONE===
--EXPECT--
testtest
===DONE===
