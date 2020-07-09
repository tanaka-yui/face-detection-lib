#include <iostream> // std::cout
#include <string.h>
#include <jni.h>
#include <android/log.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <dlib/opencv/cv_image.h>
#include "jni_bitmap2mat.hpp"

using namespace dlib;
using namespace std;

#if defined(__arm__)
#if defined(__ARM_ARCH_7A__)
        #if defined(__ARM_NEON__)
          #if defined(__ARM_PCS_VFP)
            #define ABI "armeabi-v7a/NEON (hard-float)"
          #else
            #define ABI "armeabi-v7a/NEON"
          #endif
        #else
          #if defined(__ARM_PCS_VFP)
            #define ABI "armeabi-v7a (hard-float)"
          #else
            #define ABI "armeabi-v7a"
          #endif
        #endif
      #else
       #define ABI "armeabi"
      #endif
#elif defined(__i386__)
#define ABI "x86"
#elif defined(__x86_64__)
#define ABI "x86_64"
    #elif defined(__mips64)  /* mips64el-* toolchain defines __mips__ too */
    #define ABI "mips64"
    #elif defined(__mips__)
    #define ABI "mips"
    #elif defined(__aarch64__)
    #define ABI "arm64-v8a"
    #else
    #define ABI "unknown"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define CLASSNAME_VISION_DET_RET "com/fda/facedetectionlib/jni/VisionDetRet"
#define CONSTSIG_VISION_DET_RET "()V"

class DLibHOGFaceDetector {
private:
    dlib::frontal_face_detector mFaceDetector;

    inline void init() {
        mFaceDetector = dlib::get_frontal_face_detector();
    }

public:
    DLibHOGFaceDetector() { init(); }

    virtual inline std::vector<dlib::rectangle> det(const cv::Mat& image) {
        dlib::cv_image<dlib::bgr_pixel> img(image);
        return mFaceDetector(img);
    }
};

//std::vector<cv::Rect> det(cv::Mat src_img) {
//    cv::HOGDescriptor hog;
//    hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
//    std::vector<cv::Rect> found, found_filtered;
//    hog.detectMultiScale(src_img, found, 0, cv::Size(8, 8), cv::Size(32, 32), 1.05, 2, false);
//
//    size_t i, j;
//    for (i = 0; i < found.size(); i++) {
//        cv::Rect r = found[i];
//        for (j = 0; j < found.size(); j++) {
//            if (j != i && (r & found[j]) == r) {
//                break;
//            }
//        }
//        if (j == found.size()) {
//            found_filtered.push_back(r);
//        }
//    }
//    return found_filtered;
//}

void setRect(JNIEnv* env, jobject jDetRet, const int left, const int top,
                    const int right, const int bottom) {
    jclass detRetClass = env->FindClass(CLASSNAME_VISION_DET_RET);
    env->SetIntField(jDetRet, env->GetFieldID(detRetClass, "mLeft", "I"), left);
    env->SetIntField(jDetRet, env->GetFieldID(detRetClass, "mTop", "I"), top);
    env->SetIntField(jDetRet, env->GetFieldID(detRetClass, "mRight", "I"), right);
    env->SetIntField(jDetRet, env->GetFieldID(detRetClass, "mBottom", "I"), bottom);
}

jobject createJObject(JNIEnv* env) {
    jclass detRetClass = env->FindClass(CLASSNAME_VISION_DET_RET);
    jmethodID mid = env->GetMethodID(detRetClass, "<init>", CONSTSIG_VISION_DET_RET);
    return env->NewObject(detRetClass, mid);
}

jobjectArray createJObjectArray(JNIEnv* env, const int& size) {
    jclass detRetClass = env->FindClass(CLASSNAME_VISION_DET_RET);
    return (jobjectArray)env->NewObjectArray(size, detRetClass, NULL);
}

DLibHOGFaceDetector *openDetector;

JNIEXPORT jint JNICALL
Java_com_fda_facedetectionlib_jni_FaceDetection_init(JNIEnv *env, jobject thiz) {
    openDetector = new DLibHOGFaceDetector();
    return JNI_OK;
}

JNIEXPORT jobjectArray JNICALL
Java_com_fda_facedetectionlib_jni_FaceDetection_detect(JNIEnv *env, jobject thiz, jobject bitmap) {
    __android_log_print(ANDROID_LOG_DEBUG, "TAG", "detect start");
    cv::Mat rgbaMat;
    cv::Mat bgrMat;
    jniutils::ConvertBitmapToRGBAMat(env, bitmap, rgbaMat, true);
    cv::cvtColor(rgbaMat, bgrMat, cv::COLOR_RGBA2BGR);

    std::vector<dlib::rectangle> vec = openDetector->det(bgrMat);
    jobjectArray jDetRetArray = createJObjectArray(env, vec.size());
    for (int i = 0; i < vec.size(); i++) {
        jobject jDetRet = createJObject(env);
        dlib::rectangle rect = vec[i];
        setRect(env, jDetRet, rect.left(), rect.top(),rect.right(), rect.bottom());
        env->SetObjectArrayElement(jDetRetArray, i, jDetRet);
    }
//    for (int i = 0; i < vec.size(); i++) {
//        env->SetObjectArrayElement(jDetRetArray, i, jDetRet);
//        dlib::rectangle rect = vec[i];
//        setRect(env, jDetRet, rect.x, rect.y, rect.x + rect.width, rect.y + rect.height);
//    }

    __android_log_print(ANDROID_LOG_DEBUG, "TAG", "detect end");
    return jDetRetArray;
}

}