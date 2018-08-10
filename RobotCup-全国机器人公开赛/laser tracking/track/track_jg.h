#ifndef	_TRACK_JG_H_
#define _TRACK_JG_H_


//#include "track.h"
#include "SuperSharkV1.0.h"
#include <stm32f10x_lib.h>	

void Test();  

void Track_steep_line_jg();	 //激光走直线
void Track_steep_round_jg(); //激光走圆

void Track_wheel_left_90();  //左转90-1
void Track_wheel_right_90();  //右转90-1

void Track_wheel_left_45_2();  //左转45-2
void Track_wheel_right_45_2(); //右转45-2

void DMotor_Control(u8 D1,s8 DP1,u8 D2,s8 DP2,u8 D3,s8 DP3,u8 D4,s8 DP4);
void DMotor_Control_Par(s8 left,s8 right);

#endif
