PROVIDE("rand@LIBC" = rand);
PROVIDE("srand@LIBC" = noop);
PROVIDE("__cxa_finalize@LIBC" = noop);
PROVIDE("__cxa_atexit@LIBC" = noop);
PROVIDE("__stack_chk_fail@LIBC" = noop);

