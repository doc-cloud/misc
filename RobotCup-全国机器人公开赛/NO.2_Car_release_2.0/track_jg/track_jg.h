//filename:	track_jg.h
//language:	C.
//usage:	provide explanation for C file track_jg.c
//version:	1.1 by song,zong and chen on 8/19/2014.

#ifndef	_TRACK_JG_H_
#define _TRACK_JG_H_

#include "sys.h"
#include "delay.h"
#include "driver.h"	
#include "colour.h"

#define	j1 GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_9)	
#define	j2 GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_10)
#define	j3 GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_11)
#define	j4 GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_12)
#define	j5 GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_13)
#define	j6 GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_14)
#define	j7 GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_15)
#define	j8 GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_7)
#define j9 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_10)
#define j10 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_12)

  
#define PASS_NORTHERN_CROSSROAD			while(!is_northern_crossroad())\
													forward_steep();

#define PASS_SOUTHERN_CROSSROAD			while(!is_southern_crossroad())\
													forward_steep();

#define PASS_LEFT_NORTHERN_CROSSROAD		while(!is_left_northern_crossroad())\
													forward_steep();

#define PASS_RIGHT_NORTHERN_CROSSROAD		while(!is_right_northern_crossroad())\
													forward_steep();

#define PASS_NORTHERN_CROSSROAD_CATCH		while(!is_northern_crossroad())\
													forward_steep();

#define PASS_SOUTHERN_CROSSROAD_CATCH			while(!is_southern_crossroad())\
													forward_steep();

#define PASS_LEFT_NORTHERN_CROSSROAD_CATCH		while(!is_left_northern_crossroad())\
													forward_steep();

#define PASS_RIGHT_NORTHERN_CROSSROAD_CATCH		while(!is_right_northern_crossroad())\
													forward_steep();

#define PASS_STORAGE_CROSSROAD					while(!is_storage())\
													forward_steep();

//definition of the colour value.
#define GREEN 0
#define WHITE 1
#define RED 2
#define BLACK 3
#define BLUE 4

//definition of the value of gray.
#define ANALOG_MAX_LEFT	 2700
#define ANALOG_MAX_RIGHT  2200
#define ANALOG_MIN_LEFT	 1200
#define ANALOG_MIN_RIGHT  930

//a test function for the robot debugging.
void main_test(void);

//two steps of this competition.
void step0(void);
void step1(void);

//four procedures for the step0
void procedure0_former(void);
void procedure1_former(void);
void procedure2_former(void);
void procedure3_latter(void);

//four procedures for the step1
void face_to_left_storage(void);
void left_storage_filter(void);
void right_storage_filter(void);
void track_routine0(unsigned char i);
void track_routine1(unsigned char i);

//some process functions may be called in the function main_test realization.
void forward_steep(void);
void forward_slow(void);
void TCS_Power_On(void);
void internal_push_back(unsigned char colour_val);
void pass_center(void);
void turn_degree(signed int radian);
void turn_catch_degree(signed int radian);
void place_obj(void);
void catch_obj(void);
void catch_storage_1_obj(void);
void catch_storage_2_obj(void);
void catch_storage_3_obj(void);
void catch_storage_4_obj(void);
void catch_storage_5_obj(void);
void backward_moderate(void);
void delay_level0(void);
void drag_obj(unsigned char i);

//some function return a value for the judgement.
unsigned char test_colour(void);
unsigned char is_northern_crossroad(void);
unsigned char is_southern_crossroad(void);
unsigned char is_left_northern_crossroad(void);
unsigned char is_right_northern_crossroad(void);
unsigned char is_pre_center(void);
unsigned char is_storage(void);
unsigned char is_edge(unsigned char push_colour);

#endif
