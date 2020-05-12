package com.fda.app.camera

import android.graphics.*
import android.util.Log
import androidx.camera.core.ImageAnalysis
import androidx.camera.core.ImageProxy
import com.fda.app.ext.toBitmap
import com.fda.facedetectionlib.jni.FaceDetection

class ImageAnalyzer(private val callbackCameraImage: (bitmap: Bitmap) -> Unit): ImageAnalysis.Analyzer {
    companion object {
        const val TAG = "ImageAnalyzer"
    }

    private val faceDetection = FaceDetection()

    override fun analyze(imageProxy: ImageProxy) {
        try {
            val bitmap = imageProxy.toBitmap()
            faceDetection.detect(bitmap)
            callbackCameraImage(bitmap)
        } catch (e: Exception) {
            Log.e(TAG, e.localizedMessage ?: "unexpected error", e)
        } finally {
            imageProxy.close()
        }
    }
}
