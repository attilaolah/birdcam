# LsSec Functions

## `LsSecInit`

```c
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
```

```c
#include <stdint.h>
#include <string.h>

static uint32_t dword_9040;

void sub_A50() {
  dword_9040 = 1;
}

int LsSecInit(uint32_t *buf, int64_t seed) {
  memset(buf, 0, 8408);
  if (seed) {
    srand(seed);
  }
  sub_A50();
  buf[2100] = 1;
  return 0;
}
```

## `LsSec1stStage`

```c
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
```

```c
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
```

```c
void sub_1A40(uint8_t *a, uint64_t *b) {
  uint64_t tmp; // rax

  tmp = *b;
  a[3] = *b;
  *a = BYTE3(tmp);
  a[1] = BYTE2(tmp);
  a[2] = BYTE1(tmp);
}
```

```c
int LsSec1stStage(uint32_t *data, uint8_t *buf) {
  if (data[2100] != 1) {
    return -103;
  }

  sub_1A40(buf, rand());
  sub_1A40(buf + 4, rand());
  data[2100] = 3;
  return 0;
}
```

## `LsSec3rdStage`

```c
__int64 __fastcall LsSec3rdStage(__int64 a1, __int64 a2, __int64 a3, __int64 a4, uint8_t *a5)
{
  __int64 result; // rax
  __int16 v6; // r14
  char *v9; // r15

  result = 4294967193LL;
  if ( *(_DWORD *)(a1 + 8400) == 3 )
  {
    v6 = 0;
    sub_1A80(a1 + 32, a2, 8LL);
    sub_1A80(a1 + 40, a3, 8LL);
    v9 = (char *)&unk_4AC0;
    sub_1A80(a1, a2, 4LL);
    sub_1A80(a1 + 4, a3, 4LL);
    while ( 1 )
    {
      sub_1A80(a1 + 24, v9, 8LL);
      sub_A80(a1 + 24, (uint8_t *)(a1 + 8), 0x18u);
      if ( !(unsigned int)sub_1C20(a1 + 8, a4, 8LL) )
        break;
      ++v6;
      v9 += 8;
      if ( v6 == 8 )
        return 4294967194LL;
    }
    *(_BYTE *)a1 = v6;
    sub_1A80(a1 + 32, a3, 8LL);
    sub_1A80(a1 + 40, a2, 8LL);
    sub_A80(a1 + 24, a5, 0x18u);
    *(_DWORD *)(a1 + 8400) = 5;
    return 0LL;
  }
  return result;
}
```

```c
int LsSec3rdStage(uint32_t *data, __int64 buf_1, __int64 buf_2, __int64 buf_3, uint8_t *buf_4) {
  if (data[2100] != 3) {
    return -103;
  }

  memcpy(data+8, buf_1, 8);
  memcpy(data+10, buf_2, 8);
  memcpy(data, buf_1, 4);
  memcpy(data+1, buf_2, 4);

  int16_t i = 0;
  for (i = 0; i < 8; ++i) {
	memcpy(data+6, (&byte_4AC0)+(i*8), 8);
	sub_A80((int16_t)(data + 6), (uint8_t *)data + 8, 0x18u);
	if (!memcmp(data + 2, buf_3, 8)) {
	  break;
	}
  }
  if (i == 8) {
	return -102;
  }
  *(uint8_t *)data = i;
  memcpy(data+8, buf_2, 8);
  memcpy(data+10, buf_1, 8);
  sub_A80((int16_t)(data + 6), buf_4, 0x18u);
  data[2100] = 5;
  return 0;
}
```
