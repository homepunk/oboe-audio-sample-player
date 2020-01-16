#include <jni.h>
#include <string>

#include "util/Logger.h"

Logger *temp = new Logger();

extern "C" JNIEXPORT jstring JNICALL
Java_com_itcraft_audiofrequencyfilter_NativeLibBridge_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    temp->d_log(hello);
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT void JNICALL
Java_com_itcraft_audiofrequencyfilter_NativeLibBridge_logToJNI(
        JNIEnv *env,
        jobject /* this */,
        jstring message) {
    const char *messageUTF = env->GetStringUTFChars(message, 0);
    temp->e_log(messageUTF);
}


