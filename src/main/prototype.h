#ifndef __PROTOTYPE_H__
#define __PROTOTYPE_H__

// motor.ino
void motor_init();

void motor_a_cw(int pwm);
void motor_a_stop();

void motor_b_ccw(int pwm);
void motor_b_stop();

void motor_c_cw(int pwm);
void motor_c_stop();

void motor_d_ccw(int pwm);
void motor_d_stop();

#endif // __PROTOTYPE_H__