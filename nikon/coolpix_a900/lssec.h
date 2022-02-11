#ifndef _LSSEC_H_
#define _LSSEC_H_

#include <stdint.h>
#include <x86intrin.h>

#define SIZE_8140_128 268

typedef union {
  __m128i i128[SIZE_8140_128];

  int64_t i64[SIZE_8140_128*2];
  int32_t i32[SIZE_8140_128*4];
  int16_t i16[SIZE_8140_128*8];
  int8_t i8[SIZE_8140_128*16];

  uint64_t u64[SIZE_8140_128*2];
  uint32_t u32[SIZE_8140_128*4];
  uint16_t u16[SIZE_8140_128*8];
  uint8_t u8[SIZE_8140_128*16];
} byte_8140_t;

typedef union {
  int64_t i64;
  int32_t i32[2];
  int8_t i8[8];

  uint64_t u64;
  uint32_t u32[2];
  uint8_t u8[8];
} ai8_t;

void LsSecInit(byte_8140_t *byte_8140, uint32_t seed);

int32_t LsSec1stStage(byte_8140_t *byte_8140, ai8_t *res);

int32_t LsSec3rdStage(byte_8140_t *byte_8140, ai8_t *a1, ai8_t *a2, ai8_t *a3, ai8_t *res);

#endif /* !_LSSEC_H_ */
