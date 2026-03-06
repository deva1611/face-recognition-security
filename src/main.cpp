#include <opencv2/opencv.hpp>
#include "face_detector.h"
#include "face_recognizer.h"
#include <iostream>

int main() {
    FaceDetector detector;
    FaceRecognizer recognizer;

    if (!detector.loadClassifier(
        "/usr/share/opencv4/haarcascades/haarcascade_frontalface_default.xml")) {
        std::cerr << "Error: Could not load Haar Cascade classifier" << std::endl;
        return -1;
    }

    recognizer.train("../known_faces");

    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open webcam" << std::endl;
        return -1;
    }

    cv::Mat frame;
    while (true) {
        cap >> frame;
        if (frame.empty()) break;

        std::vector<cv::Rect> faces = detector.detectFaces(frame);

        for (const auto& face : faces) {
            cv::Mat faceROI = frame(face);
            std::string name = recognizer.predict(faceROI);
            cv::rectangle(frame, face, cv::Scalar(0, 255, 0), 2);
            cv::putText(frame, name, cv::Point(face.x, face.y - 10),
                        cv::FONT_HERSHEY_SIMPLEX, 0.8, 
                        cv::Scalar(0, 255, 0), 2);
        }

        cv::imshow("Face Recognition", frame);
        if (cv::waitKey(1) == 'q') break;
    }

    return 0;
}