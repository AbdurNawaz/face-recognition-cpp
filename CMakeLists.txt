cmake_minimum_required(VERSION 3.22)

project(face-recognition-cpp)

include(FetchContent)
FetchContent_Declare(dlib
    GIT_REPOSITORY https://github.com/davisking/dlib.git
    GIT_TAG        v19.24.4
)
FetchContent_MakeAvailable(dlib)

add_executable(${PROJECT_NAME} opencv-version.cpp)
# add_executable(${PROJECT_NAME} opencv-webcam.cpp)
# add_executable(${PROJECT_NAME} opencv-dlib-face-det.cpp)
# add_executable(${PROJECT_NAME} opencv-dlib-face-recognition.cpp)
target_link_libraries(${PROJECT_NAME} dlib::dlib)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})