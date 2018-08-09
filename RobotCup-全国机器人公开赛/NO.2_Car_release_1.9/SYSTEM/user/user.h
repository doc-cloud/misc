#ifndef __USER_H
#define __USER_H
 
#include <stm32f10x_lib.h>		 
#include "sys.h"
#include "delay.h"
#include "lcd5110.h"
//#include "lcd12864.h" 
#include "led.h"
#include "driver.h"	
#include "getsensor.h"
#include "beep.h"
//#include "remote.h"
#include "iic.h" 
#include "key.h"
#include "distance.h"
//#include "colour.h"
#include "compass.h" 
#include "track_jg.h"

//系统函数
extern void Sys_Init(void);			 //系统总初始化
extern void delay_ms(u16 nms);		 //毫秒延迟，不超过1864ms
extern void delay_us(u32 nus);		 //微秒延迟

void anologTest(void);
void Digit1_4Test(void);
void Digit16_22Test(void);
void manu(void);

//12864液晶函数 大小为6*10点阵
//extern void PutString(unsigned char x,unsigned char y,unsigned char *p);	 //x,y坐标上显示字符串
//extern void ShowVar(unsigned char x,unsigned char y,unsigned short a);		 //x,y坐标上显示16位无符号变量（5位十进制）
//extern void ClrScreen(void);												 //清屏

//LED函数
#define LED2_ON   LED0=0	  //LED2_ON; 亮 LED2_OFF;暗
#define LED2_OFF  LED0=1
#define LED1_ON   LED1=0	  //LED1_ON; 亮 LED1_OFF;暗
#define LED1_OFF  LED1=1

//电机、舵机驱动函数
extern void speed(int pwm1, int pwm2);
extern void servo1(int pwm);
extern void servo2(int pwm);
extern void servo3(int pwm);
extern void servo4(int pwm);
extern void speed_24(int pwm1, int pwm2,int pwm3, int pwm4);

//模拟、数字口函数
extern u8 digtal(u8 channel);  	//获取X通道数字值（0，1）		  1~22						  
extern u16 analog(u8 channel);  //获取X通道AD值（0~1023）		  1~16



/*/蜂鸣器函数  
#define Beep_ON   Beep=0;
#define Beep_OFF  Beep=1;
*/
//遥控函数	
/***********
162 098 226	  对用遥控器键值
034 002 194
224 168 144
104 152 176
048 024 122
016 056 090
066 074 082  
************/ 
//#define Key_stop 162     //用户自定义停止按钮，(参考键值）

//EEPROM函数
extern u16 EEPROM_Read(u8 ReadAddr);  //在AT24C02指定地址读出一个16位的数据 				  地址参数： 0~127
extern void EEPROM_Write(u8 WriteAddr,u16 DataToWrite);//在AT24C02指定地址写入一个16位数据	  地址参数：0~127
	


//测距传感器
extern u16 distance(u8 channel);
#define  Close  2000
#define  Mid   1000
#define  Far    500


//颜色传感器
//#define White_and_Green 100
//#define White  1
//#define Green  2 
//extern u8 TCS230_Distinguish(void);//物体颜色判别 返回（White 或Green）
//extern void showRGB(void); //显示RGB数值

//指南针函数
void cal_on(void);	//校准
void CMP_OFFS(void);  //修改指南针磁偏角值
void cal_off(void);	//关闭校准
u16 read_cmp(void);	 //获取角度值
void recovery_factory(void);//恢复出厂设置



#endif	   
















