package com.itcraft.audiofrequencyfilter

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import com.itcraft.audiofrequencyfilter.bridge.NativeAudioEngineBridge
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {
    private val jniBridge = NativeAudioEngineBridge()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // Example of a call to a native method
//        sample_text.text = jniBridge.stringFromJNI()
//        jniBridge.logToJNI("Hi from Android")

        jniBridge.loadFromAssets(this, "dpm_shape_of_you_a_melody_01.wav")

        btn_play.setOnClickListener {
            jniBridge.play(0)
        }
    }

}
