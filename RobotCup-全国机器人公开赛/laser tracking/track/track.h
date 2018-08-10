#ifndef	_TRACK_H_
#define _TRACK_H_

#include "SuperSharkV1.0.h"

#define D(channel) DigitalIn(channel)  //数字口宏定义


u8 An_to_Di(u8 channel,u16 num1,u16 num2);//模拟通道值转数字值
//4路电机同时控制函数
void DMotor_Control(u8 D1,s8 DP1,u8 D2,s8 DP2,u8 D3,s8 DP3,u8 D4,s8 DP4);
void DMotor_Control_Par(s8 left,s8 right);//电机双行并列控制
void Track_steep_line(void);//直线前进单循迹 --快速
void Track_steep_Moderato(void);//直线单向前进中速循迹
void Track_steep_Moderato_low(void);//直线单向前进中慢速循迹
void Track_steep_low(void);//直线单向前进慢速循迹
void Track_steep_turn(void);//直线后退单循迹 --快速
void Track_steep_turn_Moderato(void);//直线后退中速单循迹
void Track_steep_turn_Moderato_low(void);//直线后退中慢速单循迹
void Track_steep_turn_low(void);//直线后退慢速单循迹
void Track_steep_WavyLine(unsigned char direction);//波浪线循迹
void Track_round(unsigned char direction);//走大圆

void Track_wheel_left(unsigned char num,unsigned char angle);//左转弯
void Track_wheel_right(unsigned char num,unsigned char angle);//右转弯
void Track_wheel_left180(void);//平台型景点180度左转

void Track_straight_line(unsigned char speed);//走直线
//指南针走直线
void Track_steep_cmp(unsigned char num,unsigned int floor,unsigned int upper_limit);

void Track_steep_Diaoyu_Islands(void);//钓鱼岛过桥

int my_intersection(int view);//判断识别路口
void mid_stop(int r1);//路口停止
void Track_crash_ward(void);//景点碰撞 
//指南针碰撞景点
void Track_cmp_ward(unsigned char num,unsigned int floor,unsigned int upper_limit);
int Track_JudgeBarrier_Place(int flag);//判断小车在障碍物的位置

void Fork_road_intersection(unsigned char flag);//作岔路口检测

void Track_Triaxial_Uphill(unsigned int floor,unsigned int upper_limit);//三轴上下坡




/*各种特殊处理路段函数*/  
//过桥函数
//1.去、回钓鱼岛
//2.去、回太平岛
void Track_GapBridge(unsigned int floor,unsigned int upper_limit);
//去低平台景点  
//1.从钓鱼岛回来过完桥---->从崇明岛回来	0
//2.过完5号门去夏威夷	0
//3.去佘山			  0
//4.去太湖			  1
//去无阶梯平台型景点
void Track_Speaicl_BridgeZM_to(unsigned char flag);
void Track_Taiping_To(void);	   
//倒退过门槛
void Track_Doorsill_Turn(void);	
//前进过门槛
void Track_Doorsill_line(void);	
//波浪线门槛
void Track_Doorsill_WavyLine(void); 
//上珠穆朗玛峰并下来
void Track_Qomolangma_To(void);	


#endif

