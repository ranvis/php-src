/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 241d767979bc7df8e6dc240e0b580a67a846a9ba */

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_DoOperationNoCast___construct, 0, 0, 1)
	ZEND_ARG_TYPE_INFO(0, val, IS_LONG, 0)
ZEND_END_ARG_INFO()


static ZEND_METHOD(DoOperationNoCast, __construct);


static const zend_function_entry class_DoOperationNoCast_methods[] = {
	ZEND_ME(DoOperationNoCast, __construct, arginfo_class_DoOperationNoCast___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static zend_class_entry *register_class_DoOperationNoCast(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "DoOperationNoCast", class_DoOperationNoCast_methods);
	class_entry = zend_register_internal_class_ex(&ce, NULL);
	class_entry->ce_flags |= ZEND_ACC_FINAL;

	zval property_val_default_value;
	ZVAL_UNDEF(&property_val_default_value);
	zend_string *property_val_name = zend_string_init("val", sizeof("val") - 1, 1);
	zend_declare_typed_property(class_entry, property_val_name, &property_val_default_value, ZEND_ACC_PRIVATE, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_val_name);

	return class_entry;
}
