#include "dmp.hpp"

volatile float yaw_ref_1, yaw_ref_2, pitch_ref_1, pitch_ref_2;
volatile float ypr[3];
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
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            float ypr_local[3];
            mpu.dmpGetYawPitchRoll(ypr_local, &q, &gravity);
            ypr[0] = ypr_local[0];
            ypr[1] = ypr_local[1];
            ypr[2] = ypr_local[2];
            Serial.print(ypr[0]);
            Serial.print(" ");
            Serial.print(ypr[1]);
            Serial.print(" ");
            Serial.print(ypr[2]);
            Serial.println("");
            last_vector = vector3D(ypr[0], ypr[1]);
            tmr = millis();
        }
    }
    return last_vector;
}

void calibrate_x_1()
{
    get_vector();
    yaw_ref_1 = ypr[0];
}
void calibrate_x_2()
{
    get_vector();
    yaw_ref_2 = ypr[0];
}
void calibrate_y_1()
{
    get_vector();
    pitch_ref_1 = ypr[1];
}
void calibrate_y_2()
{
    get_vector();
    pitch_ref_2 = ypr[1];
}

void IRAM_ATTR calibrate_center()
{
    get_vector();
    float delta_y = yaw_ref_2 - yaw_ref_1;
    yaw_ref_1 = +delta_y / 2 + ypr[0];
    yaw_ref_2 = -delta_y / 2 + ypr[0];
    float delta_p = pitch_ref_2 - pitch_ref_1;
    pitch_ref_1 = -delta_p / 2 + ypr[1];
    pitch_ref_2 = +delta_p / 2 + ypr[1];
}

point get_data()
{
    get_vector();
    Serial.println("----------------");
    Serial.println(yaw_ref_1);
    Serial.println(yaw_ref_2);
    Serial.println(pitch_ref_1);
    Serial.println(pitch_ref_2);
    Serial.println(ypr[0]);
    Serial.println(ypr[1]);
    return point(
        -(ypr[0] - yaw_ref_1) / (yaw_ref_1 - yaw_ref_2),
        (ypr[1] - pitch_ref_1) / (pitch_ref_2 - pitch_ref_1)
    );
}
