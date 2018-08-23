/*****************************************************
�����ܣ���1602Һ������ʾ��MCU��TimerAģ�������
          ʽʵʱʱ�ӡ�
-----------------------------------------------------
����˵�����۲�Һ����ʾ
*****************************************************/
#include <msp430x14x.h>
#include "BoardConfig.h"
#include "cry1602.h"
#include "clock.h"

uchar tishi[]={"Current Time is"};   //��ʾ��Ϣ
extern uchar second,minute,hour,hour0;
extern uchar pmin,phour,ps1;

#define SetTime(H,M,S) {second=S;minute=M;hour=H;hour0=H;}

/*************************������************************/
void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;   //�رտ��Ź�
    BoardConfig(0xb8);          //�ر�74LVC4245������ܺ���ˮ��
	
    CCR0 = 32768 - 1;           //���ö�ʱ��A���ж�ʱ��Ϊ1S
    TACTL = TASSEL_1 + MC_1;    //����ʱ��ACLK, ������ģʽ
    CCTL0 |= CCIE;              //ʹ��CCR0�Ƚ��ж�
    _EINT();                    //��ȫ���ж�
    
    //���ڴ˴�������ȷʱ��
    SetTime(8,26,50);           //˳��ʱ���֣��룬��ʽ��BCD��
      
    LcdReset(); 
    DispNChar(0,0,15,tishi);     //��ʾ��ʾ����
    Disp1Char(6,1,':');          //��ʾ�ַ� :
    Disp1Char(9,1,':');
    
    while(1)
    {
        LPM3;                    //����LPM3�͹���ģʽ
        Display();         
    }    
}

/*******************************************
�������ƣ�TimerA_ISR
��    �ܣ���ʱ��A���жϷ�����
��    ������
����ֵ  ����
********************************************/
#pragma vector=TIMERA0_VECTOR
__interrupt void TimerA_ISR(void)
{
    Clock();
    LPM3_EXIT;
}
