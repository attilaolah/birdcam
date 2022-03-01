#include "ls_sec_cgo.h"

#include "ls_sec.h"

#define OK 0

LsSec ls_sec_new(uint32_t seed) {
  ls_sec::LsSec *ret = new ls_sec::LsSec(seed);
  return (void *)ret;
}

void ls_sec_free(LsSec ptr) {
  ls_sec::LsSec *self = (ls_sec::LsSec *)ptr;
  delete self;
}

int8_t ls_sec_stage_1(LsSec ptr, uint64_t *dst) {
  ls_sec::LsSec *self = (ls_sec::LsSec *)ptr;
  try {
    *dst = self->stage_1();
  } catch (const ls_sec::Error &err) {
    return err.status_code();
  }
  return OK;
}

int8_t ls_sec_stage_2(LsSec ptr, uint64_t stage_1, uint64_t *dst_1,
                      uint64_t *dst_2) {
  ls_sec::LsSec *self = (ls_sec::LsSec *)ptr;
  std::pair<uint64_t, uint64_t> result;
  try {
    result = self->stage_2(stage_1);
  } catch (const ls_sec::Error &err) {
    return err.status_code();
  }
  *dst_1 = result.first;
  *dst_2 = result.second;
  return OK;
}

int8_t ls_sec_stage_3(LsSec ptr, uint64_t nonce, uint64_t stage_1,
                      uint64_t device_id, uint64_t *dst) {
  ls_sec::LsSec *self = (ls_sec::LsSec *)ptr;
  try {
    *dst = self->stage_3(nonce, stage_1, device_id);
  } catch (const ls_sec::Error &err) {
    return err.status_code();
  }
  return OK;
}

int8_t ls_sec_stage_4(LsSec ptr, uint64_t nonce, uint64_t stage_1,
                      uint64_t stage_3) {
  ls_sec::LsSec *self = (ls_sec::LsSec *)ptr;
  try {
    self->stage_4(nonce, stage_1, stage_3);
  } catch (const ls_sec::Error &err) {
    return err.status_code();
  }
  return OK;
}
