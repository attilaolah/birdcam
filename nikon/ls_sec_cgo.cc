#include "ls_sec_cgo.h"
#include "ls_sec.h"

LsSec ls_sec_new(uint32_t seed) {
  ls_sec::LsSec *ret = new ls_sec::LsSec(seed);
  return (void *)ret;
}

void ls_sec_free(LsSec ptr) {
  ls_sec::LsSec *self = (ls_sec::LsSec *)ptr;
  delete self;
}

uint64_t ls_sec_stage_1(LsSec ptr) {
  ls_sec::LsSec *self = (ls_sec::LsSec *)ptr;
  return self->stage_1();
}

uint64_t ls_sec_stage_3(LsSec ptr, uint64_t nonce, uint64_t stage_1,
                        uint64_t device_id) {
  ls_sec::LsSec *self = (ls_sec::LsSec *)ptr;
  return self->stage_3(nonce, stage_1, device_id);
}
