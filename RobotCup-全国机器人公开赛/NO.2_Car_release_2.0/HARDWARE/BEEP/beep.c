#include <stm32f10x_lib.h>	   
#include "beep.h"
	   
//初始化PD2输出口.并使能PD口的时钟	
	    

void Beep_Init(void)
{
//	RCC->APB2ENR|=1<<5;    //使能PORTD时钟	 	 	
	  	 
	GPIOD->CRL&=0XFFFFF0FF; 
	GPIOD->CRL|=0X00000300;//PD2 推挽输出   	 
    GPIOD->ODR|=1<<2;      //PD2 输出高											 
}

