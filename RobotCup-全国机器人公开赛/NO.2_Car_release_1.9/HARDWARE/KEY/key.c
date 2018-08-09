#include <stm32f10x_lib.h>	   
#include "key.h"
	   	
/*
**函数功能：按键端口初始化
**所用GPIO口：GPIOD.0、1口
**			  GPIOC.10、11、12口
**端口模式：上拉输入模式
**与控制板对应按键：
**		S1			S2			S3			S4			S5
**	  GPIOD0	  GPIOC12	  GPIOC11	  GPIOC10	  GPIOD1
**	   菜单		 确认/取消	   加上        减去		   启动
*/	    
void Key_Init(void)	       
{	 		  	 
	GPIOD->CRL&=0XFFFFFF00; 
	GPIOD->CRL|=0X00000088; 
    GPIOD->ODR|=1<<0; 
	GPIOD->ODR|=1<<1;      
	
	GPIOC->CRH&=0XFFF000FF; 
	GPIOC->CRH|=0X00088800;	 
    GPIOC->ODR|=1<<10;  
	GPIOC->ODR|=1<<11;
	GPIOC->ODR|=1<<12;    											 
}



