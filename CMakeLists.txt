cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 17)

project(face-recognition-cpp)


# add_executable(${PROJECT_NAME} src/opencv-version.cpp)
# add_executable(${PROJECT_NAME} src/opencv-webcam.cpp)
# add_executable(${PROJECT_NAME} src/opencv-read-write.cpp)
# add_executable(${PROJECT_NAME} src/opencv-dlib-face-det.cpp)
add_executable(${PROJECT_NAME} src/opencv-dlib-face-recognition.cpp)
# add_executable(${PROJECT_NAME} src/http-client.cpp)
# add_executable(${PROJECT_NAME} src/web-server.cpp)
# add_executable(${PROJECT_NAME} src/fmt.cpp)
# target_link_libraries(${PROJECT_NAME} dlib::dlib)

# find_package(CURL REQUIRED)
# include_directories(${CURL_INCLUDE_DIR})
# target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES})

find_package(OpenCV CONFIG REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE opencv_core opencv_highgui)

include(FetchContent)
FetchContent_Declare(dlib
    GIT_REPOSITORY https://github.com/davisking/dlib.git
    GIT_TAG        v19.24.4
)
FetchContent_MakeAvailable(dlib)

# set(USE_SSE4_INSTRUCTIONS ON "Use AVX instructions")
# find_package(dlib CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC dlib::dlib opencv_core opencv_highgui)

find_package(Boost COMPONENTS chrono CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::chrono)

find_package(restinio CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE restinio::restinio)
