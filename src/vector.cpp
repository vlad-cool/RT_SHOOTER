#include "vector.hpp"

vector3D::vector3D()
{
    x = 0;
    y = 0;
    z = 0;
}
vector3D::vector3D(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}
vector3D::vector3D(float yaw, float pitch)
{
    x = sin(yaw) * cos(pitch);
    y = cos(yaw) * cos(pitch);
    z = sin(pitch);
}
void vector3D::normalize()
{
    float a = abs();
    x /= a;
    y /= a;
    z /= a;
}
float vector3D::abs()
{
    return sqrt(x * x + y * y + z * z);
}
vector3D vector3D::operator%(const vector3D &r) // vector multiply
{
    return vector3D(y * r.z - z * r.y, z * r.x - x * r.z, x * r.y - y * r.x);
}
float vector3D::operator*(const vector3D &r) // scalar multiply
{
    return x * r.x + y * r.y + z * r.z;
}
vector3D vector3D::operator*(float r)
{
    return vector3D(x * r, y * r, z * r);
}
vector3D vector3D::operator+(const vector3D &r)
{
    return vector3D(x + r.x, y + r.y, z + r.z);
}
vector3D vector3D::operator-(const vector3D &r)
{
    return vector3D(x - r.x, y - r.y, z - r.z);
}
vector3D &vector3D::operator*=(float r)
{
    x *= r;
    y *= r;
    z *= r;
    return *this;
}
vector3D &vector3D::operator+=(const vector3D &r)
{
    x += r.x;
    y += r.y;
    z += r.z;
    return *this;
}
vector3D &vector3D::operator-=(const vector3D &r)
{
    x -= r.x;
    y -= r.y;
    z -= r.z;
    return *this;
}
String vector3D::to_str()
{
    return String(x) + ", " + y + ", " + z;
}