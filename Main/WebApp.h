#ifndef WEBAPP_H
#define WEBAPP_H
#include <Servo.h>
#include "DriveControl.h"

class WebApp {
  private:
    WiFiServer server;
  public:
    WebApp();
    WebApp(const char* ssid, const char* password);
    void connectToWifi();
    void serveClient(DriveControl& controller, bool pathClear);
    void webInterface(WiFiClient& client);
};
#endif