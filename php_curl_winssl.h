/*
   +----------------------------------------------------------------------+
   | PHP Version 7                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2017 The PHP Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Author: Sterling Hughes <sterling@php.net>                           |
   |         Wez Furlong <wez@thebrainroom.com>                           |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef _PHP_CURL_H
#define _PHP_CURL_H

#include "php.h"
#include "zend_smart_str.h"

#ifdef COMPILE_DL_CURL_WINSSL
#undef HAVE_CURL_WINSSL
#define HAVE_CURL_WINSSL 1
#endif

#if HAVE_CURL_WINSSL

#define PHP_CURL_DEBUG 0

#ifdef PHP_WIN32
# define PHP_CURL_WINSSL_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
# define PHP_CURL_WINSSL_API __attribute__ ((visibility("default")))
#else
# define PHP_CURL_WINSSL_API
#endif

#include "php_version.h"
#define PHP_CURL_VERSION PHP_VERSION

#include <curl/curl.h>
#include <curl/multi.h>

extern zend_module_entry curl_winssl_module_entry;
#define curl_winssl_module_ptr &curl_winssl_module_entry

#define CURLOPT_RETURNTRANSFER 19913
#define CURLOPT_BINARYTRANSFER 19914 /* For Backward compatibility */
#define PHP_CURL_STDOUT 0
#define PHP_CURL_FILE   1
#define PHP_CURL_USER   2
#define PHP_CURL_DIRECT 3
#define PHP_CURL_RETURN 4
#define PHP_CURL_IGNORE 7

extern int  le_curl_winssl;
#define le_curl_winssl_name "cURL handle"
extern int  le_curl_winssl_multi_handle;
#define le_curl_winssl_multi_handle_name "cURL Multi Handle"
extern int  le_curl_winssl_share_handle;
#define le_curl_winssl_share_handle_name "cURL Share Handle"
//extern int  le_curl_winssl_pushheaders;
//#define le_curl_winssl_pushheaders "cURL Push Headers"

PHP_MINIT_FUNCTION(curl_winssl);
PHP_MSHUTDOWN_FUNCTION(curl_winssl);
PHP_MINFO_FUNCTION(curl_winssl);

PHP_FUNCTION(curl_winssl_close);
PHP_FUNCTION(curl_winssl_copy_handle);
PHP_FUNCTION(curl_winssl_errno);
PHP_FUNCTION(curl_winssl_error);
PHP_FUNCTION(curl_winssl_exec);
PHP_FUNCTION(curl_winssl_getinfo);
PHP_FUNCTION(curl_winssl_init);
PHP_FUNCTION(curl_winssl_setopt);
PHP_FUNCTION(curl_winssl_setopt_array);
PHP_FUNCTION(curl_winssl_version);

PHP_FUNCTION(curl_winssl_multi_add_handle);
PHP_FUNCTION(curl_winssl_multi_close);
PHP_FUNCTION(curl_winssl_multi_exec);
PHP_FUNCTION(curl_winssl_multi_getcontent);
PHP_FUNCTION(curl_winssl_multi_info_read);
PHP_FUNCTION(curl_winssl_multi_init);
PHP_FUNCTION(curl_winssl_multi_remove_handle);
PHP_FUNCTION(curl_winssl_multi_select);

PHP_FUNCTION(curl_winssl_share_close);
PHP_FUNCTION(curl_winssl_share_init);
PHP_FUNCTION(curl_winssl_share_setopt);

#if LIBCURL_VERSION_NUM >= 0x070c00 /* 7.12.0 */
PHP_FUNCTION(curl_winssl_strerror);
PHP_FUNCTION(curl_winssl_multi_strerror);
#endif

#if LIBCURL_VERSION_NUM >= 0x070c01 /* 7.12.1 */
PHP_FUNCTION(curl_winssl_reset);
#endif

#if LIBCURL_VERSION_NUM >= 0x070f04 /* 7.15.4 */
PHP_FUNCTION(curl_winssl_escape);
PHP_FUNCTION(curl_winssl_unescape);

PHP_FUNCTION(curl_winssl_multi_setopt);
#endif

#if LIBCURL_VERSION_NUM >= 0x071200 /* 7.18.0 */
PHP_FUNCTION(curl_winssl_pause);
#endif
PHP_FUNCTION(curl_winssl_file_create);


void _php_curl_winssl_multi_close(zend_resource *);
void _php_curl_winssl_share_close(zend_resource *);

typedef struct {
	zval                  func_name;
	zend_fcall_info_cache fci_cache;
	FILE                 *fp;
	smart_str             buf;
	int                   method;
	zval                  stream;
} php_curl_winssl_write;

typedef struct {
	zval                  func_name;
	zend_fcall_info_cache fci_cache;
	FILE                 *fp;
	zend_resource        *res;
	int                   method;
	zval                  stream;
} php_curl_winssl_read;

typedef struct {
	zval                  func_name;
	zend_fcall_info_cache fci_cache;
	int                   method;
} php_curl_winssl_progress, php_curl_winssl_fnmatch, php_curl_winsslm_server_push;

typedef struct {
	php_curl_winssl_write    *write;
	php_curl_winssl_write    *write_header;
	php_curl_winssl_read     *read;
#if CURLOPT_PASSWDFUNCTION != 0
	zval                      passwd;
#endif
	zval                      std_err;
	php_curl_winssl_progress *progress;
#if LIBCURL_VERSION_NUM >= 0x071500 /* Available since 7.21.0 */
	php_curl_winssl_fnmatch  *fnmatch;
#endif
} php_curl_winssl_handlers;

struct _php_curl_winssl_error  {
	char str[CURL_ERROR_SIZE + 1];
	int  no;
};

struct _php_curl_winssl_send_headers {
	zend_string *str;
};

struct _php_curl_winssl_free {
	zend_llist str;
	zend_llist post;
	HashTable *slist;
};

typedef struct {
	CURL                                *cp;
	php_curl_winssl_handlers            *handlers;
	zend_resource                       *res;
	struct _php_curl_winssl_free        *to_free;
	struct _php_curl_winssl_send_headers header;
	struct _php_curl_winssl_error err;
	zend_bool                            in_callback;
	uint32_t*                            clone;
} php_curl_winssl;

#define CURLOPT_SAFE_UPLOAD -1

typedef struct {
	php_curl_winsslm_server_push	*server_push;
} php_curl_winsslm_handlers;

typedef struct {
	int         still_running;
	CURLM      *multi;
	zend_llist  easyh;
	php_curl_winsslm_handlers *handlers;
	struct {
		int no;
	} err;
} php_curl_winsslm;

typedef struct {
	CURLSH     *share;
	struct {
		int no;
	} err;
} php_curl_winsslsh;

php_curl_winssl *alloc_curl_winssl_handle();
void _php_curl_winssl_cleanup_handle(php_curl_winssl *);
void _php_curl_winssl_multi_cleanup_list(void *data);
void _php_curl_winssl_verify_handlers(php_curl_winssl *ch, int reporterror);
void _php_setup_winssl_easy_copy_handlers(php_curl_winssl *ch, php_curl_winssl *source);

void CurlWinSSLFile_register_class(void);
PHP_CURL_WINSSL_API extern zend_class_entry *curl_CurlWinSSLFile_class;

#else
#define curl_winssl_module_ptr NULL
#endif /* HAVE_CURL_WINSSL */
#define phpext_curl_winssl_ptr curl_winssl_module_ptr
#endif  /* _PHP_CURL_H */
