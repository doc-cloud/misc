/*********************************************************
�����ܣ��ù̶�Ƶ�ʵķ�����������������16���������ڷ�����
          ������ͬ������ͬʱ��һ���������ʾ�����ı�š�
          PC�������ַ�������������������������
-----------------------------------------------------------
ͨ�Ÿ�ʽ��N.8.1,  9600
-----------------------------------------------------------
����˵�����򿪴��ڵ������֣���ȷ����ͨ�Ÿ�ʽ����PC���򴮿�
          ����0~Fʮ����ʮ���������֣��۲�����������������
          ����ʾ���
**********************************************************/
#include <msp430.h>
#include "BoardConfig.h"
#include "uart0.h"

uchar step = 0xff;

/**************************������**************************/
void main( void )
{
    uchar i;
    
    WDTCTL = WDTPW + WDTHOLD;           //�ع�
    BoardConfig(0x88);                  //������ܣ�����ˮ�ƺ͵�ƽת��
    
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
    _EINT();
    
    P6DIR = BIT7;                      //��������ӦIO����Ϊ���
    P6OUT = BIT7;
    P4DIR = 0xff;
    P5DIR = 0xff;
    P4OUT = 0x00;
    P5OUT = ~0x04;
    
    InitUART();                         //��ʼ��UART�˿�
    
    DisplayConfigMenu();
    while(1)
    {
        Send1Char('>');
        Send1Char('\n');
        i=Get1Char();
        HandleConfigMenu(i);
    }
    
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