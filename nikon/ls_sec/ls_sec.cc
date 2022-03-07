#include "ls_sec.h"

#include <cstdlib>
#include <cstring>
#include <limits>

#include "entangle.h"

namespace ls_sec {
namespace {
// Alignment for encoding/decoding.
constexpr size_t kAlign = sizeof(uint64_t) / sizeof(uint8_t);

uint64_t urand64() { return ((uint64_t)rand() << 32) | rand(); }

void _init_key(KeyMaterial &key, const uint64_t *src, int16_t n) {
  int v7;
  int v8;
  int v9;
  uint64_t v10;
  uint64_t v11;

  // TODO: do a for &iterator loop!
  for (size_t i = 0; i < key.header.size(); i++) {
    size_t v6 = n + 1;
    n = (int16_t)n;
    if ((int16_t)v6 >= (int16_t)n)
      v6 = 0;
    v7 = v6 + 1;
    if ((int16_t)(v6 + 1) >= (int16_t)n)
      v7 = 0;
    v8 = v7 + 1;
    v9 = (*((uint8_t *)src + (int16_t)v6) |
          ((uint64_t) * ((uint8_t *)src + n) << 8))
         << 8;
    if ((int16_t)(v7 + 1) >= (int16_t)n)
      v8 = 0;
    v10 = (*((uint8_t *)src + (int16_t)v7) | v9) << 8;
    n = v8 + 1;
    v11 = *((uint8_t *)src + (int16_t)v8);
    if ((int16_t)n >= (int16_t)n)
      n = 0;
    key.header[i] = kKeyMaterial2.header[i] ^ (v11 | v10);
  }

  // TODO: Set this up in the ctor!
  key.data = kKeyMaterial2.data;
  uint32_t x, y = 0;
  for (size_t i = 0; i < key.header.size(); i += 2) {
    entangle_2(key, &x, &y);
    key.header[i] = x;
    key.header[i + 1] = y;
  }

  uint32_t v17 = key.header[16];
  uint32_t v18 = key.header[17];

  for (size_t i = 0; i < key.data.size(); i++) {
    for (size_t j = 0; j < key.data[i].size() / 2; j += 2) {
      //  TODO: Use entangle_2()!
      for (size_t k = 0; k < 16; k++) {
        uint32_t prev = key.header[k] ^ v17;
        uint32_t f0 = key.data[0][(prev >> 0x18) & 0xff];
        uint32_t f1 = key.data[1][(prev >> 0x10) & 0xff];
        uint32_t f2 = key.data[2][(prev >> 0x08) & 0xff];
        uint32_t f3 = key.data[3][(prev >> 0x00) & 0xff];
        v17 = v18 ^ (f3 + (f2 ^ (f1 + f0)));
        v18 = prev;
      }
      uint32_t v26 = key.header[16] ^ v17;
      uint32_t v27 = key.header[17] ^ v18;

      key.data[i][j] = v27;
      key.data[i][j + 1] = v26;
      v17 = v27;
      v18 = v26;
    }
  }
}

} // namespace

LsSec::LsSec(uint32_t seed) noexcept {
  if (seed) {
    std::srand(seed);
  }
}

uint64_t LsSec::stage_1() {
  if (stage_ != Stage::STAGE_1) {
    throw ErrStage();
  }
  stage_ = Stage::STAGE_3;

  return urand64();
}

std::pair<uint64_t, uint64_t> LsSec::stage_2(uint64_t stage_1) {
  if (stage_ != Stage::STAGE_1) {
    throw ErrStage();
  }
  stage_ = Stage::STAGE_2;

  uint64_t nonce = urand64();

  index_ = rand() & 7;
  set_secret(nonce, stage_1);
  return std::make_pair(nonce, hash_3(nonce, stage_1));
}

uint64_t LsSec::stage_3(uint64_t nonce, uint64_t stage_1, uint64_t device_id) {
  if (stage_ != Stage::STAGE_3) {
    throw ErrStage();
  }

  for (index_ = 0; index_ < kSeed.size(); index_++) {
    if (hash_3(nonce, stage_1) == device_id) {
      break;
    }
  }
  if (index_ == 8) {
    throw ErrAuthn();
  }
  stage_ = Stage::STAGE_5;

  set_secret(nonce, stage_1);
  return hash_3(stage_1, nonce);
}

void LsSec::stage_4(uint64_t nonce, uint64_t stage_1, uint64_t stage_3) {
  if (stage_ != Stage::STAGE_2) {
    throw ErrStage();
  }

  if (hash_3(stage_1, nonce) != stage_3) {
    throw ErrAuthn();
  }
  stage_ = Stage::STAGE_5;
}

void LsSec::generate_key(uint64_t stage_4, uint64_t device_id) {
  if (stage_ != Stage::STAGE_5) {
    throw ErrStage();
  }

  // TODO!
  // const uint64_t tmp = entangle({stage_4, device_id, todo});
  // sub_15A0(data + 8, tmp, 8);
  const uint64_t tmp = entangle({stage_4, device_id, secret_});
  _init_key(key_, &tmp, 8);
  // OK: printf("%u, %u\n", key_.header[0], key_.header[1]);

  stage_ = Stage::STAGE_6;
}

std::vector<uint8_t> LsSec::encode(const std::vector<uint8_t> &data) const {
  if (stage_ != Stage::STAGE_6) {
    throw ErrStage();
  }

  if (data.size() % kAlign != 0) {
    throw ErrAlign();
  }

  std::vector<uint64_t> src, dst;
  src.resize(data.size() / kAlign);
  dst.resize(data.size() / kAlign);
  std::memcpy(src.data(), data.data(), data.size());

  uint32_t x = 0, y = 0;
  for (size_t i = 0; i < src.size(); i++) {
    x = __bswap_32(src[i] & std::numeric_limits<uint32_t>::max()) ^ x;
    y = __bswap_32(src[i] >> 32) ^ y;
    entangle_2(key_, &x, &y);
    dst[i] = (uint64_t)__bswap_32(x) | (uint64_t)__bswap_32(y) << 32;
  }

  std::vector<uint8_t> res;
  res.resize(data.size());
  std::memcpy(res.data(), dst.data(), res.size());
  return res;
}

std::vector<uint8_t> LsSec::decode(const std::vector<uint8_t> &data) const {
  if (stage_ != Stage::STAGE_6) {
    throw ErrStage();
  }

  if (data.size() % kAlign != 0) {
    throw ErrAlign();
  }

  std::vector<uint64_t> src, dst;
  src.resize(data.size() / kAlign);
  dst.resize(data.size() / kAlign);
  std::memcpy(src.data(), data.data(), data.size());

  uint32_t x = 0, y = 0;
  for (size_t i = 0; i < src.size(); i++) {
    const uint32_t ea =
        __bswap_32(src[i] & std::numeric_limits<uint32_t>::max());
    const uint32_t eb = __bswap_32(src[i] >> 32);
    uint32_t a = ea, b = eb;
    untangle_2(key_, &a, &b);
    dst[i] = (uint64_t)__bswap_32(a ^ x) | (uint64_t)__bswap_32(b ^ y) << 32;
    x = ea;
    y = eb;
  }

  std::vector<uint8_t> res;
  res.resize(data.size());
  std::memcpy(res.data(), dst.data(), res.size());
  return res;
}

const uint64_t LsSec::hash_3(const uint64_t a, const uint64_t b) const {
  return entangle({kSeed[index_], a, b});
}

void LsSec::set_secret(const uint64_t nonce, const uint64_t device_id) {
  secret_ = (nonce & std::numeric_limits<uint32_t>::max()) | (device_id << 32);
  secret_ = (secret_ ^ std::numeric_limits<uint8_t>::max()) | index_;
}

Error::Error(const Status &status) noexcept : status_(status) {}

const int8_t Error::status_code() const noexcept {
  return static_cast<int8_t>(status_);
}

const char *Error::status_message() const noexcept {
  switch (status_) {
  case Status::OK:
    return kMsgOk;
  case Status::ERR_ALIGN:
    return kMsgAlign;
  case Status::ERR_AUTHN:
    return kMsgAuthn;
  case Status::ERR_STAGE:
    return kMsgStage;
  default:
    return kMsgUnknown;
  }
}

ErrAlign::ErrAlign() noexcept : Error(Status::ERR_ALIGN) {}

const char *ErrAlign::what() const noexcept { return status_message(); }

ErrAuthn::ErrAuthn() noexcept : Error(Status::ERR_AUTHN) {}

const char *ErrAuthn::what() const noexcept { return status_message(); }

ErrStage::ErrStage() noexcept : Error(Status::ERR_STAGE) {}

const char *ErrStage::what() const noexcept { return status_message(); }

} // namespace ls_sec
