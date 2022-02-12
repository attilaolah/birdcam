#include "lssec.h"
#include "lssec_data.h"
#include "lssec_sub.h"

void LsSecInit(byte_8140_t *byte_8140, uint32_t seed) {
  if (seed != 0) {
    srand(seed);
  }
  byte_8140->i32[1058] = 1;
}

int32_t LsSec1stStage(byte_8140_t *byte_8140, ai8_t *res) {
  if (byte_8140->i32[1058] != 1) {
    return -103;
  }
  res->i32[0] = rand();
  res->i32[1] = rand();
  byte_8140->i32[1058] = 3;
  return 0;
}

/*
   byte_8140 memory layout:
  --------------------------------
  | a1->u32[0]:i | a2->u32[0]    | u64[0]
  | ?                            | u64[1]
  | ?                            | u64[2]
  | byte_4200 @ offset i [0-7]   | u64[3]
  | a1->u64 / a2->u64            | u64[4]
  | a2->u64 / a1->u64            | u64[5]
  --------------------------------
 */




int32_t LsSec3rdStage(byte_8140_t *byte_8140, ai8_t *a1, ai8_t *a2, ai8_t *a3, ai8_t *res) {
  if (byte_8140->i32[1058] != 3) {
    return -103;
  }

  byte_8140->u32[0] = a1->u32[0];
  byte_8140->u32[1] = a2->u32[0];
  byte_8140->u64[4] = a1->u64;
  byte_8140->u64[5] = a2->u64;

  int32_t i;
  for (i = 0; i != 7; i++) {
    byte_8140->u8[24+0] = byte_4200[i+0];
    byte_8140->u8[24+1] = byte_4200[i+1];
    byte_8140->u8[24+2] = byte_4200[i+2];
    byte_8140->u8[24+3] = byte_4200[i+3];
    byte_8140->u8[24+4] = byte_4200[i+4];
    byte_8140->u8[24+5] = byte_4200[i+5];
    byte_8140->u8[24+6] = byte_4200[i+6];
    byte_8140->u8[24+7] = byte_4200[i+7];
    // segfaults:
    // i32[6] is what we just filled in, i32[2] is ???
    //sub_8C0(&byte_8140->i32[6], &byte_8140->i32[2], 0x18u);
    if (byte_8140->u64[1] == a3->u64) {
      break;
    }
  }
  if (i == 7) {
    return -102;
  }
  byte_8140->u8[0] = (uint8_t) i;
  byte_8140->u64[4] = a2->u64;
  byte_8140->u64[5] = a1->u64;
  //sub_8C0(&byte_8140->i32[6], res, 0x18u);

  byte_8140->i32[1058] = 5;
  return 0;
}
