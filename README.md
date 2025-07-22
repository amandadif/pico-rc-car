RC Car with WiFi Control and Obstacle Detection:

This project is a Wifi controlled RC car powered by a Raspberry Pi Pico 2W. It uses an ultrasonic sensor to detect obstacles and prevent forward collisions in real-time. The car is controlled through a browser-based interface
and uses keyboard inputs for movement.

Features:
- Web-based control interface
- Obstacle detection
  - The ultrasonic sensor monitors the distance from an obstacle. If the object is too close, forward movement is blocked.
- Automatic Emergency Stop
  If the car is moving forward and an obstacle appears the car is immediately stopped and inhibited from moving forward
- LED Feedback
  - [Green LED = path is clear] [Red LED = path is not clear]

Components:
  - Raspberry Pi Pico 2W
  - Tamiya tt-02 RC Car Kit (chassis, ESC, motor)
  - 20 Kg Servo
  - 7.2V Battery
  - 5V Portable Charger
  - Ultrasonic Sensor
  - MB102 Power Supply Module
  - 2 LEDs with 220 resistors

Future Ideas:
  - Change direction of the Ultrasonic sensor to detect obstacles from all directions
  - "Roomba Mode"- Autonomously drive and not crash
  - Camera for live video
  - Path following
  - Speaker(Horn), turn signals, LED screen to display info
  
  

