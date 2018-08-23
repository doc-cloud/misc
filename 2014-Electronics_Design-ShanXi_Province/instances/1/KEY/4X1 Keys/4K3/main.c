/******************************************************
程序功能：用中断方式读取四个独立式按键的键值，同时用
          D1~D4四个LED的点亮来指示k1~K4四个按键的按下
----------------------------------------------------
测试说明：按动K1~k4四个按键，观察LED是否正确点亮
*******************************************************/
#include <msp430x14x.h>
#include "BoardConfig.h"

#define keyin    (P1IN & 0x0f)

uchar KeyVal = 0;   // 按键的键值

/********************主函数********************/
void main( void )
{   
    WDTCTL = WDTPW + WDTHOLD;   //关闭看门狗
    BoardConfig(0xb0);          //打开流水灯，关闭数码管和电平转换
    
    P1IES = 0x0f;               // P1.0~P1.3选择下降沿中断
    P1IE  = 0x0f;               // 打开中断使能
    P1DIR = BIT7;               //设置P1.0~P.3为输入状态，P.7为输出
    P1OUT = 0;
    P2DIR = 0xff;
    P2OUT = 0xff;
    _EINT();                    //打开全局中断控制位
    while(1)
    {
        LPM1;
        P2OUT = ~(1 << (KeyVal - 1));
    }
}
/*******************************************
函数名称：delay
功    能：用于消抖的延时
参    数：无
返回值  ：无
********************************************/
void delay(void)
{
    uint tmp;
    
    for(tmp = 12000;tmp > 0;tmp--);
}
/*******************************************
函数名称：PORT1_ISR 
功    能：P1端口的中断服务函数
参    数：无
返回值  ：无
********************************************/
#pragma vector=PORT1_VECTOR
__interrupt void  PORT1_ISR(void)
{
    if(P1IFG & 0x0f)
    {
        switch(P1IFG)
        {
        case 0x01:
                    if(keyin == 0x0e)   //如果是第一个按键被按下
                    {
                        delay();
                        if(keyin == 0x0e)
                        {
                            while(keyin != 0x0f);       //等待按键放开
                            KeyVal = 1;
                            LPM1_EXIT;
                            P1IFG = 0;
                            return;
                        }
                    }
        case 0x02:
                    if(keyin == 0x0d)   //如果是第二个按键被按下
                    {
                        delay();
                        if(keyin == 0x0d)
                        {
                            while(keyin != 0x0f);       //等待按键放开
                            KeyVal = 2;
                            LPM1_EXIT;
                            P1IFG = 0;
                            return;
                        }
                    }
        case 0x04:
                    if(keyin == 0x0b)   //如果是第三个按键被按下
                    {
                        delay();
                        if(keyin == 0x0b)
                        {
                            while(keyin != 0x0f);       //等待按键放开
                            KeyVal = 3;
                            LPM1_EXIT;
                            P1IFG = 0;
                            return;
                        }
                    }
        case 0x08:
                    if(keyin == 0x07)   //如果是第四个按键被按下
                    {
                        delay();
                        if(keyin == 0x07)
                        {
                            while(keyin != 0x0f);       //等待按键放开
                            KeyVal = 4;
                            LPM1_EXIT;
                            P1IFG = 0;
                            return;
                        }
                    }
        default:
                    while(keyin != 0x0f);       //等待按键放开
                    P1IFG = 0;
                    return;
        }
    }
}
