#ifndef BITMAP2MAT_H
#define BITMAP2MAT_H

#include "../../../../../../../../Library/Android/sdk/ndk/20.0.5594570/toolchains/llvm/prebuilt/darwin-x86_64/sysroot/usr/include/jni.h"
#include "../../../../../../../../Library/Android/sdk/ndk/20.0.5594570/toolchains/llvm/prebuilt/darwin-x86_64/sysroot/usr/include/android/bitmap.h"
#include "../../../../../../../../Library/Android/sdk/ndk/20.0.5594570/toolchains/llvm/prebuilt/darwin-x86_64/sysroot/usr/include/android/log.h"
#include "../../../../vendor/opencv/native/jni/include/opencv2/core/core.hpp"
#include "../../../../vendor/opencv/native/jni/include/opencv2/opencv.hpp"

/*
 *     Author : TzuTaLin
 * Created on : 07/25 2016
 *
 * Copyright (c) 2016 Tzutalin. All rights reserved.
 */
namespace jniutils {

    void ConvertBitmapToRGBAMat(JNIEnv* env, jobject& bitmap, cv::Mat& dst,
                                bool needUnPremultiplyAlpha);

}  // end jniutils

#endif /* BITMAP2MAT_H */
