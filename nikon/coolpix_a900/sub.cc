#include "sub.h"

#include <cstdlib>
#include <cstring>
#include <limits>

#include "sub_data.h"

#include "code/defs.h"

namespace ls_sec {
namespace {
// Args:
// - a: pointer to 4 bytes of writeable memory.
// - b: pointer to 4 bytes of writeable memory.
void entangle_2(uint32_t *a, uint32_t *b) {
  uint32_t a_1 = *a;
  uint32_t b_1 = *b;
  for (size_t i = 0; i < 16; i++) {
    uint32_t prev = R16[i] ^ a_1;
    size_t o_0 = (prev >> 0x18) & 0xff;
    size_t o_1 = (prev >> 0x10) & 0xff;
    size_t o_2 = (prev >> 0x08) & 0xff;
    size_t o_3 = (prev >> 0x00) & 0xff;
    a_1 = b_1 ^ (FIELD_3[o_3] + (FIELD_2[o_2] ^ (FIELD_1[o_1] + FIELD_0[o_0])));
    b_1 = prev;
  }
  *b = 0x096EA497E ^ a_1;
  *a = 0x07C3F81CA ^ b_1;
}
} // namespace

uint64_t entangle(const std::vector<uint64_t> &elements) {
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
