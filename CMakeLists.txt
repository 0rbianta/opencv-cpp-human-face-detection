cmake_minimum_required(VERSION 2.8)
project(opencv_human_detection)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(opencv_human_detection opencv_human_detection.cpp )
target_link_libraries(opencv_human_detection ${OpenCV_LIBS} )
