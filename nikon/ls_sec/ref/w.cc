#include <cstdlib>

extern "C" {

int __libc_rand() { return rand(); }
__asm__(".symver __libc_rand,rand@LIBC");

void __libc_srand(unsigned int seed) { srand(seed); }
__asm__(".symver __libc_srand,srand@LIBC");

int __libc__cxa_atexit(void (*func)(void *), void *arg, void *dso_handle) {
  // Ignore global destructors.
  return 0;
}
__asm__(".symver __libc__cxa_atexit,__cxa_atexit@LIBC");

void __libc__cxa_finalize(void *d) {
  // Ignore global destructors.
}
__asm__(".symver __libc__cxa_finalize,__cxa_finalize@LIBC");

void __libc__stack_chk_fail() {
  // Ignore stack check failures.
}
__asm__(".symver __libc__stack_chk_fail,__stack_chk_fail@LIBC");
}
