#include "sub.h"

#include <cstdlib>
#include <cstring>

#include "sub_data.h"

#include "code/defs.h"

extern "C" {

// Args:
// - src: pointer to 4 bytes of readable memory.
// - dst: pointer to 4 bytes of writeable memory.
void _sub_1A10(const uint32_t *src, uint32_t *dst) { *dst = __bswap_32(*src); }

// Args:
// - dst: pointer to 4 bytes of writeable memory.
// - src: pointer to 4 bytes of readable memory.
void _sub_1A40(uint8_t *dst, const uint32_t *src) {
  dst[0] = BYTE3(*src);
  dst[1] = BYTE2(*src);
  dst[2] = BYTE1(*src);
  dst[3] = *src;
}

// Args:
// - dst: pointer to `n` bytes of writeable memory.
// - src: pointer to `n` bytes of readable memory.
// - n: how many bytes to copy.
void _sub_1A80(uint8_t *dst, const uint8_t *src, size_t n) {
  memcpy(dst, src, n);
}

// Args:
// - a: pointer to `n` bytes of readable memory.
// - b: pointer to `n` bytes of readable memory.
// - n: how many bytes to compare.
int _sub_1C20(const uint8_t *a, const uint8_t *b, size_t n) {
  return memcmp(a, b, n);
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

// Args:
// - data: `n` bytes of readable memory.
// - dst: 8 bytes of writeable memory.
// - n: how many bytes to go through in the inner loop.
void _sub_A80(const uint64_t *data, uint64_t *dst, size_t n) {
  if (!DATA_9040) {
    DATA_9040 = 1;
  }

  uint64_t x;
  uint64_t y;
  uint64_t a = 84281096;
  uint64_t b = 16909060;
  // Here n could be: {8 (0x8u), 24 (0x18u), 32 (0x20u)}.
  // This puts the 64-bit (8-byte) offset at {1, 3, 4} respectively.
  const uint64_t *p = data + ((n - 8) >> 3) + 1; // p += n / 8;
  do {
    _sub_1A10((uint32_t *)data, (uint32_t *)&x);
    _sub_1A10((uint32_t *)data + 1, (uint32_t *)&y);
    x ^= b;
    y ^= a;
    _sub_1480(DATA_2A00.data(), &x, &y);
    b = x;
    a = y;
    data++;
  } while (p != data);
  _sub_1A40((uint8_t *)dst, (uint32_t *)&x);
  _sub_1A40((uint8_t *)dst + 4, (uint32_t *)&y);
}
}

namespace ls_sec {

uint64_t sub_A80(const uint64_t *data, size_t n) {
  uint64_t dst;
  _sub_A80(data, &dst, n);
  return dst;
}

std::pair<uint64_t, uint64_t> sub_1480(uint64_t a, uint64_t b) {
  _sub_1480(DATA_2A00.data(), &a, &b);
  return std::make_pair(a, b);
}

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

void sub_1A80(uint8_t *dst, const uint8_t *src, std::size_t n) {
  _sub_1A80(dst, src, n);
}

bool sub_1C20(uint8_t *a, uint8_t *b, std::size_t n) {
  return _sub_1C20(a, b, n) != 0;
}

} // namespace ls_sec
