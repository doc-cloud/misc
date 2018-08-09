//#include <stm32f10x_lib.h>	   
#include "led.h"
	   
//初始化PE2、PE3为输出口.并使能PE口的时钟	
	    
void LED_Init(void)	       //LED初始化函数
{	 		  	 
	GPIOE->CRL&=0XFFFFF0FF; 
	GPIOE->CRL|=0X00000300;//PE2 推挽输出   	 
    GPIOE->ODR|=1<<2;      //PE2 输出高  
	
	GPIOE->CRL&=0XFFFF0FFF; 
	GPIOE->CRL|=0X00003000;//PE3 推挽输出   	 
    GPIOE->ODR|=1<<3;      //PE3 输出高											 
}

