#pragma once

#include <cstdint>
#include <utility>

namespace ls_sec {

void sub_A50();
uint64_t sub_A80(const uint64_t *data, std::size_t n);
std::pair<uint64_t, uint64_t> sub_1480(uint64_t a, uint64_t b);
uint32_t sub_1A10(uint32_t src);
uint32_t sub_1A40(uint32_t src);
void sub_1A80(uint8_t *dst, const uint8_t *src, std::size_t n);
bool sub_1C20(uint8_t *a, uint8_t *b, std::size_t n);

} // namespace ls_sec
