#include "ls_sec.h"

#include <cstdlib>
#include <cstring>

#include "sub.h"
#include "sub_data.h"

namespace ls_sec {
namespace {
uint64_t urand64() { return ((uint64_t)rand() << 32) | rand(); }
} // namespace

LsSec::LsSec(unsigned int seed) : stage_(Stage::STAGE_1), index_(-1) {
  if (seed) {
    std::srand(seed);
  }
}

uint64_t LsSec::stage_1() {
  if (stage_ != Stage::STAGE_1) {
    throw ErrWrongStage();
  }
  stage_ = Stage::STAGE_3;

  return urand64();
}

std::pair<uint64_t, uint64_t> LsSec::stage_2(uint64_t stage_1) {
  if (stage_ != Stage::STAGE_1) {
    throw ErrWrongStage();
  }
  stage_ = Stage::STAGE_2;

  uint64_t nonce = urand64();
  index_ = rand() & 7;
  std::array<uint64_t, 3> buf = {{DATA_4AC0[index_], nonce, stage_1}};
  return std::make_pair(nonce, sub_A80(buf.data(), 24));
}

uint64_t LsSec::stage_3(uint64_t nonce, uint64_t stage_1, uint64_t device_id) {
  if (stage_ != Stage::STAGE_3) {
    throw ErrWrongStage();
  }

  std::array<uint64_t, 3> buf = {{0, nonce, stage_1}};

  for (index_ = 0; index_ < 8; index_++) {
    buf[0] = DATA_4AC0[index_];
    if (sub_A80(buf.data(), 24) == device_id) {
      break;
    }
  }
  if (index_ == 8) {
    throw ErrAuth();
  }
  stage_ = Stage::STAGE_5;

  buf[1] = stage_1;
  buf[2] = nonce;
  return sub_A80(buf.data(), 24);
}

void LsSec::stage_4(uint64_t a, uint64_t b, uint64_t device_id) {
  if (stage_ != Stage::STAGE_2) {
    throw ErrWrongStage();
  }

  std::array<uint64_t, 3> buf = {{DATA_4AC0[index_], b, a}};
  if (sub_A80(buf.data(), 24) != device_id) {
    throw ErrAuth();
  }
  stage_ = Stage::STAGE_5;
}

const char *ErrAuth::what() const noexcept {
  return "ls_sec error: authentication error";
}

const char *ErrWrongStage::what() const noexcept {
  return "ls_sec error: wrong stage";
}

} // namespace ls_sec
