/*****************************************************
程序功能：MCU不停向PC机发送数据,在屏幕上显示0~127对应
          的ASCII字符
------------------------------------------------------
通信格式：N.8.1, 2400
------------------------------------------------------
测试说明：打开串口调试助手，正确设置通信格式，观察屏幕
******************************************************/

#include  <msp430x14x.h>
#include  "BoardConfig.h"

void Delays(void);
void PutString(uchar *ptr);
   unsigned char ch;
/********************主函数**********************/
void main(void)
{

  
    WDTCTL = WDTPW + WDTHOLD;                 // 关狗
    BoardConfig(0xb8);                        // 关流水灯、蜂鸣器和数码管
    P3SEL |= 0x30;
    P3DIR = BIT4;                             // P3.4,5选择为UART收发端口
    ME1 |= UTXE0 + URXE0;                     // 使能USART0收发
    UCTL0 |= CHAR;                            // 8-bit character
    UTCTL0 |= SSEL0;                          // UCLK = ACLK
    UBR00 = 0x0D;                             // 32k/2400 - 13.65
    UBR10 = 0x00;                             //
    UMCTL0 = 0x6B;                            // Modulation
    UCTL0 &= ~SWRST;                                            // 初始化UART0状态机
    IE1 |= URXIE0;   
  //  IE1 |= UTXIE0; 
    _EINT();
 
    TXBUF0='s';
    while(1)
    { 
 
    
    }
} 

#pragma vector=UART0RX_VECTOR
 __interrupt void uart(void)
 {
   while (!(IFG1 & UTXIFG0));  
   TXBUF0 = RXBUF0;   
  // TXBUF0 = RXBUF0;
 }   

