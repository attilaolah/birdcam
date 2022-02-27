#include "ls_sec.h"
#include "ls_sec_jni.h"

namespace ls_sec {

LsSec::LsSec(unsigned int seed) { LsSecInit(&data_, seed); }

LsSecError::LsSecError(int code) : code_(code) {}

} // namespace ls_sec
