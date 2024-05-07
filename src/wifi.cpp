#include "wifi.hpp"
#include "dmp.hpp"

const char *ssid = "RT_SHOOTER";
const char *password = "Poltorashka";

#include "assets/img/aim.h"
#include "assets/img/bird.h"
#include "assets/img/scenes.h"
#include "assets/js/responce.h"
#include "assets/templates/responce.h"

#define TRIGGER_PIN D3

const byte DNS_PORT = 53;
IPAddress apIP(10, 10, 10, 1);
DNSServer dnsServer;

ESP8266WebServer server(80);
volatile int trigger_state = 1;

void setup_wifi()
{
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid, password);

    IPAddress IP = WiFi.softAPIP();
    
    pinMode(TRIGGER_PIN, INPUT_PULLUP);
    // attachInterrupt(digitalPinToInterrupt(TRIGGER_PIN), trigger_interrupt, FALLING);

    Serial.println(IP);
    server.on("/", handleRoot);
    server.on("/calibration", handleCalibrate);
    server.on("/calibrate_x_1", handleCalibrateX1);
    server.on("/calibrate_x_2", handleCalibrateX2);
    server.on("/calibrate_y_1", handleCalibrateY1);
    server.on("/calibrate_y_2", handleCalibrateY2);
    server.on("/img/aim.png", handle_get_aim);
    server.on("/img/ducks.png", handle_get_bird);
    server.on("/img/scenes.png", handle_get_scene);
    server.on("/js/responce.js", handle_get_script);
    server.on("/get_data", handleGetData);
    server.begin();

    dnsServer.start(DNS_PORT, "*", IP);
}

void handle_server()
{
    server.handleClient();
}

void handleRoot()
{
    server.send(200, "text/html", templates_responce_html, templates_responce_html_len);
}

void handleCalibrate()
{
    server.send(200, "text/html", "<h1> Calibration page </h1><br> \
        <a href=\"/calibrate_x_1\">x1</a><br> \
        <a href=\"/calibrate_x_2\">x2</a><br> \
        <a href=\"/calibrate_y_1\">y1</a><br> \
        <a href=\"/calibrate_y_2\">y2</a><br> \
    ");
}

void handleCalibrateX1()
{
    calibrate_x_1();
    server.send(200, "text/plaintext", "X 1 calibrated");
}

void handleCalibrateX2()
{
    calibrate_x_2();
    server.send(200, "text/plaintext", "X 2 calibrated");
}

void handleCalibrateY1()
{
    calibrate_y_1();
    server.send(200, "text/plaintext", "Y 1 calibrated");
}

void handleCalibrateY2()
{
    calibrate_y_2();
    server.send(200, "text/plaintext", "Y 2 calibrated");
}

void handleGetData()
{
    point p = get_data();
    server.send(200, "text/json", String("{\"x\": ") + (int)(p.x * 1920) + ", \"y\": " + (int)(p.y * 1080) + ", \"triggger_press\": " + (1 - trigger_state) + ", \"trigger_hold]\": " + (1 - digitalRead(TRIGGER_PIN)) + "}");
    trigger_state = 1;
}

void handle_get_aim()
{
    server.send(200, "image/png", img_aim_png, img_aim_png_len);
}

void handle_get_bird()
{
    server.send(200, "image/png", img_bird_png, img_bird_png_len);
}

void handle_get_scene()
{
    server.send(200, "image/png", img_scenes_png, img_scenes_png_len);
}

void handle_get_script()
{
    server.send(200, "application/javascript", js_responce_js, js_responce_js_len);
}

void trigger_interrupt()
{
    trigger_state = 0;
}
