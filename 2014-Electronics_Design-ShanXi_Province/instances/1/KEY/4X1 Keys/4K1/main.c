/***************************************************
程序功能：用扫描方式读取四个独立式按键的键值，同时将
          按键的键值在数码管上显示出来   
----------------------------------------------------
测试说明：按动K1~k4四个按键，观察数码管显示
***************************************************/
#include <msp430x14x.h>
#include "BoardConfig.h"

#define keyin    (P1IN & 0x0f)

//数码管7位段码：0--f
uchar scandata[16] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
                      0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};

void delay(void);

/********************主函数********************/
void main( void )
{
    uchar temp,keyval = 0;
    
    WDTCTL = WDTPW + WDTHOLD;   //关闭看门狗
    BoardConfig(0x88);          //打开数码管，关闭流水灯和电平转换
    
    P1DIR = BIT7;               //设置P1.0~P.3为输入状态，P.7为输出
    P1OUT = 0;
    P3DIR |= BIT4;              //设置P3.4为输出状态
    P3OUT |= BIT4;              //P3.4输出1
    P4DIR = 0xff;
    P5DIR = 0xff;
    P4OUT = 0x3f;
    P5OUT = 0xf7;
    while(1)
    {
        if(keyin != 0x0f)       //如果有键被按下
        {
            delay();            //延时消抖
            if(keyin != 0x0f)   //再次检测按键状态
            {
                temp=keyin;
                while(keyin != 0x0f);   //等待按键被放开
                switch(temp)    //转换键值    
                {
                case 0x0e:
                            keyval = 1;break;
                case 0x0d:
                            keyval = 2;break;
                case 0x0b:
                            keyval = 3;break;
                case 0x07:
                            keyval = 4;break;
                default:
                            keyval = 0;break;
                }
                P4OUT = scandata[keyval]; //用一位数码管显示
                P3OUT &= ~BIT4;           //P3.4连接的LED闪烁一下
                delay();delay();
                P3OUT |= BIT4;
            }
        }
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
