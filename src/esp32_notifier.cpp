#include "esp32_notifier.h"
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

ESP32Notifier::ESP32Notifier(const std::string& esp32_ip, int port)
    : ip(esp32_ip), port(port) {}

std::string ESP32Notifier::httpPost(const std::string& path) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) return "";

    struct sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_port   = htons(port);
    inet_pton(AF_INET, ip.c_str(), &server.sin_addr);

    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
        close(sock);
        return "";
    }

    std::string request =
        "POST " + path + " HTTP/1.1\r\n"
        "Host: " + ip + "\r\n"
        "Content-Length: 0\r\n"
        "Connection: close\r\n\r\n";

    send(sock, request.c_str(), request.size(), 0);

    char buf[512] = {};
    recv(sock, buf, sizeof(buf) - 1, 0);
    close(sock);
    return std::string(buf);
}

std::string ESP32Notifier::httpGet(const std::string& path) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) return "";

    struct sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_port   = htons(port);
    inet_pton(AF_INET, ip.c_str(), &server.sin_addr);

    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
        close(sock);
        return "";
    }

    std::string request =
        "GET " + path + " HTTP/1.1\r\n"
        "Host: " + ip + "\r\n"
        "Connection: close\r\n\r\n";

    send(sock, request.c_str(), request.size(), 0);

    char buf[512] = {};
    recv(sock, buf, sizeof(buf) - 1, 0);
    close(sock);
    return std::string(buf);
}

void ESP32Notifier::sendAlert() {
    std::cout << "[ESP32] Sending unknown face alert..." << std::endl;
    std::string response = httpPost("/alert");
    if (!response.empty())
        std::cout << "[ESP32] Alert acknowledged" << std::endl;
    else
        std::cerr << "[ESP32] Could not reach ESP32 - skipping alert" << std::endl;
}

bool ESP32Notifier::checkStatus() {
    std::string response = httpGet("/status");
    return !response.empty();
}
