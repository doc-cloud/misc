/****************************************************
程序功能：用两个按键控制DAC的输出电压驱动LED发光
----------------------------------------------------
跳线设置：将跳线座J1的1脚和2脚（靠上面的两个）短接
-----------------------------------------------------
测试说明：按动K3键可以减小DAC的输出电压；
          按动K4键可以增加DAC的输出电压。
          观察LED亮度变化。
******************************************************/
#include <msp430x14x.h>
#include "BoardConfig.h"
#include "IIC.h"

uchar   DAC_Val;          //DAC输出数据

void delay20ms(void);
uchar Write_DAC(uchar wdata);
/****************主函数****************/
void main(void)
{
    uchar keyval;
    
    WDTCTL = WDTPW + WDTHOLD;   //停止看门狗
    BoardConfig(0xb8);
    
    Set_IO();                   //设置IIC端口 
    P1DIR |= BIT7;              //P1.7输出低电平控制键盘工作于独立按键模式
    P1OUT &= ~BIT7;
    DAC_Val = 0xff;
    Write_DAC(DAC_Val);
    while(1)
    {
        if((P1IN & 0x0c) != 0x0c)
        {
            delay20ms();
            if((P1IN & 0x0c) != 0x0c)
            {
                keyval = P1IN & 0x0c;
                while((P1IN & 0x0c) != 0x0c);       //等待按键放开
                if(keyval == 0x04)                  //如果是K3键按下
                {
                     DAC_Val -= 20;                 //DAC的输出减少20个偏置量
                     Write_DAC(DAC_Val);            //写入DAC
                }
                else if(keyval == 0x08)             //如果是K4键按下 
                {
                     DAC_Val += 20;                 //DAC的输出增加20个偏置量
                     Write_DAC(DAC_Val);            //写入DAC   
                }
                else
                {
                     _NOP();
                }
            }
        }
    }
}
/*******************************************
函数名称：delay20ms
功    能：用于消抖的延时
参    数：无
返回值  ：无
********************************************/
void delay20ms(void)
{
    uint tmp;
    
    for(tmp = 12000;tmp > 0;tmp--);
}

/*******************************************
函数名称：Write_DAC
功    能：向DAC中写入输出电压数据
参    数：无
返回值  ：写入结果：1--成功，0--失败
********************************************/
uchar Write_DAC(uchar wdata)
{
    start();
    write1byte(0x98);   //DAC的设备地址
    if(check())   write1byte(wdata >> 4);   //写控制模式和电压数据的高四位
    else          return 0;
    if(check())   write1byte(wdata << 4);  //写电压数据的低四位
    else          return 0;
    if(check())	  stop();
    else          return 0;
    return 1;    
}
