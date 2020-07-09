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

    private val faceDetection by lazy { FaceDetection().apply {
        init()
    } }

    private val detectionDrawHelper by lazy { DetectionDrawHelper() }

    override fun analyze(imageProxy: ImageProxy) {
        try {
            val bitmap = imageProxy.toBitmap()
            val ret = faceDetection.detect(bitmap)
            detectionDrawHelper.drawFaceDetectionData(bitmap, ret)
            for (d in ret) {
                Log.i(TAG, d.toString() )
            }
            callbackCameraImage(bitmap)
        } catch (e: Exception) {
            Log.e(TAG, e.localizedMessage ?: "unexpected error", e)
        } finally {
            imageProxy.close()
        }
    }
}
