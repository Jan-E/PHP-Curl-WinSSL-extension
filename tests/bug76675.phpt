--TEST--
Bug #76675 (H2 server push write/writeheader handlers / pipelining)
--SKIPIF--
<?php
include 'skipif.inc';
if (getenv("SKIP_ONLINE_TESTS")) {
	die("skip online test");
}
$curl_version = curl_winssl_version();
if ($curl_version['version_number'] < 0x073d00) {
	exit("skip: test may crash with curl < 7.61.0");
}
?>
--FILE--
<?php
$transfers = 1;
$callback = function($parent, $passed) use (&$transfers) {
    curl_winssl_setopt($passed, CURLOPT_WRITEFUNCTION, function ($ch, $data) {
        echo "Received ".strlen($data);
        return strlen($data);
    });
    $transfers++;
    return CURL_PUSH_OK;
};
$mh = curl_winssl_multi_init();
curl_winssl_multi_setopt($mh, CURLMOPT_PIPELINING, CURLPIPE_MULTIPLEX);
//curl_winssl_multi_setopt($mh, CURLMOPT_PUSHFUNCTION, $callback);
$ch = curl_winssl_init();
curl_winssl_setopt($ch, CURLOPT_URL, 'https://http2.golang.org/serverpush');
curl_winssl_setopt($ch, CURLOPT_HTTP_VERSION, 3);
curl_winssl_setopt($ch, CURLOPT_SSL_VERIFYHOST, 0);
curl_winssl_setopt($ch, CURLOPT_SSL_VERIFYPEER, 0);
curl_winssl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
curl_winssl_multi_add_handle($mh, $ch);
$active = null;
do {
    $status = curl_winssl_multi_exec($mh, $active);
    do {
        $info = curl_winssl_multi_info_read($mh);
        if (false !== $info && $info['msg'] == CURLMSG_DONE) {
            $handle = $info['handle'];
            if ($handle !== null) {
                $transfers--;
                curl_winssl_multi_remove_handle($mh, $handle);
                curl_winssl_close($handle);
            }
        }
    } while ($info);
} while ($transfers);
curl_winssl_multi_close($mh);
?>
--EXPECTREGEX--
(Received \d+)+
