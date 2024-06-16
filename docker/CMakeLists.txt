cmake_minimum_required(VERSION 3.22)
project(face-recognition-cpp)

set(CMAKE_CXX_STANDARD 20)

# Fetch from git
include(FetchContent)

FetchContent_Declare(
    opencv
    GIT_REPOSITORY https://github.com/opencv/opencv.git
    GIT_TAG        4.4.0
)
FetchContent_MakeAvailable(opencv)

# Find on pc
find_package(OpenCV REQUIRED)
# Link
add_executable(${PROJECT_NAME} opencv-version.cpp)
target_include_directories(
    ${PROJECT_NAME} 
    PRIVATE
    ${OPENCV_CONFIG_FILE_INCLUDE_DIR}
    ${OPENCV_MODULE_opencv_core_LOCATION}/include
    ${OPENCV_MODULE_opencv_highgui_LOCATION}/include
)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})