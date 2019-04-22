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
   | Author: Stanislav Malyshev <stas@php.net>                            |
   +----------------------------------------------------------------------+
 */

/* $Id$ */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "Zend/zend_exceptions.h"
#include "php_curl_winssl.h"
#if HAVE_CURL_WINSSL

PHP_CURL_WINSSL_API zend_class_entry *curl_CurlWinSSLFile_class;

static void curl_winssl_file_ctor(INTERNAL_FUNCTION_PARAMETERS)
{
	char *fname = NULL, *mime = NULL, *postname = NULL;
	size_t fname_len, mime_len, postname_len;
	zval *cf = return_value;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "p|ss", &fname, &fname_len, &mime, &mime_len, &postname, &postname_len) == FAILURE) {
		return;
	}

	if (fname) {
		zend_update_property_string(curl_CurlWinSSLFile_class, cf, "name", sizeof("name")-1, fname);
	}

	if (mime) {
		zend_update_property_string(curl_CurlWinSSLFile_class, cf, "mime", sizeof("mime")-1, mime);
	}

	if (postname) {
		zend_update_property_string(curl_CurlWinSSLFile_class, cf, "postname", sizeof("postname")-1, postname);
	}
}

/* {{{ proto void CurlWinSSLFile::__construct(string $name, [string $mimetype [, string $postfilename]])
   Create the CurlWinSSLFile object */
ZEND_METHOD(CurlWinSSLFile, __construct)
{
	return_value = getThis();
	curl_winssl_file_ctor(INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

/* {{{ proto CurlWinSSLFile curl_winssl_file_create(string $name, [string $mimetype [, string $postfilename]])
   Create the CurlWinSSLFile object */
PHP_FUNCTION(curl_winssl_file_create)
{
    object_init_ex( return_value, curl_CurlWinSSLFile_class );
    curl_winssl_file_ctor(INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

static void curl_winssl_file_get_property(char *name, INTERNAL_FUNCTION_PARAMETERS)
{
	zval *res, rv;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}
	res = zend_read_property(curl_CurlWinSSLFile_class, getThis(), name, strlen(name), 1, &rv);
	ZVAL_DEREF(res);
	ZVAL_COPY(return_value, res);
}

static void curl_winssl_file_set_property(char *name, INTERNAL_FUNCTION_PARAMETERS)
{
	char *arg = NULL;
	size_t arg_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}
	zend_update_property_string(curl_CurlWinSSLFile_class, getThis(), name, strlen(name), arg);
}

/* {{{ proto string CurlWinSSLFile::getFilename()
   Get file name */
ZEND_METHOD(CurlWinSSLFile, getFilename)
{
	curl_winssl_file_get_property("name", INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

/* {{{ proto string CurlWinSSLFile::getMimeType()
   Get MIME type */
ZEND_METHOD(CurlWinSSLFile, getMimeType)
{
	curl_winssl_file_get_property("mime", INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

/* {{{ proto string CurlWinSSLFile::getPostFilename()
   Get file name for POST */
ZEND_METHOD(CurlWinSSLFile, getPostFilename)
{
	curl_winssl_file_get_property("postname", INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

/* {{{ proto void CurlWinSSLFile::setMimeType(string $mime)
   Set MIME type */
ZEND_METHOD(CurlWinSSLFile, setMimeType)
{
	curl_winssl_file_set_property("mime", INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

/* {{{ proto void CurlWinSSLFile::setPostFilename(string $name)
   Set file name for POST */
ZEND_METHOD(CurlWinSSLFile, setPostFilename)
{
	curl_winssl_file_set_property("postname", INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

/* {{{ proto void CurlWinSSLFile::__wakeup()
   Unserialization handler */
ZEND_METHOD(CurlWinSSLFile, __wakeup)
{
	zend_unset_property(curl_CurlWinSSLFile_class, getThis(), "name", sizeof("name")-1);
	zend_update_property_string(curl_CurlWinSSLFile_class, getThis(), "name", sizeof("name")-1, "");
	zend_throw_exception(NULL, "Unserialization of CurlWinSSLFile instances is not allowed", 0);
}
/* }}} */

ZEND_BEGIN_ARG_INFO_EX(arginfo_curl_winssl_file_create, 0, 0, 1)
	ZEND_ARG_INFO(0, filename)
	ZEND_ARG_INFO(0, mimetype)
	ZEND_ARG_INFO(0, postname)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_curl_winssl_file_name, 0)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()


static const zend_function_entry curl_winssl_file_funcs[] = {
	PHP_ME(CurlWinSSLFile,	__construct,        arginfo_curl_winssl_file_create, ZEND_ACC_CTOR|ZEND_ACC_PUBLIC)
	PHP_ME(CurlWinSSLFile,	getFilename,        NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CurlWinSSLFile,	getMimeType,        NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CurlWinSSLFile,	setMimeType,        arginfo_curl_winssl_file_name, ZEND_ACC_PUBLIC)
	PHP_ME(CurlWinSSLFile,	getPostFilename,    NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CurlWinSSLFile,	setPostFilename,    arginfo_curl_winssl_file_name, ZEND_ACC_PUBLIC)
	PHP_ME(CurlWinSSLFile,	__wakeup,           NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

void CurlWinSSLFile_register_class(void)
{
	zend_class_entry ce;
	INIT_CLASS_ENTRY( ce, "CurlWinSSLFile", curl_winssl_file_funcs );
	curl_CurlWinSSLFile_class = zend_register_internal_class(&ce);
	zend_declare_property_string(curl_CurlWinSSLFile_class, "name", sizeof("name")-1, "", ZEND_ACC_PUBLIC);
	zend_declare_property_string(curl_CurlWinSSLFile_class, "mime", sizeof("mime")-1, "", ZEND_ACC_PUBLIC);
	zend_declare_property_string(curl_CurlWinSSLFile_class, "postname", sizeof("postname")-1, "", ZEND_ACC_PUBLIC);
}

#endif
