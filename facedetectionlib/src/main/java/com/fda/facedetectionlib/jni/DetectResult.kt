package com.fda.facedetectionlib.jni

import android.graphics.Point

data class DetectResult(
    val mLabel: String = "",
    val mConfidence: Float = 0f,
    val mLeft: Int = 0,
    val mTop: Int = 0,
    val mRight: Int = 0,
    val mBottom: Int = 0,
    val mLandmarkPoints: List<Point>
)