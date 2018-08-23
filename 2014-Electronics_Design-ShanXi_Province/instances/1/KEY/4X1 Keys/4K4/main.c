/*********************************************************
�����ܣ��ð������Ʒ�����������������
          K1���º���2KHz��������������
          K2���º���4KHz��������������
          K3���º���6KHz��������������
          K4���º�ֹͣ����
----------------------------------------------------------
����˵��������K1~k4�ĸ���������������������Ƶ��
**********************************************************/
#include <msp430.h>
#include "BoardConfig.h"


#define keyin    (P1IN & 0x0f)

uchar step = 0xff;

void main( void )
{
    uchar i;
    
    WDTCTL = WDTPW + WDTHOLD;           //�ع�
    BoardConfig(0xb0);                  //������ܺ͵�ƽת��,����ˮ��
    
    /*------ѡ��ϵͳ��ʱ��Ϊ8MHz-------*/
    BCSCTL1 &= ~XT2OFF;                 //��XT2��Ƶ��������
    do
    {
        IFG1 &= ~OFIFG;                 //�������ʧ�ܱ�־
        for (i = 0xFF; i > 0; i--);     //�ȴ�8MHz��������
    }
    while ((IFG1 & OFIFG));             //����ʧЧ��־��Ȼ���ڣ�
    BCSCTL2 |= SELM_2 + SELS;           //MCLK��SMCLKѡ���Ƶ����
    
    TACTL |= TASSEL_2 + ID_3 + MC_1;    //����ʱ��ѡ��SMLK=8MHz��1/8��Ƶ��Ϊ1MHz
    
    P1IES = 0x0f;                       // P1.0~P1.3ѡ���½����ж�
    P1IE = 0x0f;                        // ���ж�ʹ��
    P1DIR = BIT7;                       //����P1.0~P.3Ϊ����״̬��P.7Ϊ���
    P1OUT = 0;
    P2DIR = 0xff;
    P2OUT = 0xff;
    P6DIR |= BIT7;                      //��������ӦIO����Ϊ���
    P6OUT |= BIT7;
    
    _EINT();
    LPM1;
}
// Timer A0 interrupt service routine
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
  P6OUT ^= BIT7;                        // Toggle P6.7
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
    uchar i;
    
    for(i = 7; i > 0; i--)
    {
        for(tmp = 12000;tmp > 0;tmp--);
    }
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
                            TACCR0 = 250;               // 2KHz
                            TACCTL0 |= CCIE; 
                            P2OUT = 0xfe;
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
                            TACCR0 = 125;               // 4KHz
                            TACCTL0 |= CCIE;                            
                            P2OUT = 0x0fd;
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
                            TACCR0 = 83;               // 6KHz
                            TACCTL0 |= CCIE;                            
                            P2OUT = 0xfb;
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
                            P6OUT |= BIT7; 
                            TACCTL0 &= ~CCIE;             //ֹͣ����
                            P2OUT = 0xf7;                 
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
    
    P1IFG = 0;
}
