#pragma once

#include <array>
#include <cstdint>
#include <exception>
#include <vector>

namespace ls_sec {

static constexpr char kMsgOk[] = "ls_sec: ok";
static constexpr char kMsgAuth[] = "ls_sec: authentication error";
static constexpr char kMsgWrongStage[] = "ls_sec: wrong stage error";
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

private:
  const uint64_t hash_3(const uint64_t a, const uint64_t b) const;

  enum class Stage {
    STAGE_1,
    STAGE_2,
    STAGE_3,
    STAGE_4,
    STAGE_5,
    STAGE_6,
  };
  Stage stage_;
  uint8_t index_;
};

enum class Status {
  OK = 0,
  ERR_ENC = -100,
  ERR_AUTH = -102,
  ERR_WRONG_STAGE = -103,
};

class Error {
public:
  Error(const Status &status) noexcept;
  const int8_t status_code() const noexcept;
  const char *status_message() const noexcept;

protected:
  Status status_;
};

class ErrAuth : public Error, public std::exception {
public:
  ErrAuth() noexcept;
  virtual const char *what() const noexcept override;
};

class ErrWrongStage : public Error, public std::exception {
public:
  ErrWrongStage() noexcept;
  virtual const char *what() const noexcept override;
};

} // namespace ls_sec
