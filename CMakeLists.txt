cmake_minimum_required(VERSION 3.10)
project(FaceRecognitionSecurity)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

include_directories(include ${OpenCV_INCLUDE_DIRS})

add_executable(face_recognition
    src/main.cpp
    src/face_detector.cpp
    src/face_recognizer.cpp
)

target_link_libraries(face_recognition 
    ${OpenCV_LIBS}
    opencv_face
)