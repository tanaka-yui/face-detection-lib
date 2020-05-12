package com.fda.app

import android.graphics.Bitmap
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel

class MainViewModel: ViewModel() {
    val previewImage = MutableLiveData<Bitmap>()
}