#ifndef __COLOUR_H
#define __COLOUR_H	

#include "user.h"

//COLOUR�˿ڶ���
#define TCS32_EO PAout(11) 
#define TCS32_S3 PAout(12) 
#define TCS32_S2 PAout(13) 
#define TCS32_S1 PAout(14) 
#define TCS32_S0 PAout(15) 

#define Red1    1
#define Green1  2
#define Blue1   3
//#define White_and_Green 100
/*�ⲿ��������*/
void Timer3_Init(u16 arr,u16 psc);//ͨ�ö�ʱ��3�жϳ�ʼ��
void EXTI11_Init(void);	//�ⲿ�ж�0�������
void TCS230_Init(void);//TCS230��ʼ��
void Colour_Init(u8 Colour);//TCS230�ڲ���ɫ�˲�������
void TCS230_Start(void);//��ʼ������������ʱ��3���ⲿ�ж�0�������������
u32 TCS230_Read_Colour(u8 Colour);//������ɫ�˲�����������ӦƵ�ʲ���
u8 TCS230_Distinguish(void);//������ɫ�б�
void showRGB(void);

		 				    
#endif
