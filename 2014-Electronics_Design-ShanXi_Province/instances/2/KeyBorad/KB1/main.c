/***********************************************************
程序功能：扫描4X4键盘,当有键按下被识别以后蜂鸣器鸣响一声，并
          将键值在数码管和8个LED上显示,同时将键值通过串口发
          送给PC机
-------------------------------------------------------------
跳线设置：将跳线座J3上的短路帽拔下
-------------------------------------------------------------
通信格式：N.8.1, 9600
-------------------------------------------------------------
测试说明：打开串口调试精灵正确通信格式，按动K1~K16按键，观察
          数码管和流水灯显示聆听蜂鸣器是否发声，观察PC屏幕显
          示键值（串口调试精灵的显示格式要设置为16进制）
*************************************************************/
#include <msp430x14x.h>
#include "BoardConfig.h"
#include "Keypad.h"
#include "gdata.h"

void Init_UART0(void);
/********************主函数********************/
void main(void)
{
    uint i;
    
    BoardConfig(0x80);            //打开数码管和流水灯，关闭电平转换        
    WDTCTL = WDT_ADLY_1_9;        //设置内部看门狗工作在定时器模式，1.9ms中断一次
    IE1 |= WDTIE;                 //使能看门狗中断
  
    P2DIR = 0xff;                 //设置P2端口为输出           
    P2OUT = 0xff;
    P4DIR = 0xff; 
    P5DIR = 0xff;
    P5OUT = 0xff;
    P6DIR |= BIT7;
    
    Init_UART0();                 //初始化UART0
    Init_Keypad();                //初始化键盘端口
    
    _EINT();                      //打开全局中断  
    while(1)
    {
        Key_Event();
    
        if(key_Flag == 1)
        {
            key_Flag = 0;  
            
            Dispbuf[0] = key_val / 10;      //数码管显示键值
            Dispbuf[1] = key_val % 10;
            
            P2OUT = ~(key_val);             //LED显示键值
            
            while (!(IFG1 & UTXIFG0));      //等待以前的字符发送完毕
            TXBUF0 = key_val;                //将键值发送出去 
            
            P6OUT = 0;                      //蜂鸣器响一声
            for(i = 2000; i > 0; i--);
            P6OUT |= BIT7;            
        }
    }
}
/*******************************************
函数名称：watchdog_timer
功    能：看门狗中断服务函数，在这里输出数码
          管的段选和位选信号
参    数：无
返回值  ：无
********************************************/
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{ 
    P5OUT = 0xff;
    P4OUT = scandata[Dispbuf[cnt]];         //输出段选信号
    P5OUT &= ~(1 << (cnt+2));               //输出位选信号
  
    cnt++;                                  //位计数变量在0~1之间循环
    if(cnt == 2) cnt = 0;
}
/*******************************************
函数名称：Init_UART0
功    能：初始化UART0端口
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

