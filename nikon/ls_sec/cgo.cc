#include "cgo.h"

#include <cstring>
#include <vector>

#include "ls_sec.h"

#define OK 0

int8_t ls_sec_err_align = static_cast<int8_t>(ls_sec::Status::ERR_ALIGN);
int8_t ls_sec_err_authn = static_cast<int8_t>(ls_sec::Status::ERR_AUTHN);
int8_t ls_sec_err_stage = static_cast<int8_t>(ls_sec::Status::ERR_STAGE);

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

int8_t ls_sec_generate_key(LsSec ptr, uint64_t stage_4, uint64_t device_id) {
  ls_sec::LsSec *self = (ls_sec::LsSec *)ptr;
  try {
    self->generate_key(stage_4, device_id);
  } catch (const ls_sec::Error &err) {
    return err.status_code();
  }
  return OK;
}

int8_t ls_sec_encode(LsSec ptr, uint8_t *src, uint8_t *dst, size_t n) {
  ls_sec::LsSec *self = (ls_sec::LsSec *)ptr;
  std::vector<uint8_t> result;
  try {
    result = self->encode(std::vector<uint8_t>(src, src + n));
  } catch (const ls_sec::Error &err) {
    return err.status_code();
  }
  std::memcpy(dst, result.data(), n);
  return OK;
}

int8_t ls_sec_decode(LsSec ptr, uint8_t *src, uint8_t *dst, size_t n) {
  ls_sec::LsSec *self = (ls_sec::LsSec *)ptr;
  std::vector<uint8_t> result;
  try {
    result = self->decode(std::vector<uint8_t>(src, src + n));
  } catch (const ls_sec::Error &err) {
    return err.status_code();
  }
  std::memcpy(dst, result.data(), n);
  return OK;
}

const char *ls_sec_error(int8_t code) {
  return ls_sec::Error(static_cast<ls_sec::Status>(code)).status_message();
}
