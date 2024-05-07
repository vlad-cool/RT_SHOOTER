#include "dmp.hpp"

vector3D vec_ref_x_1, vec_ref_x_2, vec_ref_y_1, vec_ref_y_2, n_x, n_y;
MPU6050 mpu;
uint8_t fifoBuffer[45];
float alpha_x, alpha_y, gamma_x, gamma_y;

point::point(float x, float y)
{
    this->x = x;
    this->y = y;
}

void setup_dmp()
{
    Wire.begin();
    mpu.initialize();
    mpu.dmpInitialize();
    mpu.setDMPEnabled(true);
}

vector3D get_vector()
{
    static uint32_t tmr;
    static vector3D last_vector;
    if (millis() - tmr >= 11)
    {
        if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer))
        {
            Quaternion q;
            VectorFloat gravity;
            float ypr[3];
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
            last_vector = vector3D(ypr[0], ypr[1]);
            tmr = millis();
        }
    }
    return last_vector;
}

void calibrate_x_1()
{
    vec_ref_x_1 = get_vector();
    alpha_x = acos(vec_ref_x_1 * vec_ref_x_2);
    gamma_x = PI / 2 - alpha_x / 2;
    n_x = vec_ref_x_1 % vec_ref_x_2;
    n_x.normalize();
}
void calibrate_x_2()
{
    vec_ref_x_2 = get_vector();
    alpha_x = acos(vec_ref_x_1 * vec_ref_x_2);
    gamma_x = PI / 2 - alpha_x / 2;
    n_x = vec_ref_x_1 % vec_ref_x_2;
    n_x.normalize();
}
void calibrate_y_1()
{
    vec_ref_y_1 = get_vector();
    alpha_y = acos(vec_ref_y_1 * vec_ref_y_2);
    gamma_y = PI / 2 - alpha_y / 2;
    n_y = vec_ref_y_1 % vec_ref_y_2;
    n_y.normalize();
}
void calibrate_y_2()
{
    vec_ref_y_2 = get_vector();
    alpha_y = acos(vec_ref_y_1 * vec_ref_y_2);
    gamma_y = PI / 2 - alpha_y / 2;
    n_y = vec_ref_y_1 % vec_ref_y_2;
    n_y.normalize();
}

point get_data()
{
    vector3D vec_cur = get_vector();
    vector3D vec_cur_x = vec_cur - n_x * (n_x * vec_cur);
    vector3D vec_cur_y = vec_cur - n_y * (n_y * vec_cur);

    float beta_x = acos(vec_ref_x_1 * vec_cur_x);
    float beta_y = acos(vec_ref_y_1 * vec_cur_y);

    Serial.println("-------------");
    Serial.println(vec_ref_y_1.to_str());
    Serial.println(vec_ref_y_2.to_str());
    Serial.println(vec_cur.to_str());
    Serial.println(vec_cur_y.to_str());
    Serial.println(alpha_y);
    Serial.println(beta_y);
    Serial.println(gamma_y);
    Serial.println("-------------");

    return point(
        sin(beta_x) * sin(gamma_x) / (sin(alpha_x) * sin(beta_x + gamma_x)),
        sin(beta_y) * sin(gamma_y) / (sin(alpha_y) * sin(beta_y + gamma_y))
    );
}
