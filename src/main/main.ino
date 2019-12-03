/*******************************************************
 * Drone Project
 * Author: ymt
 *******************************************************/

#include "pin_layout.h"
#include "prototype.h"

void setup(){
    Serial.begin(115200);
    Serial.println("Start!!!");

    // Initialization
    motor_init();
    imu_init();

    delay(1000);
}

void loop(){
    read_Mag();

    delay(100);
}