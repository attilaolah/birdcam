#ifndef LS_SEC_H
#define LS_SEC_H

#include <cstdint>

namespace ls_sec {

class LsSec {
public:
  explicit LsSec(unsigned int seed);

private:
  uint8_t data_[8408];
};

class LsSecError {
public:
  LsSecError(int code);

private:
  int code_;
};

} // namespace ls_sec

#endif // LS_SEC_H
