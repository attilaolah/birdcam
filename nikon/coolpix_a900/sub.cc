#include "sub.h"

#include <cstdlib>
#include <cstring>

#include "code/defs.h"

extern "C" {

// Args:
// - src: pointer to 4 bytes of readable memory.
// - dst: pointer to 4 bytes of writeable memory.
void _sub_1A10(uint32_t *src, uint32_t *dst) { *dst = __bswap_32(*src); }

// Args:
// - dst: pointer to 4 bytes of writeable memory.
// - src: pointer to 4 bytes of readable memory.
void _sub_1A40(uint8_t *dst, uint32_t *src) {
  dst[0] = BYTE3(*src);
  dst[1] = BYTE2(*src);
  dst[2] = BYTE1(*src);
  dst[3] = *src;
}

// Args:
// - dst: pointer to `n` bytes of writeable memory.
// - src: pointer to `n` bytes of readable memory.
// - n: how many bytes to copy.
void _sub_1A80(uint8_t *dst, uint8_t *src, size_t n) { memcpy(dst, src, n); }

// Args:
// - a: pointer to `n` bytes of readable memory.
// - b: pointer to `n` bytes of readable memory.
// - n: how many bytes to compare.
int _sub_1C20(uint8_t *a, uint8_t *b, size_t n) { return memcmp(a, b, n); }
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

void sub_1A80(uint8_t *dst, uint8_t *src, std::size_t n) {
  _sub_1A80(dst, src, n);
}

bool sub_1C20(uint8_t *a, uint8_t *b, std::size_t n) {
  return _sub_1C20(a, b, n) != 0;
}

} // namespace ls_sec
