#ifndef WEBAPP_H
#define WEBAPP_H
#include <Servo.h>

class WebApp {
  private:
    WiFiServer server;
  public:
    WebApp();
    WebApp(const char* ssid, const char* password);
    void connectToWifi();
    void sendServoCommand(Servo& servo, Servo& esc);
    void webInterface(WiFiClient& client);
};
#endif