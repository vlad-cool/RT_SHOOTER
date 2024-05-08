#ifndef WIFI_HPP
#define WIFI_HPP

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <DNSServer.h>

void trigger_interrupt();
void handle_server();
void setup_wifi();
void handleCalibrateX1();
void handleCalibrateX2();
void handleCalibrateY1();
void handleCalibrateY2();
void handleGetData();

void handleGetAim();
void handleGetDucks();
void handleGetScenes();
void handleGetTransscenes();

void handleGetScript();

void handleRoot();
void handleCalibrate();
void handleGetCalibration();

#endif
