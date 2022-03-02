#pragma once

#include <array>
#include <cstdint>

namespace ls_sec {
extern std::array<uint32_t, 16> R16;
extern std::array<uint32_t, 256> FIELD_0;
extern std::array<uint32_t, 256> FIELD_1;
extern std::array<uint32_t, 256> FIELD_2;
extern std::array<uint32_t, 256> FIELD_3;
extern std::array<uint64_t, 8> SEED_8;
}  // namespace ls_sec
