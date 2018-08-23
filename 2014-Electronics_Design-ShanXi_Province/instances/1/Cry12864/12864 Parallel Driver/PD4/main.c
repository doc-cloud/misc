/**************************************************************
�����ܣ��ò������ݴ��䷽ʽ��Һ�����ۺ���ʾ�ַ������ֺ�ͼ��
---------------------------------------------------------------
����˵�����۲�Һ����ʾ
***************************************************************/
#include <msp430x14x.h>
#include "BoardConfig.h"
#include "subfuncs.h"
#include "dispdata.h"

uchar flag = 0;
/*************************������***************************/
int main( void )
{
    WDTCTL = WDTPW + WDTHOLD;            //�رտ��Ź�
    BoardConfig(0xbe);                   //�ر�����ܡ���ˮ�ơ�4245
    
    TACTL = TASSEL_1 + MC_1;             //����ʱ��ACLK, ������ģʽ
    CCR0 = 32768 - 1;
    CCTL0 |= CCIE;                       //ʹ��CCR0�Ƚ��ж�
    _EINT(); 
    
    Ini_Lcd();                          //��ʾ����
    Disp_HZ(0x81,line1,6);
    Disp_HZ(0x92,line2,4);
    Disp_HZ(0x8a,line3,4);
    Disp_HZ(0x98,line4,8);
    
    flag = 0;
    while(flag < 5);                    //�ȴ�5����
    Write_Cmd(0x01);                    //����
    Draw_PM(zifu);                      //��ʾ������ͼƬ
    flag = 0;
    while(flag < 5);                    //�ȴ�5����
    Write_Cmd(0x01);                    //����
    Draw_PM(zhu);                       //��ʾ�ɰ����ͼƬ
    flag = 0;
    while(flag < 5);                    //�ȴ�5����
    Write_Cmd(0x01);                    //����
    Disp_HZ(0x92,jieshu,4);             //�������� 
    while(1);
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
    flag++;    
}
