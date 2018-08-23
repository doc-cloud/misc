/**********************************************
�����ܣ�����λ���������ʾһ�������ƶ��Ĺ�꣬
          �����ƶ��ٶ��ǹ̶��ģ�ԼΪ250ms�ƶ�
          һ��
-----------------------------------------------
����˵�����۲��������ʾ
***********************************************/
#include  <msp430x14x.h>
#include  "BoardConfig.h"

#define NBIT(x)     ~(1 << x)

//��ʾ�ַ��Ŀ��Ʊ���
uchar step = 0;
//�ƶ�Ȧ���ı���
uint circle = 0;

/********************������********************/
void main(void)
{
    WDTCTL = WDT_ADLY_1000;       //���Ź������ڶ�ʱ��ģʽ�����250ms
    IE1 |= WDTIE;                 // ʹ�ܿ��Ź��ж�    
    BoardConfig(0x88);
  
    P4DIR = 0xff;                 //����P4��P5��IO����Ϊ���
    P5DIR = 0xff;                 
  
    P4OUT = 0x40;                 //����P4��P5�������ֵ
    P5OUT = 0xff;
  
    _BIS_SR(LPM3_bits + GIE);     //CPU����LPM3�͹���ģʽ��ͬʱ��ȫ���ж�
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
    step++;
    if(step == 10)  
    {
        step = 0;
    }
    switch(step)
    {
    case 0:
            P5OUT = NBIT(5);
            break;
    case 1: 
            P5OUT = NBIT(4);
            break;
    case 2:
            P5OUT = NBIT(3);
            break;
    case 3: 
            P5OUT = NBIT(2);
            break;
    case 4:
            P5OUT = NBIT(1);
            break;
    case 5:
            P5OUT = NBIT(0);
            break;
    case 6:
            P5OUT = NBIT(1);
            break;
    case 7:
            P5OUT = NBIT(2);
            break;
    case 8:
            P5OUT = NBIT(3);
            break;
    case 9:
            P5OUT = NBIT(4);
            break;
    }
}

