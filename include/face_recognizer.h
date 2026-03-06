#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include <string>
#include <vector>
#include <map>

class FaceRecognizer {
public:
    FaceRecognizer();
    void train(const std::string& knownFacesDir);
    std::string predict(const cv::Mat& face);

private:
    cv::Ptr<cv::face::LBPHFaceRecognizer> recognizer;
    std::map<int, std::string> labelMap;
};