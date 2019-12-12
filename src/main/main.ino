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

    delay(1000);
}

void loop(){
    delay(100);
}