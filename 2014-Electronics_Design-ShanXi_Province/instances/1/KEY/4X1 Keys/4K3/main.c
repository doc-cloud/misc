/******************************************************
�����ܣ����жϷ�ʽ��ȡ�ĸ�����ʽ�����ļ�ֵ��ͬʱ��
          D1~D4�ĸ�LED�ĵ�����ָʾk1~K4�ĸ������İ���
----------------------------------------------------
����˵��������K1~k4�ĸ��������۲�LED�Ƿ���ȷ����
*******************************************************/
#include <msp430x14x.h>
#include "BoardConfig.h"

#define keyin    (P1IN & 0x0f)

uchar KeyVal = 0;   // �����ļ�ֵ

/********************������********************/
void main( void )
{   
    WDTCTL = WDTPW + WDTHOLD;   //�رտ��Ź�
    BoardConfig(0xb0);          //����ˮ�ƣ��ر�����ܺ͵�ƽת��
    
    P1IES = 0x0f;               // P1.0~P1.3ѡ���½����ж�
    P1IE  = 0x0f;               // ���ж�ʹ��
    P1DIR = BIT7;               //����P1.0~P.3Ϊ����״̬��P.7Ϊ���
    P1OUT = 0;
    P2DIR = 0xff;
    P2OUT = 0xff;
    _EINT();                    //��ȫ���жϿ���λ
    while(1)
    {
        LPM1;
        P2OUT = ~(1 << (KeyVal - 1));
    }
}
/*******************************************
�������ƣ�delay
��    �ܣ�������������ʱ
��    ������
����ֵ  ����
********************************************/
void delay(void)
{
    uint tmp;
    
    for(tmp = 12000;tmp > 0;tmp--);
}
/*******************************************
�������ƣ�PORT1_ISR 
��    �ܣ�P1�˿ڵ��жϷ�����
��    ������
����ֵ  ����
********************************************/
#pragma vector=PORT1_VECTOR
__interrupt void  PORT1_ISR(void)
{
    if(P1IFG & 0x0f)
    {
        switch(P1IFG)
        {
        case 0x01:
                    if(keyin == 0x0e)   //����ǵ�һ������������
                    {
                        delay();
                        if(keyin == 0x0e)
                        {
                            while(keyin != 0x0f);       //�ȴ������ſ�
                            KeyVal = 1;
                            LPM1_EXIT;
                            P1IFG = 0;
                            return;
                        }
                    }
        case 0x02:
                    if(keyin == 0x0d)   //����ǵڶ�������������
                    {
                        delay();
                        if(keyin == 0x0d)
                        {
                            while(keyin != 0x0f);       //�ȴ������ſ�
                            KeyVal = 2;
                            LPM1_EXIT;
                            P1IFG = 0;
                            return;
                        }
                    }
        case 0x04:
                    if(keyin == 0x0b)   //����ǵ���������������
                    {
                        delay();
                        if(keyin == 0x0b)
                        {
                            while(keyin != 0x0f);       //�ȴ������ſ�
                            KeyVal = 3;
                            LPM1_EXIT;
                            P1IFG = 0;
                            return;
                        }
                    }
        case 0x08:
                    if(keyin == 0x07)   //����ǵ��ĸ�����������
                    {
                        delay();
                        if(keyin == 0x07)
                        {
                            while(keyin != 0x0f);       //�ȴ������ſ�
                            KeyVal = 4;
                            LPM1_EXIT;
                            P1IFG = 0;
                            return;
                        }
                    }
        default:
                    while(keyin != 0x0f);       //�ȴ������ſ�
                    P1IFG = 0;
                    return;
        }
    }
}
