#include <stm32f10x_lib.h>	   
#include "beep.h"
	   
//��ʼ��PD2�����.��ʹ��PD�ڵ�ʱ��	
	    

void Beep_Init(void)
{
//	RCC->APB2ENR|=1<<5;    //ʹ��PORTDʱ��	 	 	
	  	 
	GPIOD->CRL&=0XFFFFF0FF; 
	GPIOD->CRL|=0X00000300;//PD2 �������   	 
    GPIOD->ODR|=1<<2;      //PD2 �����											 
}

