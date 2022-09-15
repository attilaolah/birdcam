// rand(), srand()
#include <stdlib.h>

#include "code/defs.h"

#define _OWORD __uint128_t

static _DWORD dword_9040;

void sub_A50()
{
    dword_9040 = 1;
}

__int64 __fastcall sub_1A40(_BYTE *a1, __int64 *a2)
{
  __int64 result; // rax

  result = *a2;
  a1[3] = *a2;
  *a1 = BYTE3(result);
  a1[1] = BYTE2(result);
  a1[2] = BYTE1(result);
  return result;
}

__int64 __fastcall LsSecInit(_BYTE *a1, __int64 a2)
{
  _OWORD *v2; // rax

  v2 = a1;
  do
    *v2++ = 0LL;
  while ( v2 != (_OWORD *)(a1 + 8400) );
  a1[8400] = 0;
  a1[8401] = 0;
  a1[8402] = 0;
  a1[8403] = 0;
  a1[8404] = 0;
  a1[8405] = 0;
  a1[8406] = 0;
  a1[8407] = 0;
  if ( a2 )
    srand(a2);
  sub_A50(0.0);
  *((_DWORD *)a1 + 2100) = 1;
  return 0LL;
}

__int64 __fastcall LsSec1stStage(__int64 a1, __int64 a2)
{
  __int64 result; // rax
  __int64 v3[4]; // [rsp+8h] [rbp-20h] BYREF

  result = 4294967193LL;
  v3[0] = 0LL;
  if ( *(_DWORD *)(a1 + 8400) == 1 )
  {
    v3[0] = rand();
    sub_1A40(a2, v3);
    v3[0] = rand();
    sub_1A40(a2 + 4, v3);
    *(_DWORD *)(a1 + 8400) = 3;
    return 0LL;
  }
  return result;
}
