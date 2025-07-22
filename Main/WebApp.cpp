#include <WiFi.h>
#include "WebApp.h"
#include <Servo.h>


#include "WebApp.h"
#include "DriveControl.h"

const char* ssid = "iPhone (50)";
const char* password = "rqnjj3ka";

WebApp::WebApp() : server(80) {}

void WebApp::connectToWifi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected! IP: "); 
  Serial.println(WiFi.localIP());
  server.begin();
}

void WebApp::serveClient(DriveControl& controller, bool pathClear) {
  WiFiClient client = server.accept();
  if (!client) return;

  String request = client.readStringUntil('\n');
  client.flush();

  if (request.indexOf("/set?val=") != -1) {
    int val = request.substring(request.indexOf("=")+1).toInt();
    controller.handleDriveCommand(val, pathClear);
  } 
  else if (request.indexOf("/set?val2=") != -1) {
    int val = request.substring(request.indexOf("=")+1).toInt();
    controller.handleSteeringCommand(val);
  }
  webInterface(client);
}

void WebApp :: webInterface(WiFiClient& client) {
  client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();

    client.println(R"=====(
    <script>
    let pathBlocked = false;
      // Track active states
      const controls = {
        forward: { active: false, url: '/set?val=1600', stopUrl: '/set?val=1500', element: null },
        reverse: { active: false, url: '/set?val=1350', stopUrl: '/set?val=1500', element: null },
        left: { active: false, url: '/set?val2=1200', stopUrl: '/set?val2=1500', element: null },
        right: { active: false, url: '/set?val2=1800', stopUrl: '/set?val2=1500', element: null }
      };

      // Initialize elements
      document.addEventListener('DOMContentLoaded', () => {
        controls.forward.element = document.getElementById('forward');
        controls.reverse.element = document.getElementById('reverse');
        controls.left.element = document.getElementById('left');
        controls.right.element = document.getElementById('right');
      });

      // Unified command sender
      function sendCommand(url) {
        fetch(url, { cache: 'no-store' }).catch(() => {});
      }

      // Button handlers
      function startControl(control) {
        if (!control.active) {
          if (pathBlocked && control === controls.forward) {
            console.log("Blocked: Ignoring forward input");
            return; 
          }
          control.active = true;
          if (control.element) control.element.classList.add('active');
          sendCommand(control.url);

          control.cooldown = true;
          setTimeout(() => { control.cooldown = false; }, 300);
        }
      }

      function stopControl(control) {
        if (control.active) {
          control.active = false;
          if (control.element) control.element.classList.remove('active');
          sendCommand(control.stopUrl);
        }
      }

      // Keyboard control - improved
      document.addEventListener('keydown', (e) => {
        switch(e.key.toLowerCase()) {
          case 'w': startControl(controls.forward); break;
          case 's': startControl(controls.reverse); break;
          case 'a': startControl(controls.left); break;
          case 'd': startControl(controls.right); break;
        }
        e.preventDefault(); // Prevent default browser behavior
      });

      document.addEventListener('keyup', (e) => {
        switch(e.key.toLowerCase()) {
          case 'w': stopControl(controls.forward); break;
          case 's': stopControl(controls.reverse); break;
          case 'a': stopControl(controls.left); break;
          case 'd': stopControl(controls.right); break;
        }
        e.preventDefault(); // Prevent default browser behavior
      });

      // Handle page visibility changes
      document.addEventListener('visibilitychange', () => {
        if (document.hidden) {
          // Return all controls to neutral if page loses focus
          Object.values(controls).forEach(stopControl);
        }
      });
    </script>
    )=====");
    delay(1);
    client.stop();
  }