#pragma once

#include <cstdint>
#include <exception>
#include <vector>

#include "data.h"

namespace ls_sec {

static constexpr char kMsgOk[] = "ls_sec: ok";
static constexpr char kMsgAlign[] = "ls_sec: alignment error";
static constexpr char kMsgAuthn[] = "ls_sec: authentication error";
static constexpr char kMsgStage[] = "ls_sec: wrong stage error";
static constexpr char kMsgUnknown[] = "ls_sec: unknown error";

class LsSec {
public:
  explicit LsSec(uint32_t seed) noexcept;

  uint64_t stage_1();

  std::pair<uint64_t, uint64_t> stage_2(uint64_t stage_1);

  uint64_t stage_3(uint64_t nonce, uint64_t stage_1, uint64_t device_id);

  void stage_4(uint64_t nonce, uint64_t stage_1, uint64_t stage_3);

  void generate_key(uint64_t stage_4, uint64_t device_id);

  std::vector<uint8_t> encode(const std::vector<uint8_t> &data) const;

  std::vector<uint8_t> decode(const std::vector<uint8_t> &data) const;

//private:
  const uint64_t hash_3(const uint64_t a, const uint64_t b) const;

  void set_secret(const uint64_t nonce, const uint64_t stage_1);

  enum class Stage {
    STAGE_1,
    STAGE_2,
    STAGE_3,
    STAGE_4,
    STAGE_5,
    STAGE_6,
  };
  Stage stage_ = Stage::STAGE_1;
  uint8_t index_ = 0;
  uint64_t secret_ = 0;
  KeyMaterial key_;
};

enum class Status {
  OK = 0,
  ERR_ALIGN = -100,
  ERR_AUTHN = -102,
  ERR_STAGE = -103,
};

class Error {
public:
  Error(const Status &status) noexcept;
  const int8_t status_code() const noexcept;
  const char *status_message() const noexcept;

protected:
  Status status_;
};

class ErrAlign : public Error, public std::exception {
public:
  ErrAlign() noexcept;
  virtual const char *what() const noexcept override;
};

class ErrAuthn : public Error, public std::exception {
public:
  ErrAuthn() noexcept;
  virtual const char *what() const noexcept override;
};

class ErrStage : public Error, public std::exception {
public:
  ErrStage() noexcept;
  virtual const char *what() const noexcept override;
};

} // namespace ls_sec
