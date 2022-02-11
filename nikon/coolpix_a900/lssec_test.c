#include <stdio.h>
#include <time.h>

#include "lssec.h"
#include "lssec_data.h"


int main() {
  const uint32_t seed = time(NULL);

  printf("seed: %u\n", seed);

  byte_8140_t byte_8140 = {0};

  LsSecInit(&byte_8140, seed);

  ai8_t nonce;
  int32_t ok = LsSec1stStage(&byte_8140, &nonce);
  printf("ok: %d\n", ok);
  printf("nonce: %016lx\n", nonce.u64);

  ai8_t s1 = nonce;
  ai8_t dev;
  dev.u64 = 0x357ed673c4281573;
  nonce.u64 = 0x0000626300006764;  // returned by camera

  ai8_t result;
  ok = LsSec3rdStage(&byte_8140, &nonce, &s1, &dev, &result);
  printf("ok: %d\n", ok);
  printf("result: %016lx\n", result.u64);

  return 0;
}
