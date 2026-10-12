# Face Recognition Security System

A real-time face recognition security system written in C++17 with OpenCV, running on Linux (Ubuntu). It recognises known people by name, labels everyone else as "Unknown", and sends an alert to an ESP32 over Wi-Fi when an unknown face appears.

## Features

- 🎥 Real-time face detection and recognition from a webcam
- 🏷️ Labels known faces by name (taken from the photo's file name)
- ⚠️ Flags unknown faces as "Unknown"
- 📡 Sends an HTTP alert to an ESP32 on the local network when an unknown face is seen

## Tech Stack

- **Language:** C++17
- **Computer vision:** OpenCV 4 with the `face` contrib module (Haar cascade + LBPH)
- **Networking:** POSIX sockets (raw HTTP over TCP, no external libraries)
- **Build system:** CMake
- **Hardware:** USB webcam, ESP32 (Wi-Fi alert receiver)
- **OS:** Ubuntu Linux

## How It Works

```
 Webcam ──► Linux PC (C++ / OpenCV) ──── HTTP over Wi-Fi ────► ESP32
            1. Detect faces (Haar cascade)        POST /alert   (unknown face)
            2. Recognise faces (LBPH)             GET  /status  (startup check)
            3. Draw name or "Unknown"
```

1. On startup, the program trains an LBPH recogniser on the photos in `known_faces/`.
2. It reads frames from the webcam and detects faces with a Haar cascade classifier.
3. Each detected face is recognised with LBPH. A match below the confidence threshold shows the person's name; anything else shows "Unknown".
4. For an unknown face, `ESP32Notifier` opens a TCP socket and sends `POST /alert` to the ESP32.
5. On startup it sends `GET /status` to check whether the ESP32 is reachable.

## ESP32 Interface

The Linux side expects an ESP32 running a small HTTP server on port 80 with two endpoints:

| Method | Path | Purpose |
|---|---|---|
| `GET` | `/status` | Health check at startup. Any response means "connected". |
| `POST` | `/alert` | Sent when an unknown face is detected. The ESP32 can trigger a buzzer, LED or notification. |

The ESP32 IP address is set in `src/main.cpp` (default `192.168.1.100`). Change it to match your network.

## Project Structure

```
face-recognition-security/
├── src/
│   ├── main.cpp              ← Capture loop: detect, recognise, alert
│   ├── face_detector.cpp     ← Haar cascade face detection
│   ├── face_recognizer.cpp   ← LBPH training and prediction
│   └── esp32_notifier.cpp    ← HTTP client for ESP32 alerts (POSIX sockets)
├── include/
│   ├── face_detector.h
│   ├── face_recognizer.h
│   └── esp32_notifier.h
├── known_faces/              ← Add your own photos here (not committed)
├── samples/
├── CMakeLists.txt
└── LICENSE
```

## Build and Run

### 1. Install dependencies (Ubuntu)

```bash
sudo apt update
sudo apt install build-essential cmake libopencv-dev libopencv-contrib-dev
```

`libopencv-contrib-dev` provides the `face` module used for LBPH recognition. The Haar cascade file is installed with OpenCV at `/usr/share/opencv4/haarcascades/`.

### 2. Add known faces

Put one clear, front-facing photo per person in `known_faces/`, named after them:

```
known_faces/
├── Alice.jpg
└── Bob.png
```

The file name (without extension) is the name shown on screen. Photos are not committed to the repo.

### 3. Build

```bash
mkdir build && cd build
cmake ..
make
```

### 4. Run

Run from the project root so the program can find `known_faces/`:

```bash
./build/face_recognition
```

Press `q` to quit.

## Author

Devendra Reddy Keesara
MSc Embedded Systems & IC Design, Liverpool John Moores University
GitHub: [github.com/deva1611](https://github.com/deva1611)
