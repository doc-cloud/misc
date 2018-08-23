/**********************************************
程序功能：在六位数码管上显示一个绕动的光圈，光
          圈的速度自由变化（快-->慢-->快）
-----------------------------------------------
测试说明：观察数码管显示
***********************************************/
#include  <msp430x14x.h>
#include  "BoardConfig.h"

#define NBIT(x)     ~(1 << x)

//绕动光圈对应的字符
uchar scandata[16] = {0x01,0x01,0x01,0x01,0x01,0x01,0x20,0x10,
                      0x08,0x08,0x08,0x08,0x08,0x08,0x04,0x02};
//显示字符的控制变量
uchar step = 0;
//绕动圈数的变量
uint circle = 0;

/********************主函数********************/
void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;       //关闭看门狗    
    BoardConfig(0x88);
  
    P4DIR = 0xff;                 //设置P4，P5的IO方向为输出
    P5DIR = 0xff;                 
  
    P4OUT = 0x00;                 //设置P4，P5的输出初值
    P5OUT = 0xff;
    
    CCR0 = 164;
    TACCTL0 |= CCIE;              //使能比较中断
    TACTL |= TASSEL_1 + MC_1;     //ACLK, up mode
  
    _BIS_SR(LPM3_bits + GIE);     //CPU进入LPM3低功耗模式，同时打开全局中断
}

/*******************************************
函数名称：TimerA_ISR
功    能：定时器A中断服务函数，在这里输出数码管的
          段选和位选信号
参    数：无
返回值  ：无
********************************************/
#pragma vector=TIMERA0_VECTOR
__interrupt void TimerA_ISR(void)
{ 
    step++;
    if(step == 16)  
    {
        step = 0;
        circle++;
        if(circle == 10)        //如果已经绕动了10圈
        {
            circle = CCR0;
            CCR0 += circle;     //速度降为原来的一半
            if(CCR0 > 32700)    //如果速度到达底线，则从头开始
                CCR0 = 164;     
            circle = 0;
        }
    }
    switch(step)
    {
    case 0:
            P5OUT = NBIT(5);
            P4OUT = scandata[step];
            break;
    case 1: 
            P5OUT = NBIT(4);
            P4OUT = scandata[step];
            break;
    case 2:
            P5OUT = NBIT(3);
            P4OUT = scandata[step];
            break;
    case 3: 
            P5OUT = NBIT(2);
            P4OUT = scandata[step];
            break;
    case 4:
            P5OUT = NBIT(1);
            P4OUT = scandata[step];
            break;
    case 5:
            P5OUT = NBIT(0);
            P4OUT = scandata[step];
            break;
    case 6:
            P5OUT = NBIT(0);
            P4OUT = scandata[step];
            break;
    case 7:
            P5OUT = NBIT(0);
            P4OUT = scandata[step];
            break;
    case 8:
            P5OUT = NBIT(0);
            P4OUT = scandata[step];
            break;
    case 9:
            P5OUT = NBIT(1);
            P4OUT = scandata[step];
            break;
    case 10:
            P5OUT = NBIT(2);
            P4OUT = scandata[step];
            break;
    case 11:
            P5OUT = NBIT(3);
            P4OUT = scandata[step];
            break;
    case 12:
            P5OUT = NBIT(4);
            P4OUT = scandata[step];
            break;
    case 13:
            P5OUT = NBIT(5);
            P4OUT = scandata[step];
            break;
    case 14:
            P5OUT = NBIT(5);
            P4OUT = scandata[step];
            break;
    case 15:
            P5OUT = NBIT(5);
            P4OUT = scandata[step];
            break;
    }
}

