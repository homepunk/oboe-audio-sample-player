package com.itcraft.audiofrequencyfilter.util

import android.content.Context
import java.io.*

/**Created by Homepunk on 16.01.2020. **/
object SampleLoaderUtil {
    /**
     * Returns the list of internal storage paths.
     */
    fun copyAssetsToInternalStorage(
        context: Context,
        assetsFilePaths: List<String>
    ): ArrayList<String> {
        val assetManager = context.applicationContext.assets
        val internalStorageFilesDirAbsolutePath = context.filesDir.absolutePath
        val result = ArrayList<String>()

        for (assetsFilePath in assetsFilePaths) {
            var inputStream: InputStream? = null
            var outputStream: OutputStream? = null
            try {
                val outFile = File(internalStorageFilesDirAbsolutePath, assetsFilePath)
                result.add(outFile.absolutePath)
                if (!outFile.exists()) {
                    val file = File(outFile.absolutePath).parentFile
                    if (!file.exists()) {
                        file.mkdirs()
                    }
                    inputStream = assetManager.open(assetsFilePath)
                    outputStream = FileOutputStream(outFile)
                    copyFile(inputStream, outputStream)
                }
            } catch (e: IOException) {
                throw IllegalStateException("Failed to copy asset file: $assetsFilePath", e)
            } finally {
                try {
                    inputStream?.close()
                } catch (e: IOException) {
                    e.printStackTrace()
                }
                try {
                    outputStream?.close()
                } catch (e: IOException) {
                    e.printStackTrace()
                }
            }
        }
        return result
    }
    /**
     * Returns the list of internal storage paths.
     */
    fun copyAssetToInternalStorage(
        context: Context,
        assetsFilePath: String): String {
        val assetManager = context.applicationContext.assets
        val internalStorageFilesDirAbsolutePath = context.filesDir.absolutePath
        var result: String

        var inputStream: InputStream? = null
            var outputStream: OutputStream? = null
            try {
                val outFile = File(internalStorageFilesDirAbsolutePath, assetsFilePath)
                result = outFile.absolutePath
                if (!outFile.exists()) {
                    val file = File(outFile.absolutePath).parentFile
                    if (!file.exists()) {
                        file.mkdirs()
                    }
                    inputStream = assetManager.open(assetsFilePath)
                    outputStream = FileOutputStream(outFile)
                    copyFile(inputStream, outputStream)
                }
            } catch (e: IOException) {
                throw IllegalStateException("Failed to copy asset file: $assetsFilePath", e)
            } finally {
                try {
                    inputStream?.close()
                } catch (e: IOException) {
                    e.printStackTrace()
                }
                try {
                    outputStream?.close()
                } catch (e: IOException) {
                    e.printStackTrace()
                }
            }
        return result
    }

    private fun copyFile(inputStream: InputStream, out: OutputStream) {
        val buffer = ByteArray(1024)
        while (true) {
            val bytesRead = inputStream.read(buffer)
            if (bytesRead == -1) {
                break
            }
            out.write(buffer, 0, bytesRead)
        }
    }

}