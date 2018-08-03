//#ifndef __COLOUR_H
//#define __COLOUR_H	

////#include "user.h"
//#include <stm32f10x_lib.h>		 
//#include "sys.h"
//#include "delay.h"
//#include "lcd5110.h"
////#include "lcd12864.h" 
////#include "led.h"
//#include "driver.h"	
//#include "getsensor.h"
//#include "beep.h"
////#include "remote.h"
//#include "iic.h" 
//#include "key.h"
//#include "distance.h"
////#include "colour.h"
//#include "compass.h" 

////COLOUR端口定义
//#define TCS32_EO PAout(11) 
//#define TCS32_S3 PBout(14) 
//#define TCS32_S2 PBout(13) 
//#define TCS32_S1 PAout(14) 
//#define TCS32_S0 PAout(15) 

//#define Red1    1
//#define Green1  2
//#define Blue1   3
////#define White_and_Green 100
///*外部函数声明*/
//void Timer3_Init(u16 arr,u16 psc);//通用定时器3中断初始化
//void EXTI11_Init(void);	//外部中断0服务程序
//void TCS230_Init(void);//TCS230初始化
//void Colour_Init(u8 Colour);//TCS230内部颜色滤波器设置
//void TCS230_Start(void);//初始化各变量及定时器3、外部中断0，用于脉冲计数
//u32 TCS230_Read_Colour(u8 Colour);//设置颜色滤波器并读出相应频率参数
//void TCS230_Distinguish(void);//物体颜色判别
//void showRGB(void);

//		 				    
//#endif


#ifndef _ColorSensor_H
#define _ColorSensor_H
#include <stm32f10x_lib.h>	
#include "delay.h"
#include "sys.h"

#define Red1    1
#define Green1  2
#define Blue1   3
#define Yellow1 4

//#define uint unsigned int
//#define uchar unsigned char

/*端口定义*/
#define TCS32_S2 PBout(13)
#define TCS32_S3 PBout(14)



/*外部函数声明*/
void Timer2_Init(u16 arr,u16 psc);     //通用定时器2中断初始化
void EXTI5_Init(void);	               //外部中断5服务程序
void TCS230_Init(void);    			   //TCS230初始化
void Colour_Init(u8 Colour);		   //TCS230内部颜色滤波器设置
void TCS230_Start(void);               //初始化各变量及定时器2、外部中断5，用于脉冲计数
u32 TCS230_Read_Colour(u8 Colour);     //设置颜色滤波器并读出相应频率参数
u8 TCS230_Distinguish(void);           //物体颜色判别
void ColorSensor_init(void);
void ColorSensor(void);				   //执行

#endif
