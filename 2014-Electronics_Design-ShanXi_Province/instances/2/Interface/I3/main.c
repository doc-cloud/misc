/***************************************************************
程序功能：学习班作为通信中继，将从RS232端口接收到的数据通过RS485
          端口发送出去
----------------------------------------------------------------
通信格式：N.8.1, 9600
----------------------------------------------------------------
测试说明：用串口线连接学习板与PC机，打开串口调试精灵，正确设置通
          信格式，通过软件向学习板发送数据。用示波器观察RS485端
          口A、B信号线上的波形或者用RS485接收器接收发送的字符。
***************************************************************/
#include  <msp430x14x.h>
#include  "BoardConfig.h"
#include  "UART.h"

#define DRE_out     P3DIR |= BIT3     //连接485芯片的DE，RE端口的IO设置为输出状态
#define DE          P3OUT |= BIT3     //设置485芯片处于发送状态 
#define RE          P3OUT &= ~BIT3    //设置485芯片处于接收状态

uchar Windex=0,Rindex=0;
uchar Recbuf[64];


/****************主函数****************/
void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;                 //关闭看门狗
    BoardConfig(0xb8);                        //关闭流水灯、数码管和电平转换
    
    InitUART0();                              //初始化RS232端口
    DRE_out;
    DE;
    InitUART1();                              //初始化RS485端口
    
    _EINT();
    while(1)
    {
        if(Windex != Rindex)
        {
            while(!(IFG2 & UTXIFG1));               //等待发送结束 
            TXBUF1 = Recbuf[Windex++];
            Windex &= 0x3f;
        }
    }
}
/*******************************************
函数名称：UART0_RXISR
功    能：UART0的接收中断服务函数
参    数：无
返回值  ：无
********************************************/
#pragma vector = UART0RX_VECTOR
__interrupt void UART0_RXISR(void)
{    
    Recbuf[Rindex++] = RXBUF0;   //将接收到的数据存放到缓存中
    Rindex &= 0x3f;
}
