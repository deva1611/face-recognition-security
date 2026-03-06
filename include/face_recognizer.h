#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include <string>
#include <map>

class FaceRecognizer {
public:
    FaceRecognizer();
    void loadKnownFaces(const std::string& folder);
    std::string recognize(const cv::Mat& frame, const cv::Rect& face);

private:
    cv::Ptr<cv::face::LBPHFaceRecognizer> recognizer;
    std::map<int, std::string> label_names;
};

