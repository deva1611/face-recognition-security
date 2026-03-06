#include "face_detector.h"

FaceDetector::FaceDetector() {}

bool FaceDetector::loadClassifier(const std::string& cascadePath) {
    return classifier.load(cascadePath);
}

std::vector<cv::Rect> FaceDetector::detectFaces(const cv::Mat& frame) {
    cv::Mat grey;
    cv::cvtColor(frame, grey, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(grey, grey);
    std::vector<cv::Rect> faces;
    classifier.detectMultiScale(grey, faces, 1.1, 4);
    return faces;
}