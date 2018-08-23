/*******************************************************
�����ܣ��ô�P2.3��P2.4�����PWM��������LED��˸
          P2.3�����������ռ�ձ�Ϊ75%
          P2.4�����������ռ�ձ�Ϊ25%
-------------------------------------------------------
����˵�����۲�LED�������ʱ�䳤��
*******************************************************/
#include  <msp430x14x.h>
#include  "BoardConfig.h"
void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // �ع�
  BoardConfig(0xb0);                        // �ر�����ܺ͵�ƽת��������ˮ��
  P2DIR = 0xff; 
  P3DIR = BIT4;                             // P2�˿�����Ϊ���
  P2OUT = 0xff;
  P3OUT = BIT4;                             // �ر�����LED
  P2SEL |= BIT3 + BIT4;                     // P2.3��P2.4�����ڲ�ģ��
  P3SEL |= BIT4;
  CCR0 = 4096-1;                            // PWM����Ϊ1S
  CCTL1 = OUTMOD_2;                         // CCR1 reset/set
  CCR1 = 3072;                              // CCR1 PWM duty cycle
  CCTL2 = OUTMOD_2;                         // CCR2 reset/set
  CCR2 = 1024;                              // CCR2 PWM duty cycle
  TACTL = TASSEL_1 + ID_3 + MC_1;           // ACLK/8, up mode

  _BIS_SR(LPM3_bits);                       // Enter LPM3
}
