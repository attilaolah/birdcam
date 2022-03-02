# JNI Functions

## `Java.com.nikon.LsSec.jniLsSec.init`

Original, as decompiled by IDA Free 7.7:

```c
__int64 __fastcall Java_com_nikon_LsSec_jniLsSec_init(__int64 a1, __int64 a2, int a3, char a4)
{
  if ( a4 == 1 )
    return LsSecInit(&unk_D280, a3);
  else
    return LsSecInit(&unk_B180, a3);
}
```

After setting types renaming symbols:

```c
#include <jni.h>

JNIEXPORT jint JNICALL
Java_com_nikon_LsSec_jniLsSec_init(
    JNIEnv *env, jobject thisobj,
    jint seed, jboolean z) {
  if (z == JNI_TRUE)
    return LsSecInit(&unk_D280, seed);
  else
    return LsSecInit(&unk_B180, seed);
}
```

## `com.nikon.LsSec.jniLsSec.GenerateKey`

Original, as decompiled by IDA Free 7.7:

```c
__int64 __fastcall Java_com_nikon_LsSec_jniLsSec_GenerateKey(__int64 a1, __int64 a2, __int64 a3, __int64 a4, char a5)
{
  __int64 v8; // r14
  __int64 v9; // r13
  unsigned int Key; // r15d
  char v12[57]; // [rsp+Fh] [rbp-39h] BYREF

  v8 = (*(__int64 (__fastcall **)(__int64, __int64, char *))(*(_QWORD *)a1 + 1472LL))(a1, a3, v12);
  v9 = (*(__int64 (__fastcall **)(__int64, __int64, char *))(*(_QWORD *)a1 + 1472LL))(a1, a4, v12);
  if ( a5 == 1 )
    Key = LsSecGenerateKey(&unk_D280, v8, v9);
  else
    Key = LsSecGenerateKey(&unk_B180, v8, v9);
  (*(void (__fastcall **)(__int64, __int64, __int64, _QWORD))(*(_QWORD *)a1 + 1536LL))(a1, a3, v8, 0LL);
  (*(void (__fastcall **)(__int64, __int64, __int64, _QWORD))(*(_QWORD *)a1 + 1536LL))(a1, a4, v9, 0LL);
  return Key;
}
```

After setting types renaming symbols:

```c
#include <jni.h>

JNIEXPORT jint JNICALL
Java_com_nikon_LsSec_jniLsSec_GenerateKey(
    JNIEnv *env, jobject thisobj,
    jbyteArray array_1, jbyteArray array_2, jboolean z) {
  jbyte *buf_1;
  jbyte *buf_2;
  jint result;
  jboolean *isCopy;

  buf_1 = (*env)->GetByteArrayElements(env, array_1, &isCopy);
  buf_2 = (*env)->GetByteArrayElements(env, array_2, &isCopy);
  if (z == JNI_TRUE)
    result = LsSecGenerateKey(&unk_D280, buf_1, buf_2);
  else
    result = LsSecGenerateKey(&unk_B180, buf_1, buf_2);
  (*env)->ReleaseByteArrayElements(env, array_1, buf_1, 0);
  (*env)->ReleaseByteArrayElements(env, array_2, buf_2, 0);
  return result;
}
```

## `Java.com.nikon.LsSec.jniLsSec.Stage1st`

Original, as decompiled by IDA Free 7.7:

```c
__int64 __fastcall Java_com_nikon_LsSec_jniLsSec_Stage1st(__int64 a1, __int64 a2, __int64 a3)
{
  __int64 v4; // r12
  unsigned int v5; // r13d
  char v7[41]; // [rsp+Fh] [rbp-29h] BYREF

  v4 = (*(__int64 (__fastcall **)(__int64, __int64, char *))(*(_QWORD *)a1 + 1472LL))(a1, a3, v7);
  v5 = LsSec1stStage(&unk_B180, v4);
  (*(void (__fastcall **)(__int64, __int64, __int64, _QWORD))(*(_QWORD *)a1 + 1536LL))(a1, a3, v4, 0LL);
  return v5;
}
```

After setting types renaming symbols:

```c
#include <jni.h>

JNIEXPORT jint JNICALL
Java_com_nikon_LsSec_jniLsSec_Stage1st(
    JNIEnv *env, jobject thisobj,
    jbyteArray array) {
  jbyte *buf;
  jint result;
  jboolean *isCopy;

  buf = (*env)->GetByteArrayElements(env, array, &isCopy);
  result = LsSec1stStage(&unk_B180, buf);
  (*env)->ReleaseByteArrayElements(env, array, buf, 0);
  return result;
}
```

## `Java.com.nikon.LsSec.jniLsSec.Stage2nd`

Original, as decompiled by IDA Free 7.7:

```c
__int64 __fastcall Java_com_nikon_LsSec_jniLsSec_Stage2nd(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5)
{
  __int64 v8; // r15
  __int64 v9; // r14
  __int64 v10; // rbp
  unsigned int v12; // [rsp+4h] [rbp-54h]
  char v14[57]; // [rsp+1Fh] [rbp-39h] BYREF

  v8 = (*(__int64 (__fastcall **)(__int64, __int64, char *))(*(_QWORD *)a1 + 1472LL))(a1, a3, v14);
  v9 = (*(__int64 (__fastcall **)(__int64, __int64, char *))(*(_QWORD *)a1 + 1472LL))(a1, a4, v14);
  v10 = (*(__int64 (__fastcall **)(__int64, __int64, char *))(*(_QWORD *)a1 + 1472LL))(a1, a5, v14);
  v12 = LsSec2ndStage(&unk_D280, v8, v9, v10);
  (*(void (__fastcall **)(__int64, __int64, __int64, _QWORD))(*(_QWORD *)a1 + 1536LL))(a1, a3, v8, 0LL);
  (*(void (__fastcall **)(__int64, __int64, __int64, _QWORD))(*(_QWORD *)a1 + 1536LL))(a1, a4, v9, 0LL);
  (*(void (__fastcall **)(__int64, __int64, __int64, _QWORD))(*(_QWORD *)a1 + 1536LL))(a1, a5, v10, 0LL);
  return v12;
}
```

After setting types renaming symbols:

```c
#include <jni.h>

JNIEXPORT jint JNICALL
Java_com_nikon_LsSec_jniLsSec_Stage2nd(
    JNIEnv *env, jobject thisobj,
    jbyteArray array_1, jbyteArray array_2, jbyteArray array_3) {
  jbyte *buf_1;
  jbyte *buf_2;
  jbyte *buf_3;
  jint result;
  jboolean *isCopy;

  buf_1 = (*env)->GetByteArrayElements(env, array_1, &isCopy);
  buf_2 = (*env)->GetByteArrayElements(env, array_2, &isCopy);
  buf_3 = (*env)->GetByteArrayElements(env, array_3, &isCopy);
  result = LsSec2ndStage(&unk_D280, buf_1, buf_2, buf_3);
  (*env)->ReleaseByteArrayElements(env, array_1, buf_1, 0);
  (*env)->ReleaseByteArrayElements(env, array_2, buf_2, 0);
  (*env)->ReleaseByteArrayElements(env, array_3, buf_3, 0);
  return result;
}
```

## `Java.com.nikon.LsSec.jniLsSec.Stage3rd`

Original, as decompiled by IDA Free 7.7:

```c
__int64 __fastcall Java_com_nikon_LsSec_jniLsSec_Stage3rd(
        __int64 a1,
        __int64 a2,
        __int64 a3,
        __int64 a4,
        __int64 a5,
        __int64 a6)
{
  __int64 v9; // r15
  __int64 v10; // r14
  __int64 v11; // r12
  __int64 v12; // rbx
  __int64 v15; // [rsp+8h] [rbp-60h]
  unsigned int v16; // [rsp+14h] [rbp-54h]
  char v18[57]; // [rsp+2Fh] [rbp-39h] BYREF

  v9 = (*(__int64 (__fastcall **)(__int64, __int64, char *))(*(_QWORD *)a1 + 1472LL))(a1, a3, v18);
  v15 = a5;
  v10 = (*(__int64 (__fastcall **)(__int64, __int64, char *))(*(_QWORD *)a1 + 1472LL))(a1, a4, v18);
  v11 = (*(__int64 (__fastcall **)(__int64, __int64, char *))(*(_QWORD *)a1 + 1472LL))(a1, a5, v18);
  v12 = (*(__int64 (__fastcall **)(__int64, __int64, char *))(*(_QWORD *)a1 + 1472LL))(a1, a6, v18);
  v16 = LsSec3rdStage(&unk_B180, v9, v10, v11, v12);
  (*(void (__fastcall **)(__int64, __int64, __int64, _QWORD))(*(_QWORD *)a1 + 1536LL))(a1, a3, v9, 0LL);
  (*(void (__fastcall **)(__int64, __int64, __int64, _QWORD))(*(_QWORD *)a1 + 1536LL))(a1, a4, v10, 0LL);
  (*(void (__fastcall **)(__int64, __int64, __int64, _QWORD))(*(_QWORD *)a1 + 1536LL))(a1, v15, v11, 0LL);
  (*(void (__fastcall **)(__int64, __int64, __int64, _QWORD))(*(_QWORD *)a1 + 1536LL))(a1, a6, v12, 0LL);
  return v16;
}
```

After setting types renaming symbols:

```c
#include <jni.h>

JNIEXPORT jint JNICALL
Java_com_nikon_LsSec_jniLsSec_Stage3rd(
    JNIEnv *env, jobject thisobj,
    jbyteArray array_1, jbyteArray array_2, jbyteArray array_3, jbyteArray array_4) {
  jbyte *buf_1;
  jbyte *buf_2;
  jbyte *buf_3;
  jbyte *buf_4;
  jbyteArray tmp;
  jint result;
  jboolean *isCopy;

  buf_1 = (*env)->GetByteArrayElements(env, array_1, &isCopy);
  tmp = array_3;
  buf_2 = (*env)->GetByteArrayElements(env, array_2, &isCopy);
  buf_3 = (*env)->GetByteArrayElements(env, array_3, &isCopy);
  buf_4 = (*env)->GetByteArrayElements(env, array_4, &isCopy);
  result = LsSec3rdStage(&unk_B180, buf_1, buf_2, buf_3, buf_4);
  (*env)->ReleaseByteArrayElements(env, array_1, buf_1, 0);
  (*env)->ReleaseByteArrayElements(env, array_2, buf_2, 0);
  (*env)->ReleaseByteArrayElements(env, tmp, buf_3, 0);
  (*env)->ReleaseByteArrayElements(env, array_4, buf_4, 0);
  return result;
}
```

## `Java.com.nikon.LsSec.jniLsSec.Stage4th`

Original, as decompiled by IDA Free 7.7:

```c
_int64 __fastcall Java_com_nikon_LsSec_jniLsSec_Stage4th(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5)
{
  __int64 v8; // r15
  __int64 v9; // r14
  __int64 v10; // rbp
  unsigned int v12; // [rsp+4h] [rbp-54h]
  char v14[57]; // [rsp+1Fh] [rbp-39h] BYREF

  v8 = (*(__int64 (__fastcall **)(__int64, __int64, char *))(*(_QWORD *)a1 + 1472LL))(a1, a3, v14);
  v9 = (*(__int64 (__fastcall **)(__int64, __int64, char *))(*(_QWORD *)a1 + 1472LL))(a1, a4, v14);
  v10 = (*(__int64 (__fastcall **)(__int64, __int64, char *))(*(_QWORD *)a1 + 1472LL))(a1, a5, v14);
  v12 = LsSec4thStage(&unk_D280, v8, v9, v10);
  (*(void (__fastcall **)(__int64, __int64, __int64, _QWORD))(*(_QWORD *)a1 + 1536LL))(a1, a3, v8, 0LL);
  (*(void (__fastcall **)(__int64, __int64, __int64, _QWORD))(*(_QWORD *)a1 + 1536LL))(a1, a4, v9, 0LL);
  (*(void (__fastcall **)(__int64, __int64, __int64, _QWORD))(*(_QWORD *)a1 + 1536LL))(a1, a5, v10, 0LL);
  return v12;
}
```

After setting types renaming symbols:

```c
#include <jni.h>

JNIEXPORT jint JNICALL
Java_com_nikon_LsSec_jniLsSec_Stage4th(
    JNIEnv *env, jobject thisobj,
    jbyteArray array_1, jbyteArray array_2, jbyteArray array_3) {
  jbyte *buf_1;
  jbyte *buf_2;
  jbyte *buf_3;
  jint result;
  jboolean *isCopy;

  buf_1 = (*env)->GetByteArrayElements(env, array_1, &isCopy);
  buf_2 = (*env)->GetByteArrayElements(env, array_2, &isCopy);
  buf_3 = (*env)->GetByteArrayElements(env, array_3, &isCopy);
  result = LsSec4thStage(&unk_D280, buf_1, buf_2, buf_3);
  (*env)->ReleaseByteArrayElements(env, array_1, buf_1, 0);
  (*env)->ReleaseByteArrayElements(env, array_2, buf_2, 0);
  (*env)->ReleaseByteArrayElements(env, array_3, buf_3, 0);
  return result;
}
```

## `com.nikon.LsSec.jniLsSec.Encipher`

Original, as decompiled by IDA Free 7.7:

```c
__int64 __fastcall Java_com_nikon_LsSec_jniLsSec_Encipher(
        __int64 a1,
        __int64 a2,
        __int64 a3,
        __int64 a4,
        unsigned __int16 a5,
        char a6)
{
  __int64 v9; // r15
  __int64 v10; // rax
  __int64 v11; // r14
  unsigned int v12; // ebp
  char v15[57]; // [rsp+1Fh] [rbp-39h] BYREF

  v9 = (*(__int64 (__fastcall **)(__int64, __int64, char *))(*(_QWORD *)a1 + 1472LL))(a1, a3, v15);
  v10 = (*(__int64 (__fastcall **)(__int64, __int64, char *))(*(_QWORD *)a1 + 1472LL))(a1, a4, v15);
  v11 = v10;
  if ( a6 == 1 )
    v12 = LsSecEncipher(&unk_D280, v9, v10, a5);
  else
    v12 = LsSecEncipher(&unk_B180, v9, v10, a5);
  (*(void (__fastcall **)(__int64, __int64, __int64, _QWORD))(*(_QWORD *)a1 + 1536LL))(a1, a3, v9, 0LL);
  (*(void (__fastcall **)(__int64, __int64, __int64, _QWORD))(*(_QWORD *)a1 + 1536LL))(a1, a4, v11, 0LL);
  return v12;
}
```

After setting types renaming symbols:

```c
#include <jni.h>

JNIEXPORT jint JNICALL
Java_com_nikon_LsSec_jniLsSec_Encipher(
    JNIEnv *env, jobject thisobj,
    jbyteArray array_1, jbyteArray array_2, jchar c, jboolean z) {
  jbyte *buf_1;
  jbyte *buf_2;
  jbyte *tmp;
  jint result;
  jboolean *isCopy;

  buf_1 = (*env)->GetByteArrayElements(env, array_1, &isCopy);
  buf_2 = (*env)->GetByteArrayElements(env, array_2, &isCopy);
  tmp = buf_2;
  if (z == JNI_TRUE)
    result = LsSecEncipher(&unk_D280, buf_1, buf_2, c);
  else
    result = LsSecEncipher(&unk_B180, buf_1, buf_2, c);
  (*env)->ReleaseByteArrayElements(env, array_1, buf_1, 0LL);
  (*env)->ReleaseByteArrayElements(env, array_2, tmp, 0LL);
  return result;
}
```

## `Java.com.nikon.LsSec.jniLsSec.Decipher`

Original, as decompiled by IDA Free 7.7:

```c
__int64 __fastcall Java_com_nikon_LsSec_jniLsSec_Decipher(
        __int64 a1,
        __int64 a2,
        __int64 a3,
        __int64 a4,
        unsigned __int16 a5,
        char a6)
{
  __int64 v9; // r15
  __int64 v10; // rax
  __int64 v11; // r14
  unsigned int v12; // ebp
  char v15[57]; // [rsp+1Fh] [rbp-39h] BYREF

  v9 = (*(__int64 (__fastcall **)(__int64, __int64, char *))(*(_QWORD *)a1 + 1472LL))(a1, a3, v15);
  v10 = (*(__int64 (__fastcall **)(__int64, __int64, char *))(*(_QWORD *)a1 + 1472LL))(a1, a4, v15);
  v11 = v10;
  if ( a6 == 1 )
    v12 = LsSecDecipher(&unk_D280, v9, v10, a5);
  else
    v12 = LsSecDecipher(&unk_B180, v9, v10, a5);
  (*(void (__fastcall **)(__int64, __int64, __int64, _QWORD))(*(_QWORD *)a1 + 1536LL))(a1, a3, v9, 0LL);
  (*(void (__fastcall **)(__int64, __int64, __int64, _QWORD))(*(_QWORD *)a1 + 1536LL))(a1, a4, v11, 0LL);
  return v12;
}
```

After setting types renaming symbols:

```c
#include <jni.h>

JNIEXPORT jint JNICALL
Java_com_nikon_LsSec_jniLsSec_Decipher(
    JNIEnv *env, jobject thisobj,
    jbyteArray array_1, jbyteArray array_2, jchar c, jboolean z) {
  jbyte *buf_1;
  jbyte *buf_2;
  jbyte *tmp;
  jint result;
  jboolean *isCopy;

  buf_1 = (*env)->GetByteArrayElements(env, array_1, &isCopy);
  buf_2 = (*env)->GetByteArrayElements(env, array_2, &isCopy);
  tmp = buf_2;
  if (z == JNI_TRUE)
    result = LsSecDecipher(&unk_D280, buf_1, buf_2, c);
  else
    result = LsSecDecipher(&unk_B180, buf_1, buf_2, c);
  (*env)->ReleaseByteArrayElements(env, array_1, buf_1, 0LL);
  (*env)->ReleaseByteArrayElements(env, array_2, tmp, 0LL);
  return result;
}
```

## `Java.com.nikon.LsSec.jniLsSec.GetContextData`

Original, as decompiled by IDA Free 7.7:

```c
__int64 __fastcall Java_com_nikon_LsSec_jniLsSec_GetContextData(
        __int64 a1,
        __int64 a2,
        __int64 a3,
        __int64 a4,
        __int64 a5,
        __int64 a6,
        __int64 a7,
        __int64 a8,
        __int64 a9,
        char a10)
{
  __int64 v14; // r13
  __int64 v15; // rax
  __int64 v16; // rbx
  unsigned int v17; // r15d
  __int64 v19; // [rsp+18h] [rbp-80h]
  __int64 v20; // [rsp+20h] [rbp-78h]
  __int64 v21; // [rsp+28h] [rbp-70h]
  __int64 v22; // [rsp+30h] [rbp-68h]
  __int64 v23; // [rsp+38h] [rbp-60h]
  char v26[57]; // [rsp+5Fh] [rbp-39h] BYREF

  v19 = (*(__int64 (__fastcall **)(__int64, __int64, char *))(*(_QWORD *)a1 + 1472LL))(a1, a3, v26);
  v20 = (*(__int64 (__fastcall **)(__int64, __int64, char *))(*(_QWORD *)a1 + 1472LL))(a1, a4, v26);
  v21 = (*(__int64 (__fastcall **)(__int64, __int64, char *))(*(_QWORD *)a1 + 1472LL))(a1, a5, v26);
  v22 = (*(__int64 (__fastcall **)(__int64, __int64, char *))(*(_QWORD *)a1 + 1472LL))(a1, a6, v26);
  v23 = (*(__int64 (__fastcall **)(__int64, __int64, char *))(*(_QWORD *)a1 + 1504LL))(a1, a7, v26);
  v14 = (*(__int64 (__fastcall **)(__int64, __int64, char *))(*(_QWORD *)a1 + 1504LL))(a1, a8, v26);
  v15 = (*(__int64 (__fastcall **)(__int64, __int64, char *))(*(_QWORD *)a1 + 1496LL))(a1, a9, v26);
  v16 = v15;
  if ( a10 == 1 )
    v17 = sub_1E20((unsigned int)&unk_D280, v19, v20, v21, v22, v23, v14, v15);
  else
    v17 = sub_1E20((unsigned int)&unk_B180, v19, v20, v21, v22, v23, v14, v15);
  (*(void (__fastcall **)(__int64, __int64, __int64, _QWORD))(*(_QWORD *)a1 + 1536LL))(a1, a3, v19, 0LL);
  (*(void (__fastcall **)(__int64, __int64, __int64, _QWORD))(*(_QWORD *)a1 + 1536LL))(a1, a4, v20, 0LL);
  (*(void (__fastcall **)(__int64, __int64, __int64, _QWORD))(*(_QWORD *)a1 + 1536LL))(a1, a5, v21, 0LL);
  (*(void (__fastcall **)(__int64, __int64, __int64, _QWORD))(*(_QWORD *)a1 + 1536LL))(a1, a6, v22, 0LL);
  (*(void (__fastcall **)(__int64, __int64, __int64, _QWORD))(*(_QWORD *)a1 + 1568LL))(a1, a7, v23, 0LL);
  (*(void (__fastcall **)(__int64, __int64, __int64, _QWORD))(*(_QWORD *)a1 + 1568LL))(a1, a8, v14, 0LL);
  (*(void (__fastcall **)(__int64, __int64, __int64, _QWORD))(*(_QWORD *)a1 + 1560LL))(a1, a9, v16, 0LL);
  return v17;
}
```

```c
#include <jni.h>

JNIEXPORT jint JNICALL
Java_com_nikon_LsSec_jniLsSec_GetContextData(
    JNIEnv *env, jobject thisobj,
    jbyteArray barray_1, jbyteArray barray_2, jbyteArray barray_3, jbyteArray barray_4, jlongArray larray_1, jlongArray larray_2, jintArray iarray_1, jboolean z) {
  jlong *lbuf_2;
  jint *ibuf;
  jint *tmp;
  jint result;
  jbyte *bbuf_1;
  jbyte *bbuf_2;
  jbyte *bbuf_3;
  jbyte *bbuf_4;
  jlong *lbuf_1;
  jboolean *isRopy;

  bbuf_1 = (*env)->GetByteArrayElements(env, barray_1, &isRopy);
  bbuf_2 = (*env)->GetByteArrayElements(env, barray_2, &isRopy);
  bbuf_3 = (*env)->GetByteArrayElements(env, barray_3, &isRopy);
  bbuf_4 = (*env)->GetByteArrayElements(env, barray_4, &isRopy);
  lbuf_1 = (*env)->GetLongArrayElements(env, larray_1, &isRopy);
  lbuf_2 = (*env)->GetLongArrayElements(env, larray_2, &isRopy);
  ibuf = (*env)->GetIntArrayElements(env, iarray_1, &isRopy);
  tmp = ibuf;
  if (z == JNI_TRUE)
    result = sub_1E20(
               (unsigned int)&unk_D280,
               (_DWORD)bbuf_1,
               (_DWORD)bbuf_2,
               (_DWORD)bbuf_3,
               (_DWORD)bbuf_4,
               (_DWORD)lbuf_1,
               (__int64)lbuf_2,
               (__int64)ibuf);
  else
    result = sub_1E20(
               (unsigned int)&unk_B180,
               (_DWORD)bbuf_1,
               (_DWORD)bbuf_2,
               (_DWORD)bbuf_3,
               (_DWORD)bbuf_4,
               (_DWORD)lbuf_1,
               (__int64)lbuf_2,
               (__int64)ibuf);
  (*env)->ReleaseByteArrayElements(env, barray_1, bbuf_1, 0);
  (*env)->ReleaseByteArrayElements(env, barray_2, bbuf_2, 0);
  (*env)->ReleaseByteArrayElements(env, barray_3, bbuf_3, 0);
  (*env)->ReleaseByteArrayElements(env, barray_4, bbuf_4, 0);
  (*env)->ReleaseLongArrayElements(env, larray_1, lbuf_1, 0);
  (*env)->ReleaseLongArrayElements(env, larray_2, lbuf_2, 0);
  (*env)->ReleaseIntArrayElements(env, iarray_1, tmp, 0);
  return result;
}
```

## `Java.com.nikon.LsSec.jniLsSec.SetContextData`

Original, as decompiled by IDA Free 7.7:

```c
__int64 __fastcall Java_com_nikon_LsSec_jniLsSec_SetContextData(
        __int64 a1,
        __int64 a2,
        __int64 a3,
        __int64 a4,
        __int64 a5,
        __int64 a6,
        __int64 a7,
        __int64 a8,
        int a9,
        char a10)
{
  __int64 v14; // rax
  __int64 v15; // rbx
  unsigned int v16; // r15d
  __int64 v18; // [rsp+10h] [rbp-78h]
  __int64 v19; // [rsp+18h] [rbp-70h]
  __int64 v20; // [rsp+20h] [rbp-68h]
  __int64 v21; // [rsp+28h] [rbp-60h]
  __int64 v22; // [rsp+30h] [rbp-58h]
  char v24[57]; // [rsp+4Fh] [rbp-39h] BYREF

  v18 = (*(__int64 (__fastcall **)(__int64, __int64, char *))(*(_QWORD *)a1 + 1472LL))(a1, a3, v24);
  v19 = (*(__int64 (__fastcall **)(__int64, __int64, char *))(*(_QWORD *)a1 + 1472LL))(a1, a4, v24);
  v20 = (*(__int64 (__fastcall **)(__int64, __int64, char *))(*(_QWORD *)a1 + 1472LL))(a1, a5, v24);
  v21 = (*(__int64 (__fastcall **)(__int64, __int64, char *))(*(_QWORD *)a1 + 1472LL))(a1, a6, v24);
  v22 = (*(__int64 (__fastcall **)(__int64, __int64, char *))(*(_QWORD *)a1 + 1504LL))(a1, a7, v24);
  v14 = (*(__int64 (__fastcall **)(__int64, __int64, char *))(*(_QWORD *)a1 + 1504LL))(a1, a8, v24);
  v15 = v14;
  if ( a10 == 1 )
    v16 = sub_1F60((unsigned int)&unk_D280, v18, v19, v20, v21, v22, v14, a9);
  else
    v16 = sub_1F60((unsigned int)&unk_B180, v18, v19, v20, v21, v22, v14, a9);
  (*(void (__fastcall **)(__int64, __int64, __int64, _QWORD))(*(_QWORD *)a1 + 1536LL))(a1, a3, v18, 0LL);
  (*(void (__fastcall **)(__int64, __int64, __int64, _QWORD))(*(_QWORD *)a1 + 1536LL))(a1, a4, v19, 0LL);
  (*(void (__fastcall **)(__int64, __int64, __int64, _QWORD))(*(_QWORD *)a1 + 1536LL))(a1, a5, v20, 0LL);
  (*(void (__fastcall **)(__int64, __int64, __int64, _QWORD))(*(_QWORD *)a1 + 1536LL))(a1, a6, v21, 0LL);
  (*(void (__fastcall **)(__int64, __int64, __int64, _QWORD))(*(_QWORD *)a1 + 1568LL))(a1, a7, v22, 0LL);
  (*(void (__fastcall **)(__int64, __int64, __int64, _QWORD))(*(_QWORD *)a1 + 1568LL))(a1, a8, v15, 0LL);
  return v16;
}
```

After setting types renaming symbols:

```c
#include <jni.h>

JNIEXPORT jint JNICALL
Java_com_nikon_LsSec_jniLsSec_SetContextData(
    JNIEnv *env, jobject thisobj,
    jbyteArray barray_1, jbyteArray barray_2, jbyteArray barray_3, jbyteArray barray_4, jlongArray larray_1, jlongArray larray_2, jint i, jboolean z) {
  jlong *lbuf_2;
  jlong *tmp;
  jint result;
  jbyte *bbuf_1;
  jbyte *bbuf_2;
  jbyte *bbuf_3;
  jbyte *bbuf_4;
  jlong *lbuf_1;
  jboolean *isCopy;

  bbuf_1 = (*env)->GetByteArrayElements(env, barray_1, &isCopy);
  bbuf_2 = (*env)->GetByteArrayElements(env, barray_2, &isCopy);
  bbuf_3 = (*env)->GetByteArrayElements(env, barray_3, &isCopy);
  bbuf_4 = (*env)->GetByteArrayElements(env, barray_4, &isCopy);
  lbuf_1 = (*env)->GetLongArrayElements(env, larray_1, &isCopy);
  lbuf_2 = (*env)->GetLongArrayElements(env, larray_2, &isCopy);
  tmp = lbuf_2;
  if (z == JNI_TRUE)
    result = sub_1F60(
               (unsigned int)&unk_D280,
               (_DWORD)bbuf_1,
               (_DWORD)bbuf_2,
               (_DWORD)bbuf_3,
               (_DWORD)bbuf_4,
               (_DWORD)lbuf_1,
               (__int64)lbuf_2,
               i);
  else
    result = sub_1F60(
               (unsigned int)&unk_B180,
               (_DWORD)bbuf_1,
               (_DWORD)bbuf_2,
               (_DWORD)bbuf_3,
               (_DWORD)bbuf_4,
               (_DWORD)lbuf_1,
               (__int64)lbuf_2,
               i);
  (*env)->ReleaseByteArrayElements(env, barray_1, bbuf_1, 0);
  (*env)->ReleaseByteArrayElements(env, barray_2, bbuf_2, 0);
  (*env)->ReleaseByteArrayElements(env, barray_3, bbuf_3, 0);
  (*env)->ReleaseByteArrayElements(env, barray_4, bbuf_4, 0);
  (*env)->ReleaseLongArrayElements(env, larray_1, lbuf_1, 0);
  (*env)->ReleaseLongArrayElements(env, larray_2, tmp, 0);
  return result;
}
```
