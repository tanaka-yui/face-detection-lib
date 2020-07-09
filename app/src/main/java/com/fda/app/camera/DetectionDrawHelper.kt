package com.fda.app.camera

import android.graphics.*
import android.media.Image
import com.fda.facedetectionlib.jni.VisionDetRet
import java.io.ByteArrayOutputStream

class DetectionDrawHelper {

    private val cyanPaint = Paint().apply {
        color = Color.CYAN
        style = Paint.Style.STROKE
        strokeWidth = 8.0f
        isAntiAlias = true
    }

    private val yellowWPaint = Paint().apply {
        color = Color.YELLOW
        style = Paint.Style.STROKE
        strokeWidth = 8.0f
        isAntiAlias = true
    }

    fun convertBitmap(byteArray: ByteArray?, image: Image): Bitmap {
        val yuvImage = YuvImage(byteArray, ImageFormat.NV21, image.width, image.height, null)
        val out = ByteArrayOutputStream()
        yuvImage.compressToJpeg(Rect(0, 0, yuvImage.width, yuvImage.height), 50, out)
        val imageBytes = out.toByteArray()
        return BitmapFactory.decodeByteArray(imageBytes, 0, imageBytes.size, BitmapFactory.Options())
    }

    fun drawFaceDetectionData(bitmap: Bitmap, faceDetection: Array<VisionDetRet>) {
        val canvas = Canvas(bitmap)
        for (data in faceDetection) {
            drawRectDetectionData(canvas, cyanPaint, data)
        }
    }

    private fun drawRectDetectionData(canvas: Canvas, paint: Paint, detectionInfo: VisionDetRet) {
        canvas.drawRect(
            detectionInfo.left.toFloat(),
            detectionInfo.top.toFloat(),
            detectionInfo.right.toFloat(),
            detectionInfo.bottom.toFloat(),
            paint
        )
    }
}