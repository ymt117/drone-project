/**************************************************
 * Reference:
 *  - https://github.com/TKJElectronics/KalmanFilter
 **************************************************/
#include "all.h"

//#define SERIAL_PRINT_KALMAN

Kalman kalmanX;
Kalman kalmanY;

double gyroXangle, gyroYangle;  // Angle calculate using the gyro only
double compAngleX, compAngleY;  // Calculated angle using a complementary filter
double kalAngleX, kalAngleY;    // Calculated angle using a kalman filter

uint32_t timer;

void kalman_filter_init(){
    delay(100); // Wait for sensor to stabilize
    read_Accel();

    // atan2 outputs the value of -π to π (radians)
    roll  = atan2(aY, aZ) * RAD_TO_DEG;
    pitch = atan(-aX / sqrt(aY * aY + aZ * aZ)) * RAD_TO_DEG;

    kalmanX.setAngle(roll); // Set starting angle
    kalmanY.setAngle(pitch);
    gyroXangle = roll;
    gyroYangle = pitch;
    compAngleX = roll;
    compAngleY = pitch;

    timer = micros();
}

void kalman_filter_update(){
    // Update all the values
    read_Accel();
    read_Gyro();

    double dt = (double)(micros() - timer) / 1000000; // Calculate delta time
    timer = micros();

    roll  = atan2(aY, aZ) * RAD_TO_DEG;
    pitch = atan(-aX / sqrt(aY * aY + aZ * aZ)) * RAD_TO_DEG;

    double gyroXrate = gX / 131.0; // Convert to deg/s
    double gyroYrate = gY / 131.0; // Convert to deg/s

    // This fixes the transition problem when the accelerometer angle jumps between -180 and 180 degrees
    if((roll < -90 && kalAngleX > 90) || (roll > 90 && kalAngleX < -90)){
        kalmanX.setAngle(roll);
        compAngleX = roll;
        kalAngleX = roll;
        gyroXangle = roll;
    }
    else{
        kalAngleX = kalmanX.getAngle(roll, gyroXrate, dt); // Calculate the angle using a Kalman filter
    }

    if(abs(kalAngleX) > 90){
        gyroYrate = -gyroYrate; // Invert rate, so it fits the restricedaccelerometer reading
    }
    kalAngleY = kalmanY.getAngle(pitch, gyroYrate, dt);

    gyroXangle += gyroXrate * dt; // Calculate gyro angle without any filter
    gyroYangle += gyroYrate * dt;

    compAngleX = 0.93 * (compAngleX + gyroXrate * dt) + 0.07 * roll; // Calculate the angle using a Complimentary filter
    compAngleY = 0.93 * (compAngleY + gyroYrate * dt) + 0.07 * pitch;

    // Reset the gyro angle when it has drifted too much
    if(gyroXangle < -180 || gyroXangle > 180)
        gyroXangle = kalAngleX;
    if(gyroYangle < -180 || gyroYangle > 180)
        gyroYangle = kalAngleY;

#ifdef SERIAL_PRINT_KALMAN
    Serial.print("roll: "  + String(roll)  + "\t");
    Serial.print("pitch: " + String(pitch) + "\t");
    Serial.println();
#endif

    delay(2);
}