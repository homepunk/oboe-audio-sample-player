package com.itcraft.audiofrequencyfilter

/**Created by Homepunk on 15.01.2020. **/
class NativeLibBridge {
    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    external fun logToJNI(message: String)

    init {
        System.loadLibrary("native-lib")
    }
}