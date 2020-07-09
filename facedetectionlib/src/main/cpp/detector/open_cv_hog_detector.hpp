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

#ifndef FACE_DETECTION_ANDROID_OPEN_CV_HOG_DETECTOR_HPP
#define FACE_DETECTION_ANDROID_OPEN_CV_HOG_DETECTOR_HPP

class OpenCVHOGDetector {
public:
    OpenCVHOGDetector();
    ~OpenCVHOGDetector();

    int det(const cv::Mat& src_img);
    std::vector<cv::Rect>& getResult();
};

#endif //FACE_DETECTION_ANDROID_OPEN_CV_HOG_DETECTOR_HPP
