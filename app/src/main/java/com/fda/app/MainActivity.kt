package com.fda.app

import android.Manifest
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import androidx.lifecycle.Observer
import androidx.lifecycle.ViewModelProvider
import com.fda.app.camera.CameraModule
import com.fda.app.databinding.ActivityMainBinding
import permissions.dispatcher.NeedsPermission
import permissions.dispatcher.RuntimePermissions

@RuntimePermissions
class MainActivity : AppCompatActivity() {

    private val factory: ViewModelProvider.Factory = ViewModelProvider.NewInstanceFactory()
    private lateinit var binding: ActivityMainBinding
    private lateinit var viewModel: MainViewModel
    private lateinit var cameraModule: CameraModule

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        viewModel = ViewModelProvider(this, factory).get(MainViewModel::class.java)

        cameraModule = CameraModule(
            this,
            callbackCameraImage = {
                viewModel.previewImage.postValue(it)
            },
            callbackDetectionInfo = {

            }
        )

        showCameraWithPermissionCheck()

        setObserver()
    }

    private fun setObserver() {
        viewModel.previewImage.observe(this, Observer {
            binding.previewImage.setImageBitmap(it)
        })
    }

    @NeedsPermission(Manifest.permission.CAMERA)
    fun showCamera() {
        cameraModule.startCamera()
    }
}
