cmake_minimum_required(VERSION 3.10)

project(face-detection-lib)

set(LIB_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp)

add_library(
        face-detection-lib
        SHARED
        ${LIB_SRC}/face_detection.cpp)
target_link_libraries(
        face-detection-lib
        android
        log
)
