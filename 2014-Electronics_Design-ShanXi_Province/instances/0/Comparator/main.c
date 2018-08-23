
#include <msp430x14x.h>
#include "BoardConfig.h"

void main(void)
{
    WDTCTL = WDTHOLD + WDTPW;         // 关看门狗
    BoardConfig(0xb0);                //开流水灯，关数码管和电平转换
    CACTL1 = CARSEL + CAREF0 + CAON ; //  Vcc/4 = - cmp      
    CACTL2 = P2CA0;                   // 使用 CA0 
    P2DIR = 0xff;
    P2OUT = 0xff;
    
    while(1)
    {  
        if((CACTL2 | 0xfe) ==0xff)
        {                             // 比较电压是否超过0.25Vcc
          P2OUT &= ~BIT4;   
          CACTL1 &= 0xfe;             // CAIFG = 0               
        }
        else
        {
          P2OUT |= BIT4;
        }
    }      
}