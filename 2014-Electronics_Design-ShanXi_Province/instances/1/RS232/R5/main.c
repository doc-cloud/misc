/*********************************************************
程序功能：用固定频率的方波驱动蜂鸣器，共16种音调；在蜂鸣器
          发出不同音调的同时，一个数码管显示音调的编号。
          PC机发送字符决定蜂鸣器发出何种鸣响音
-----------------------------------------------------------
通信格式：N.8.1,  9600
-----------------------------------------------------------
测试说明：打开串口调试助手，正确设置通信格式，由PC机向串口
          发送0~F十六个十六进制数字，观察蜂鸣器发声和数码管
          的显示情况
**********************************************************/
#include <msp430.h>
#include "BoardConfig.h"
#include "uart0.h"

uchar step = 0xff;

/**************************主函数**************************/
void main( void )
{
    uchar i;
    
    WDTCTL = WDTPW + WDTHOLD;           //关狗
    BoardConfig(0x88);                  //开数码管，关流水灯和电平转换
    
    /*------选择系统主时钟为8MHz-------*/
    BCSCTL1 &= ~XT2OFF;                 //打开XT2高频晶体振荡器
    do
    {
        IFG1 &= ~OFIFG;                 //清除晶振失败标志
        for (i = 0xFF; i > 0; i--);     //等待8MHz晶体起振
    }
    while ((IFG1 & OFIFG));             //晶振失效标志仍然存在？
    BCSCTL2 |= SELM_2 + SELS;           //MCLK和SMCLK选择高频晶振
    
    TACCTL0 |= CCIE;                    //使能比较中断
    TACTL |= TASSEL_2 + ID_3 ;          //计数时钟选择SMLK=8MHz，1/8分频后为1MHz
    _EINT();
    
    P6DIR = BIT7;                      //蜂鸣器对应IO设置为输出
    P6OUT = BIT7;
    P4DIR = 0xff;
    P5DIR = 0xff;
    P4OUT = 0x00;
    P5OUT = ~0x04;
    
    InitUART();                         //初始化UART端口
    
    DisplayConfigMenu();
    while(1)
    {
        Send1Char('>');
        Send1Char('\n');
        i=Get1Char();
        HandleConfigMenu(i);
    }
    
}
/*******************************************
函数名称：Timer_A
功    能：定时器A的中断服务函数，在这里驱动
          蜂鸣器发声
参    数：无
返回值  ：无
********************************************/
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
  P6OUT ^= BIT7;                            // Toggle P6.7
}
