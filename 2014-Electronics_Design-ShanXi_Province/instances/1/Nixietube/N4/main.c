/**********************************************
程序功能：在六位数码管上显示一个来回移动的光标，
          光标的移动速度是固定的，约为250ms移动
          一格
-----------------------------------------------
测试说明：观察数码管显示
***********************************************/
#include  <msp430x14x.h>
#include  "BoardConfig.h"

#define NBIT(x)     ~(1 << x)

//显示字符的控制变量
uchar step = 0;
//绕动圈数的变量
uint circle = 0;

/********************主函数********************/
void main(void)
{
    WDTCTL = WDT_ADLY_1000;       //看门狗工作在定时器模式，间隔250ms
    IE1 |= WDTIE;                 // 使能看门狗中断    
    BoardConfig(0x88);
  
    P4DIR = 0xff;                 //设置P4，P5的IO方向为输出
    P5DIR = 0xff;                 
  
    P4OUT = 0x40;                 //设置P4，P5的输出初值
    P5OUT = 0xff;
  
    _BIS_SR(LPM3_bits + GIE);     //CPU进入LPM3低功耗模式，同时打开全局中断
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
    step++;
    if(step == 10)  
    {
        step = 0;
    }
    switch(step)
    {
    case 0:
            P5OUT = NBIT(5);
            break;
    case 1: 
            P5OUT = NBIT(4);
            break;
    case 2:
            P5OUT = NBIT(3);
            break;
    case 3: 
            P5OUT = NBIT(2);
            break;
    case 4:
            P5OUT = NBIT(1);
            break;
    case 5:
            P5OUT = NBIT(0);
            break;
    case 6:
            P5OUT = NBIT(1);
            break;
    case 7:
            P5OUT = NBIT(2);
            break;
    case 8:
            P5OUT = NBIT(3);
            break;
    case 9:
            P5OUT = NBIT(4);
            break;
    }
}

