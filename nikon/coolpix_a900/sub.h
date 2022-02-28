#pragma once

#include <cstdint>
#include <utility>
#include <vector>

namespace ls_sec {

uint64_t entangle(const std::vector<uint64_t> &elements);
std::pair<uint64_t, uint64_t> sub_1480(uint64_t a, uint64_t b);
uint32_t sub_1A40(uint32_t src);
void sub_1A80(uint8_t *dst, const uint8_t *src, std::size_t n);
bool sub_1C20(uint8_t *a, uint8_t *b, std::size_t n);

} // namespace ls_sec
