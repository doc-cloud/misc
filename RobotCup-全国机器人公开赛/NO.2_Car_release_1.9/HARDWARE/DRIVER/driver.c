#include <stm32f10x_lib.h>	   
#include "driver.h"	   
#include "sys.h"

/*
**函数功能：舵机初始化配置
*/
void servo_Configuration(void)
{
	//**********舵机驱动设置************// 
 	TIM_OCInitTypeDef  TIM_OCInitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure ;
	GPIO_InitTypeDef GPIO_InitStructure;
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 | RCC_APB2Periph_GPIOE  | RCC_APB2Periph_AFIO, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟 	
	TIM_DeInit(TIM1);//初始化TIM1寄存器
 	
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE); //Timer1完全重映射  TIM1_CH1->PE9 CH2->PE11 CH1->PE13 CH1->PE14 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_14; //TIM1_CH1	 //设置该引脚为复用输出功能,输出TIM1 CH1的PWM脉冲波形	GPIOE.9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIO

	                   
//**************************************************************************
//     定时器1设置： 720分频，频率1/20ms，向上计数
//**************************************************************************	 
    TIM_TimeBaseStructure.TIM_Period = 16000;
    TIM_TimeBaseStructure.TIM_Prescaler = 71;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

// 主定时器T1为 PWM1 模式 
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;  
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

    TIM_OC1Init(TIM1, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);//使能的预装载寄存器

	TIM_OCInitStructure.TIM_Pulse = 0; 
    TIM_OC2Init(TIM1, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);//使能的预装载寄存器

	TIM_OCInitStructure.TIM_Pulse = 0; 
    TIM_OC3Init(TIM1, &TIM_OCInitStructure);
    TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);//使能的预装载寄存器

	TIM_OCInitStructure.TIM_Pulse = 0; 
    TIM_OC4Init(TIM1, &TIM_OCInitStructure);
    TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);//使能的预装载寄存器
      
    TIM_ARRPreloadConfig(TIM1, ENABLE);	//使能定时器1
    TIM_Cmd(TIM1, ENABLE);

//******************************************************************************
//  IO口设置
//******************************************************************************
	TIM1->BDTR|=0x8000;  //使能定时器1输出
}

/*
**函数功能：电机驱动配置初始化函数
**配置情况：TIM4通道1、2
**使用端口：GPIOB.3		GPIOD.7
*/
//void speed_Configuration(void)	 //定时器4的1、2通道
//{	 
////**********电机驱动设置************//
//    TIM_OCInitTypeDef  TIM_OCInitStructure;
//    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure ;
//	GPIO_InitTypeDef GPIO_InitStructure;
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//打开TIM4外设时钟                     
////**************************************************************************
////     定时器1设置： 72分频，频率1KHz，向上计数
////**************************************************************************	 
//    TIM_TimeBaseStructure.TIM_Period = 1000;
//    TIM_TimeBaseStructure.TIM_Prescaler = 71;
//    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
//    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
//    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

//// 主定时器T4为 PWM1 模式 
//    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
//    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//    TIM_OCInitStructure.TIM_Pulse = 0;  
//    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
//    TIM_OC1Init(TIM4, &TIM_OCInitStructure);
//    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);//使能的预装载寄存器
//    
//    TIM_OCInitStructure.TIM_Pulse = 0; 
//    TIM_OC2Init(TIM4, &TIM_OCInitStructure); 
//    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);//使能的预装载寄存器
//    
//    TIM_ARRPreloadConfig(TIM4, ENABLE);	//使能定时器1
//    TIM_Cmd(TIM4, ENABLE);

////******************************************************************************
////  IO口设置
////******************************************************************************
// 
////	RCC->APB2ENR|=1<<3;    //使能PORTB时钟
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 ;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(GPIOB, &GPIO_InitStructure); 

//	GPIOD->CRL&=0X0FFFFFFF; //PD7 推挽输出 
//	GPIOD->CRL|=0X30000000;
//	GPIOD->ODR|=1<<7;  
//	
//	GPIOB->CRL&=0XFFFF0FFF; //PB3 推挽输出
//	GPIOB->CRL|=0X00003000;
//	GPIOB->ODR|=1<<7;
// }

void speed_Configuration(void)	 //定时器4的1、2通道
{	 
//**********电机驱动设置************//
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure ;
	GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//打开TIM4外设时钟                     
//**************************************************************************
//     定时器1设置： 72分频，频率1KHz，向上计数
//**************************************************************************	 
    TIM_TimeBaseStructure.TIM_Period = 1000;
    TIM_TimeBaseStructure.TIM_Prescaler = 71;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

// 主定时器T4为 PWM1 模式 
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;  
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM4, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);//使能的预装载寄存器
    
    TIM_OCInitStructure.TIM_Pulse = 0; 
    TIM_OC2Init(TIM4, &TIM_OCInitStructure); 
    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);//使能的预装载寄存器

	TIM_OCInitStructure.TIM_Pulse = 0; 
    TIM_OC3Init(TIM4, &TIM_OCInitStructure); 
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);//使能的预装载寄存器

    TIM_OCInitStructure.TIM_Pulse = 0; 
    TIM_OC4Init(TIM4, &TIM_OCInitStructure); 
    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);//使能的预装载寄存器
    
    TIM_ARRPreloadConfig(TIM4, ENABLE);	//使能定时器1
    TIM_Cmd(TIM4, ENABLE);

//******************************************************************************
//  IO口设置
//******************************************************************************
 
//	RCC->APB2ENR|=1<<3;    //使能PORTB时钟
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure); 


	GPIOD->CRL&=0X0FFFFFFF; //PD7 推挽输出 
	GPIOD->CRL|=0X30000000;
	GPIOD->ODR|=1<<7;  
	
	GPIOB->CRL&=0XFFFF0FFF; //PB3 推挽输出
	GPIOB->CRL|=0X00003000;
	GPIOB->ODR|=1<<3;

	GPIOE->CRL&=0XFFFFFFF0; //PE0 推挽输出
	GPIOE->CRL|=0X00000003;
	GPIOE->ODR|=1;

	GPIOE->CRL&=0XFFFFFF0F; //PE1 推挽输出
	GPIOE->CRL|=0X00000030;
	GPIOE->ODR|=1<<1;
 }

/*
**函数功能：电机驱动函数
**参数：pwm1---电机驱动pwm值，对应GPIOD.7口
**		pwm2---电机驱动pwm值，对应GPIOB.3口
**pwm取值：-100~100
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
**函数功能：舵机1驱动函数
**参数：	pwm---舵机转向角度
**pwm取值：	-90~90度
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
**函数功能：舵机2驱动函数
**参数：	pwm---舵机转向角度
**pwm取值：	-90~90度
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
**函数功能：舵机3驱动函数
**参数：	pwm---舵机转向角度
**pwm取值：	-90~90度
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
**函数功能：舵机4驱动函数
**参数：	pwm---舵机转向角度
**pwm取值：	-90~90度
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
