#pragma once

#include <cstdint>
#include <utility>
#include <vector>

namespace ls_sec {

uint64_t entangle(const std::vector<uint64_t> &elements);
std::pair<uint32_t, uint32_t> sub_1480(uint32_t a, uint32_t b);
uint32_t sub_1A40(uint32_t src);

} // namespace ls_sec
