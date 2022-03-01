#include "ls_sec.h"

#include <cstdlib>
#include <cstring>

#include "sub.h"
#include "sub_data.h"

namespace ls_sec {
namespace {
uint64_t urand64() { return ((uint64_t)rand() << 32) | rand(); }
} // namespace

LsSec::LsSec(unsigned int seed) : stage_(Stage::STAGE_1), index_(0) {
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
  return std::make_pair(nonce, hash_3(nonce, stage_1));
}

uint64_t LsSec::stage_3(uint64_t nonce, uint64_t stage_1, uint64_t device_id) {
  if (stage_ != Stage::STAGE_3) {
    throw ErrWrongStage();
  }

  for (index_ = 0; index_ < SEED_8.size(); index_++) {
    if (hash_3(nonce, stage_1) == device_id) {
      break;
    }
  }
  if (index_ == 8) {
    throw ErrAuth();
  }
  stage_ = Stage::STAGE_5;

  return hash_3(stage_1, nonce);
}

void LsSec::stage_4(uint64_t nonce, uint64_t stage_1, uint64_t stage_3) {
  if (stage_ != Stage::STAGE_2) {
    throw ErrWrongStage();
  }

  if (hash_3(stage_1, nonce) != stage_3) {
    throw ErrAuth();
  }
  stage_ = Stage::STAGE_5;
}

const uint64_t LsSec::hash_3(const uint64_t a, const uint64_t b) const {
  return entangle({SEED_8[index_], a, b});
}

const char *ErrAuth::what() const noexcept {
  return "ls_sec error: authentication error";
}

const char *ErrWrongStage::what() const noexcept {
  return "ls_sec error: wrong stage";
}

} // namespace ls_sec
