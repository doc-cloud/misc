/******************************************************
程序功能：接收来自PC机的字符，然后重新发送给PC机
-------------------------------------------------------
通信格式：N.8.1,  9600
         无校验，8个数据位，1个停止位，波特率9600
------------------------------------------------------
测试说明：打开SSCOM，正确设置通信格式，向学习板发送一个
          字符或者是字符串（字符和字符串结尾必须添加结束
          符'\'），观察PC机是否正确收到回发的字符
*******************************************************/
#include  <msp430x14x.h>
#include  "BoardConfig.h"

uchar  RecBuf[256];
uchar  Windex;
uchar  Rindex; 

void Send1Char(uchar sendchar);
void PutString(uchar *ptr);
/********************主函数********************/
void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;                 // 关闭看门狗
    BoardConfig(0xb8);                        // 关闭数码管、流水灯和电平转换
    
    P3SEL |= 0x30;                            // 选择P3.4和P3.5做UART通信端口
    ME1 |= UTXE0 + URXE0;                     // 使能USART0的发送和接受
    UCTL0 |= CHAR;                            // 选择8位字符
    UTCTL0 |= SSEL0;                          // UCLK = ACLK
    UBR00 = 0x03;                             // 波特率9600
    UBR10 = 0x00;                             //
    UMCTL0 = 0x4A;                            // Modulation
    UCTL0 &= ~SWRST;                          // 初始化UART状态机
    IE1 |= URXIE0;                            // 使能USART0的接收中断
    _EINT();                                  //打开全局中断
    
    Windex = 0;
    Rindex = 0;
    
    PutString("     这是一个测试能够显示中文的串口调试工具SSCOM32的示例程序");
    PutString("请在发送栏输入单个或多个字符（英文字母、数字或者汉字，可以任意组合），\
               但是在字符的结尾必须添加结束符号'\\'，点击发送后观察PC机屏幕显示接收结果");
    while(1)
    {
        while(Rindex != Windex)
        {
            Send1Char(RecBuf[Rindex++]);             //将收到的字符发送出去
            Rindex &= 0x3f;
        } 
        Send1Char(0x0d);   //说明0x0d0a是软件SSCOM32的换行指令
        Send1Char(0x0a);
        LPM1;
    }
}
/*******************************************
函数名称：UART0_RXISR
功    能：UART0的接收中断服务函数，在这里唤醒
          CPU，使它退出低功耗模式
参    数：无
返回值  ：无
********************************************/
#pragma vector = UART0RX_VECTOR
__interrupt void UART0_RXISR(void)
{
    if(RXBUF0 == '\\')   LPM1_EXIT;
    else
    {
        RecBuf[Windex++] = RXBUF0;
        Windex &= 0x3f;
    }
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
      TXBUF0 = 0x0d;  
      while (!(IFG1 & UTXIFG0));
      TXBUF0 = 0x0a;                              //发送换行指令
}
