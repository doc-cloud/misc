#include <stm32f10x_lib.h>
#include "sys.h"
#include "usart.h"		
#include "delay.h"
#include "SuperSharkV1.0.h"
#include "led.h"
#include "beep.h"
#include "lcd12864.h" 
#include "getsensor.h"
#include "key.h" 
#include "remote.h"
#include "driver.h"	
#include "myiic.h" 
#include "adxl345.h"
#include "24cxx.h" 
#include "timer.h"
#include "exit.h"
#include "compass.h"

void manu(void);
void logo(void);
void anologTest(void);
void Digit0_15Test(void);
void Digit16_33Test(void);
void Digit34_49Test(void);

short x,y,z;  	    
u16 angx,angy,angz;
 
void SuperShark_Init()
{
	//ϵͳ��ʼ��
	Stm32_Clock_Init(9); //ϵͳʱ������
	delay_init(72);	     //��ʱ��ʼ��

	//����A��B��C��D��E�ڵ�ʱ��
	RCC->APB2ENR|=1<<2;    //ʹ��PORTAʱ��
	RCC->APB2ENR|=1<<3;    //ʹ��PORTBʱ��
	RCC->APB2ENR|=1<<4;    //ʹ��PORTCʱ��	   	 
	RCC->APB2ENR|=1<<5;    //ʹ��PORTDʱ��
	RCC->APB2ENR|=1<<6;    //ʹ��PORTEʱ��
	RCC->APB2ENR|=1<<0;    //ʹ��AFIOʱ��
	JTAG_Set(JTAG_SWD_DISABLE);//�ر�JTAG��SWD

    //�����ʼ��
	LED_Init();
	BEEP_Init();
	LCD_Init();
	Sensor_Init();
	Key_Init();	
	Remote_Init();
	servo_Configuration();
	speed_Configuration();
	IIC_Init();
//	while(ADXL345_Init()); 
	ADXL345_Read_Average(&x,&y,&z,10);	//��ȡX,Y,Z��������ļ��ٶ�ֵ 
	ADXL345_AUTO_Adjust((char*)&x,(char*)&y,(char*)&z);//�Զ�У׼
	Timer2_init();
	Code_init();
	EXIT_Init();
	//����ͷ��ʼ��
	
	TIM_Cmd(TIM2, ENABLE); //ʹ�ܶ�ʱ��	
	TIM_Cmd(TIM1, ENABLE);  //ʹ�ܼ�����

	//��������
	#ifdef LOGO 
		logo();
	#endif

	#ifdef MENU
		manu();
		FontSet(0,1);
		FontSet_cn(0,1);
	#endif	

	TIM_Cmd(TIM2, DISABLE); //ʹ�ܶ�ʱ��
	TIM_Cmd(TIM1, DISABLE);
		 
/*	PutString(0,0,"Control_V:"); 
	ShowVar(60,0,BatteryVoltage(0));
	PutString(90,0,"V");

	PutString(0,10,"Driver_V:"); 
	ShowVar(60,10,BatteryVoltage(1));
	PutString(90,10,"V");	  */
}	

void logo()
{
	PutBitmap(28,0,72,64);		//�������28,0Ϊ���Ͻǵ�λ����ʾ�ߴ��СΪ72X64�������λͼ
	delay_ms(1000);
	ClrScreen();		
}

void anologTest(void)
{	
	PutString_cn(0,0,"A0:");
	ShowVar(26,0,AnalogIn(0));	
	ShowVar(62,0,AnalogIn(1));
	ShowVar(98,0,AnalogIn(2));
	delay_ms(2);	
	
	PutString_cn(0,10,"A3:");
	ShowVar(26,10,AnalogIn(3));	
	ShowVar(62,10,AnalogIn(4));
	ShowVar(98,10,AnalogIn(5));	
	delay_ms(2);

	PutString_cn(0,20,"A6:");
	ShowVar(26,20,AnalogIn(6));	
	ShowVar(62,20,AnalogIn(7));
	ShowVar(98,20,AnalogIn(8));
	delay_ms(2);	

	PutString_cn(0,30,"A9:");
	ShowVar(26,30,AnalogIn(9));	
	ShowVar(62,30,AnalogIn(10));
	ShowVar(98,30,AnalogIn(11));
	delay_ms(2);

	PutString_cn(0,40,"A12:");
	ShowVar(26,40,AnalogIn(12));	
	ShowVar(62,40,AnalogIn(13));
	ShowVar(98,40,AnalogIn(14));
	delay_ms(2);

	PutString_cn(0,50,"A15:");
	ShowVar(26,50,AnalogIn(15));
	delay_ms(2);	
}

void Digit0_15Test(void)
{	
	PutString_cn(0,0,"D0:");
	ShowVar(26,0,DigitalIn(0));	
	ShowVar(62,0,DigitalIn(1));
	ShowVar(98,0,DigitalIn(2));	
	delay_ms(2);
	
	PutString_cn(0,10,"D3:");
	ShowVar(26,10,DigitalIn(3));	
	ShowVar(62,10,DigitalIn(4));
	ShowVar(98,10,DigitalIn(5));	

	PutString_cn(0,20,"D6:");
	ShowVar(26,20,DigitalIn(6));	
	ShowVar(62,20,DigitalIn(7));
	ShowVar(98,20,DigitalIn(8));
	delay_ms(2);	

	PutString_cn(0,30,"D9:");
	ShowVar(26,30,DigitalIn(9));	
	ShowVar(62,30,DigitalIn(10));
	ShowVar(98,30,DigitalIn(11));
	delay_ms(2);

	PutString_cn(0,40,"D12:");
	ShowVar(26,40,DigitalIn(12));	
	ShowVar(62,40,DigitalIn(13));
	ShowVar(98,40,DigitalIn(14));
	delay_ms(2);

	PutString_cn(0,50,"D15:");
	ShowVar(26,50,DigitalIn(15));
	delay_ms(2);	
}

void Digit16_33Test(void)
{	
	PutString_cn(0,0,"D16:");
	ShowVar(26,0,DigitalIn(16));	
	ShowVar(62,0,DigitalIn(17));
	ShowVar(98,0,DigitalIn(18));	
	delay_ms(2);
	
	PutString_cn(0,10,"D19:");
	ShowVar(26,10,DigitalIn(19));	
	ShowVar(62,10,DigitalIn(20));
	ShowVar(98,10,DigitalIn(21));
	delay_ms(2);	

	PutString_cn(0,20,"D22:");
	ShowVar(26,20,DigitalIn(22));	
	ShowVar(62,20,DigitalIn(23));
	ShowVar(98,20,DigitalIn(24));
	delay_ms(2);	

	PutString_cn(0,30,"D25:");
	ShowVar(26,30,DigitalIn(25));	
	ShowVar(62,30,DigitalIn(26));
	ShowVar(98,30,DigitalIn(27));
	delay_ms(2);

	PutString_cn(0,40,"D28:");
	ShowVar(26,40,DigitalIn(28));	
	ShowVar(62,40,DigitalIn(29));
	ShowVar(98,40,DigitalIn(30));
	delay_ms(2);

	PutString_cn(0,50,"D31:");
	ShowVar(26,50,DigitalIn(31));
	ShowVar(62,50,DigitalIn(32));
	ShowVar(98,50,DigitalIn(33));
	delay_ms(2);	
}

void Digit34_49Test(void)
{	
	PutString_cn(0,0,"D34:");
	ShowVar(26,0,DigitalIn(34));	
	ShowVar(62,0,DigitalIn(35));
	ShowVar(98,0,DigitalIn(36));	
	delay_ms(2);
	
	PutString_cn(0,10,"D37:");
	ShowVar(26,10,DigitalIn(37));	
	ShowVar(62,10,DigitalIn(38));
	ShowVar(98,10,DigitalIn(39));
	delay_ms(2);	

	PutString_cn(0,20,"D40:");
	ShowVar(26,20,DigitalIn(40));	
	ShowVar(62,20,DigitalIn(41));
	ShowVar(98,20,DigitalIn(42));
	delay_ms(2);	

	PutString_cn(0,30,"D43:");
	ShowVar(26,30,DigitalIn(43));	
	ShowVar(62,30,DigitalIn(44));
	ShowVar(98,30,DigitalIn(45));
	delay_ms(2);

	PutString_cn(0,40,"D46:");
	ShowVar(26,40,DigitalIn(46));	
	ShowVar(62,40,DigitalIn(47));
	ShowVar(98,40,DigitalIn(48));
	delay_ms(2);

	PutString_cn(0,50,"D49:");
	ShowVar(26,50,DigitalIn(49));
	delay_ms(2);	
}

void manu()
{
	u8 	menu_state = 1;	   //0�˳� 1Ŀ¼ 2������ʾ������
	u8 	menu_num = 1;
	u8  time_num;

	FontSet(1,1);
	FontSet_cn(1,1);
	PutString(20,24,"A0-A15"); 
	PutString_cn(68,24,"ģ��ֵ");

	while(menu_state != 0)
	{
		if(KeyUp==0 || KeyDown==0 || KeyConfirm==0 || KeyOut==0 || KeyStart==0)
		{
			delay_ms(10);
			if(KeyUp==0 || KeyDown==0 || KeyConfirm==0 || KeyOut==0 || KeyStart==0)
			{
				ClrScreen();
				if(KeyOut == 0)	
				{
					menu_state--;
					LED_OFF();
					if(menu_state == 1) 
					{
						FontSet(1,1);
						FontSet_cn(1,1);
					}
					else if(menu_state == 2)
						FontSet(0,1);
				}
				else if(KeyUp ==0)
				{
					if(menu_state == 1)
					{	
						if(menu_num <9) menu_num ++;
					}
				}
				else if(KeyDown ==0)
				{
					if(menu_state == 1)
					{
						if(menu_num>1) 	menu_num --;
					}
				}
				else if(KeyConfirm == 0)
				{
					menu_state ++;
					LED_ON();
					if(menu_state == 1) 
					{
						FontSet(1,1);
						FontSet_cn(1,1);
					}
					else if(menu_state == 2)
					{
						FontSet(0,1);
						FontSet_cn(0,1);
						TIM_SetCounter(TIM1, 0);   // ���������CNT
						lEncoderTotal = 0;          /* pulse�ۼ�ֵ                */
						iEncoderMax = 0;            /* pulse���ֵ                */
						iEncoder = 0;               /* ����ֵ                    */
					}				
				}
				while(KeyUp==0 || KeyDown==0 || KeyConfirm==0 || KeyOut==0 || KeyStart==0);
			}
			if(menu_state == 1)
			{
				switch(menu_num)
				{
					case 1:	   //8*16  16*16	
						PutString(20,24,"A0-A15"); 
						PutString_cn(68,24,"ģ��ֵ");
						break;
					case 2:
						PutString(20,24,"D0-D15"); 
						PutString_cn(68,24,"����ֵ");
						break;
					case 3:
						PutString(12,24,"D16-D33"); 
						PutString_cn(68,24,"����ֵ");
						break;
					case 4:
						PutString(12,24,"D34-D49"); 
						PutString_cn(68,24,"����ֵ");
						break;
					case 5:
						PutString_cn(8,24,"��Ǵ�����У׼");
						break;
					case 6:
						PutString_cn(8,24,"��Ǵ���������");
						break;
					case 7:
						PutString_cn(8,24,"��ת����������");
						break;
					case 8:
						PutString_cn(18,24,"��������У׼");
						break;
					case 9:
						PutString_cn(18,24,"�������̲���");
						break;
				}
			}
		}

		if(menu_state == 2)
		{		
			switch(menu_num)
			{
				case 1:
					anologTest();
					break;
				case 2:
					Digit0_15Test();
					break;
				case 3:
					Digit16_33Test();
					break;
				case 4:
					Digit34_49Test();
					break;
				case 5:
					PutString_cn(20,24,"��Ǵų�У׼��");
					ADXL345_Read_Average(&x,&y,&z,10);	//��ȡX,Y,Z��������ļ��ٶ�ֵ 
					ADXL345_AUTO_Adjust((char*)&x,(char*)&y,(char*)&z);//�Զ�У׼
					ClrScreen();
					menu_num=6;
					break;
				case 6:
/*					ADXL345_Read_Average(&x,&y,&z,10);	//��ȡX,Y,Z��������ļ��ٶ�ֵ 
					angx=ADXL345_Get_Angle(x,y,z,1)+180;    
					angy=ADXL345_Get_Angle(x,y,z,2)+180;   
					angz=ADXL345_Get_Angle(x,y,z,0)+180; 
													
					PutString(0,0,"X-Y:");
					ShowVar(25,0,angx);
					PutString(0,10,"X-Z:");
					ShowVar(25,10,angy);
					PutString(0,20,"Y-Z:");
					ShowVar(25,20,angz);	   */
					PutString(0,0,"X-Y:");
					ShowVar(25,0,ADXL345(1));
					PutString(0,10,"X-Z:");
					ShowVar(25,10,ADXL345(2));
					PutString(0,20,"Y-Z:");
					ShowVar(25,20,ADXL345(3));
					break;
				case 7:					
					PutString_cn(0,0,"��ǰ�ٶ�ֵ��");
					ShowVar(72,0,iEncoder);

					PutString_cn(0,14,"����ٶ�ֵ��");
					ShowVar(72,14,iEncoderMax);

					PutString_cn(0,28,"�������ֵ��");					
					ShowVar(0,42,lEncoderTotal>>16); 
					ShowVar(30,42,lEncoderTotal); 				 					 
					break;	
				case 8:					
					cal_on();
					for(time_num=0;time_num<60;time_num++) delay_ms(1000);
					cal_off();
					ClrScreen();
					menu_num=9;				 					 
					break;
				case 9:					
					ShowVar(0,0,read_cmp()); //��ȡ�Ƕ�ֵ				 					 
					break;												
			}
			delay_ms(200);
		}				
	}			
}

u16 ADXL345(u8 num)
{
	ADXL345_Read_Average(&x,&y,&z,10);	//��ȡX,Y,Z��������ļ��ٶ�ֵ 
	if(num==1) return ADXL345_Get_Angle(x,y,z,1)+180;
	else if(num==2) return ADXL345_Get_Angle(x,y,z,2)+180;   
	else if(num==3) return ADXL345_Get_Angle(x,y,z,0)+180; 	
	else return 0;
}



