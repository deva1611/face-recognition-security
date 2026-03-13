#pragma once
#include <string>

class ESP32Notifier {
public:
    ESP32Notifier(const std::string& esp32_ip, int port = 80);
    void sendAlert();
    bool checkStatus();

private:
    std::string ip;
    int port;
    std::string httpPost(const std::string& path);
    std::string httpGet(const std::string& path);
};
