#pragma once
#include <opencv2/opencv.hpp>
#include <string>

class FaceDetector {
public:
    FaceDetector();
    bool loadClassifier(const std::string& cascadePath);
    std::vector<cv::Rect> detectFaces(const cv::Mat& frame);

private:
    cv::CascadeClassifier classifier;
};