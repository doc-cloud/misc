#include <stm32f10x_lib.h>	   
#include "distance.h"

	   	
/*
**�������ܣ���ȡ15��16ͨ��ģ��ֵ
**����	  ��channel---ѡ��ֵ
**����ȡֵ��	0��1
**������  �������ഫ����
*/	    
u16 distance(u8 channel)	      
{
	if(channel == 15)
		return analog(15);  //��ȡXͨ��ADֵ��0~1023��		  1~16	
	else
		return analog(16);  //��ȡXͨ��ADֵ��0~1023��		  1~16											 
}

