/*******************************************************
 * Drone Project
 * Author: ymt
 *******************************************************/
#include "all.h"

void setup(){
    Serial.begin(115200);
    Serial.println("Start!!!");
    SerialBT.begin("ymt drone");
    SerialBT.println("Hello Bluetooth!!!");

    // Initialization
    motor_init();
    imu_init();
    kalman_filter_init();

    delay(1000);
}

void loop(){
    kalman_filter_update();
    Serial.print("roll: "  + String(roll)  + "\t");
    Serial.print("pitch: " + String(pitch) + "\t");
    Serial.println();
}