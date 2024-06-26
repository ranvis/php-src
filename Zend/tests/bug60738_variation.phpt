--TEST--
Bug #60738 Allow 'set_error_handler' to handle NULL
--FILE--
<?php

var_dump(set_exception_handler(
    function() { echo 'Intercepted exception!', "\n"; }
));

var_dump(set_exception_handler(null));

throw new Exception('Exception!');
?>
--EXPECTF--
NULL
object(Closure)#%d (3) {
  ["name"]=>
  string(%d) "{closure:%s:%d}"
  ["file"]=>
  string(%d) "%s"
  ["line"]=>
  int(%d)
}

Fatal error: Uncaught Exception: Exception! in %s:%d
Stack trace:
#0 {main}
  thrown in %s on line %d
