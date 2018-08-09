#ifndef	_TRACK_JG_H_
#define _TRACK_JG_H_


//#include "track.h"
//#include "user.h"
#include "sys.h"
#include "delay.h"
#include "driver.h"	

void main_test(void);
void step0(void);
void step1(void);
unsigned char is_center(void);
void forward_steep(void);
void forward_low(void);
void delay_level0(void);
void turn_degree(signed int radian);
void move_level0(void);
u8 test_colour(void);
void move_further(void);
void place_obj(void);
void edge_round(void);
void turn_center(signed char radian);
void turn_edge(signed char radian);
void forward_moderate(void);
void backward_moderate(void);
void delay_level1(void);
//unsigned char is_storage();
//void track_thick_round();
//unsigned char test_distance0();
void catch_obj(void);
//void track_back0();
//void track_routine0(signed char radian0,signed char radian1);
void track_routine1(signed int radian0,signed int radian1);
void track_routine2(signed int radian0,signed int radian1);
//void track_routine3(signed char radian0,signed char radian1);
void left_area_filter(void);
void right_area_filter(void);
void circle0_to_aim_to_center(void);
void center_to_aim_to_center(void);
void circle0_to_center(void);
void special_center_to_circle0_to_center(void);
void center_to_circle0_to_center(void);

void Track_steep_line_jg(void);
void Track_wheel_left_90(void);
void Track_wheel_right_90(void);
void Track_wheel_left_45_2(void);
void Track_wheel_right_45_2(void);

void move_long(void);
void aim_to_center(void);


#endif
