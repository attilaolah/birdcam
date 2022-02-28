#include "sub.h"

#include <cstdlib>

#include "code/defs.h"

using std::size_t;

extern "C" {

// Args:
// - src: pointer to 4 bytes of readable memory.
// - dst: pointer to 4 bytes of writeable memory.
void _sub_1A10(uint32_t *src, uint32_t *dst) { *dst = __bswap_32(*src); }

// Args:
// - dst: pointer to 4 bytes of writeable memory.
// - src: pointer to 4 bytes of writeable memory.
void _sub_1A40(uint8_t *dst, uint32_t *src) {
  dst[0] = BYTE3(*src);
  dst[1] = BYTE2(*src);
  dst[2] = BYTE1(*src);
  dst[3] = *src;
}
}

namespace ls_sec {

uint32_t sub_1A10(uint32_t src) {
  uint32_t dst;
  _sub_1A10(&src, &dst);
  return dst;
}

uint32_t sub_1A40(uint32_t src) {
  uint32_t dst;
  _sub_1A40(reinterpret_cast<uint8_t *>(&dst), &src);
  return dst;
}

} // namespace ls_sec
