/*************************************************
程序功能：用DS18B20测量室温并在数码管上显示。
-------------------------------------------------
测试说明：观察显示温度数值。
*************************************************/
#include <msp430x14x.h>
#include "BoardConfig.h"
#include "DS18B20.h"

//要显示的6位温度数字
uchar dN[6];        
//数码管七段码；0--f
uchar scandata[16] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
                      0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
//数码管位选变量
uchar cnt = 0;  

void Disp_Numb(uint temper);

/****************主函数****************/
void main(void)
{
    uchar i;
    
    WDTCTL=WDTPW+WDTHOLD; 
     
    /*------选择系统主时钟为8MHz-------*/
    BCSCTL1 &= ~XT2OFF;                 //打开XT2高频晶体振荡器
    do
    {
        IFG1 &= ~OFIFG;                 //清除晶振失败标志
        for (i = 0xFF; i > 0; i--);     //等待8MHz晶体起振
    }
    while ((IFG1 & OFIFG));             //晶振失效标志仍然存在？
    BCSCTL2 |= SELM_2 + SELS;           //MCLK和SMCLK选择高频晶振
   
    BoardConfig(0x88);                  //打开数码管

    //设置看门狗定时器，初始化控制数码管的IO
         
    IE1 |= WDTIE;                            
    P4DIR = 0xff;
    P5DIR = 0xff; 
    P4OUT = 0x00;
    P5OUT = 0xff;
    
    //计数时钟选择SMLK=8MHz，1/8分频后为1MHz
    TACTL |= TASSEL_2 + ID_3; 
    //打开全局中断
    _EINT();
    //循环读数显示
    while(1)
    {
       Disp_Numb(Do1Convert());
    }
}

/*******************************************
函数名称：Disp_Numb
功    能：将从DS18B20读取的11bit温度数据转换
          成数码管显示的温度数字
参    数：temper--11bit温度数据
返回值  ：无
********************************************/
/*void Disp_Numb(uint temper)
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
    if(temper&BIT1)     
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

/*