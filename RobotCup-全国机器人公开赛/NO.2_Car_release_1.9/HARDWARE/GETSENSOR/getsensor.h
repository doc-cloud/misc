#ifndef __GETSENSOR_H
#define __GETSENSOR_H	 
#include "sys.h"

#define  N   50	     //每通道采50次
#define  M  16	     //为16个通道


/*-------------端口定义----------------*/

/*-------------数字端口----------------*/
#define D1 digtal(1)
#define D2 digtal(2)
#define D3 digtal(3)
#define D4 digtal(4)
#define D5 digtal(5)
#define D6 digtal(6)
#define D7 digtal(7)
#define D8 digtal(8)
#define D9 digtal(9)
#define D10 digtal(10)
#define D11 digtal(11)
#define D12 digtal(12)
#define D13 digtal(13)
#define D14 digtal(14)
#define D15 digtal(15)
#define D16 digtal(16)
#define D17 digtal(17)
#define D18 digtal(18)
#define D19 digtal(19)
#define D20 digtal(20)
#define D21 digtal(21)
#define D22 digtal(22)

/*--------------模拟端口---------------*/
#define A1 analog(1)
#define A2 analog(2)
#define A3 analog(3)
#define A4 analog(4)
#define A5 analog(5)
#define A6 analog(6)
#define A7 analog(7)
#define A8 analog(8)
#define A9 analog(9)
#define A10 analog(10)
#define A11 analog(11)
#define A12 analog(12)
#define A13 analog(13)
#define A14 analog(14)
#define A15 analog(15)
#define A16 analog(16)

void Sensor_Init(void);		//端口初始化
u8 digtal(u8 channel);  	//获取X通道数字值（0，1）		  1~22						  
u16 analog(u8 channel);  //获取X通道AD值（0~1023）		  1~16
	 				    
#endif
