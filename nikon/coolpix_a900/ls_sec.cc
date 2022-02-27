#include "ls_sec.h"

// LsSec shim:
// extern int LsSecInit(void *buf, unsigned int seed);

namespace ls_sec {

int init(void *buf, unsigned int seed) {
  // TODO:
  // return LsSecInit(buf, seed);
  return 0;
}

} // namespace ls_sec
