#include <stm32f10x_lib.h>
#include "user.h"
#include "key.h"
#include "driver.h"
#include "getsensor.h"

//�����ʼ��
 
void Sys_Init(void)
{
	Stm32_Clock_Init(9); //ϵͳʱ������
	delay_init(72);	     //��ʱ��ʼ��
//	LCD_Init();
	N5110_Init();
//	LED_Init();
	Sensor_Init();
	servo_Configuration();
	speed_Configuration();
	Beep_Init(); 
//	Remote_Init();	
	Key_Init();
	IIC_Init();
	TCS230_Init();//TCS230��ʼ��
//	Compass_Init();
//	manu();
}

//void anologTest(void)
//{	
//	show_string(0,0,"A0:");
//	display_num_add(15,0,analog(1));
//	write_char(' ');
//	display_num_add(39,0,analog(2));
//	write_char(' ');
//	display_num_add(63,0,analog(3));
//	delay_ms(2);	
//	
//	show_string(0,1,"A3:");
//	display_num_add(15,1,analog(4));
//	write_char(' ');
//	display_num_add(39,1,analog(5));
//	write_char(' ');
//	display_num_add(63,1,analog(6));
//	delay_ms(2);
//	
//	show_string(0,2,"A6:");
//	display_num_add(15,2,analog(7));
//	write_char(' ');
//	display_num_add(39,2,analog(8));
//	write_char(' ');
//	display_num_add(63,2,analog(9));
//	delay_ms(2);
//	
//	show_string(0,3,"A9:");
//	display_num_add(15,3,analog(10));
//	write_char(' ');
//	display_num_add(39,3,analog(11));
//	write_char(' ');
//	display_num_add(63,3,analog(12));
//	delay_ms(2);
//	
//	show_string(0,4,"A12:");
//	display_num_add(15,4,analog(13));
//	write_char(' ');
//	display_num_add(39,4,analog(14));
//	write_char(' ');
//	display_num_add(63,4,analog(15));
//	delay_ms(2);
//	
//	show_string(0,5,"A15:");
//	display_num_add(15,5,analog(16));
//	delay_ms(2);
//}

//void Digit1_4Test(void)
//{	
//	show_string(0,0,"D1:");
//	display_num_a(32,0,digtal(1));
//	show_string(0,1,"D2:");
//	display_num_a(32,1,digtal(2));
//	show_string(0,2,"D1:");
//	display_num_a(32,2,digtal(3));		
//	show_string(0,3,"D4:");
//	display_num_a(32,3,digtal(4));
//	delay_ms(2);
////	
////	show_string(0,20,"D7:");
////	display_num_add(26,10,digtal(7));
////	display_num_add(62,10,digtal(8));
////	display_num_add(98,10,digtal(9));
////	delay_ms(2);
////	
////	show_string(0,30,"D10:");
////	display_num_add(26,10,digtal(10));
////	display_num_add(62,10,digtal(11));
////	display_num_add(98,10,digtal(12));
////	delay_ms(2);
////	
////	show_string(0,40,"D13:");
////	display_num_add(26,10,digtal(13));
////	display_num_add(62,10,digtal(14));
////	display_num_add(98,10,digtal(15));
////	delay_ms(2);
//	
//}

//void Digit16_22Test(void)
//{	
////	show_string(0,30,"D16:");
////	display_num_add(26,10,digtal(16));
////	display_num_add(62,10,digtal(17));
////	display_num_add(98,10,digtal(18));
////	delay_ms(2);
////	
////	show_string(0,40,"D19:");
////	display_num_add(26,10,digtal(19));
////	display_num_add(62,10,digtal(20));
////	display_num_add(98,10,digtal(21));
////	delay_ms(2);
////	
////	show_string(0,50,"D22:");
////	display_num_add(26,10,digtal(22));
////	delay_ms(2);	
//}

//void manu()
//{
//	u8 	menu_state = 1;	   //0�˳� 1Ŀ¼ 2������ʾ������
//	u8 	menu_num = 1;

////	FontSet(1,1);
////	FontSet_cn(1,1);
//	show_string(20,24,"A0-A15"); 
////	PutString_cn(68,24,"ģ��ֵ");

//	while(menu_state != 0)
//	{
//		if(KeyUp==0 || KeyDown==0 || KeyConfirm==0 || KeyOut==0 || KeyStart==0)
//		{
//			delay_ms(10);
//			if(KeyUp==0 || KeyDown==0 || KeyConfirm==0 || KeyOut==0 || KeyStart==0)
//			{
//				Clean_Screen();
//				if(KeyOut == 0)	
//				{
//					menu_state--;
////					LED0_OFF;
////					if(menu_state == 1) 
////					{
////						FontSet(1,1);
////						FontSet_cn(1,1);
////					}
////					else if(menu_state == 2)
////						FontSet(0,1);
//				}
//				else if(KeyUp ==0)
//				{
//					if(menu_state == 1)
//					{	
//						if(menu_num <8) menu_num ++;
//					}
//				}
//				else if(KeyDown ==0)
//				{
//					if(menu_state == 1)
//					{
//						if(menu_num>1) 	menu_num --;
//					}
//				}
//				else if(KeyConfirm == 0)
//				{
//					menu_state ++;
////					LED0_ON;
////					if(menu_state == 1) 
////					{
////						FontSet(1,1);
////						FontSet_cn(1,1);
////					}
////					else if(menu_state == 2)
////					{
////						FontSet(0,1);
////						FontSet_cn(0,1);
////						TIM_SetCounter(TIM1, 0);   // ���������CNT
////						lEncoderTotal = 0;          /* pulse�ۼ�ֵ                */
////						iEncoderMax = 0;            /* pulse���ֵ                */
////						iEncoder = 0;               /* ����ֵ                    */
////					}				
//				}
//				while(KeyUp==0 || KeyDown==0 || KeyConfirm==0 || KeyOut==0 || KeyStart==0);
//			}
//			if(menu_state == 1)
//			{
//				switch(menu_num)
//				{
//					case 1:	   //8*16  16*16	
//						show_string(20,24,"A0-A15"); 
////						PutString_cn(68,24,"ģ��ֵ");
//						break;
//					case 2:
//						show_string(20,24,"D1-D4"); 
////						PutString_cn(68,24,"����ֵ");
//						break;
//					case 3:
//						show_string(12,24,"D16-D22"); 
////						PutString_cn(68,24,"����ֵ");
//						break;
//					case 4:
//						show_string(12,24,"D34-D49"); 
////						PutString_cn(68,24,"����ֵ");
//						break;
//					case 5:
//						show_string(8,24,"gesture");
//						break;
//					case 6:
////						PutString_cn(8,24,"��ת����������");
//						break;
//					case 7:
////						PutString_cn(8,24,"����ͷ�Խ�����");
//						break;
//					case 8:
////						PutString_cn(32,24,"�������");
//						break;
//				}
//			}
//		}

//		if(menu_state == 2)
//		{		
//			switch(menu_num)
//			{
//				case 1:
//					anologTest();
//					break;
//				case 2:
//					Digit1_4Test();
//					break;
//				case 3:
//					Digit16_22Test();
//					break;
//				case 4:
////					Digit34_49Test();
//					break;
//				case 5:
////					PutString(0,0,"X-Y:");
////					ShowVar(25,0,HMC5883_Get_Angle(0));
////					PutString(0,10,"X-Z:");
////					ShowVar(25,10,HMC5883_Get_Angle(1));
////					PutString(0,20,"Y-Z:");
////					ShowVar(25,20,HMC5883_Get_Angle(2));
//					break;
//				case 6:					
////					PutString_cn(0,0,"��ǰ�ٶ�ֵ��");
////					ShowVar(72,0,iEncoder);

////					PutString_cn(0,14,"����ٶ�ֵ��");
////					ShowVar(72,14,iEncoderMax);

////					PutString_cn(0,28,"�������ֵ��");					
////					ShowVar(0,42,lEncoderTotal>>16); 
////					ShowVar(30,42,lEncoderTotal); 				 					 
//					break;												
//			}
//			delay_ms(200);
//		}				
//	}			
//}


//#include <stm32f10x_lib.h>
//#include "user.h"
//#include "key.h"
//#include "driver.h"
//#include "getsensor.h"

////�����ʼ��
// 
//void Sys_Init(void)
//{
//	Stm32_Clock_Init(9); //ϵͳʱ������
//	delay_init(72);	     //��ʱ��ʼ��
////	LCD_Init();
//	N5110_Init();
////	LED_Init();
//	servo_Configuration();
//	speed_Configuration();
//	Sensor_Init();
////	Remote_Init();	
//	Key_Init();
//	IIC_Init();
////	manu();
////	TCS230_Init();//TCS230��ʼ��
//}

//void anologTest(void)
//{	
//	show_string(0,0,"A0:");
//	display_num_add(15,0,analog(1));
//	write_char(' ');
//	display_num_add(39,0,analog(2));
//	write_char(' ');
//	display_num_add(63,0,analog(3));
//	delay_ms(2);	
//	
//	show_string(0,1,"A3:");
//	display_num_add(15,1,analog(4));
//	write_char(' ');
//	display_num_add(39,1,analog(5));
//	write_char(' ');
//	display_num_add(63,1,analog(6));
//	delay_ms(2);
//	
//	show_string(0,2,"A6:");
//	display_num_add(15,2,analog(7));
//	write_char(' ');
//	display_num_add(39,2,analog(8));
//	write_char(' ');
//	display_num_add(63,2,analog(9));
//	delay_ms(2);
//	
//	show_string(0,3,"A9:");
//	display_num_add(15,3,analog(10));
//	write_char(' ');
//	display_num_add(39,3,analog(11));
//	write_char(' ');
//	display_num_add(63,3,analog(12));
//	delay_ms(2);
//	
//	show_string(0,4,"A12:");
//	display_num_add(15,4,analog(13));
//	write_char(' ');
//	display_num_add(39,4,analog(14));
//	write_char(' ');
//	display_num_add(63,4,analog(15));
//	delay_ms(2);
//	
//	show_string(0,5,"A15:");
//	display_num_add(15,5,analog(16));
//	delay_ms(2);
//}

//void Digit1_4Test(void)
//{	
//	show_string(0,0,"D1:");
//	display_num_a(32,0,digtal(1));
//	show_string(0,1,"D2:");
//	display_num_a(32,1,digtal(2));
//	show_string(0,2,"D1:");
//	display_num_a(32,2,digtal(3));		
//	show_string(0,3,"D4:");
//	display_num_a(32,3,digtal(4));
//	delay_ms(2);
//	
//	show_string(0,20,"D7:");
//	display_num_add(26,10,digtal(7));
//	display_num_add(62,10,digtal(8));
//	display_num_add(98,10,digtal(9));
//	delay_ms(2);
//	
//	show_string(0,30,"D10:");
//	display_num_add(26,10,digtal(10));
//	display_num_add(62,10,digtal(11));
//	display_num_add(98,10,digtal(12));
//	delay_ms(2);
//	
//	show_string(0,40,"D13:");
//	display_num_add(26,10,digtal(13));
//	display_num_add(62,10,digtal(14));
//	display_num_add(98,10,digtal(15));
//	delay_ms(2);
//	
//}

////void Digit16_22Test(void)
////{	
////	show_string(0,30,"D16:");
////	display_num_add(26,10,digtal(16));
////	display_num_add(62,10,digtal(17));
////	display_num_add(98,10,digtal(18));
////	delay_ms(2);
////	
////	show_string(0,40,"D19:");
////	display_num_add(26,10,digtal(19));
////	display_num_add(62,10,digtal(20));
////	display_num_add(98,10,digtal(21));
////	delay_ms(2);
////	
////	show_string(0,50,"D22:");
////	display_num_add(26,10,digtal(22));
////	delay_ms(2);	
////}

//void manu()
//{
//	u8 	menu_state = 1;	   //0�˳� 1Ŀ¼ 2������ʾ������
//	u8 	menu_num = 1;

////	FontSet(1,1);
////	FontSet_cn(1,1);
//	show_string(20,24,"A0-A15"); 
////	PutString_cn(68,24,"ģ��ֵ");

//	while(menu_state != 0)
//	{
//		if(KeyUp==0 || KeyDown==0 || KeyConfirm==0 || KeyOut==0 || KeyStart==0)
//		{
//			delay_ms(10);
//			if(KeyUp==0 || KeyDown==0 || KeyConfirm==0 || KeyOut==0 || KeyStart==0)
//			{
//				Clean_Screen();
//				if(KeyOut == 0)	
//				{
//					menu_state--;
////					LED0_OFF;
////					if(menu_state == 1) 
////					{
////						FontSet(1,1);
////						FontSet_cn(1,1);
////					}
////					else if(menu_state == 2)
////						FontSet(0,1);
//				}
//				else if(KeyUp ==0)
//				{
//					if(menu_state == 1)
//					{	
//						if(menu_num <8) menu_num ++;
//					}
//				}
//				else if(KeyDown ==0)
//				{
//					if(menu_state == 1)
//					{
//						if(menu_num>1) 	menu_num --;
//					}
//				}
//				else if(KeyConfirm == 0)
//				{
//					menu_state ++;
////					LED0_ON;
////					if(menu_state == 1) 
////					{
////						FontSet(1,1);
////						FontSet_cn(1,1);
////					}
////					else if(menu_state == 2)
////					{
////						FontSet(0,1);
////						FontSet_cn(0,1);
////						TIM_SetCounter(TIM1, 0);   // ���������CNT
////						lEncoderTotal = 0;          /* pulse�ۼ�ֵ                */
////						iEncoderMax = 0;            /* pulse���ֵ                */
////						iEncoder = 0;               /* ����ֵ                    */
////					}				
//				}
//				while(KeyUp==0 || KeyDown==0 || KeyConfirm==0 || KeyOut==0 || KeyStart==0);
//			}
//			if(menu_state == 1)
//			{
//				switch(menu_num)
//				{
//					case 1:	   //8*16  16*16	
//						show_string(20,24,"A0-A15"); 
////						PutString_cn(68,24,"ģ��ֵ");
//						break;
//					case 2:
//						show_string(20,24,"D1-D4"); 
////						PutString_cn(68,24,"����ֵ");
//						break;
//					case 3:
//						show_string(12,24,"D16-D22"); 
////						PutString_cn(68,24,"����ֵ");
//						break;
//					case 4:
//						show_string(12,24,"D34-D49"); 
////						PutString_cn(68,24,"����ֵ");
//						break;
//					case 5:
//						show_string(8,24,"gesture");
//						break;
//					case 6:
////						PutString_cn(8,24,"��ת����������");
//						break;
//					case 7:
////						PutString_cn(8,24,"����ͷ�Խ�����");
//						break;
//					case 8:
////						PutString_cn(32,24,"�������");
//						break;
//				}
//			}
//		}

//		if(menu_state == 2)
//		{		
//			switch(menu_num)
//			{
//				case 1:
//					anologTest();
//					break;
//				case 2:
//					Digit1_4Test();
//					break;
//				case 3:
//					Digit16_22Test();
//					break;
//				case 4:
////					Digit34_49Test();
//					break;
//				case 5:
////					PutString(0,0,"X-Y:");
////					ShowVar(25,0,HMC5883_Get_Angle(0));
////					PutString(0,10,"X-Z:");
////					ShowVar(25,10,HMC5883_Get_Angle(1));
////					PutString(0,20,"Y-Z:");
////					ShowVar(25,20,HMC5883_Get_Angle(2));
//					break;
//				case 6:					
////					PutString_cn(0,0,"��ǰ�ٶ�ֵ��");
////					ShowVar(72,0,iEncoder);

////					PutString_cn(0,14,"����ٶ�ֵ��");
////					ShowVar(72,14,iEncoderMax);

////					PutString_cn(0,28,"�������ֵ��");					
////					ShowVar(0,42,lEncoderTotal>>16); 
////					ShowVar(30,42,lEncoderTotal); 				 					 
//					break;												
//			}
//			delay_ms(200);
//		}				
//	}			
//}





