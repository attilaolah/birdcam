#include "entangle.h"

#include <cstdlib>
#include <limits>

#include "data.h"

namespace ls_sec {
namespace {
static constexpr auto const &kKM = kKeyMaterial1;

// Args:
// - a: pointer to 4 bytes of writeable memory.
// - b: pointer to 4 bytes of writeable memory.
void entangle_2(uint32_t *a, uint32_t *b) noexcept {
  uint32_t a_1 = *a;
  uint32_t b_1 = *b;
  for (size_t i = 0; i < 16; i++) {
    uint32_t prev = kKM.header[i] ^ a_1;
    uint32_t f0 = kKM.data[0][(prev >> 0x18) & 0xff];
    uint32_t f1 = kKM.data[1][(prev >> 0x10) & 0xff];
    uint32_t f2 = kKM.data[2][(prev >> 0x08) & 0xff];
    uint32_t f3 = kKM.data[3][(prev >> 0x00) & 0xff];
    a_1 = b_1 ^ (f3 + (f2 ^ (f1 + f0)));
    b_1 = prev;
  }
  *b = kKM.header[16] ^ a_1;
  *a = kKM.header[17] ^ b_1;
}
} // namespace

uint64_t entangle(const std::vector<uint64_t> &elements) noexcept {
  uint32_t x = 0x1020304;
  uint32_t y = 0x5060708;

  for (const uint64_t &elem : elements) {
    x = __bswap_32(elem & std::numeric_limits<uint32_t>::max()) ^ x;
    y = __bswap_32(elem >> 32) ^ y;
    entangle_2(&x, &y);
  }

  return (uint64_t)__bswap_32(x) | (uint64_t)__bswap_32(y) << 32;
}

} // namespace ls_sec
