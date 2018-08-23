#include  <msp430x14x.h>

/*******************************************
函数名称：nit_UART0
功    能：初始化UART0端口寄存器
参    数：无
返回值  ：无
********************************************/
void Init_UART0(void)
{
    P3SEL |= 0x30;                            // 选择P3.4和P3.5做UART通信端口
    ME1 |= UTXE0 + URXE0;                     // 使能USART0的发送和接受
    UCTL0 |= CHAR;                            // 选择8位字符
    UTCTL0 |= SSEL0;                          // UCLK = ACLK
    UBR00 = 0x03;                             // 波特率9600
    UBR10 = 0x00;                             //
    UMCTL0 = 0x4A;                            // Modulation
    UCTL0 &= ~SWRST;                          // 初始化UART状态机
}

void Send_Char(unsigned char schar)
{   
    while(!(IFG1 & UTXIFG0));                 //等待字符发送结束
    TXBUF0 = schar;
}
    
