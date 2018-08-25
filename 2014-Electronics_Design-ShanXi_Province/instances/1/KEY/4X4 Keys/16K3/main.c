/***********************************************
�����ܣ�ɨ��4X4���̲�����ֵ�����������ʾ
------------------------------------------------
�������ã���������J3�ϵĶ�·ñ����
------------------------------------------------
����˵��������K1~K16�������۲��������ʾ������
          ����ʱ�������Ƿ���
************************************************/
#include <msp430x14x.h>
#include "BoardConfig.h"
#include "Keypad.h"
#include "gdata.h"

/********************������********************/
void main(void)
{
    uint i;
    BoardConfig(0x80);            //������ܡ���ˮ��,�رյ�ƽת��        
    WDTCTL = WDT_ADLY_1_9;        //�����ڲ����Ź������ڶ�ʱ��ģʽ��1.9ms�ж�һ��
    IE1 |= WDTIE;                 //ʹ�ܿ��Ź��ж�
  
    P2DIR = 0xff;
    P4DIR = 0xff;                 //����P4��P5��IO����Ϊ���
    P5DIR = 0xff;  
    P6DIR |= BIT7; 
    P2OUT = 0xff;
    P4OUT = 0x00;                 //����P4��P5�������ֵ
    P5OUT = 0xff;
    P6OUT |= BIT7;
    _EINT();                      //��ȫ���ж�
    Init_Keypad();
    while(1)
    {
        Key_Event();
    
        if(key_Flag == 1)
        {
            key_Flag = 0;
            Dispbuf[0] = key_val / 10;
            Dispbuf[1] = key_val % 10;
            P2OUT = ~(key_val);         //LED��ʾ��ֵ
            P6OUT = 0;                  //��������һ��
            for(i = 2000; i > 0; i--);
            P6OUT |= BIT7;
        }
    }
}
/*******************************************
�������ƣ�watchdog_timer
��    �ܣ����Ź��жϷ��������������������ܵ�
          ��ѡ��λѡ�ź�
��    ������
����ֵ  ����
********************************************/
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{ 
    P5OUT = 0xff;
    P4OUT = scandata[Dispbuf[cnt]];         //�����ѡ�ź�
    P5OUT &= ~(1 << (cnt+2));               //���λѡ�ź�
  
    cnt++;                                  //λ����������0~1֮��ѭ��
    if(cnt == 2) cnt = 0;
}
