#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void *LsSec;

LsSec ls_sec_new(uint32_t seed);
void ls_sec_free(LsSec ptr);

int8_t ls_sec_stage_1(LsSec ptr, uint64_t *dst);
int8_t ls_sec_stage_2(LsSec ptr, uint64_t stage_1, uint64_t *dst_1,
                      uint64_t *dst_2);
int8_t ls_sec_stage_3(LsSec ptr, uint64_t nonce, uint64_t stage_1,
                      uint64_t device_id, uint64_t *dst);
int8_t ls_sec_stage_4(LsSec ptr, uint64_t nonce, uint64_t stage_1,
                      uint64_t stage_3);

const char* ls_sec_error(int8_t code);

#ifdef __cplusplus
}
#endif
