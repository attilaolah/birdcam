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

int32_t LsSec3rdStage(byte_8140_t *byte_8140, ai8_t *a1, ai8_t *a2, ai8_t *a3, ai8_t *res) {
  if (byte_8140->i32[1058] != 3) {
    return -103;
  }

  sub_1B40(&byte_8140->u32[8], a1->u32, 8);
  sub_1B40(&byte_8140->u32[10], a2->u32, 8);
  sub_1B40(&byte_8140->u32[0], a1->u32, 4);
  sub_1B40(&byte_8140->u32[1], a2->u32, 4);

  int32_t i;
  for (i = 0; i != 7; ++i) {
    sub_1B40(&byte_8140->u32[6], &byte_4200[i], 8);
    // segfaults:
    //sub_8C0(&byte_8140->i32[6], &byte_8140->i32[2], 0x18u);
    if (byte_8140->u64[1] == a3->u64) {
      break;
    }
  }
  byte_8140->u8[0] = (uint8_t) i;
  sub_1B40(&byte_8140->u32[8], a2->u32, 8);
  sub_1B40(&byte_8140->u32[10], a1->u32, 8);
  //sub_8C0(&byte_8140->i32[6], res, 0x18u);

  if (i == 7) {
    return -102;
  }
  byte_8140->i32[1058] = 5;
  return 0;
}
