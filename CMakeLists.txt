cmake_minimum_required(VERSION 3.22)

project(face-recognition-cpp)

# include(FetchContent)
# FetchContent_Declare(dlib
#     GIT_REPOSITORY https://github.com/davisking/dlib.git
#     GIT_TAG        v19.24.4
# )
# FetchContent_MakeAvailable(dlib)


add_executable(${PROJECT_NAME} src/opencv-version.cpp)
# add_executable(${PROJECT_NAME} src/opencv-webcam.cpp)
# add_executable(${PROJECT_NAME} src/opencv-read-write.cpp)
# add_executable(${PROJECT_NAME} src/opencv-dlib-face-det.cpp)
# add_executable(${PROJECT_NAME} src/opencv-dlib-face-recognition.cpp)
# add_executable(${PROJECT_NAME} src/rest-client.cpp)
# add_executable(${PROJECT_NAME} src/fmt.cpp)
# target_link_libraries(${PROJECT_NAME} dlib::dlib)

# find_package(CURL REQUIRED)
# include_directories(${CURL_INCLUDE_DIR})
# target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES})

find_package(OpenCV CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE opencv_core)

find_package(dlib CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE dlib::dlib)