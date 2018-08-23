/***********************************************
程序功能：实现流水灯以三种流动方式和四种流动速度
          的不同组合而进行点亮"流动"
------------------------------------------------
测试说明：观察流水灯流动顺序和速度的变化
************************************************/
#include  <msp430x14x.h>
#include  "BoardConfig.h"

uint i = 0,j = 0,dir = 0;
uint flag = 0,speed = 0;  //flag--灯光流动方式，speed--灯光流动速度

/****************主函数****************/
void main(void)
{
  
    WDTCTL = WDTPW + WDTHOLD;       //关闭看门狗
    BoardConfig(0xf0);
    
    CCTL0 = CCIE;                   //使能CCR0中断
    CCR0 = 50000;
    TACTL = TASSEL_2 + ID_3 + MC_1; //定时器A的时钟源选择SMCLK，增计数模式
    P2DIR = 0xff;                   //设置P2口方向为输出
    P2OUT = 0xff;
 
    _EINT();                        //使能全局中断
    LPM0;                           //CPU进入LPM0模式
}

/*******************************************
函数名称：Timer_A 
功    能：定时器A的中断服务函数，在这里通过标志
          控制流水灯的流动方向和流动速度
参    数：无
返回值  ：无
********************************************/
#pragma vector = TIMERA0_VECTOR
__interrupt void Timer_A (void)
{  
    if(flag == 0)
    {
        P2OUT = ~(0x80>>(i++));    //灯的点亮顺序D8 -> D1
    }
    else if(flag == 1)
    {
        P2OUT = ~(0x01<<(i++));    //灯的点亮顺序D1 -> D8
    }
    else 
    {
        if(dir)                  //灯的点亮顺序  D8 -> D1,D1 -> D8,循环绕圈                        
        {
            P2OUT = ~(0x80>>(i++));
        }
        else
        {
            P2OUT = ~(0x01<<(i++));
        }
    }
  
    if(i == 8) 
    {
        i = 0;
        dir = ~dir;
    }
  
    j++;
    if(j == 40) 
    {
        i = 0;
        j = 0;
        flag++;
        if(flag == 4) flag = 0;
        switch(speed)
        {
        case 0:
            TACTL &=~ (ID0 + ID1);
            TACTL |= ID_3;
            break;
        case 1:
            TACTL &=~ (ID0 + ID1);
            TACTL |= ID_2;
            break;
        case 2:
            TACTL &=~ (ID0 + ID1);
            TACTL |= ID_1;
            break;
        case 3:
            TACTL &=~ (ID0 + ID1);
            TACTL |= ID_0;
            break;
        default:
            break;
        }
        if(flag != 3)   speed++;
        if(speed == 4) speed = 0;
    } 
}

