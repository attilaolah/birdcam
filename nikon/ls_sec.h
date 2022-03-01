#ifndef LS_SEC_H
#define LS_SEC_H

#include <array>
#include <cstdint>
#include <exception>

namespace ls_sec {

class LsSec {
 public:
  explicit LsSec(uint32_t seed) noexcept;

  uint64_t stage_1();

  std::pair<uint64_t, uint64_t> stage_2(uint64_t stage_1);

  uint64_t stage_3(uint64_t nonce, uint64_t stage_1, uint64_t device_id);

  void stage_4(uint64_t nonce, uint64_t stage_1, uint64_t stage_3);

 private:
  const uint64_t hash_3(const uint64_t a, const uint64_t b) const;

  enum class Stage {
    STAGE_1,
    STAGE_2,
    STAGE_3,
    STAGE_4,
    STAGE_5,
  };
  Stage stage_;
  uint8_t index_;
};

enum class Status {
  OK = 0,
  ERR_AUTH = -102,
  ERR_WRONG_STAGE = -103,
};

class Error {
 public:
  Error(const Status &status) noexcept;
  const int8_t status_code() const noexcept;

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

}  // namespace ls_sec

#endif  // LS_SEC_H
