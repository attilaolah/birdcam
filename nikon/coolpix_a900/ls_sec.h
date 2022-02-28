#ifndef LS_SEC_H
#define LS_SEC_H

#include <array>
#include <cstdint>

namespace ls_sec {

class LsSec {
public:
  explicit LsSec(unsigned int seed) noexcept;

  std::array<uint8_t, 8> stage_1();

private:
  std::array<uint8_t, 8408> data_ = {{0}};
};

enum class Status {
  OK = 0,
  ERR_WRONG_STAGE = -103,
};

class ErrWrongStage : public std::exception {
  virtual const char *what() const noexcept override;
};

} // namespace ls_sec

#endif // LS_SEC_H
