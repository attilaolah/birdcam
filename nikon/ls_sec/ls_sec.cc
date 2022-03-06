#include "ls_sec.h"

#include <cstdlib>
#include <cstring>

#include "data.h"
#include "entangle.h"

namespace ls_sec {
namespace {
uint64_t urand64() { return ((uint64_t)rand() << 32) | rand(); }
} // namespace

LsSec::LsSec(uint32_t seed) noexcept : stage_(Stage::STAGE_1), index_(0) {
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

void LsSec::generate_key(uint64_t stage_4, uint64_t device_id) {
  if (stage_ != Stage::STAGE_5) {
    throw ErrWrongStage();
  }

  // TODO!
  //uint64_t todo; // == data[0]
  //const uint64_t tmp = entangle({stage_4, device_id, todo});
  // sub_15A0(data + 8, tmp, 8);

  stage_ = Stage::STAGE_6;
}

std::vector<uint8_t> LsSec::encode(const std::vector<uint8_t> &data) const {
  if (stage_ != Stage::STAGE_6) {
    throw ErrWrongStage();
  }

  // TODO!
  return data;
}

std::vector<uint8_t> LsSec::decode(const std::vector<uint8_t> &data) const {
  if (stage_ != Stage::STAGE_6) {
    throw ErrWrongStage();
  }

  // TODO!
  return data;
}

const uint64_t LsSec::hash_3(const uint64_t a, const uint64_t b) const {
  return entangle({SEED_8[index_], a, b});
}

Error::Error(const Status &status) noexcept : status_(status) {}

const int8_t Error::status_code() const noexcept {
  return static_cast<int8_t>(status_);
}

const char *Error::status_message() const noexcept {
  switch (status_) {
  case Status::OK:
    return kMsgOk;
  case Status::ERR_AUTH:
    return kMsgAuth;
  case Status::ERR_WRONG_STAGE:
    return kMsgWrongStage;
  default:
    return kMsgUnknown;
  }
}

ErrAuth::ErrAuth() noexcept : Error(Status::ERR_AUTH) {}

const char *ErrAuth::what() const noexcept { return status_message(); }

ErrWrongStage::ErrWrongStage() noexcept : Error(Status::ERR_WRONG_STAGE) {}

const char *ErrWrongStage::what() const noexcept { return status_message(); }

} // namespace ls_sec
