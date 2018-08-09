#ifndef __USER_H
#define __USER_H
 
#include <stm32f10x_lib.h>		 
#include "sys.h"
#include "delay.h"
#include "lcd5110.h"
//#include "lcd12864.h" 
#include "led.h"
#include "driver.h"	
#include "getsensor.h"
#include "beep.h"
//#include "remote.h"
#include "iic.h" 
#include "key.h"
#include "distance.h"
//#include "colour.h"
#include "compass.h" 
#include "track_jg.h"

//ϵͳ����
extern void Sys_Init(void);			 //ϵͳ�ܳ�ʼ��
extern void delay_ms(u16 nms);		 //�����ӳ٣�������1864ms
extern void delay_us(u32 nus);		 //΢���ӳ�

void anologTest(void);
void Digit1_4Test(void);
void Digit16_22Test(void);
void manu(void);

//12864Һ������ ��СΪ6*10����
//extern void PutString(unsigned char x,unsigned char y,unsigned char *p);	 //x,y��������ʾ�ַ���
//extern void ShowVar(unsigned char x,unsigned char y,unsigned short a);		 //x,y��������ʾ16λ�޷��ű�����5λʮ���ƣ�
//extern void ClrScreen(void);												 //����

//LED����
#define LED2_ON   LED0=0	  //LED2_ON; �� LED2_OFF;��
#define LED2_OFF  LED0=1
#define LED1_ON   LED1=0	  //LED1_ON; �� LED1_OFF;��
#define LED1_OFF  LED1=1

//����������������
extern void speed(int pwm1, int pwm2);
extern void servo1(int pwm);
extern void servo2(int pwm);
extern void servo3(int pwm);
extern void servo4(int pwm);
extern void speed_24(int pwm1, int pwm2,int pwm3, int pwm4);

//ģ�⡢���ֿں���
extern u8 digtal(u8 channel);  	//��ȡXͨ������ֵ��0��1��		  1~22						  
extern u16 analog(u8 channel);  //��ȡXͨ��ADֵ��0~1023��		  1~16



/*/����������  
#define Beep_ON   Beep=0;
#define Beep_OFF  Beep=1;
*/
//ң�غ���	
/***********
162 098 226	  ����ң������ֵ
034 002 194
224 168 144
104 152 176
048 024 122
016 056 090
066 074 082  
************/ 
//#define Key_stop 162     //�û��Զ���ֹͣ��ť��(�ο���ֵ��

//EEPROM����
extern u16 EEPROM_Read(u8 ReadAddr);  //��AT24C02ָ����ַ����һ��16λ������ 				  ��ַ������ 0~127
extern void EEPROM_Write(u8 WriteAddr,u16 DataToWrite);//��AT24C02ָ����ַд��һ��16λ����	  ��ַ������0~127
	


//��ഫ����
extern u16 distance(u8 channel);
#define  Close  2000
#define  Mid   1000
#define  Far    500


//��ɫ������
//#define White_and_Green 100
//#define White  1
//#define Green  2 
//extern u8 TCS230_Distinguish(void);//������ɫ�б� ���أ�White ��Green��
//extern void showRGB(void); //��ʾRGB��ֵ

//ָ���뺯��
void cal_on(void);	//У׼
void CMP_OFFS(void);  //�޸�ָ�����ƫ��ֵ
void cal_off(void);	//�ر�У׼
u16 read_cmp(void);	 //��ȡ�Ƕ�ֵ
void recovery_factory(void);//�ָ���������



#endif	   
















