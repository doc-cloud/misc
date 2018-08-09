#ifndef __DRIVER_H
#define __DRIVER_H	

void servo_Configuration(void);
void speed_Configuration(void);
//void speed(int pwm1, int pwm2);
void speed(int pwm2, int pwm1);
void servo1(int pwm);
void servo2(int pwm);
void servo3(int pwm);
void servo4(int pwm);
void DMotor_Control_Par(int pwm2 , int pwm1);
void speed_24(int pwm1, int pwm2,int pwm3, int pwm4);
		 				    
#endif



















