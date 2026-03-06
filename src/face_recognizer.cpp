#include "face_recognizer.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

FaceRecognizer::FaceRecognizer() {
    recognizer = cv::face::LBPHFaceRecognizer::create();
}

void FaceRecognizer::train(const std::string& knownFacesDir) {
    std::vector<cv::Mat> images;
    std::vector<int> labels;
    int label = 0;

    for (const auto& entry : fs::directory_iterator(knownFacesDir)) {
        if (entry.path().extension() == ".jpg" ||
            entry.path().extension() == ".png") {
            cv::Mat img = cv::imread(entry.path().string(),
                                     cv::IMREAD_GRAYSCALE);
            if (!img.empty()) {
                cv::resize(img, img, cv::Size(100, 100));
                images.push_back(img);
                labels.push_back(label);
                labelMap[label] = entry.path().stem().string();
                label++;
            }
        }
    }

    if (!images.empty()) {
        recognizer->train(images, labels);
        std::cout << "Trained on " << images.size()
                  << " faces" << std::endl;
    }
}

std::string FaceRecognizer::predict(const cv::Mat& face) {
    cv::Mat grey;
    cv::resize(face, grey, cv::Size(100, 100));
    cv::cvtColor(grey, grey, cv::COLOR_BGR2GRAY);

    int label;
    double confidence;
    recognizer->predict(grey, label, confidence);

    if (confidence < 100) {
        return labelMap[label];
    }
    return "Unknown";
}