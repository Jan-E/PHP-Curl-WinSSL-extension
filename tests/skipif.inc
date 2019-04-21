<?php
    if (!extension_loaded("curl_winssl")) exit("skip curl_winssl extension not loaded");
    if(false === getenv('PHP_CURL_HTTP_REMOTE_SERVER')) {
        if (php_sapi_name() != "cli") {
                die("skip PHP_CURL_HTTP_REMOTE_SERVER env variable is not defined");
        }
    }
