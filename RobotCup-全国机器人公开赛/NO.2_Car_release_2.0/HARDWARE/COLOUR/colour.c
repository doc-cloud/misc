//#include <stm32f10x_lib.h>	   
//#include "colour.h"

//u32 Colour_num=0;	 // ������ɫ�������������
//u8  Time3_flag=0;    // ��ʱ���жϱ�־	
//u16 r=0,g=0,b=0;   

//		 
///*==============================����Ϊ��ʱ��3���򲿷�=================================*/
///*��ʱ��3�жϷ�����*/
////void TIM3_IRQHandler(void)
////{ 
////  if(TIM3->SR&0X0001)//����ж�
////   {
////	 Time3_flag=1;
////	 EXTI->IMR&=~(1<<12);	 //�ر��ⲿ�ж�6
////	 TIM3->CR1&=0Xfe;	//�رն�ʱ��3
////   }
////   TIM3->SR&=~(1<<0);//����жϱ�־λ 
////}

///**********************************************
//�������ƣ�Timer3_Init
//�������ܣ�ͨ�ö�ʱ��3�жϳ�ʼ��
//��ں�����arr���Զ���װֵ��
//          psc(ʱ��Ԥ��Ƶ��)
//���ز�������
//��ע��ʱ��Ϊ2��APB1(36M)
//���ʱ�䣨MS)=(arr*(psc+1))/����ʱ��Ƶ��(10KHZ) 

//***********************************************/
//void Timer3_Init(u16 arr,u16 psc)
//{
//     RCC->APB1ENR|=1<<1;//ʹ��TIM3ʱ��
//     TIM3->ARR=arr;//���ü������Զ���װֵ(0.1ms)
//     TIM3->PSC=psc;//Ԥ��Ƶ��7200���պ�10khz
//     TIM3->DIER|=1<<0; //��������ж�
//     TIM3->DIER|=1<<6; //�������ж�
//     TIM3->CR1|=0X01;	//ʹ�ܶ�ʱ��3
//     MY_NVIC_Init(1,1,TIM3_IRQChannel,2);// ��ռ1�������ȼ�1����2
//}
////////////////////////////////////////////////////////////////////////////////////

///*=============================����Ϊ�ⲿ�ж�0���򲿷�=================================*/
///********************************
//�������ƣ�EXTI0_Init
//�������ܣ��ⲿ�ж϶˿ڳ�ʼ��
//��ڲ�������
//���ز�������
//��ע����ʼ��PC6Ϊ�ж�����
//********************************/
//void EXTI6_Init(void)
//{
//	 JTAG_Set(JTAG_SWD_DISABLE);
////     GPIOC->CRL&=0XF0FFFFFF;//PC6���ó�����
////     GPIOC->CRL|=0X08000000;
//		 GPIOD->CRH&=0XFFFFFFF0;
//		 GPIOD->CRH|=0X00000008;
//     Ex_NVIC_Config(GPIO_D,8,FTIR);//�½��ش���
//     MY_NVIC_Init(2,2,EXTI15_10_IRQChannel,2);//��ռ2�������ȼ�2����2
//}

///*�ⲿ�ж�0�������*/
////void EXTI15_10_IRQHandler(void)
////{
////	Colour_num++;
////    EXTI->PR = 1<<12; //���line6�ϵ��жϱ�־λ
////}


/////////////////////////////////////////////////////////////////////////////////////

///**********************************************************
// �������ƣ�TCS230_Init
// �������ܣ�TCS230��ʼ��
// ��ڲ�������
// ���ز�������
// ��    ע����ʼ���ⲿ�ж�0����ʱ���ж�3�����I/O������
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

////	TCS32_S1 = 1;	 //���Ƶ�����	   ����Ϊ�� ���ǹص�
////	TCS32_S0 = 1;
////	TCS32_EO = 0;

//	Timer3_Init(400,7199); //40ms
//	EXTI6_Init();
//}

///***********************************************
// �������ƣ�Colour_Init
// �������ܣ�TCS230�ڲ���ɫ�˲�������
// ��ڲ�����Colour
// ���ز�������
// ��    ע��Colour ѡ����ɫ��Red1/Blue1/Green1��
//		TCS32_S2=0		TCS32_S3=0 
//			0				0		ѡ���ɫ�˹���
//			0				1		ѡ����ɫ�˹���
//			1				1		ѡ����ɫ�˹���		
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
// �������ƣ�TCS230_Start
// �������ܣ���ʼ������������ʱ��3���ⲿ�ж�0�������������
// ��ڲ�������
// ���ز�������
//**********************************************************/ 
//void TCS230_Start(void)
//{		
//        TIM3->CR1|=0X01;	//ʹ�ܶ�ʱ��3
//		Colour_num=0;//	��������
//		Time3_flag=0; // ��ʱ����־����
//	    EXTI->IMR|=1<<12;//�����ⲿ�ж�6	
//}

///******************************************
// �������ƣ�TCS230_Read_Colour
// �������ܣ�������ɫ�˲�����������ӦƵ�ʲ���
// ��ڲ�����Colour
// ���ز�����Colour num
// ��    ע��Colour     ����ɫ�˲������ò���
//           Colour num ���������
//******************************************/ 
//u32 TCS230_Read_Colour(u8 Colour)
//{
//	Colour_Init(Colour);//����TCS230����ɫ�˲���
//	delay_ms(5);
//	TCS230_Start();//��ʼ������������ʱ��3���ⲿ�ж�6
//	while(Time3_flag==0);//�ȴ��������
//	return Colour_num;	// ���ؼ�������
//}

///******************************************
// �������ƣ�TCS230_Distinguish
// �������ܣ�������ɫ�б�
// ��ڲ�������
// ���ز�����1/2
//******************************************/ 
//void TCS230_Distinguish(void)
//{
//	u8 i;
//	for(i=0;i<5;i++)   // ��ȡ��������
//	{
//		r=r+TCS230_Read_Colour(Red1);
//		b=b+TCS230_Read_Colour(Blue1);
//		g=g+TCS230_Read_Colour(Green1);
//	}

//	r=r*255/10000;//ȡ���β�����ƽ��ֵ
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
//**�������ܣ���RGBֵ��ʾ��12864Һ������
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


u32 Colour_num=0;								  // ������ɫ�������������
u8  Time2_flag=0;                                 // ��ʱ���жϱ�־

/*��ʱ��3�жϷ�����*/
//void TIM2_IRQHandler(void)
//{ 
//	if(TIM2->SR&(1 << 1))			//����ж�
//	{
//	 Time2_flag=1;
//	 EXTI->IMR|=0<<8;				//�ر��ⲿ�ж�0
//	 TIM2->CR1|=0X00;				//�رն�ʱ��3
//	}
//	TIM2->SR&=~(1<<1);				//����жϱ�־λ 
//}
/**********************************************
�������ƣ�Timer3_Init
�������ܣ�ͨ�ö�ʱ��3�жϳ�ʼ��
��ں�����arr���Զ���װֵ��
          psc(ʱ��Ԥ��Ƶ��)
���ز�������
��ע��ʱ��Ϊ2��APB1(36M)
���ʱ�䣨MS)=(arr*(psc+1))/����ʱ��Ƶ��(10KHZ) 
***********************************************/
void Timer2_Init(u16 arr,u16 psc)
{
//     RCC->APB1ENR|=1<<0;			//ʹ��TIM3ʱ��
		 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
     TIM2->ARR=arr;					//���ü������Զ���װֵ(0.1ms)
     TIM2->PSC=psc;					//Ԥ��Ƶ��7200���պ�10khz
     TIM2->DIER|=1<<1; 				//��������ж�
     TIM2->DIER|=1<<6; 				//�������ж�
     TIM2->CR1|=0X01;				//ʹ�ܶ�ʱ��3
     MY_NVIC_Init(1,1,TIM2_IRQChannel,2);// ��ռ1�������ȼ�1����2
}
/********************************
�������ƣ�EXTI0_Init
�������ܣ��ⲿ�ж϶˿ڳ�ʼ��
��ڲ�������
���ز�������
��ע����ʼ��PA0Ϊ�ж�����
********************************/
void EXTI5_Init(void)
{
     RCC->APB2ENR|=1<<2; 			    	//ʹ��PORTAʱ��
     GPIOD->CRH&=0XFFFFFFF0;			    //PA5���ó�����
     GPIOD->CRH|=0X00000008;
     Ex_NVIC_Config(GPIO_D,8,FTIR);		    //�½��ش���
     MY_NVIC_Init(2,2,EXTI9_5_IRQChannel,2);//��ռ2�������ȼ�2����2
}

/*�ⲿ�ж�0�������*/
//void EXTI9_5_IRQHandler(void)
//{
//	Colour_num++;
//    EXTI->PR = 1<<8;             //���line0�ϵ��жϱ�־λ
//	EXTI->IMR|=0<<8;             //�ر��ⲿ�ж�5
//	TIM2->CR1|=0X00;	         //�رն�ʱ��2
//}
/**********************************************************
 �������ƣ�TCS230_Init
 �������ܣ�TCS230��ʼ��
 ��ڲ�������
 ���ز�������
 ��    ע����ʼ���ⲿ�ж�0����ʱ���ж�3�����I/O������
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
//	RCC->APB2ENR|=1<<4;            //ʹ��PORTAʱ��	   	 
//	GPIOC->CRL&=0X00FFFFFF; 
//	GPIOC->CRL|=0X33000000;        //PC6/PC7 ������� 
		GPIOB->CRH&=0XF00FFFFF; 
	  GPIOB->CRH|=0X03300000; 
//	GPIOC->ODR|=1<<6;              //����
//	GPIOC->ODR|=1<<7; 
		GPIOB->ODR|=1<<13;
		GPIOB->ODR|=1<<14;
	Timer2_Init(400,7199);         //40ms
	EXTI5_Init();

}
/***********************************************
 �������ƣ�Colour_Init
 �������ܣ�TCS230�ڲ���ɫ�˲�������
 ��ڲ�����Colour
 ���ز�������
 ��    ע��Colour ѡ����ɫ��Red1/Blue1/Green1��
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
 �������ƣ�TCS230_Start
 �������ܣ���ʼ������������ʱ��3���ⲿ�ж�0�������������
 ��ڲ�������
 ���ز�������
**********************************************************/ 
void TCS230_Start(void)
{		
	TIM2->CR1|=0X01;	//ʹ�ܶ�ʱ��3
	Colour_num=0;		//	��������
	Time2_flag=0;		// ��ʱ����־����
	EXTI->IMR|=1<<8;	//�����ⲿ�ж�0	
}
/******************************************
 �������ƣ�TCS230_Read_Colour
 �������ܣ�������ɫ�˲�����������ӦƵ�ʲ���
 ��ڲ�����Colour
 ���ز�����Colour num
 ��    ע��Colour     ����ɫ�˲������ò���
           Colour num ���������
******************************************/ 
u32 TCS230_Read_Colour(u8 Colour)
{
	Colour_Init(Colour);       //����TCS230����ɫ�˲���
	delay_ms(5);
	TCS230_Start();            //��ʼ������������ʱ��3���ⲿ�ж�0
	while(Time2_flag==0);      //�ȴ��������
	return Colour_num;	       // ���ؼ�������
}
/******************************************
 �������ƣ�TCS230_Distinguish
 �������ܣ�������ɫ�б�
 ��ڲ�������
 ���ز�����0/1/2/3
 ��    ע��0:Red1
           1:Blue1
		   2:Green1
		   3:Yellow1
******************************************/ 
u8 TCS230_Distinguish(void)
{
	u8 i;
	float r=0.0,b=0.0,g=0.0;
	float k=1.4;          //����ϵ��
	for(i=0;i<3;i++)      // ��ȡ��������
	{
		r=r+TCS230_Read_Colour(Red1);
		b=b+TCS230_Read_Colour(Blue1);
		g=g+TCS230_Read_Colour(Green1);
	}

	r=r/3;               //ȡ���β�����ƽ��ֵ
	b=b/3;
	g=g/3;
	if((r>1.25*b)&&(r>1.25*g))// ��ɫ
	return Red1;
	if((g>1.15*b)&&(g>1.05*r))// ��ɫ
	return Green1; 
	if((b>1.35*r)&&(b>1.35*g))// ��ɫ
	return Blue1;
	if((r>k*b)&&(g>k*b))      // ��ɫ
	return Yellow1;
	return 0;
}

////���������
//void ColorSensor_init(void)
//{
//     RCC->APB2ENR|=1<<2; 			    	
//     GPIOA->CRL&=0XFFFF0000;			    
//     GPIOA->CRL|=0X00003333;
//}

//ִ����Ӧ�Ĺ���
//void ColorSensor(void)
//{
//	u8 j;
//	j=TCS230_Distinguish();//�õ���Ӧ��ɫ
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






