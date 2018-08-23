#include <msp430.h>
#include <ctype.h> 
typedef unsigned char uchar;

/*******************************************
函数名称：InitUART
功    能：初始化UART端口
参    数：无
返回值  ：无
********************************************/
void InitUART(void)
{
    P3SEL |= 0x30;                            // P3.4,5 = USART0 TXD/RXD
    ME1 |= URXE0 + UTXE0;                             // Enable USART0 T/RXD
    UCTL0 |= CHAR;                            // 8-bit character
    UTCTL0 |= SSEL0;                          // UCLK = ACLK
    UBR00 = 0x1B;                             // 32k/1200
    UBR10 = 0x00;                             //
    UMCTL0 = 0x03;                            // Modulation
    UCTL0 &= ~SWRST;                          // Initialize USART state machine
    IE1 |= URXIE0;                            //使能接收中断
}
/*******************************************
函数名称：Send1Char
功    能：向PC机发送一个字符
参    数：sendchar--要发送的字符
返回值  ：无
********************************************/
void Send1Char(uchar sendchar)
{
      while (!(IFG1 & UTXIFG0));    //等待发送寄存器为空         
      TXBUF0 = sendchar; 
   
}
/*******************************************
函数名称：PutSting
功    能：向PC机发送字符串
参    数：ptr--指向发送字符串的指针
返回值  ：无
********************************************/
void PutString(uchar *ptr)
{
      while(*ptr != '\0')
      {
            Send1Char(*ptr++);                     // 发送数据
      }
      while (!(IFG1 & UTXIFG0));
      TXBUF0 = '\n';                              //发送换行指令
}
/*******************************************
函数名称：Get1Char
功    能：接收一个来自PC机的字符
参    数：无
返回值  ：接收到的字符
********************************************/
uchar Get1Char(void)
{
    while (!(IFG1 & URXIFG0));    //等待接收到字符        
    return  RXBUF0;
}
