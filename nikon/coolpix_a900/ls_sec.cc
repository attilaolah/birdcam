#include "ls_sec.h"
#include "ls_sec_jni.h"

namespace ls_sec {

LsSec::LsSec(unsigned int seed) { LsSecInit(&data_, seed); }

std::array<uint8_t, 8> LsSec::stage_1() {
  std::array<uint8_t, 8> result;
  if (const int err = LsSec1stStage(&data_, result.data()); err != 0) {
    throw LsSecError(err);
  }

  return result;
}

LsSecError::LsSecError(int code) : code_(code) {}

const char *LsSecError::what() const noexcept {
  switch (code_) {
  case OK:
    return "ok";
  case ERR_WRONG_STAGE:
    return "lssec error: wrong stage";
  default:
    return "lssec error: unknown";
  }
}

} // namespace ls_sec
