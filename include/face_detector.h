#pragma once
#include <opencv2/opencv.hpp>
#include <vector>

class FaceDetector {
public:
    FaceDetector();
    std::vector<cv::Rect> detect(const cv::Mat& frame);

private:
    cv::CascadeClassifier face_cascade;
};
