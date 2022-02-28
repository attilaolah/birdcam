#include "sub.h"

#include <cstdlib>
#include <cstring>
#include <limits>

#include "sub_data.h"

#include "code/defs.h"

extern "C" {

// Args:
// - dst: pointer to 4 bytes of writeable memory.
// - src: pointer to 4 bytes of readable memory.
void _sub_1A40(uint8_t *dst, const uint32_t src) {
  dst[0] = BYTE3(src);
  dst[1] = BYTE2(src);
  dst[2] = BYTE1(src);
  dst[3] = src;
}

// Args:
// - a: pointer to 4 bytes of writeable memory.
// - b: pointer to 4 bytes of writeable memory.
void entangle_2(uint32_t *a, uint32_t *b) {
  uint32_t a_1 = *a;
  uint32_t b_1 = *b;
  for (size_t i = 0; i <= 16; i++) {
    uint32_t prev = DATA_2A00[i] ^ a_1;
    size_t o_0 = 0x012 + BYTE3(prev);
    size_t o_1 = 0x112 + BYTE2(prev);
    size_t o_2 = 0x212 + BYTE1(prev);
    size_t o_3 = 0x312 + (uint8_t)prev;
    a_1 = b_1 ^ (DATA_2A00[o_3] +
                 (DATA_2A00[o_2] ^ (DATA_2A00[o_1] + DATA_2A00[o_0])));
    b_1 = prev;
  }
  *b = DATA_2A00[16] ^ a_1;
  *a = DATA_2A00[17] ^ b_1;
}
}

namespace ls_sec {

uint64_t entangle(const std::vector<uint64_t> &elements) {
  uint32_t x = 0x1020304;
  uint32_t y = 0x5060708;

  for (const uint64_t &elem : elements) {
    x = __bswap_32(elem & std::numeric_limits<uint32_t>::max()) ^ x;
    y = __bswap_32(elem >> 32) ^ y;
    entangle_2(&x, &y);
  }

  uint64_t dst;
  _sub_1A40((uint8_t *)&dst, x);
  _sub_1A40((uint8_t *)&dst + 4, y);
  return dst;
}

std::pair<uint32_t, uint32_t> sub_1480(uint32_t a, uint32_t b) {
  entangle_2(&a, &b);
  return std::make_pair(a, b);
}

uint32_t sub_1A40(uint32_t src) {
  uint32_t dst;
  _sub_1A40(reinterpret_cast<uint8_t *>(&dst), src);
  return dst;
}

} // namespace ls_sec
