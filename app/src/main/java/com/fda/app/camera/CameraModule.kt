package com.fda.app.camera

import android.graphics.Bitmap
import android.util.Log
import androidx.appcompat.app.AppCompatActivity
import androidx.camera.core.AspectRatio
import androidx.camera.core.CameraSelector
import androidx.camera.core.ImageAnalysis
import androidx.camera.lifecycle.ProcessCameraProvider
import androidx.core.content.ContextCompat
import java.util.concurrent.Executors

class CameraModule(private val act: AppCompatActivity,
                   private val callbackCameraImage: (bitmap: Bitmap) -> Unit,
                   private val callbackDetectionInfo: (value: String) -> Unit
) {
    companion object {
        private const val TAG = "CameraModule"
    }

    private var imageAnalyzer: ImageAnalyzer? = null

    private val cameraProvider = ProcessCameraProvider.getInstance(act)

    fun startCamera() {
        try {
            imageAnalyzer = ImageAnalyzer(callbackCameraImage)

            val cameraSelector = CameraSelector.Builder().requireLensFacing(CameraSelector.LENS_FACING_FRONT).build()

            val analyzer = ImageAnalysis.Builder().apply {
                setTargetAspectRatio(AspectRatio.RATIO_4_3)
            }.build().apply {
                setAnalyzer(Executors.newSingleThreadExecutor(), imageAnalyzer!!)
            }

            cameraProvider.addListener(Runnable {
                cameraProvider.get().apply {
                    unbindAll()
                    bindToLifecycle(act, cameraSelector, analyzer)
                }
            }, ContextCompat.getMainExecutor(act))
        } catch (e: Exception) {
            Log.e(TAG, e.localizedMessage ?: "unexpected error", e)
        }
    }

    fun stopCamera() {
        try {
            cameraProvider.cancel(true)
        } catch (e: Exception) {
            Log.e(TAG, e.localizedMessage ?: "unexpected error", e)
        }
    }
}