/***********************************************
程序功能：扫描4X4键盘并将键值在数码管上显示
------------------------------------------------
跳线设置：将跳线座J3上的短路帽拔下
------------------------------------------------
测试说明：按动K1~K16按键，观察数码管显示，聆听
          按键时蜂鸣器是否发声
************************************************/
#include <msp430x14x.h>
#include "BoardConfig.h"
#include "Keypad.h"
#include "gdata.h"

/********************主函数********************/
void main(void)
{
    uint i;
    BoardConfig(0x80);            //打开数码管、流水灯,关闭电平转换        
    WDTCTL = WDT_ADLY_1_9;        //设置内部看门狗工作在定时器模式，1.9ms中断一次
    IE1 |= WDTIE;                 //使能看门狗中断
  
    P2DIR = 0xff;
    P4DIR = 0xff;                 //设置P4，P5的IO方向为输出
    P5DIR = 0xff;  
    P6DIR |= BIT7; 
    P2OUT = 0xff;
    P4OUT = 0x00;                 //设置P4，P5的输出初值
    P5OUT = 0xff;
    P6OUT |= BIT7;
    _EINT();                      //打开全局中断
    Init_Keypad();
    while(1)
    {
        Key_Event();
    
        if(key_Flag == 1)
        {
            key_Flag = 0;
            Dispbuf[0] = key_val / 10;
            Dispbuf[1] = key_val % 10;
            P2OUT = ~(key_val);         //LED显示键值
            P6OUT = 0;                  //蜂鸣器响一声
            for(i = 2000; i > 0; i--);
            P6OUT |= BIT7;
        }
    }
}
/*******************************************
函数名称：watchdog_timer
功    能：看门狗中断服务函数，在这里输出数码管的
          段选和位选信号
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

