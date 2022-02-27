#include "sub.h"

#include "code/defs.h"

extern "C" {

// Args:
// - dst: pointer to 4 bytes of writeable memory.
// - src: pointer to 4 bytes of writeable memory.
void sub_1A40(uint8_t *dst, uint64_t *src) {
  uint64_t tmp = *src;
  dst[0] = BYTE3(tmp);
  dst[1] = BYTE2(tmp);
  dst[2] = BYTE1(tmp);
  dst[3] = tmp;
}

}
