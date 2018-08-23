/****************************************************
程序功能：在PC上用串口控制DAC输出的模拟电压值，用这个
          电压来驱动LED发光
----------------------------------------------------
跳线设置：将跳线座J1的1脚和2脚（靠上面的两个）短接
----------------------------------------------------
通信格式：N.8.1, 9600
-----------------------------------------------------
测试说明：打开SSCOM332正确设置通信格式，根据提示信息
          输入控制数据进行测试
******************************************************/
#include <msp430x14x.h>
#include "BoardConfig.h"
#include "uart0.h"
#include "IIC.h"

uchar Write_DAC(uchar wdata);
/****************主函数****************/
void main(void)
{
    uchar ctrlvalue;
    
    WDTCTL = WDTPW + WDTHOLD;   //停止看门狗
    BoardConfig(0xb8);          //关闭数码管、流水灯和电平转换
    InitUART();                 //初始化UART端口
    Set_IO();                   //设置DAC控制端口对应的IO
    
    PutString("请用16进制格式输入DAC的控制电压：");
    while(1)
    {
        ctrlvalue = Get1Char();
        if(Write_DAC(ctrlvalue))
        {
            PutString("操作成功");   
        }
        else
        {
            PutString("操作失败，请重新发送控制电压");
        }
    }
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
