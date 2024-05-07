#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cmath>
#include <Arduino.h>

class vector3D
{
private:
    float x, y, z;

public:
    vector3D();
    vector3D(float x, float y, float z);
    vector3D(float yaw, float pitch);
    void normalize();
    float abs();
    vector3D operator%(const vector3D &r); // vector multiply
    float operator*(const vector3D &r);    // scalar multiply
    vector3D operator*(float r);
    vector3D operator+(const vector3D &r);
    vector3D operator-(const vector3D &r);
    vector3D& operator*=(float r);
    vector3D& operator+=(const vector3D &r);
    vector3D& operator-=(const vector3D &r);
    String to_str();
};

#endif
