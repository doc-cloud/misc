//#include <stm32f10x_lib.h>	   
#include "led.h"
	   
//��ʼ��PE2��PE3Ϊ�����.��ʹ��PE�ڵ�ʱ��	
	    
void LED_Init(void)	       //LED��ʼ������
{	 		  	 
	GPIOE->CRL&=0XFFFFF0FF; 
	GPIOE->CRL|=0X00000300;//PE2 �������   	 
    GPIOE->ODR|=1<<2;      //PE2 �����  
	
	GPIOE->CRL&=0XFFFF0FFF; 
	GPIOE->CRL|=0X00003000;//PE3 �������   	 
    GPIOE->ODR|=1<<3;      //PE3 �����											 
}

