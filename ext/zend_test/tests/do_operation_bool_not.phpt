--TEST--
Test DoOperationNotCast do_operation bool_not
--EXTENSIONS--
zend_test
--FILE--
<?php

$a = new DoOperationNoCast(5);
var_dump(!$a);

?>
--EXPECT--
object(DoOperationNoCast)#2 (1) {
  ["val":"DoOperationNoCast":private]=>
  int(0)
}
