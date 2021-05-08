#include <jni.h>;
#include <string>;
#include "Testing.h"


//extern "C" jint Java_com_example_ahc_MainActivity_stringTesting(JNIEnv* env,
//                                                                jobject);

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_ahc_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
//    int s=Java_com_example_ahc_MainActivity_stringTesting(JNIEnv* ,
//                                                          jobject);
    std::string hello = "Hello from C++";

    return env->NewStringUTF(hello.c_str());
}


//extern "C" JNIEXPORT jstring JNICALL
//Java_com_example_ahc_MainActivity_stringTesting(
//        JNIEnv* env,
//        jobject /* this */) {
//    std::string hello = "Success";
//    return env->NewStringUTF(hello.c_str());
//}

extern "C" JNIEXPORT jint JNICALL
Java_com_example_ahc_MainActivity_check(
        _JNIEnv* env,
        jobject /* this */) {
    int temp= Testing::Testing1();
    return temp;
}