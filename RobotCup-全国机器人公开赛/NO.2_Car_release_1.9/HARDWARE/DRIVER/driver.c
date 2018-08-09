#include <stm32f10x_lib.h>	   
#include "driver.h"	   
#include "sys.h"

/*
**�������ܣ������ʼ������
*/
void servo_Configuration(void)
{
	//**********�����������************// 
 	TIM_OCInitTypeDef  TIM_OCInitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure ;
	GPIO_InitTypeDef GPIO_InitStructure;
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 | RCC_APB2Periph_GPIOE  | RCC_APB2Periph_AFIO, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ�� 	
	TIM_DeInit(TIM1);//��ʼ��TIM1�Ĵ���
 	
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE); //Timer1��ȫ��ӳ��  TIM1_CH1->PE9 CH2->PE11 CH1->PE13 CH1->PE14 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_14; //TIM1_CH1	 //���ø�����Ϊ�����������,���TIM1 CH1��PWM���岨��	GPIOE.9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIO

	                   
//**************************************************************************
//     ��ʱ��1���ã� 720��Ƶ��Ƶ��1/20ms�����ϼ���
//**************************************************************************	 
    TIM_TimeBaseStructure.TIM_Period = 16000;
    TIM_TimeBaseStructure.TIM_Prescaler = 71;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

// ����ʱ��T1Ϊ PWM1 ģʽ 
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;  
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

    TIM_OC1Init(TIM1, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);//ʹ�ܵ�Ԥװ�ؼĴ���

	TIM_OCInitStructure.TIM_Pulse = 0; 
    TIM_OC2Init(TIM1, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);//ʹ�ܵ�Ԥװ�ؼĴ���

	TIM_OCInitStructure.TIM_Pulse = 0; 
    TIM_OC3Init(TIM1, &TIM_OCInitStructure);
    TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);//ʹ�ܵ�Ԥװ�ؼĴ���

	TIM_OCInitStructure.TIM_Pulse = 0; 
    TIM_OC4Init(TIM1, &TIM_OCInitStructure);
    TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);//ʹ�ܵ�Ԥװ�ؼĴ���
      
    TIM_ARRPreloadConfig(TIM1, ENABLE);	//ʹ�ܶ�ʱ��1
    TIM_Cmd(TIM1, ENABLE);

//******************************************************************************
//  IO������
//******************************************************************************
	TIM1->BDTR|=0x8000;  //ʹ�ܶ�ʱ��1���
}

/*
**�������ܣ�����������ó�ʼ������
**���������TIM4ͨ��1��2
**ʹ�ö˿ڣ�GPIOB.3		GPIOD.7
*/
//void speed_Configuration(void)	 //��ʱ��4��1��2ͨ��
//{	 
////**********�����������************//
//    TIM_OCInitTypeDef  TIM_OCInitStructure;
//    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure ;
//	GPIO_InitTypeDef GPIO_InitStructure;
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//��TIM4����ʱ��                     
////**************************************************************************
////     ��ʱ��1���ã� 72��Ƶ��Ƶ��1KHz�����ϼ���
////**************************************************************************	 
//    TIM_TimeBaseStructure.TIM_Period = 1000;
//    TIM_TimeBaseStructure.TIM_Prescaler = 71;
//    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
//    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
//    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

//// ����ʱ��T4Ϊ PWM1 ģʽ 
//    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
//    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//    TIM_OCInitStructure.TIM_Pulse = 0;  
//    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
//    TIM_OC1Init(TIM4, &TIM_OCInitStructure);
//    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);//ʹ�ܵ�Ԥװ�ؼĴ���
//    
//    TIM_OCInitStructure.TIM_Pulse = 0; 
//    TIM_OC2Init(TIM4, &TIM_OCInitStructure); 
//    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);//ʹ�ܵ�Ԥװ�ؼĴ���
//    
//    TIM_ARRPreloadConfig(TIM4, ENABLE);	//ʹ�ܶ�ʱ��1
//    TIM_Cmd(TIM4, ENABLE);

////******************************************************************************
////  IO������
////******************************************************************************
// 
////	RCC->APB2ENR|=1<<3;    //ʹ��PORTBʱ��
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 ;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(GPIOB, &GPIO_InitStructure); 

//	GPIOD->CRL&=0X0FFFFFFF; //PD7 ������� 
//	GPIOD->CRL|=0X30000000;
//	GPIOD->ODR|=1<<7;  
//	
//	GPIOB->CRL&=0XFFFF0FFF; //PB3 �������
//	GPIOB->CRL|=0X00003000;
//	GPIOB->ODR|=1<<7;
// }

void speed_Configuration(void)	 //��ʱ��4��1��2ͨ��
{	 
//**********�����������************//
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure ;
	GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//��TIM4����ʱ��                     
//**************************************************************************
//     ��ʱ��1���ã� 72��Ƶ��Ƶ��1KHz�����ϼ���
//**************************************************************************	 
    TIM_TimeBaseStructure.TIM_Period = 1000;
    TIM_TimeBaseStructure.TIM_Prescaler = 71;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

// ����ʱ��T4Ϊ PWM1 ģʽ 
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;  
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM4, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);//ʹ�ܵ�Ԥװ�ؼĴ���
    
    TIM_OCInitStructure.TIM_Pulse = 0; 
    TIM_OC2Init(TIM4, &TIM_OCInitStructure); 
    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);//ʹ�ܵ�Ԥװ�ؼĴ���

	TIM_OCInitStructure.TIM_Pulse = 0; 
    TIM_OC3Init(TIM4, &TIM_OCInitStructure); 
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);//ʹ�ܵ�Ԥװ�ؼĴ���

    TIM_OCInitStructure.TIM_Pulse = 0; 
    TIM_OC4Init(TIM4, &TIM_OCInitStructure); 
    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);//ʹ�ܵ�Ԥװ�ؼĴ���
    
    TIM_ARRPreloadConfig(TIM4, ENABLE);	//ʹ�ܶ�ʱ��1
    TIM_Cmd(TIM4, ENABLE);

//******************************************************************************
//  IO������
//******************************************************************************
 
//	RCC->APB2ENR|=1<<3;    //ʹ��PORTBʱ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure); 


	GPIOD->CRL&=0X0FFFFFFF; //PD7 ������� 
	GPIOD->CRL|=0X30000000;
	GPIOD->ODR|=1<<7;  
	
	GPIOB->CRL&=0XFFFF0FFF; //PB3 �������
	GPIOB->CRL|=0X00003000;
	GPIOB->ODR|=1<<3;

	GPIOE->CRL&=0XFFFFFFF0; //PE0 �������
	GPIOE->CRL|=0X00000003;
	GPIOE->ODR|=1;

	GPIOE->CRL&=0XFFFFFF0F; //PE1 �������
	GPIOE->CRL|=0X00000030;
	GPIOE->ODR|=1<<1;
 }

/*
**�������ܣ������������
**������pwm1---�������pwmֵ����ӦGPIOD.7��
**		pwm2---�������pwmֵ����ӦGPIOB.3��
**pwmȡֵ��-100~100
*/
//void speed(int pwm1, int pwm2)
// {
// 	if (pwm1 > 0)
//	{
// 		TIM4->CCR1 =  pwm1 * 10;	 //PD7
//		PDout(7) = 0;
//	}
//	else if (pwm1 <= 0)
//	{
//		TIM4->CCR1 =  (-pwm1) * 10;	 //PD7
//		PDout(7) = 1;
//	}
//	if (pwm2 > 0)
//	{
//		TIM4->CCR2 =  pwm2 * 10;	 //PB3
//		PBout(3) = 0;
//	}
//	else if (pwm2 <= 0)
//	{
//		TIM4->CCR2 = (-pwm2) * 10;	 //PB3
//		PBout(3) = 1;
//	}
//}

void speed_24(int pwm1, int pwm2,int pwm3, int pwm4)
 {
 	if (pwm1 > 0)
	{
 		TIM4->CCR1 =  pwm1 * 10;	 //PD7
		PDout(7) = 0;
	}
	else if (pwm1 <= 0)
	{
		TIM4->CCR1 =  (-pwm1) * 10;	 //PD7
		PDout(7) = 1;
	}

	if (pwm2 > 0)
	{
		TIM4->CCR2 =  pwm2 * 10;	 //PB3
//		PBout(3) = 0;
		PBout(3) = 0;
	}
	else if (pwm2 <= 0)
	{
		TIM4->CCR2 = (-pwm2) * 10;	 //PB3
		PBout(3) = 1;
//		PBout(3) = 0;
	}

		if (pwm3 > 0)
	{
		TIM4->CCR3 =  pwm3 * 10;	 //PB3
		PEout(0) = 0;
	}
	else if (pwm3 <= 0)
	{
		TIM4->CCR3 = (-pwm3) * 10;	 //PB3
		PEout(0) = 1;
	}

		if (pwm4 > 0)
	{
		TIM4->CCR4 =  pwm4 * 10;	 //PB3
		PEout(1) = 1;
//		PEout(1) = 0;
	}
	else if (pwm4 <= 0)
	{
		TIM4->CCR4 = (-pwm4) * 10;	 //PB3
//		PEout(1) = 1;
		PEout(1) = 0;
	}
}
 
 
void speed(int pwm2, int pwm1)
 {
 	if (pwm1 > 0)
	{
		TIM4->CCR2 =  (pwm1) * 10;	 //PD7
		TIM4->CCR1 = 0;
//		PDout(7) = 1;
	}
	else if (pwm1 <= 0)
	{

		 	TIM4->CCR1 =  (-pwm1) * 10;	 //PD7
//		PDout(7) = 0;
		TIM4->CCR2 = 0;
	}

	if (pwm2 > 0)
	{
		TIM4->CCR3 =  pwm2 * 10;	 //PB3
		TIM4->CCR4 = 0;
//		PBout(3) = 0;
//		PBout(3) = 1;
	}
	else if (pwm2 <= 0)
	{
		TIM4->CCR4 = (-pwm2) * 10;	 //PB3
		TIM4->CCR3 = 0;
//		PBout(3) = 0;
//		PBout(3) = 0;
	}


}

/*
**�������ܣ����1��������
**������	pwm---���ת��Ƕ�
**pwmȡֵ��	-90~90��
*/
void servo1(int pwm)
{
	if (pwm > 0)
	{
		TIM1->CCR1 = 1500 + (pwm*80 / 9);
	}
	else if (pwm == 0)
	{
		TIM1->CCR1 =  1500;
	}
	else 
	{
		TIM1->CCR1 = 1500 + (pwm*80 / 9);
	}

} 

/*
**�������ܣ����2��������
**������	pwm---���ת��Ƕ�
**pwmȡֵ��	-90~90��
*/
void servo2(int pwm)
{
	if (pwm > 0)
	{
		TIM1->CCR2 = 1500 + (pwm*80 / 9);
	}
	else if (pwm == 0)
	{
		TIM1->CCR2 =  1500;
	}
	else 
	{
		TIM1->CCR2 = 1500 + (pwm*80 / 9);
	}
} 

/*
**�������ܣ����3��������
**������	pwm---���ת��Ƕ�
**pwmȡֵ��	-90~90��
*/
void servo3(int pwm)
{
	if (pwm > 0)
	{
		TIM1->CCR3 = 1500 + (pwm*80 / 9);
	}
	else if (pwm == 0)
	{
		TIM1->CCR3 =  1500;
	}
	else 
	{
		TIM1->CCR3 = 1500 + (pwm*80 / 9);
	}

} 

/*
**�������ܣ����4��������
**������	pwm---���ת��Ƕ�
**pwmȡֵ��	-90~90��
*/
void servo4(int pwm)
{
	if (pwm > 0)
	{
		TIM1->CCR4 = 1500 + (pwm*80 / 9);
	}
	else if (pwm == 0)
	{
		TIM1->CCR4 =  1500;
	}
	else 
	{
		TIM1->CCR4 = 1500 + (pwm*80 / 9);
	}

} 

void DMotor_Control_Par(int pwm2 , int pwm1)
{
//	speed((-pwm2), (-pwm1));
		speed_24(pwm1, pwm2,0,0);
}
