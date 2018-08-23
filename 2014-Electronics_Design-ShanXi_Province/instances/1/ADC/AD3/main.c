/*********************************************************
程序功能：将ADC对P6.0端口电压的转换结果按转换数据和对应的
          模拟电压的形式通过串口发送到PC机屏幕上显示
-----------------------------------------------------------
通信格式：N.8.1, 9600
-----------------------------------------------------------
测试说明：打开串口调试精灵，正确设置通信格式，观察接收数据
**********************************************************/
#include <msp430.h>
#include "BoardConfig.h"
#include "allfunc.h"

#define   Num_of_Results   32
uint results[Num_of_Results];    //保存ADC转换结果的数组
uint average;
uchar tcnt = 0;

/***********************主函数***********************/
void main( void )
{
    uchar i;
    uchar buffer[5];
    
    WDTCTL = WDTPW + WDTHOLD;           //关狗
    BoardConfig(0xb8);                  //关数码管，流水灯和电平转换
    
    InitUART();
    Init_ADC();
    _EINT();
    
    buffer[4] = '\0';
    while(1)
    {
        LPM1;
        Hex2Dec(average,buffer);
        for(i = 0; i < 4; i++)
            buffer[i] += 0x30;
        PutString0("The digital value is: ");
        PutString(buffer);
        
        
        Trans_val(average,buffer);
        buffer[3] = buffer[2];
        buffer[2] = buffer[1];
        buffer[1] = 0x2e - 0x30;
        for(i = 0; i < 4; i++)
            buffer[i] += 0x30;
        PutString0("The analog value is: ");
        PutString(buffer);     
    }
    
}

/*******************************************
函数名称：ADC12ISR
功    能：ADC中断服务函数，在这里用多次平均的
          计算P6.0口的模拟电压数值
参    数：无       
返回值  ：无
********************************************/
#pragma vector=ADC_VECTOR
__interrupt void ADC12ISR (void)
{
    static uchar index = 0;
  
    results[index++] = ADC12MEM0;               // Move results
    if(index == Num_of_Results)
    {
        uchar i;

        average = 0;
        for(i = 0; i < Num_of_Results; i++)
        {
            average += results[i];
        }
        average >>= 5;                            //除以32
        
        index = 0;
        tcnt++;
        if(tcnt == 250)      //主要是降低串口发送速度
        {
            LPM1_EXIT;
            tcnt = 0;
        }
    }
}
