#include <iostream>
#include <opencv2/opencv.hpp>
#include "face_detector.h"
#include "face_recognizer.h"

int main() {
    std::cout << "=== Face Recognition Security System ===" << std::endl;
    std::cout << "Starting webcam..." << std::endl;

    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open webcam" << std::endl;
        return -1;
    }

    FaceDetector detector;
    FaceRecognizer recognizer;
    recognizer.loadKnownFaces("known_faces/");

    cv::Mat frame;
    while (true) {
        cap >> frame;
        if (frame.empty()) break;

        auto faces = detector.detect(frame);
        for (auto& face : faces) {
            std::string name = recognizer.recognize(frame, face);
            cv::rectangle(frame, face, cv::Scalar(0, 255, 0), 2);
            cv::putText(frame, name, cv::Point(face.x, face.y - 10),
                cv::FONT_HERSHEY_SIMPLEX, 0.9, cv::Scalar(0, 255, 0), 2);
        }

        cv::imshow("Face Recognition Security", frame);
        if (cv::waitKey(1) == 'q') break;
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}