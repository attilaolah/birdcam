#include "ref.h"

#include <cstdint>
#include <cstdlib>

namespace ls_sec::ref {

static uint32_t addr_9040;

void sub_A50() {
    addr_9040 = 1;
}

int64_t LsSecInit(uint8_t *a1, uint64_t a2)
{
  uint8_t *v2; // rax

  v2 = a1;
  do {
    *(__uint128_t *)v2 = 0LL;
    v2 += 16;
  } while ( v2 != a1 + 8400 );
  a1[8400] = 0;
  a1[8401] = 0;
  a1[8402] = 0;
  a1[8403] = 0;
  a1[8404] = 0;
  a1[8405] = 0;
  a1[8406] = 0;
  a1[8407] = 0;
  if ( a2 )
    srand(a2);
  sub_A50();
  *((uint32_t *)a1 + 2100) = 1;
  return 0LL;
}

} // namespace ls_sec::ref
