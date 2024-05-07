#ifndef DMP_HPP
#define DMP_HPP

#include <Arduino.h>
#include <I2Cdev.h>
#include <MPU6050_6Axis_MotionApps20.h>

#include "vector.hpp"

struct point
{
    float x, y;
    point(float x, float y);
};


void setup_dmp();

void calibrate_x_1();
void calibrate_x_2();
void calibrate_y_1();
void calibrate_y_2();

point get_data();

#endif