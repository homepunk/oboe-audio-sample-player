#include <jni.h>
#include <string>

#include "util/Logger.h"
#include "engine/AudioEngine.h"

static AudioEngine *audioEngine = new AudioEngine();

extern "C" JNIEXPORT void JNICALL
Java_com_itcraft_audiofrequencyfilter_bridge_NativeAudioEngineBridge_jniLoad(
        JNIEnv *env,
        jobjectArray internal_storage_paths_java) {
    int nbFilePaths = env->GetArrayLength(internal_storage_paths_java);
    const char **filePathsInput = (const char **) calloc((size_t) nbFilePaths, sizeof(char *));
    for (int i = 0; i < nbFilePaths; i++) {
        jstring input = (jstring) (env->GetObjectArrayElement(internal_storage_paths_java, i));
        filePathsInput[i] = env->GetStringUTFChars(input, 0);
    }
//    audioEngine->load(filePathsInput, nbFilePaths);
}

extern "C" JNIEXPORT void JNICALL
Java_com_itcraft_audiofrequencyfilter_bridge_NativeAudioEngineBridge_jniLoadAndPlay(
        JNIEnv *env,
        jobject /* this */,
        jstring internal_storage_path_java) {
    const char *pathUTF = env->GetStringUTFChars(internal_storage_path_java, 0);
    audioEngine->load(pathUTF);
}

extern "C" JNIEXPORT void JNICALL
Java_com_itcraft_audiofrequencyfilter_bridge_NativeAudioEngineBridge_jniPlay(
        JNIEnv *env,
        jobject /* this */,
        jint indexJava) {
    audioEngine->play();
}


