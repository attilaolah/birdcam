#ifndef LS_SEC_H
#define LS_SEC_H

#include <array>
#include <cstdint>

namespace ls_sec {

class LsSec {
public:
  explicit LsSec(unsigned int seed);

  std::array<uint8_t, 8> stage_1();

private:
  uint8_t data_[8408];
};

class LsSecError : public std::exception {
public:
  LsSecError(int code);

  virtual const char *what() const noexcept override;

private:
  static constexpr int OK = 0;
  static constexpr int ERR_WRONG_STAGE = -103;

  int code_;
};

} // namespace ls_sec

#endif // LS_SEC_H
