#pragma once

#include <cstdint>

namespace ls_sec {

uint32_t sub_1A10(uint32_t src);
uint32_t sub_1A40(uint32_t src);
void sub_1A80(uint8_t *dst, uint8_t *src, std::size_t n);
bool sub_1C20(uint8_t *a, uint8_t *b, std::size_t n);

} // namespace ls_sec
