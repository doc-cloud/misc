#include <stm32f10x_lib.h>	   
#include "distance.h"

	   	
/*
**函数功能：获取15、16通道模拟值
**参数	  ：channel---选择值
**参数取值：	0、1
**传感器  ：红外测距传感器
*/	    
u16 distance(u8 channel)	      
{
	if(channel == 15)
		return analog(15);  //获取X通道AD值（0~1023）		  1~16	
	else
		return analog(16);  //获取X通道AD值（0~1023）		  1~16											 
}

