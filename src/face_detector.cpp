#include "face_detector.h"
#include <iostream>

FaceDetector::FaceDetector() {
    // Load the Haar cascade classifier for face detection
    if (!face_cascade.load("/usr/share/opencv4/haarcascades/haarcascade_frontalface_default.xml")) {
        std::cerr << "Error loading face cascade!" << std::endl;
    } else {
        std::cout << "Face detector loaded successfully" << std::endl;
    }
}

std::vector<cv::Rect> FaceDetector::detect(const cv::Mat& frame) {
    std::vector<cv::Rect> faces;
    cv::Mat gray;
    
    // Convert to grayscale for faster detection
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(gray, gray);
    
    // Detect faces
    face_cascade.detectMultiScale(
        gray, faces, 1.1, 4,
        0 | cv::CASCADE_SCALE_IMAGE,
        cv::Size(30, 30)
    );
    
    return faces;
}