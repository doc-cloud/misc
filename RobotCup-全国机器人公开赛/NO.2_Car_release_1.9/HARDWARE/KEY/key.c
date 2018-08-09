#include <stm32f10x_lib.h>	   
#include "key.h"
	   	
/*
**�������ܣ������˿ڳ�ʼ��
**����GPIO�ڣ�GPIOD.0��1��
**			  GPIOC.10��11��12��
**�˿�ģʽ����������ģʽ
**����ư��Ӧ������
**		S1			S2			S3			S4			S5
**	  GPIOD0	  GPIOC12	  GPIOC11	  GPIOC10	  GPIOD1
**	   �˵�		 ȷ��/ȡ��	   ����        ��ȥ		   ����
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



