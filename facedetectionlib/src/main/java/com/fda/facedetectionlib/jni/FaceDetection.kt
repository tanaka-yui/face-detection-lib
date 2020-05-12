package com.fda.facedetectionlib.jni

import android.graphics.Bitmap

class FaceDetection {
    companion object {
        init {
            System.loadLibrary("face-detection-lib")
        }
    }

    external fun detect(bitmap: Bitmap): String
}