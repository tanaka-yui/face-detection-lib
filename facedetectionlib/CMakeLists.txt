cmake_minimum_required(VERSION 3.10)

project(face_detection_lib)

set(LIB_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp)
set(JNI_LIB ${CMAKE_CURRENT_SOURCE_DIR}/src/main/jniLibs)
set(DLIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/dlib)
set(OPENCV_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/opencv)
set(JNI_UTIL_DIR ${LIB_SRC}/util)

add_library(face_detection_lib SHARED
        ${JNI_UTIL_DIR}/jni_bitmap2mat.cpp
        ${LIB_SRC}/face_detection_jni.cpp
        ${DLIB_DIR}/dlib/threads/threads_kernel_shared.cpp
        ${DLIB_DIR}/dlib/entropy_decoder/entropy_decoder_kernel_2.cpp
        ${DLIB_DIR}/dlib/base64/base64_kernel_1.cpp
        ${DLIB_DIR}/dlib/threads/threads_kernel_1.cpp
        ${DLIB_DIR}/dlib/threads/threads_kernel_2.cpp
)
target_link_libraries(
        face_detection_lib
        android
        jnigraphics
        log
        ${JNI_LIB}/${ANDROID_ABI}/libopencv_java3.so
)
target_include_directories(
        face_detection_lib
        PUBLIC
        ${JNI_UTIL_DIR}
        ${DLIB_DIR}
        ${OPENCV_DIR}/native/jni/include
)
