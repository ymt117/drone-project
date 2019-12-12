#ifndef __PROTOTYPE_H__
#define __PROTOTYPE_H__
#include "all.h"

/**************************************************
 * motor.ino
 **************************************************/
void motor_init();

void motor_a_cw(int pwm);
void motor_a_stop();

void motor_b_ccw(int pwm);
void motor_b_stop();

void motor_c_cw(int pwm);
void motor_c_stop();

void motor_d_ccw(int pwm);
void motor_d_stop();

void motor_test();

/**************************************************
 * imu.ino
 **************************************************/
void imu_init();
void setMagMinMaxAndSetOffset(MPU9250_asukiaaa*, int);

void read_Accel();
void read_Gyro();
void read_Mag();

/**************************************************
 * imu.ino
 **************************************************/
void kalman_filter_init();
void kalman_filter_update();

#endif // __PROTOTYPE_H__