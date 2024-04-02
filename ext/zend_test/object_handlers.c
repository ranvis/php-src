/*
  +----------------------------------------------------------------------+
  | Copyright (c) The PHP Group                                          |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | https://www.php.net/license/3_01.txt                                 |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Authors: George Peter Banyard <girgias@php.net>                      |
  +----------------------------------------------------------------------+
*/

#include "object_handlers.h"
#include "zend_API.h"
#include "object_handlers_arginfo.h"

/* donc refers to DoOperationNoCast */
static zend_class_entry *donc_ce;
static zend_object_handlers donc_object_handlers;

static zend_object* donc_object_create_ex(zend_class_entry* ce, zend_long l) {
	zend_object *obj = zend_objects_new(ce);
	object_properties_init(obj, ce);
	obj->handlers = &donc_object_handlers;
	ZVAL_LONG(OBJ_PROP_NUM(obj, 0), l);
	return obj;
}
static zend_object *donc_object_create(zend_class_entry *ce) /* {{{ */
{
	return donc_object_create_ex(ce, 0);
}
/* }}} */

static inline void donc_create(zval *target, zend_long l) /* {{{ */
{
	ZVAL_OBJ(target, donc_object_create_ex(donc_ce, l));
}

#define IS_DONC(zval) \
	(Z_TYPE_P(zval) == IS_OBJECT && instanceof_function(Z_OBJCE_P(zval), donc_ce))

static void donc_bool_not(zval *result, zval *op)
{
	zend_long val;
	ZEND_ASSERT(IS_DONC(op));
	val = Z_LVAL_P(OBJ_PROP_NUM(Z_OBJ_P(op), 0));
	donc_create(result, !val);
}

static zend_result donc_do_operation(zend_uchar opcode, zval *result, zval *op1, zval *op2)
{
	zval op1_copy;
	zend_result status;

	if (result == op1) {
		ZVAL_COPY_VALUE(&op1_copy, op1);
		op1 = &op1_copy;
	}

	switch (opcode) {
		case ZEND_BOOL_NOT:
			donc_bool_not(result, op1);
			if (UNEXPECTED(EG(exception))) { status = FAILURE; }
			status = SUCCESS;
			break;
		default:
			status = FAILURE;
			break;
	}

	if (status == SUCCESS && op1 == &op1_copy) {
		zval_ptr_dtor(op1);
	}

	return status;
}

ZEND_METHOD(DoOperationNoCast, __construct)
{
	zend_long l;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(l)
	ZEND_PARSE_PARAMETERS_END();

	ZVAL_LONG(OBJ_PROP_NUM(Z_OBJ_P(ZEND_THIS), 0), l);
}

void zend_test_object_handlers_init(void)
{
	/* DoOperationNoCast class */
	donc_ce = register_class_DoOperationNoCast();
	donc_ce->create_object = donc_object_create;
	memcpy(&donc_object_handlers, &std_object_handlers, sizeof(zend_object_handlers));
	donc_object_handlers.do_operation = donc_do_operation;
}
