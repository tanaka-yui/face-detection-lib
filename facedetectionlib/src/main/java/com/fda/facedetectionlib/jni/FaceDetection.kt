package com.fda.facedetectionlib.jni

import android.graphics.Bitmap

class FaceDetection {
    companion object {
        init {
            System.loadLibrary("face_detection_lib")
        }
    }

    external fun init(): Int

    external fun detect(bitmap: Bitmap): Array<VisionDetRet>
}