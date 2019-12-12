/**************************************************
 * Reference:
 *  - https://github.com/asukiaaa/MPU9250_asukiaaa
 **************************************************/
#include "all.h"

#ifdef _ESP32_HAL_I2C_H_
#define SDA_PIN 21
#define SCL_PIN 22
#endif

//#define CALIB_ON
#define CALIB_SEC 20

//#define SERIAL_PRINT_IMU

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

#ifdef CALIB_ON
    // Clibrate mag sensor
    Serial.println("Start scanning values of magnetometer to get offset values.");
    Serial.println("Rotate your device for " + String(CALIB_SEC) + " seconds.");
    setMagMinMaxAndSetOffset(&mySensor, CALIB_SEC);
    Serial.println("Finished setting offset values.");
#endif
}

/**************************************************
 * Mag offset
 **************************************************/
void setMagMinMaxAndSetOffset(MPU9250_asukiaaa* sensor, int seconds){
    unsigned long calibStartAt = millis();
    float magX, magXMin, magXMax, magY, magYMin, magYMax, magZ, magZMin, magZMax;

    sensor->magUpdate();
    magXMin = magXMax = sensor->magX();
    magYMin = magYMax = sensor->magY();
    magZMin = magZMax = sensor->magZ();

    while(millis() - calibStartAt < (unsigned long) seconds * 1000) {
        delay(100);
        sensor->magUpdate();
        magX = sensor->magX();
        magY = sensor->magY();
        magZ = sensor->magZ();
        if (magX > magXMax) magXMax = magX;
        if (magY > magYMax) magYMax = magY;
        if (magZ > magZMax) magZMax = magZ;
        if (magX < magXMin) magXMin = magX;
        if (magY < magYMin) magYMin = magY;
        if (magZ < magZMin) magZMin = magZ;
    }

    sensor->magXOffset = - (magXMax + magXMin) / 2;
    sensor->magYOffset = - (magYMax + magYMin) / 2;
    sensor->magZOffset = - (magZMax + magZMin) / 2;
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
    #ifdef SERIAL_PRINT_IMU
        Serial.print("accelX: " + String(aX) + "\t");
        Serial.print("accelY: " + String(aY) + "\t");
        Serial.print("accelZ: " + String(aZ) + "\t");
        Serial.println("accelSqrt: " + String(aSqrt));
    #endif
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
    #ifdef SERIAL_PRINT_IMU
        Serial.print("gyroX: " + String(gX) + "\t");
        Serial.print("gyroY: " + String(gY) + "\t");
        Serial.println("gyroZ: " + String(gZ));
    #endif
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
    #ifdef SERIAL_PRINT_IMU
        Serial.print("magX: " + String(mX) + "\t");
        Serial.print("magY: " + String(mY) + "\t");
        Serial.print("magZ: " + String(mZ) + "\t");
        Serial.println("horizontal direction: " + String(mDirection));
    #endif
    }
    else{
        Serial.println("Cannot read mag values");
    }
}