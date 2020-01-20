#include <jni.h>
#include <string>

#include "util/Logger.h"
#include "engine/AudioEngine.h"

Logger *temp = new Logger();
static AudioEngine *audioEngine = new AudioEngine();

extern "C" JNIEXPORT jstring JNICALL
Java_com_itcraft_audiofrequencyfilter_NativeAudioEngineBridge_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    temp->d_log(hello);
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT void JNICALL
Java_com_itcraft_audiofrequencyfilter_NativeAudioEngineBridge_logToJNI(
        JNIEnv *env,
        jobject /* this */,
        jstring message) {
    const char *messageUTF = env->GetStringUTFChars(message, 0);
    temp->e_log(messageUTF);
}

extern "C" JNIEXPORT void JNICALL
Java_com_itcraft_audiofrequencyfilter_NativeAudioEngineBridge_jniLoad(
        JNIEnv *env,
        jobject /* this */,
        jobjectArray internal_storage_paths_java) {
    int nbFilePaths = env->GetArrayLength(internal_storage_paths_java);
    const char **filePathsInput = (const char **) calloc((size_t) nbFilePaths, sizeof(char *));
    for (int i = 0; i < nbFilePaths; i++) {
        jstring input = (jstring) (env->GetObjectArrayElement(internal_storage_paths_java, i));
        filePathsInput[i] = env->GetStringUTFChars(input, 0);
    }
    audioEngine->lo(filePathsInput, nbFilePaths);
}

extern "C" JNIEXPORT void JNICALL
Java_com_itcraft_audiofrequencyfilter_NativeAudioEngineBridge_jniPlay(
        JNIEnv *env,
        jobject /* this */,
        jint indexJava) {
    const char *messageUTF = env->GetStringUTFChars(message, 0);
    temp->e_log(messageUTF);
}


