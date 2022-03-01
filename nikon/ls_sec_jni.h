#ifndef LS_SEC_JNI_H
#define LS_SEC_JNI_H

#include <jni.h>

extern "C" {

// LsSec:

int LsSecInit(void *, unsigned int);

int LsSec1stStage(void *, uint8_t *);

// JNI exports:

JNIEXPORT jint JNICALL
// com.nikon.LsSec.jniLsSec.init
Java_com_nikon_LsSec_jniLsSec_init(JNIEnv *, jobject, jint, jboolean);

JNIEXPORT jint JNICALL
// com.nikon.LsSec.jniLsSec.GenerateKey
Java_com_nikon_LsSec_jniLsSec_GenerateKey(JNIEnv *, jobject, jbyteArray,
                                          jbyteArray, jboolean);

JNIEXPORT jint JNICALL
// com.nikon.LsSec.jniLsSec.Stage1st
Java_com_nikon_LsSec_jniLsSec_Stage1st(JNIEnv *, jobject, jbyteArray array);

JNIEXPORT jint JNICALL
// com.nikon.LsSec.jniLsSec.Stage2nd
Java_com_nikon_LsSec_jniLsSec_Stage2nd(JNIEnv *, jobject, jbyteArray,
                                       jbyteArray, jbyteArray);

JNIEXPORT jint JNICALL
// com.nikon.LsSec.jniLsSec.Stage3rd
Java_com_nikon_LsSec_jniLsSec_Stage3rd(JNIEnv *, jobject, jbyteArray,
                                       jbyteArray, jbyteArray, jbyteArray);

JNIEXPORT jint JNICALL
// com.nikon.LsSec.jniLsSec.Stage4th
Java_com_nikon_LsSec_jniLsSec_Stage4th(JNIEnv *, jobject, jbyteArray,
                                       jbyteArray, jbyteArray);

JNIEXPORT jint JNICALL
// com.nikon.LsSec.jniLsSec.Encipher
Java_com_nikon_LsSec_jniLsSec_Encipher(JNIEnv *, jobject, jbyteArray,
                                       jbyteArray, jchar, jboolean);

JNIEXPORT jint JNICALL
// com.nikon.LsSec.jniLsSec.Decipher
Java_com_nikon_LsSec_jniLsSec_Decipher(JNIEnv *, jobject, jbyteArray,
                                       jbyteArray, jchar, jboolean);

JNIEXPORT jint JNICALL
// com.nikon.LsSec.jniLsSec.GetContextData
Java_com_nikon_LsSec_jniLsSec_GetContextData(JNIEnv *, jobject, jbyteArray,
                                             jbyteArray, jbyteArray, jbyteArray,
                                             jlongArray, jlongArray, jintArray,
                                             jboolean);

JNIEXPORT jint JNICALL
// com.nikon.LsSec.jniLsSec.SetContextData
Java_com_nikon_LsSec_jniLsSec_SetContextData(JNIEnv *, jobject, jbyteArray,
                                             jbyteArray, jbyteArray, jbyteArray,
                                             jlongArray, jlongArray, jint,
                                             jboolean);
}

#endif // LS_SEC_JNI_H
