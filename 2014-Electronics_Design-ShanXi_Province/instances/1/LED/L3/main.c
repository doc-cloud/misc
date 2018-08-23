/*******************************************************
程序功能：用从P2.3和P2.4输出的PWM波形驱动LED闪烁
          P2.3口输出方波的占空比为75%
          P2.4口输出方波的占空比为25%
-------------------------------------------------------
测试说明：观察LED的亮灭的时间长短
*******************************************************/
#include  <msp430x14x.h>
#include  "BoardConfig.h"
void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // 关狗
  BoardConfig(0xb0);                        // 关闭数码管和电平转换，打开流水灯
  P2DIR = 0xff; 
  P3DIR = BIT4;                             // P2端口设置为输出
  P2OUT = 0xff;
  P3OUT = BIT4;                             // 关闭其他LED
  P2SEL |= BIT3 + BIT4;                     // P2.3和P2.4连接内部模块
  P3SEL |= BIT4;
  CCR0 = 4096-1;                            // PWM周期为1S
  CCTL1 = OUTMOD_2;                         // CCR1 reset/set
  CCR1 = 3072;                              // CCR1 PWM duty cycle
  CCTL2 = OUTMOD_2;                         // CCR2 reset/set
  CCR2 = 1024;                              // CCR2 PWM duty cycle
  TACTL = TASSEL_1 + ID_3 + MC_1;           // ACLK/8, up mode

  _BIS_SR(LPM3_bits);                       // Enter LPM3
}
