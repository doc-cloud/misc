/*********************************************************
�����ܣ��ù̶�Ƶ�ʵķ�����������������16���������ڷ�����
          ������ͬ������ͬʱ��LED�����Զ�����������ʽָʾ
          ��ǰ�����ı�ţ�1~16��
----------------------------------------------------------
����˵�������������������������仯��
**********************************************************/
#include <msp430.h>
#include "BoardConfig.h"

uchar step = 0xff;

/************************������************************/
void main( void )
{
    uchar i;
    
    WDTCTL = WDTPW + WDTHOLD;           //�ع�
    BoardConfig(0xb0);                  //������ܡ���ˮ�ƺ͵�ƽת��
    
    /*------ѡ��ϵͳ��ʱ��Ϊ8MHz-------*/
    BCSCTL1 &= ~XT2OFF;                 //��XT2��Ƶ��������
    do
    {
        IFG1 &= ~OFIFG;                 //�������ʧ�ܱ�־
        for (i = 0xFF; i > 0; i--);     //�ȴ�8MHz��������
    }
    while ((IFG1 & OFIFG));             //����ʧЧ��־��Ȼ���ڣ�
    BCSCTL2 |= SELM_2 + SELS;           //MCLK��SMCLKѡ���Ƶ����
    
    TACCTL0 |= CCIE;                    //ʹ�ܱȽ��ж�
    TACTL |= TASSEL_2 + ID_3 ;          //����ʱ��ѡ��SMLK=8MHz��1/8��Ƶ��Ϊ1MHz
    
    TBCCR0 = 4096*2 - 1;                //��������
    TBCCTL0 |= CCIE;
    TBCTL |= TBSSEL_1 + ID_3 + MC_1;    //ʱ��ԴACLK/8��up mode
    
    P6DIR |= BIT7;                      //��������ӦIO����Ϊ���
    P2DIR = 0xff;
    P2OUT = 0xff;
    
    _EINT();
    
    LPM1;
}
/*******************************************
�������ƣ�Timer_A
��    �ܣ���ʱ��A���жϷ�����������������
          ����������
��    ������
����ֵ  ����
********************************************/
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
  P6OUT ^= BIT7;                            // Toggle P6.7
}
/*******************************************
�������ƣ�Timer_B
��    �ܣ���ʱ��B���жϷ����������������
          ����������Ƶ��
��    ������
����ֵ  ����
********************************************/
#pragma vector=TIMERB0_VECTOR
__interrupt void Timer_B (void)
{
    if(step == 0xff)                        //up mode
      TACTL |= MC_1;   
    step++;
    switch(step)
    {  
    case    0:  TACCR0 = 5000;  P2OUT = ~1;   break;      // 100Hz
    case    1:  TACCR0 = 2500;  P2OUT = ~2;   break;      // 200Hz
    case    2:  TACCR0 = 1250;  P2OUT = ~3;   break;      // 400Hz
    case    3:  TACCR0 = 625;   P2OUT = ~4;   break;      // 800Hz
    case    4:  TACCR0 = 500;   P2OUT = ~5;   break;      // 1KHz
    case    5:  TACCR0 = 250;   P2OUT = ~6;   break;      // 2KHz
    case    6:  TACCR0 = 167;   P2OUT = ~7;   break;      // 3KHz
    case    7:  TACCR0 = 125;   P2OUT = ~8;   break;      // 4KHz
    case    8:  TACCR0 = 100;   P2OUT = ~9;   break;      // 5KHz
    case    9:  TACCR0 = 83;    P2OUT = ~10;   break;      // 6KHz
    case    10:  TACCR0 = 71;   P2OUT = ~11;   break;      // 7KHz
    case    11:  TACCR0 = 63;   P2OUT = ~12;   break;      // 8KHz
    case    12:  TACCR0 = 56;   P2OUT = ~13;   break;      // 9KHz
    case    13:  TACCR0 = 50;   P2OUT = ~14;   break;      // 10KHz
    case    14:  TACCR0 = 33;   P2OUT = ~15;   break;      // 15KHz
    case    15:  TACCR0 = 25;   P2OUT = ~16;   break;      // 20KHz
    case    16:  step = 0xff;               // ѭ������
    }
}
