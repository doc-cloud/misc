/*************************************************
程序功能：将DS18B20测温结果和DS1302的时间一起在1602
          液晶上显示
-------------------------------------------------
测试说明：观察液晶显示。
*************************************************/
#include <msp430x14x.h>
#include "BoardConfig.h"
#include "DS18B20.h"
#include "DS1302.h"
#include "cry1602.h"

uchar dN[6];        //存放十进制测温结果的数组

void Disp_Numb(uint temper);
void ShowTime(uchar *times);
/****************主函数****************/
void main(void)
{
    uchar i;
    //设置当期时间的数组，格式为BCD码，顺序：秒 分 时 日 月 星期 年
    uchar CurrentTime[7] = {0x00,0x00,0x00,0x18,0x04,0x05,0x08};
    uchar ReadTime[7];
    
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
   
    BoardConfig(0xb8);                  //关闭数码管、流水灯和电平转换
    LcdReset();                         //初始化液晶
    Reset_DS1302();                     //初始化DS1302
    //这条程序可以设置DS1302内部时间，如果不需要请将其注释掉（快捷键：Ctrl+K）
    Set_DS1302(CurrentTime);                             
    //计数时钟选择SMLK=8MHz，1/8分频后为1MHz
    TACTL |= TASSEL_2 + ID_3; 
    //在液晶上显示提示文字    
    DispStr(0,0,"Temp:"); 
    DispStr(0,1,"Time:"); 
    //循环读数显示
    while(1)
    {
       Disp_Numb(Do1Convert());         //执行一次测温
       Disp1Char(6,0,dN[5]+0x30);       //显示测温结果
       Disp1Char(7,0,dN[4]+0x30);
       Disp1Char(8,0,'.');
       Disp1Char(9,0,dN[3]+0x30);
       Disp1Char(10,0,dN[2]+0x30);
       Disp1Char(11,0,dN[1]+0x30);
       Disp1Char(12,0,dN[0]+0x30);
       
       Get_DS1302(ReadTime);            //读取当前时间
       ShowTime(ReadTime);              //显示时分秒信息
    }
}
/*******************************************
函数名称：Disp_Numb
功    能：将从DS18B20读取的11bit温度数据转换
          成十进制温度数字
参    数：temper--11bit温度数据
返回值  ：无
********************************************/
void Disp_Numb(uint temper)
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
/*******************************************
函数名称：ShowTime
功    能：将DS1302的时间转换成10进制显示
参    数：times--读取的时间数组
返回值  ：无
********************************************/    
void ShowTime(uchar *times)
{
    uchar h2[8];        //第2行显示数据
    const uchar shuzi[] = {"0123456789"};
      
    h2[0] = shuzi[times[2]>>4];     //时
    h2[1] = shuzi[times[2]&0x0f];
    h2[2] = 0x3a;       //":"
    h2[3] = shuzi[times[1]>>4];     //分
    h2[4] = shuzi[times[1]&0x0f];
    h2[5] = 0x3a;       //":"
    h2[6] = shuzi[times[0]>>4];     //秒
    h2[7] = shuzi[times[0]&0x0f];
    DispNChar(6,1,8,h2);           //在第二行显示
}

