#include "pin_layout.h"
/*
 * 白：プラス，黒：マイナス　->　反時計回りで飛ぶ
 * 
 * A(cw) B(ccw)
 *  \   /
 *  /   \
 * D(ccw)C(cw)
 */

const int CHANNEL_A = 0;
const int CHANNEL_B = 1;
const int CHANNEL_C = 2;
const int CHANNEL_D = 3;

const int LEDC_TIMER_BIT = 8;
const int LEDC_BASE_FREQ = 490;

void motor_init(){
    pinMode(ain1, OUTPUT);
    pinMode(ain2, OUTPUT);
    pinMode(pwma, OUTPUT);

    pinMode(bin1, OUTPUT);
    pinMode(bin2, OUTPUT);
    pinMode(pwmb, OUTPUT);

    pinMode(cin1, OUTPUT);
    pinMode(cin2, OUTPUT);
    pinMode(pwmc, OUTPUT);

    pinMode(din1, OUTPUT);
    pinMode(din2, OUTPUT);
    pinMode(pwmd, OUTPUT);

    ledcSetup(CHANNEL_A, LEDC_BASE_FREQ, LEDC_TIMER_BIT);
    ledcSetup(CHANNEL_B, LEDC_BASE_FREQ, LEDC_TIMER_BIT);
    ledcSetup(CHANNEL_C, LEDC_BASE_FREQ, LEDC_TIMER_BIT);
    ledcSetup(CHANNEL_D, LEDC_BASE_FREQ, LEDC_TIMER_BIT);

    ledcAttachPin(pwma, CHANNEL_A);
    ledcAttachPin(pwmb, CHANNEL_B);
    ledcAttachPin(pwmc, CHANNEL_C);
    ledcAttachPin(pwmd, CHANNEL_D);
}

void motor_a_cw(int pwm){
    digitalWrite(ain1, HIGH);
    digitalWrite(ain2, LOW);
    ledcWrite(CHANNEL_A, pwm);
}

void motor_a_stop(){
    digitalWrite(ain1, LOW);
    digitalWrite(ain1, LOW);
}

void motor_b_ccw(int pwm){
    digitalWrite(bin1, HIGH);
    digitalWrite(bin2, LOW);
    ledcWrite(CHANNEL_B, pwm);
}

void motor_b_stop(){
    digitalWrite(bin1, LOW);
    digitalWrite(bin2, LOW);
}

void motor_c_cw(int pwm){
    digitalWrite(cin1, HIGH);
    digitalWrite(cin2, LOW);
    ledcWrite(CHANNEL_C, pwm);
}

void motor_c_stop(){
    digitalWrite(cin1, LOW);
    digitalWrite(cin2, LOW);
}

void motor_d_ccw(int pwm){
    digitalWrite(din1, HIGH);
    digitalWrite(din2, LOW);
    ledcWrite(CHANNEL_D, pwm);
}

void motor_d_stop(){
    digitalWrite(din1, LOW);
    digitalWrite(din2, LOW);
}