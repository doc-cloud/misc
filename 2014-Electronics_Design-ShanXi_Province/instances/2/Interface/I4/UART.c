#include <msp430.h>
#include <ctype.h> 
typedef unsigned char uchar;

/*******************************************
函数名称：InitUART0
功    能：初始化UART0端口
参    数：无
返回值  ：无
********************************************/
void InitUART0(void)
{
    P3SEL |= 0x30;                            // P3.4,5 = USART0 TXD/RXD
    ME1 |=  UTXE0;                            // Enable USART0 TXD
    UCTL0 |= CHAR;                            // 8-bit character
    UTCTL0 |= SSEL0;                          // UCLK = ACLK
    UBR00 = 0x03;                             // 32k/9600
    UBR10 = 0x00;                             //
    UMCTL0 = 0x4a;                            // Modulation
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
/*******************************************
函数名称：InitUART1
功    能：初始化UART1端口
参    数：无
返回值  ：无
********************************************/
void InitUART1(void)
{
    P3SEL |= 0xC0;                            //将P3.6，P3.7选做UART1的通信端口
    ME2 |= URXE1;                             //使能USART1的RXD
    UCTL1 |= CHAR;                            //选择8-bit字符
    UTCTL1 |= SSEL0;                          //驱动时钟选择ACLK
    UBR01 = 0x03;                             //波特率9600
    UBR11 = 0x00;
    UMCTL1 = 0x4a;                            //调整
    UCTL1 &= ~SWRST;                          //初始化UART状态机
    IE2 |= URXIE1;                            //使能接收中断
}
