#include <iostream>
#include <chrono>
#include <opencv2/opencv.hpp>
#include "face_detector.h"
#include "face_recognizer.h"
#include "esp32_notifier.h"

int main() {
    std::cout << "=== Face Recognition Security System ===" << std::endl;
    std::cout << "Starting webcam..." << std::endl;

    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open webcam" << std::endl;
        return -1;
    }

    FaceDetector detector;
    if (!detector.loadClassifier("/usr/share/opencv4/haarcascades/haarcascade_frontalface_default.xml")) {
        std::cerr << "Error: Could not load Haar cascade (is libopencv-dev installed?)" << std::endl;
        return -1;
    }

    FaceRecognizer recognizer;
    recognizer.train("known_faces/");

    ESP32Notifier esp32("192.168.1.100");
    std::cout << "[ESP32] Checking connection..." << std::endl;
    const bool esp32Online = esp32.checkStatus();
    if (esp32Online)
        std::cout << "[ESP32] Connected!" << std::endl;
    else
        std::cout << "[ESP32] Not connected - alerts will be skipped" << std::endl;

    // Send at most one alert every 5 seconds, not one per frame
    using Clock = std::chrono::steady_clock;
    const auto alertCooldown = std::chrono::seconds(5);
    auto lastAlert = Clock::now() - alertCooldown;

    cv::Mat frame;
    while (true) {
        cap >> frame;
        if (frame.empty()) break;

        auto faces = detector.detectFaces(frame);
        for (auto& face : faces) {
            cv::Mat faceROI = frame(face);
            std::string name = recognizer.predict(faceROI);

            cv::rectangle(frame, face, cv::Scalar(0, 255, 0), 2);
            cv::putText(frame, name, cv::Point(face.x, face.y - 10),
                        cv::FONT_HERSHEY_SIMPLEX, 0.9, cv::Scalar(0, 255, 0), 2);

            if (name == "Unknown" && esp32Online &&
                Clock::now() - lastAlert >= alertCooldown) {
                esp32.sendAlert();
                lastAlert = Clock::now();
            }
        }

        cv::imshow("Face Recognition Security", frame);
        if (cv::waitKey(1) == 'q') break;
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}
