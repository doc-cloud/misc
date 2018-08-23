/*********************************************************
程序功能：在PC机上用SSCOM32显示DS18B20测量温度结果
-----------------------------------------------------------
通信格式：N.8.1,  9600
-----------------------------------------------------------
测试说明：打开SSCOM32正确设置通信格式，观察屏幕显示的测温
          结果
**********************************************************/
#include <msp430.h>
#include "BoardConfig.h"
#include "uart0.h"
#include "DS18B20.h"

void Transfer(uint temper, uchar dN[6]);
/**************************主函数**************************/
void main( void )
{
    uint tmp;
    uchar i;
    uchar Dec[6];
    
    WDTCTL = WDTPW + WDTHOLD;           //关狗
    BoardConfig(0xb8);                  //关数码管，流水灯和电平转换
    /*------选择系统主时钟为8MHz-------*/
    BCSCTL1 &= ~XT2OFF;                 //打开XT2高频晶体振荡器
    do
    {
        IFG1 &= ~OFIFG;                 //清除晶振失败标志
        for (i = 0xFF; i > 0; i--);     //等待8MHz晶体起振
    }
    while ((IFG1 & OFIFG));             //晶振失效标志仍然存在？
    BCSCTL2 |= SELM_2 + SELS;           //MCLK和SMCLK选择高频晶振
    
    TACTL |= TASSEL_2 + ID_3;           //计数时钟选择SMLK=8MHz，1/8分频后为1MHz    
    
    InitUART();                         //初始化UART端口
    
    PutString("下面显示DS18B20测量温度数值：");
    while(1)
    {
        tmp = Do1Convert();
        Transfer(tmp,Dec);
        if(tmp & 0xf800)        //如果符号位是1
        {
            Send1Char('-');     //显示负号
        }
        for(i = 0;i < 6;i++)
        {
            Send1Char(Dec[5-i]+0x30);
            if(i == 1)
            {
                Send1Char('.');
            }
        
        }
        PutString("°C"); 
        
    }
    
}
/*******************************************
函数名称：Transfer
功    能：将从DS18B20读取的11bit温度数据转换
          成6位十进制数字表示的温度
参    数：temper--11bit温度数据
返回值  ：无
********************************************/
void Transfer(uint temper, uchar dN[6])
{
    uchar i;
    
    for(i = 0;i < 6;i++) dN[i] = 0; //初始化显示变量

    //数值转换
    if(temper & BIT0) 
    {
        dN[0] = 5;
        dN[1] = 2;
        dN[2] = 6;
    }
    if(temper & BIT1)     
    {
        dN[1] += 5;
        dN[2] += 2;
        dN[3] += 1;
    }
    if(temper & BIT2)     
    {
        dN[2] += 5;
        dN[3] += 2;
        if(dN[2] >= 10)
        {
            dN[2] -= 10;
            dN[3] += 1;
        }
    }
    if(temper&BIT3)     
    {
        dN[3] += 5;
    }
    if(temper & BIT4)
    {
        dN[4] += 1;
    }
    if(temper & BIT5)     
    {
        dN[4] += 2;
    }
    if(temper & BIT6)
    {
        dN[4] += 4;
    }
    if(temper & BIT7)     
    {
        dN[4] += 8;
        if(dN[4] >= 10)
        {
            dN[4] -= 10;
            dN[5] += 1;
        }
    }
    if(temper & BIT8)
    {
        dN[4] += 6;
        dN[5] += 1;
        if(dN[4] >= 10)
        {
            dN[4] -= 10;
            dN[5] += 1;
        }
    }
    if(temper & BIT9)
    {
        dN[4] += 2;
        dN[5] += 3;
        if(dN[4] >= 10)
        {
            dN[4] -= 10;
            dN[5] += 1;
        }
    }
    if(temper & BITA)
    {
        dN[4] += 4;
        dN[5] += 6;
        if(dN[4] >= 10)
        {
            dN[4] -= 10;
            dN[5] += 1;
        }
        if(dN[5] >= 10)
        {
            dN[5] -= 10;
        }
    }
}
