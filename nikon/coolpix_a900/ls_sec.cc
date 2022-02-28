#include "ls_sec.h"

#include <cstdlib>

#include "sub.h"

namespace ls_sec {

LsSec::LsSec(unsigned int seed) noexcept {
  if (seed) {
    std::srand(seed);
  }
  sub_A50();
  reinterpret_cast<uint32_t *>(data_.data())[2100] = 1;
}

std::array<uint8_t, 8> LsSec::stage_1() {
  if (reinterpret_cast<uint32_t *>(data_.data())[2100] != 1) {
    throw ErrWrongStage();
  }

  std::array<uint8_t, 8> result;
  reinterpret_cast<uint32_t *>(result.data())[0] = sub_1A40(rand());
  reinterpret_cast<uint32_t *>(result.data())[1] = sub_1A40(rand());
  reinterpret_cast<uint32_t *>(data_.data())[2100] = 3;

  return result;
}

const char *ErrWrongStage::what() const noexcept {
  return "ls_sec error: wrong stage";
}

} // namespace ls_sec
