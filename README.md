
A real-time face recognition security system built in C++ using OpenCV, 
running on Linux (Ubuntu). Recognises known individuals by name and 
flags unknown visitors.

## Live Demo
🎥 Identifies known faces by name (e.g. "Ravi")  
⚠️ Flags unknown faces as "Unknown"  
⚡ Real-time processing via webcam or ESP32 camera feed

## Tech Stack
- **Language:** C++17
- **Computer Vision:** OpenCV 4.6
- **Build System:** CMake
- **Hardware:** ESP32 + Webcam
- **OS:** Ubuntu Linux

## How It Works
1. Load known faces from `known_faces/` folder
2. Capture live video feed
3. Detect faces using Haar Cascade classifier
4. Recognise faces using LBPH algorithm
5. Display name or "Unknown" in real time

## Project Structure
```
face-recognition-security/
├── src/
│   ├── main.cpp
│   ├── face_detector.cpp
│   └── face_recognizer.cpp
├── include/
│   ├── face_detector.h
│   └── face_recognizer.h
├── known_faces/
├── samples/
├── tests/
└── CMakeLists.txt
```

## Build Instructions
```bash
mkdir build && cd build
cmake ..
make
./face_recognition
```

## Adding Known Faces
Add a photo named after the person to the `known_faces/` folder:
```
known_faces/
├── Devendra.jpg
└── Ravi.jpg
```

## Author
Devendra Reddy Keesara  
MSc Embedded Systems & IC Design  
GitHub: github.com/deva1611