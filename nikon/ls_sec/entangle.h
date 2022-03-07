#pragma once

#include <cstdint>
#include <utility>
#include <vector>

#include "data.h"

namespace ls_sec {

uint64_t entangle(const std::vector<uint64_t> &elements) noexcept;

void entangle_2(const KeyMaterial &key, uint32_t *a, uint32_t *b) noexcept;

void untangle_2(const KeyMaterial &key, uint32_t *a, uint32_t *b) noexcept;

} // namespace ls_sec
