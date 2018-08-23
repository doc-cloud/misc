/****************************************************************
程序功能：将MCU片内的MCLK,SMCLK和ACLK三个信号转换成5V电平信号
-----------------------------------------------------------------
测试说明：用户可以用示波器测量连接器P7的第6、7、8三个引脚的
          输出波形（P7的右侧起是第1引脚）
****************************************************************/
#include  <msp430x14x.h>
#include  "BoardConfig.h"

void main(void)
{
  BoardConfig(0x38);                        // 打开电平转换，关闭流水灯和数码管
  WDTCTL = WDTPW +WDTHOLD;                  // 关狗
  DCOCTL = DCO0 + DCO1 + DCO2;              // Max DCO
  BCSCTL1 = RSEL0 + RSEL1 + RSEL2;          // XT2on, max RSEL
  BCSCTL2 |= SELS;                          // SMCLK = XT2
  P5DIR |= 0x70;                            // P5.6,5,4 outputs
  P5SEL |= 0x70;                            // P5.6,5,5 options

  while(1);
}
