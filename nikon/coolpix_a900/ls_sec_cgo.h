#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void *LsSec;
LsSec ls_sec_new(uint32_t seed);
void ls_sec_free(LsSec ptr);
uint64_t ls_sec_stage_1(LsSec ptr);
uint64_t ls_sec_stage_3(LsSec ptr, uint64_t nonce, uint64_t stage_1,
                        uint64_t device_id);

#ifdef __cplusplus
}
#endif
