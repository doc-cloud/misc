/***************************************************************
程序功能：控制DAC输出模拟电压
----------------------------------------------------------------
跳线设置：可以将跳线座J1的1脚和2脚（靠上面的两个）短接，
          用DAC输出电压驱动LED；也可以不连接1脚和2脚，直
          接用电压表测量2脚与地之间的电压。
----------------------------------------------------------------
测试说明：控制程序运行到应设置断点处，观察LED亮度或者测量
          DAC的输出电压数值
***************************************************************/
#include <msp430x14x.h>
#include "BoardConfig.h"
#include "IIC.h"

uchar Write_DAC(uchar wdata);
/****************主函数****************/
void main(void)
{    
     uchar flag = 0;
  
     WDTCTL = WDTPW + WDTHOLD;    //停止看门狗
     BoardConfig(0xb8);           //关闭蜂鸣器、流水灯、电平转换
     
     Set_IO();                    //设置IIC使用的IO方向
     
     flag = Write_DAC(0x7f);  
     _NOP();            //此处设置断点，观察flag和DAC的输出电压
     flag = 0;
     flag = Write_DAC(0xa1);
     _NOP();            //此处设置断点，观察flag和DAC的输出电压
     flag = 0;
     flag = Write_DAC(0xc8);
     _NOP();            //此处设置断点，观察flag和DAC的输出电压
     flag = 0;
     flag = Write_DAC(0xff);
     _NOP();            //此处设置断点，观察flag和DAC的输出电压
     flag = flag - 1;   //此句为了消除编译器警告
     while(1)
        LPM3;    
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
    write1byte(0x98);                     //DAC的设备地址
    if(check())   write1byte(wdata>>4);   //写控制模式和电压数据的高四位
    else          return 0;
    if(check())   write1byte(wdata<<4);   //写电压数据的低四位
    else          return 0;
    if(check())	  stop();
    else          return 0;
    return 1; 
}
