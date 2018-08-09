//#include <stm32f10x_lib.h>	   
//#include "colour.h"

//u32 Colour_num=0;	 // 用于颜色传感器脉冲计数
//u8  Time3_flag=0;    // 定时器中断标志	
//u16 r=0,g=0,b=0;   

//		 
///*==============================以下为定时器3程序部分=================================*/
///*定时器3中断服务函数*/
////void TIM3_IRQHandler(void)
////{ 
////  if(TIM3->SR&0X0001)//溢出中断
////   {
////	 Time3_flag=1;
////	 EXTI->IMR&=~(1<<12);	 //关闭外部中断6
////	 TIM3->CR1&=0Xfe;	//关闭定时器3
////   }
////   TIM3->SR&=~(1<<0);//清除中断标志位 
////}

///**********************************************
//函数名称：Timer3_Init
//函数功能：通用定时器3中断初始化
//入口函数：arr（自动重装值）
//          psc(时钟预分频数)
//返回参数：无
//备注：时钟为2倍APB1(36M)
//溢出时间（MS)=(arr*(psc+1))/输入时钟频率(10KHZ) 

//***********************************************/
//void Timer3_Init(u16 arr,u16 psc)
//{
//     RCC->APB1ENR|=1<<1;//使能TIM3时钟
//     TIM3->ARR=arr;//设置计数器自动重装值(0.1ms)
//     TIM3->PSC=psc;//预分频器7200，刚好10khz
//     TIM3->DIER|=1<<0; //允许更新中断
//     TIM3->DIER|=1<<6; //允许触发中断
//     TIM3->CR1|=0X01;	//使能定时器3
//     MY_NVIC_Init(1,1,TIM3_IRQChannel,2);// 抢占1，子优先级1，组2
//}
////////////////////////////////////////////////////////////////////////////////////

///*=============================以下为外部中断0程序部分=================================*/
///********************************
//函数名称：EXTI0_Init
//函数功能：外部中断端口初始化
//入口参数：无
//返回参数：无
//备注：初始化PC6为中断输入
//********************************/
//void EXTI6_Init(void)
//{
//	 JTAG_Set(JTAG_SWD_DISABLE);
////     GPIOC->CRL&=0XF0FFFFFF;//PC6设置成输入
////     GPIOC->CRL|=0X08000000;
//		 GPIOD->CRH&=0XFFFFFFF0;
//		 GPIOD->CRH|=0X00000008;
//     Ex_NVIC_Config(GPIO_D,8,FTIR);//下降沿触发
//     MY_NVIC_Init(2,2,EXTI15_10_IRQChannel,2);//抢占2，子优先级2，组2
//}

///*外部中断0服务程序*/
////void EXTI15_10_IRQHandler(void)
////{
////	Colour_num++;
////    EXTI->PR = 1<<12; //清除line6上的中断标志位
////}


/////////////////////////////////////////////////////////////////////////////////////

///**********************************************************
// 函数名称：TCS230_Init
// 函数功能：TCS230初始化
// 入口参数：无
// 返回参数：无
// 备    注：初始化外部中断0及定时器中断3及相关I/O口设置
//**********************************************************/ 
//void TCS230_Init(void)
//{
//	GPIOB->CRH&=0XF00FFFFF; 
//	GPIOB->CRH|=0X03300000; 	 
//    GPIOA->ODR|=1<<11;
////	GPIOA->ODR|=1<<12;
//	GPIOB->ODR|=1<<13;
//	GPIOB->ODR|=1<<14;
////	GPIOA->ODR|=1<<15;      
//	
//	GPIOB->CRL&=0X000F0000; 
//	GPIOB->CRL|=0X00030000; 	 
//  GPIOB->ODR|=1<<12;

////	TCS32_S1 = 1;	 //最高频率输出	   二个为低 就是关灯
////	TCS32_S0 = 1;
////	TCS32_EO = 0;

//	Timer3_Init(400,7199); //40ms
//	EXTI6_Init();
//}

///***********************************************
// 函数名称：Colour_Init
// 函数功能：TCS230内部颜色滤波器设置
// 入口参数：Colour
// 返回参数：无
// 备    注：Colour 选择颜色（Red1/Blue1/Green1）
//		TCS32_S2=0		TCS32_S3=0 
//			0				0		选择红色滤光器
//			0				1		选择蓝色滤光器
//			1				1		选择绿色滤光器		
//************************************************/ 
//void Colour_Init(u8 Colour)
//{
//	switch(Colour)
//	 {
//	 	case Red1  : TCS32_S2=0;TCS32_S3=0;break;
//		case Blue1 : TCS32_S2=0;TCS32_S3=1;break;
//		case Green1: TCS32_S2=1;TCS32_S3=1;break;
//		default    : break;
//	 }
//}

///**********************************************************
// 函数名称：TCS230_Start
// 函数功能：初始化各变量及定时器3、外部中断0，用于脉冲计数
// 入口参数：无
// 返回参数：无
//**********************************************************/ 
//void TCS230_Start(void)
//{		
//        TIM3->CR1|=0X01;	//使能定时器3
//		Colour_num=0;//	计数清零
//		Time3_flag=0; // 定时器标志清零
//	    EXTI->IMR|=1<<12;//开启外部中断6	
//}

///******************************************
// 函数名称：TCS230_Read_Colour
// 函数功能：设置颜色滤波器并读出相应频率参数
// 入口参数：Colour
// 返回参数：Colour num
// 备    注：Colour     ：颜色滤波器配置参数
//           Colour num ：脉冲个数
//******************************************/ 
//u32 TCS230_Read_Colour(u8 Colour)
//{
//	Colour_Init(Colour);//配置TCS230的颜色滤波器
//	delay_ms(5);
//	TCS230_Start();//初始化各变量及定时器3、外部中断6
//	while(Time3_flag==0);//等待计数完毕
//	return Colour_num;	// 返回计数个数
//}

///******************************************
// 函数名称：TCS230_Distinguish
// 函数功能：物体颜色判别
// 入口参数：无
// 返回参数：1/2
//******************************************/ 
//void TCS230_Distinguish(void)
//{
//	u8 i;
//	for(i=0;i<5;i++)   // 读取三次数据
//	{
//		r=r+TCS230_Read_Colour(Red1);
//		b=b+TCS230_Read_Colour(Blue1);
//		g=g+TCS230_Read_Colour(Green1);
//	}

//	r=r*255/10000;//取三次测量的平均值
//	b=b*255/10000;
//	g=g*255/10000;



////	if((r>White_and_Green && b>White_and_Green) 
////	|| (b>White_and_Green && g>White_and_Green) 
////	|| (r>White_and_Green && g>White_and_Green) 
////	|| (r>White_and_Green && b>White_and_Green && g>White_and_Green))
////		return White;
////	else 
////		return Green;
//}

///*
//**函数功能：将RGB值显示在12864液晶屏上
//*/
//void showRGB(void)
//{
//	display_num_add(20,0,r); 	   //
//	display_num_add(20,1,g); 	   //30	
//	display_num_add(20,2,b); 	   //30	
////	  display_num_add(20,0,TCS230_Read_Colour(Red1));
////	  display_num_add(20,1,TCS230_Read_Colour(Blue1));
////	  display_num_add(20,2,TCS230_Read_Colour(Green1));	
//}



//							 


#include <stm32f10x_lib.h>
#include "colour.h"
#include "sys.h"
#include "lcd5110.h"


u32 Colour_num=0;								  // 用于颜色传感器脉冲计数
u8  Time2_flag=0;                                 // 定时器中断标志

/*定时器3中断服务函数*/
//void TIM2_IRQHandler(void)
//{ 
//	if(TIM2->SR&(1 << 1))			//溢出中断
//	{
//	 Time2_flag=1;
//	 EXTI->IMR|=0<<8;				//关闭外部中断0
//	 TIM2->CR1|=0X00;				//关闭定时器3
//	}
//	TIM2->SR&=~(1<<1);				//清除中断标志位 
//}
/**********************************************
函数名称：Timer3_Init
函数功能：通用定时器3中断初始化
入口函数：arr（自动重装值）
          psc(时钟预分频数)
返回参数：无
备注：时钟为2倍APB1(36M)
溢出时间（MS)=(arr*(psc+1))/输入时钟频率(10KHZ) 
***********************************************/
void Timer2_Init(u16 arr,u16 psc)
{
//     RCC->APB1ENR|=1<<0;			//使能TIM3时钟
		 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
     TIM2->ARR=arr;					//设置计数器自动重装值(0.1ms)
     TIM2->PSC=psc;					//预分频器7200，刚好10khz
     TIM2->DIER|=1<<1; 				//允许更新中断
     TIM2->DIER|=1<<6; 				//允许触发中断
     TIM2->CR1|=0X01;				//使能定时器3
     MY_NVIC_Init(1,1,TIM2_IRQChannel,2);// 抢占1，子优先级1，组2
}
/********************************
函数名称：EXTI0_Init
函数功能：外部中断端口初始化
入口参数：无
返回参数：无
备注：初始化PA0为中断输入
********************************/
void EXTI5_Init(void)
{
     RCC->APB2ENR|=1<<2; 			    	//使能PORTA时钟
     GPIOD->CRH&=0XFFFFFFF0;			    //PA5设置成输入
     GPIOD->CRH|=0X00000008;
     Ex_NVIC_Config(GPIO_D,8,FTIR);		    //下降沿触发
     MY_NVIC_Init(2,2,EXTI9_5_IRQChannel,2);//抢占2，子优先级2，组2
}

/*外部中断0服务程序*/
//void EXTI9_5_IRQHandler(void)
//{
//	Colour_num++;
//    EXTI->PR = 1<<8;             //清除line0上的中断标志位
//	EXTI->IMR|=0<<8;             //关闭外部中断5
//	TIM2->CR1|=0X00;	         //关闭定时器2
//}
/**********************************************************
 函数名称：TCS230_Init
 函数功能：TCS230初始化
 入口参数：无
 返回参数：无
 备    注：初始化外部中断0及定时器中断3及相关I/O口设置
**********************************************************/ 
void TCS230_Init(void)
{
		//	GPIOB->CRH&=0XF00FFFFF; 
//	GPIOB->CRH|=0X03300000; 	 
//    GPIOA->ODR|=1<<11;
////	GPIOA->ODR|=1<<12;
//	GPIOB->ODR|=1<<13;
//	GPIOB->ODR|=1<<14;
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
//	RCC->APB2ENR|=1<<4;            //使能PORTA时钟	   	 
//	GPIOC->CRL&=0X00FFFFFF; 
//	GPIOC->CRL|=0X33000000;        //PC6/PC7 推挽输出 
		GPIOB->CRH&=0XF00FFFFF; 
	  GPIOB->CRH|=0X03300000; 
//	GPIOC->ODR|=1<<6;              //上拉
//	GPIOC->ODR|=1<<7; 
		GPIOB->ODR|=1<<13;
		GPIOB->ODR|=1<<14;
	Timer2_Init(400,7199);         //40ms
	EXTI5_Init();

}
/***********************************************
 函数名称：Colour_Init
 函数功能：TCS230内部颜色滤波器设置
 入口参数：Colour
 返回参数：无
 备    注：Colour 选择颜色（Red1/Blue1/Green1）
************************************************/ 
void Colour_Init(u8 Colour)
{
	switch(Colour)
	 {
	 	case Red1  : TCS32_S2=0;TCS32_S3=0;break;
		case Blue1 : TCS32_S2=0;TCS32_S3=1;break;
		case Green1: TCS32_S2=1;TCS32_S3=1;break;
		default    : break;
	 }
}
/**********************************************************
 函数名称：TCS230_Start
 函数功能：初始化各变量及定时器3、外部中断0，用于脉冲计数
 入口参数：无
 返回参数：无
**********************************************************/ 
void TCS230_Start(void)
{		
	TIM2->CR1|=0X01;	//使能定时器3
	Colour_num=0;		//	计数清零
	Time2_flag=0;		// 定时器标志清零
	EXTI->IMR|=1<<8;	//开启外部中断0	
}
/******************************************
 函数名称：TCS230_Read_Colour
 函数功能：设置颜色滤波器并读出相应频率参数
 入口参数：Colour
 返回参数：Colour num
 备    注：Colour     ：颜色滤波器配置参数
           Colour num ：脉冲个数
******************************************/ 
u32 TCS230_Read_Colour(u8 Colour)
{
	Colour_Init(Colour);       //配置TCS230的颜色滤波器
	delay_ms(5);
	TCS230_Start();            //初始化各变量及定时器3、外部中断0
	while(Time2_flag==0);      //等待计数完毕
	return Colour_num;	       // 返回计数个数
}
/******************************************
 函数名称：TCS230_Distinguish
 函数功能：物体颜色判别
 入口参数：无
 返回参数：0/1/2/3
 备    注：0:Red1
           1:Blue1
		   2:Green1
		   3:Yellow1
******************************************/ 
u8 TCS230_Distinguish(void)
{
	u8 i;
	float r=0.0,b=0.0,g=0.0;
	float k=1.4;          //比例系数
	for(i=0;i<3;i++)      // 读取三次数据
	{
		r=r+TCS230_Read_Colour(Red1);
		b=b+TCS230_Read_Colour(Blue1);
		g=g+TCS230_Read_Colour(Green1);
	}

	r=r/3;               //取三次测量的平均值
	b=b/3;
	g=g/3;
	if((r>1.25*b)&&(r>1.25*g))// 红色
	return Red1;
	if((g>1.15*b)&&(g>1.05*r))// 绿色
	return Green1; 
	if((b>1.35*r)&&(b>1.35*g))// 蓝色
	return Blue1;
	if((r>k*b)&&(g>k*b))      // 黄色
	return Yellow1;
	return 0;
}

////发光二极管
//void ColorSensor_init(void)
//{
//     RCC->APB2ENR|=1<<2; 			    	
//     GPIOA->CRL&=0XFFFF0000;			    
//     GPIOA->CRL|=0X00003333;
//}

//执行相应的功能
//void ColorSensor(void)
//{
//	u8 j;
//	j=TCS230_Distinguish();//得到相应颜色
//	switch(j)
//	{
//		case Red1   :
//					LED0=1;
//					LA=900;
//					LB=0;
//					RA=0;
//					RB=900;
//					delay_ms(800);
//					LED0=0; 
//					 
//				    break;
//		case Green1 :  
//					LED1=1;
//					LA=900;
//					LB=0;
//					RA=900;
//					RB=0;
//					delay_ms(800);
//					LED1=0;
//					delay_ms(200);
//					LED1=1;  
//					LA=900;
//					LB=0;
//					RA=0;
//					RB=900;
//					delay_ms(800);
//					LED1=0; 
//					 
//				    break;
//		case Blue1  :  
//					LED2=1;
//					LA=0;
//					LB=900;
//					RA=900;
//					RB=0;
//					delay_ms(800);
//					LED2=0; 
//					 
//				    break;
//		case Yellow1:  
//					LED3=1;
//					LA=900;
//					LB=0;
//					RA=900;
//					RB=0;
//					delay_ms(800);
//					LED3=0;
//					delay_ms(200);
//					LED3=1;  
//					LA=0;
//					LB=900;
//					RA=900;
//					RB=0;
//					delay_ms(800);
//					LED3=0;

//				    break;
//		default     : 
//					break;
//	}
//}

void showRGB()
{
	u16 r,g,b;
	r=TCS230_Read_Colour(Red1);
	b=TCS230_Read_Colour(Blue1);
	g=TCS230_Read_Colour(Green1);
	
	//	display_num_a(10,1,TCS230_Distinguish());
	
	
//	  show_string(4,2,"r");
//	  display_num_add(10,2,TCS230_Read_Colour(Red1));
//		show_string(4,3,"g");
//	  display_num_add(10,3,TCS230_Read_Colour(Blue1));
//	  show_string(4,4,"b");
//	  display_num_add(10,4,TCS230_Read_Colour(Green1));
	
		  show_string(4,2,"r");
	  display_num_add(10,2,r);
		show_string(4,3,"g");
	  display_num_add(10,3,g);
	  show_string(4,4,"b");
	  display_num_add(10,4,b);
	  
//	  		 if((r+5)>(b+g))		 
//		     show_string(10,5,"red");
//		 else if((b+8>r)&&(b+2>g))
//		     show_string(10,5,"blue");		
//		 else if((g-3<r)&&(g-15>b))
//		     show_string(10,5,"yellow");	  	
//		 else if((g+5>r)&&(g>b))
//		     show_string(10,5,"green");		   
//		 else if((b>r)&&(g>b))
//		     show_string(10,5,"white");
//		 else
//		     show_string(10,5,"unknown");
//		 delay_ms(100);



//	if((r>4000)&&(g>4000)&&((b-700)>4000))
//		show_string(10,5,"white");
//	else if((r<3000)&&(g<3000)&&((b-700)<3000))
//		show_string(10,5,"black");
//	else if((r>g)&&(r>(b-700)))
//		show_string(10,5,"red  ");
//	else if((g>r)&&(g>(b-700)))
//		show_string(10,5,"green");
//	else if(((b-800)>g)&&((b-700)>r))
//		show_string(10,5,"blue ");


	if((r>4000)&&(g>4000)&&((b-700)>4000))/////////////////////////////////////////////////////hps  08.20
		show_string(10,5,"white");
	else if((r<2600)&&(g<2600)&&((b-700)<2600))
		show_string(10,5,"black");
	else if((r>g)&&(r>(b-700)))
		show_string(10,5,"red  ");
	else if((g>r)&&(g>(b-700)))
		show_string(10,5,"green");
	else if(((b-800)>g)&&((b-700)>r))
		show_string(10,5,"blue ");

}






