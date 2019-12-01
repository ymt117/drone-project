/*******************************************************
 * Drone Project
 * Author: ymt
 *******************************************************/

#include "pin_layout.h"
#include "prototype.h"

void setup(){
    motor_init();

    delay(30000);
}

void loop(){

    for(int i=0; i<256; i++){
        motor_a_cw(i);
        motor_b_ccw(i);
        motor_c_cw(i);
        motor_d_ccw(i);
        delay(1);
    }

    delay(3000);

    motor_a_stop();
    motor_b_stop();
    motor_c_stop();
    motor_d_stop();

    delay(5000);
}