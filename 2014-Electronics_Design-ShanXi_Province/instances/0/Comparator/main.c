
#include <msp430x14x.h>
#include "BoardConfig.h"

void main(void)
{
    WDTCTL = WDTHOLD + WDTPW;         // �ؿ��Ź�
    BoardConfig(0xb0);                //����ˮ�ƣ�������ܺ͵�ƽת��
    CACTL1 = CARSEL + CAREF0 + CAON ; //  Vcc/4 = - cmp      
    CACTL2 = P2CA0;                   // ʹ�� CA0 
    P2DIR = 0xff;
    P2OUT = 0xff;
    
    while(1)
    {  
        if((CACTL2 | 0xfe) ==0xff)
        {                             // �Ƚϵ�ѹ�Ƿ񳬹�0.25Vcc
          P2OUT &= ~BIT4;   
          CACTL1 &= 0xfe;             // CAIFG = 0               
        }
        else
        {
          P2OUT |= BIT4;
        }
    }      
}