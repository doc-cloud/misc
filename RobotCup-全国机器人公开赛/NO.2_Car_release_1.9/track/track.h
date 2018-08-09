#ifndef _TRACK_H_
#define _TRACK_H_



void Track_steep_line(void);	//前进单循迹
void Track_steep_turn(void);	//后退单循迹
void Track_wheel_left(void);	//直角左转
void Track_wheel_right(void);	//直角右转
void Track_straight_line(void);//走直线
void Track_steep_low(void);		//慢速走直线
int intersection(int view);//判断识别路口

int my_intersection(int view);

void mid_stop(int r1);		//路口停车

void mid_stop_nottrack(void);//无轨迹路段返回路口停止

void Track_path_stop(unsigned char flag);//转直角后停止（无轨迹路段）
//不采用void Track_before_stop(void);//转直角前停止（无轨迹路段）
void Track_round_stop(unsigned char flag);	//大圆圈边界停止


void Track_crash_ward(void);	//碰撞

void Trcak_ranging_point(unsigned char flag);//红外测距

void Track_rear_20cm(void);		//20cm举高
void Track_rear_50cm(void);		//50cm举高
void Track_rear_clamp(int flag);//夹持杯子
void Trcak_ranging_cup(void);	//红外测距检测杯子

void Track_steep_cmp(unsigned char flag);		//指南针走直线

void switch_car1(int enn);	//走全程  情况：1---3
void switch_car2(int enn);	//走全程  情况：1---2
void switch_car3(int enn);	//走全程  情况：2---3
void switch_car4(int enn);	//走全程  情况：3---1 按键---先S4，后S1
void switch_car5(int enn);	//走全程  情况：2---1 按键---先S4，后S2
void switch_car6(int enn);	//走全程  情况：3---2 按键---先S4，后S3

#endif
