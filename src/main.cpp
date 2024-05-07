#include <Arduino.h>

#include "vector.hpp"
#include "wifi.hpp"
#include "dmp.hpp"

void setup()
{
    Serial.begin(9600);
    setup_wifi();
    setup_dmp();
}
void loop()
{
    handle_server();
}