#ifndef __COLOUR_H
#define __COLOUR_H	

#include "user.h"

//COLOUR端口定义
#define TCS32_EO PAout(11) 
#define TCS32_S3 PAout(12) 
#define TCS32_S2 PAout(13) 
#define TCS32_S1 PAout(14) 
#define TCS32_S0 PAout(15) 

#define Red1    1
#define Green1  2
#define Blue1   3
//#define White_and_Green 100
/*外部函数声明*/
void Timer3_Init(u16 arr,u16 psc);//通用定时器3中断初始化
void EXTI11_Init(void);	//外部中断0服务程序
void TCS230_Init(void);//TCS230初始化
void Colour_Init(u8 Colour);//TCS230内部颜色滤波器设置
void TCS230_Start(void);//初始化各变量及定时器3、外部中断0，用于脉冲计数
u32 TCS230_Read_Colour(u8 Colour);//设置颜色滤波器并读出相应频率参数
u8 TCS230_Distinguish(void);//物体颜色判别
void showRGB(void);

		 				    
#endif
