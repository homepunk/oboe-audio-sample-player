package com.itcraft.audiofrequencyfilter.bridge

import android.content.Context
import com.itcraft.audiofrequencyfilter.util.SampleLoaderUtil

/**Created by Homepunk on 15.01.2020. **/
class NativeAudioEngineBridge {
    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    external fun logToJNI(message: String)

    private external fun jniLoad(filePaths: List<String>)

    private external fun jniPlay(id: Int)

    private var filePaths = ArrayList<String>()

    fun loadFromAssets(context: Context, assetsFilePaths: List<String>) {
        SampleLoaderUtil.copyAssetsToInternalStorage(context, assetsFilePaths)
            .let {
                filePaths = it
                jniLoad(it)
            }
    }

    fun loadFromFiles(filePaths: List<String>) {
        jniLoad(filePaths)
    }

    fun play(id: Int) {
        jniPlay(id)
    }

    fun play(path: String) {
        jniPlay(extractId(path))
    }

    private fun extractId(assetsFilePath: String): Int {
        for (i in 0 until filePaths.count()) {
            if (filePaths[i] == assetsFilePath) {
                return i
            }
        }
        throw IllegalStateException("Error, not found path: $assetsFilePath")
    }
    init {
        System.loadLibrary("native-lib")
    }
}