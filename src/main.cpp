#include <Arduino.h>
#include <XboxSeriesXControllerESP32_asukiaaa.hpp>
#include <ESP32Servo.h>

#define SERVO_MIN 550
#define SERVO_MAX 2350

Servo servo1;
XboxSeriesXControllerESP32_asukiaaa::Core xboxController;
long servo_us;

void setup() {
  Serial.begin(115200);
  servo1.attach(A4, SERVO_MIN, SERVO_MAX);
  servo1.setPeriodHertz(50);
  xboxController.begin();
}

void loop() {
  xboxController.onLoop();
    if (xboxController.isConnected()) {
    if (xboxController.isWaitingForFirstNotification()) {
      Serial.println("waiting for first notification");
    } else {
        servo_us = map(xboxController.xboxNotif.joyLHori, 0, XboxControllerNotificationParser::maxJoy, SERVO_MIN, SERVO_MAX);
        Serial.println(String(servo_us));
        servo1.writeMicroseconds(servo_us);
    }
  } else {
    Serial.println("not connected");
    if (xboxController.getCountFailedConnection() > 2) {
      ESP.restart();
    }
  }
}