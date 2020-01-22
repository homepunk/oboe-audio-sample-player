package com.itcraft.audiofrequencyfilter.bridge

import android.content.Context
import android.media.AudioFormat.CHANNEL_OUT_MONO
import android.media.MediaExtractor
import android.util.Log
import com.itcraft.audiofrequencyfilter.util.SampleLoaderUtil

class NativeAudioEngineBridge {
    private external fun jniLoadAndPlay(filePath: String)

    private external fun jniLoad(filePaths: List<String>)

    private external fun jniPlay(id: Int)

    private var filePath = ""
    private var filePaths = ArrayList<String>()

    fun loadFromAssets(context: Context, assetsFilePaths: List<String>) {
        SampleLoaderUtil.copyAssetsToInternalStorage(context, assetsFilePaths)
            .let {
                filePaths = it
                jniLoad(it)
            }
    }

    fun loadFromAssets(context: Context, assetsFilePath: String) {
        SampleLoaderUtil.copyAssetToInternalStorage(context, assetsFilePath)
            .let {
                filePath = it
                logAudioFileInfo(it)
                jniLoadAndPlay(it)
            }
    }

    fun logAudioFileInfo(path: String) {
        val ex = MediaExtractor()
        ex.setDataSource(path)

        CHANNEL_OUT_MONO
        Log.w(this.javaClass.canonicalName, "Audio File $path has ${ex.trackCount} tracks:  ")
        for (i: Int in 0 until ex.trackCount) {
            Log.w(this.javaClass.canonicalName, "Track: $i INFO ${ex.getTrackFormat(i)}")
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