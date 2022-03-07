#include "entangle.h"

#include <cstdlib>
#include <limits>

namespace ls_sec {

// Args:
// - a: pointer to 4 bytes of writeable memory.
// - b: pointer to 4 bytes of writeable memory.
void entangle_2(const KeyMaterial &key, uint32_t *a, uint32_t *b) noexcept {
  uint32_t a_1 = *a;
  uint32_t b_1 = *b;
  for (size_t i = 0; i < 16; i++) {
    uint32_t prev = key.header[i] ^ a_1;
    uint32_t f0 = key.data[0][(prev >> 0x18) & 0xff];
    uint32_t f1 = key.data[1][(prev >> 0x10) & 0xff];
    uint32_t f2 = key.data[2][(prev >> 0x08) & 0xff];
    uint32_t f3 = key.data[3][(prev >> 0x00) & 0xff];
    a_1 = b_1 ^ (f3 + (f2 ^ (f1 + f0)));
    b_1 = prev;
  }
  *b = key.header[16] ^ a_1;
  *a = key.header[17] ^ b_1;
}

// Args:
// - a: pointer to 4 bytes of writeable memory.
// - b: pointer to 4 bytes of writeable memory.
void untangle_2(const KeyMaterial &key, uint32_t *a, uint32_t *b) noexcept {
  uint32_t a_1 = *a;
  uint32_t b_1 = *b;
  for (size_t i = key.header.size() - 1; i > 1; i--) {
    uint32_t prev = key.header[i] ^ a_1;
    uint32_t f0 = key.data[0][(prev >> 0x18) & 0xff];
    uint32_t f1 = key.data[1][(prev >> 0x10) & 0xff];
    uint32_t f2 = key.data[2][(prev >> 0x08) & 0xff];
    uint32_t f3 = key.data[3][(prev >> 0x00) & 0xff];
    a_1 = b_1 ^ (f3 + (f2 ^ (f1 + f0)));
    b_1 = prev;
  }
  *b = key.header[1] ^ a_1;
  *a = key.header[0] ^ b_1;
}

uint64_t entangle(const std::vector<uint64_t> &elements) noexcept {
  uint32_t x = 0x1020304;
  uint32_t y = 0x5060708;

  for (const uint64_t &elem : elements) {
    x = __bswap_32(elem & std::numeric_limits<uint32_t>::max()) ^ x;
    y = __bswap_32(elem >> 32) ^ y;
    entangle_2(kKeyMaterial1, &x, &y);
  }

  return (uint64_t)__bswap_32(x) | (uint64_t)__bswap_32(y) << 32;
}

} // namespace ls_sec
