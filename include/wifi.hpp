#ifndef WIFI_HPP
#define WIFI_HPP

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <DNSServer.h>

void trigger_interrupt();
void handle_server();
void setup_wifi();
void handleRoot();
void handleCalibrate();
void handleCalibrateX1();
void handleCalibrateX2();
void handleCalibrateY1();
void handleCalibrateY2();
void handleGetData();
void handle_get_aim();
void handle_get_bird();
void handle_get_scene();
void handle_get_script();

#endif
