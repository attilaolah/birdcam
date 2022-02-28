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
// - data: pointer to 8336 bytes of readable memory.
// - a: pointer to 8 bytes of writeable memory.
// - b: pointer to 8 bytes of writeable memory.
void _sub_1480(const uint64_t *data, uint64_t *a, uint64_t *b) {
  uint64_t a_1 = *a;
  uint64_t b_1 = *b;
  for (size_t i = 0; i <= 16; i++) {
    uint64_t prev = data[i] ^ a_1;
    size_t o_0 = 0x012 + BYTE3(prev);
    size_t o_1 = 0x112 + BYTE2(prev);
    size_t o_2 = 0x212 + BYTE1(prev);
    size_t o_3 = 0x312 + (uint8_t)prev;
    a_1 = b_1 ^ (data[o_3] + (data[o_2] ^ (data[o_1] + data[o_0])));
    b_1 = prev;
  }
  *b = data[16] ^ a_1;
  *a = data[17] ^ b_1;
}
}

namespace ls_sec {

uint64_t entangle(const std::vector<uint64_t> &elements) {
  uint64_t x = 0x1020304;
  uint64_t y = 0x5060708;

  for (const uint64_t &elem : elements) {
    x = __bswap_32(elem & std::numeric_limits<uint32_t>::max()) ^ x;
    y = __bswap_32(elem >> 32) ^ y;
    _sub_1480(DATA_2A00.data(), &x, &y);
  }

  uint64_t dst;
  _sub_1A40((uint8_t *)&dst, static_cast<uint32_t>(x));
  _sub_1A40((uint8_t *)&dst + 4, static_cast<uint32_t>(y));
  return dst;
}

std::pair<uint64_t, uint64_t> sub_1480(uint64_t a, uint64_t b) {
  _sub_1480(DATA_2A00.data(), &a, &b);
  return std::make_pair(a, b);
}

uint32_t sub_1A40(uint32_t src) {
  uint32_t dst;
  _sub_1A40(reinterpret_cast<uint8_t *>(&dst), src);
  return dst;
}

} // namespace ls_sec
