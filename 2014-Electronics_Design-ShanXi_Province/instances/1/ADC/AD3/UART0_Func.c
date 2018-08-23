#include <msp430.h>
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
    UBR00 = 0x03;                             // 32k/9600 - 3.41
    UBR10 = 0x00;                             //
    UMCTL0 = 0x4A;                            // Modulation
    UCTL0 &= ~SWRST;                          // Initialize USART state machine
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
功    能：向PC机发送字符串并换行指令
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
函数名称：PutSting0
功    能：向PC机发送字符串，无换行
参    数：ptr--指向发送字符串的指针
返回值  ：无
********************************************/
void PutString0(uchar *ptr)
{
      while(*ptr != '\0')
      {
            Send1Char(*ptr++);                     // 发送数据
      }
}
