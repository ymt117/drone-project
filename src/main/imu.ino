#include <MPU9250_asukiaaa.h>
#include "gloval_value.h"

#ifdef _ESP32_HAL_I2C_H_
#define SDA_PIN 21
#define SCL_PIN 22
#endif

MPU9250_asukiaaa mySensor;

/**************************************************
 * IMU init
 **************************************************/
void imu_init(){
    uint8_t sensorId;

#ifdef _ESP32_HAL_I2C_H_
    Wire.begin(SDA_PIN, SCL_PIN);
    mySensor.setWire(&Wire);
#endif

    mySensor.beginAccel();
    mySensor.beginGyro();
    mySensor.beginMag();

    if(mySensor.readId(&sensorId) == 0){
        Serial.println("sensorId: " + String(sensorId));
    }
    else{
        Serial.println("Cannot read sensorId");
    }
}

/**************************************************
 * Read accel, gyro, mag
 **************************************************/
void read_Accel(){
    if(mySensor.accelUpdate() == 0){
        aX = mySensor.accelX();
        aY = mySensor.accelY();
        aZ = mySensor.accelZ();
        aSqrt = mySensor.accelSqrt();
        Serial.print("accelX: " + String(aX) + "\t");
        Serial.print("accelY: " + String(aY) + "\t");
        Serial.print("accelZ: " + String(aZ) + "\t");
        Serial.println("accelSqrt: " + String(aSqrt));
    }
    else{
        Serial.println("Cannot read accel values");
    }
}

void read_Gyro(){
    if(mySensor.gyroUpdate() == 0){
        gX = mySensor.gyroX();
        gY = mySensor.gyroY();
        gZ = mySensor.gyroZ();
        Serial.print("gyroX: " + String(gX) + "\t");
        Serial.print("gyroY: " + String(gY) + "\t");
        Serial.println("gyroZ: " + String(gZ));
    }
    else{
        Serial.println("Cannot read gyro values");
    }
}

void read_Mag(){
    if(mySensor.magUpdate() == 0){
        mX = mySensor.magX();
        mY = mySensor.magY();
        mZ = mySensor.magZ();
        mDirection = mySensor.magHorizDirection();
        Serial.print("magX: " + String(mX) + "\t");
        Serial.print("magY: " + String(mY) + "\t");
        Serial.print("magZ: " + String(mZ) + "\t");
        Serial.println("horizontal direction: " + String(mDirection));
    }
    else{
        Serial.println("Cannot read mag values");
    }
}