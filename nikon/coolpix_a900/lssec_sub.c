#include "lssec_sub.h"

#include <byteswap.h>
#include <x86intrin.h>

#include "lssec_data.h"

typedef unsigned char   BYTE;           //  8-bit
typedef unsigned short  WORD;           // 16-bit
typedef unsigned long   DWORD;          // 32-bit

#if !defined(LOBYTE)
#define LOBYTE(w)           ((BYTE)(w))
#endif
#if !defined(HIBYTE)
#define HIBYTE(w)           ((BYTE)(((WORD)(w) >> 8) & 0xFF))
#endif

#if !defined(LOWORD)
#define LOWORD(d)           ((WORD)(d))
#endif
#if !defined(HIWORD)
#define HIWORD(d)           ((WORD)((((DWORD)(d)) >> 16) & 0xFFFF))
#endif

#define BYTE1(d) (((BYTE)(d)) && 0xFF)
#define BYTE2(d) (((BYTE)(d) >> 4) && 0xFF)

uint32_t uint32_7040;

int32_t sub_8C0(int32_t a1, int32_t *a2, uint16_t a3) {
  int32_t v3; // esi
  int32_t v5; // ST00_4
  int32_t v6; // edx
  uint8_t *v7; // esi
  uint8_t v8; // al
  int16_t v9; // ax
  int16_t v10; // dx
  int16_t v11; // ax
  uint32_t result; // eax
  uint32_t v13; // et1
  int32_t v14; // [esp+18h] [ebp-54h]
  int32_t v15; // [esp+1Ch] [ebp-50h]
  int32_t v16; // [esp+20h] [ebp-4Ch]
  int32_t v17; // [esp+3Ch] [ebp-30h]
  int32_t v18; // [esp+40h] [ebp-2Ch]
  uint8_t v19[4]; // [esp+44h] [ebp-28h]
  uint8_t v20; // [esp+48h] [ebp-24h]
  uint32_t v21; // [esp+4Ch] [ebp-20h]

  v3 = a1;
  uint16_t v4 = a3;
  v21 = 42; // TODO: __readgsdword(0x14u);
  if ( !uint32_7040 )
    uint32_7040 = 1;
  if ( a3 <= 7u ) {
    v16 = a1;
    v15 = 84281096;
    v14 = 16909060;
  } else {
    v15 = 84281096;
    v14 = 16909060;
    v16 = a1 + 8 * ((uint16_t)(a3 - 8) >> 3) + 8;
    do {
      sub_1AD0(v3, &v17);
      v5 = v3 + 4;
      v3 += 8;
      sub_1AD0(v5, &v18);
      v17 ^= v14;
      v18 ^= v15;
      sub_1500(byte_3180, &v17, &v18);
      v14 = v17;
      v15 = v18;
    } while ( v16 != v3 );
    v4 = a3 & 7;
  }
  if (v4) {
    v6 = 0;
    v7 = (uint8_t *)v16;
    do {
      v8 = *v7++;
      v19[v6] = v8;
      v9 = (uint16_t)v7 - v16;
      v6 = (int16_t)((uint16_t)v7 - v16);
    } while ( v6 < v4 );
    if ( v9 <= 7 ) {
      v19[v6] = -1;
      if ( (int16_t)(v9 + 1) <= 7 ) {
        v19[(int16_t)(v9 + 1)] = -1;
        if ( v9 != 6 ) {
          v19[(int16_t)(v9 + 2)] = -1;
          if ( v9 != 5 ) {
            v19[(int16_t)(v9 + 3)] = -1;
            if ( v9 != 4 ) {
              v19[(int16_t)(v9 + 4)] = -1;
              if ( v9 != 3 ) {
                v19[(int16_t)(v9 + 5)] = -1;
                if ( v9 != 2 ) {
                  v19[(int16_t)(v9 + 6)] = -1;
                  v10 = v9 + 7;
                  if ( v9 != 1 ) {
                    v11 = v9 + 8;
                    v19[v10] = -1;
                    if ( v11 != 8 ) {
                      v19[v11] = -1;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    sub_1AD0(v19, &v17);
    sub_1AD0(&v20, &v18);
    v17 ^= v14;
    v18 ^= v15;
    sub_1500(byte_3180, &v17, &v18);
  }
  sub_1B00((uint8_t *)a2, &v17);
  sub_1B00((uint8_t *)(a2 + 4), &v18);
  v13 = 42; // TODO: __readgsdword(0x14u);
  result = v13 ^ v21;
  // TODO: ASM!
  //if ( v13 != v21 )
    //sub_850();
  return result;
}

int32_t sub_1500(uint32_t *a1, int32_t *a2, int32_t *a3) {
  uint32_t *v3; // esi
  int32_t v4; // eax
  uint32_t v5; // edi
  uint32_t v6; // eax
  uint32_t v7; // edx
  int32_t result; // eax

  v3 = a1;
  v4 = *a2;
  v5 = *a3;
  do {
    v6 = *v3 ^ v4;
    ++v3;
    v7 = v6;
    v4 = v5 ^ (a1[(uint8_t)v6 + 786] + (a1[BYTE1(v7) + 530] ^ (a1[BYTE2(v6) + 274] + a1[(v6 >> 24) + 18])));
    v5 = v7;
  } while (v3 != a1 + 16);
  result = a1[16] ^ v4;
  *a2 = a1[17] ^ v7;
  *a3 = result;
  return result;
}

void sub_1AD0(uint32_t *a1, uint32_t *a2) {
  int32_t v2; // ecx
  uint32_t result; // eax

  v2 = *(uint8_t *)(a1 + 3);
  result = bswap_32(*(uint32_t *)a1);
  *a2 = result;
}

uint8_t* sub_1B00(uint8_t *a1, int32_t *a2) {
  uint8_t *result; // eax
  int32_t v3; // edx

  result = a1;
  v3 = *a2;
  a1[3] = *a2;
  *a1 = HIBYTE(v3);
  a1[1] = BYTE2(v3);
  a1[2] = BYTE1(v3);
  return result;
}

uint8_t* sub_1B40(uint32_t *a1, uint32_t *a2, int32_t a3) {
  int8_t *v4; // esi
  int32_t v5; // ebp
  int32_t v6; // ecx
  int32_t v7; // ecx
  int32_t v8; // edi
  uint8_t *v9; // esi
  int16_t v10; // cx
  int8_t v11; // dl
  uint16_t v12; // [esp+Eh] [ebp-Eh]

  uint8_t *result = (uint8_t *)a1;
  v4 = (int8_t *)a2;
  if ( (int16_t)a3 > 0 ) {
    if ( (a1 >= a2 + 16 || a2 >= a1 + 16) && (uint16_t)a3 > 0xFu )
    {
      v5 = 0;
      v6 = a3 - 16;
      // TODO: LOWORD(v6) = (uint16_t)(a3 - 16) >> 4;
      v12 = v6 + 1;
      v7 = 16 * (v6 + 1);
      v8 = 0;
      do
      {
        ++v5;
        _mm_storeu_si128((__m128i *)(a1 + v8), _mm_loadu_si128((const __m128i *)(a2 + v8)));
        v8 += 16;
      }
      while ( v12 > (uint16_t)v5 );
      result = (uint8_t *)((uint16_t)v7 + a1);
      v9 = (uint8_t *)((uint16_t)v7 + a2);
      if ( (uint16_t)a3 != (uint16_t)v7 )
      {
        *result = *v9;
        if ( (int16_t)a3 > (int16_t)(v7 + 1) )
        {
          result[1] = v9[1];
          if ( (int16_t)a3 > (int16_t)(v7 + 2) )
          {
            result[2] = v9[2];
            if ( (int16_t)a3 > (int16_t)(v7 + 3) )
            {
              result[3] = v9[3];
              if ( (int16_t)a3 > (int16_t)(v7 + 4) )
              {
                result[4] = v9[4];
                if ( (int16_t)a3 > (int16_t)(v7 + 5) )
                {
                  result[5] = v9[5];
                  if ( (int16_t)a3 > (int16_t)(v7 + 6) )
                  {
                    result[6] = v9[6];
                    if ( (int16_t)a3 > (int16_t)(v7 + 7) )
                    {
                      v10 = v7 + 8;
                      result[7] = v9[7];
                      if ( (int16_t)a3 > v10 )
                      {
                        result[8] = v9[8];
                        if ( (int16_t)a3 > (int16_t)(v10 + 1) )
                        {
                          result[9] = v9[9];
                          if ( (int16_t)a3 > (int16_t)(v10 + 2) )
                          {
                            result[10] = v9[10];
                            if ( (int16_t)a3 > (int16_t)(v10 + 3) )
                            {
                              result[11] = v9[11];
                              if ( (int16_t)a3 > (int16_t)(v10 + 4) )
                              {
                                result[12] = v9[12];
                                if ( (int16_t)a3 > (int16_t)(v10 + 5) )
                                {
                                  result[13] = v9[13];
                                  if ( (int16_t)a3 > (int16_t)(v10 + 6) )
                                    result[14] = v9[14];
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    else
    {
      do
      {
        v11 = *v4;
        ++result;
        ++v4;
        *(result - 1) = v11;
      }
      while ( result != (uint8_t *)(a1 + (uint16_t)(a3 - 1) + 1) );
    }
  }
  return result;
}

int32_t sub_1D00(uint8_t *a1, uint8_t *a2) {
  if (*a1 != *a2) { // compare 1st byte
    // Probably the case most of the time?
    return 1;
  }

  uint8_t *p1 = a1;
  uint8_t *p2 = a2;
  while (1) {
    ++p1;
    ++p2;
    if (p1 == &a1[8]) {
      return 0;
    }
    if (*p1 != *p2) {
      return 1;
    }
  }
}
