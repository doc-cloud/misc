#include <msp430.h>
typedef unsigned char uchar;
typedef unsigned int  uint;
/********************************************
函数名称：Init_ADC
功    能：初始化ADC
参    数：无
返回值  ：无
********************************************/
void Init_ADC(void)
{
    P6SEL |= 0x01;                            // 使能ADC通道
    ADC12CTL0 = ADC12ON+SHT0_15+MSC;          // 打开ADC，设置采样时间
    ADC12CTL1 = SHP+CONSEQ_2;                 // 使用采样定时器
    ADC12IE = 0x01;                           // 使能ADC中断
    ADC12CTL0 |= ENC;                         // 使能转换
    ADC12CTL0 |= ADC12SC;                     // 开始转换
}
/********************************************
函数名称：Hex2Dec
功    能：将16进制ADC转换数据变换成十进制
          表示形式
参    数：Hex_Val--16进制数据  
          ptr--指向存放转换结果的指针
返回值  ：无
********************************************/
void Hex2Dec(uint Hex_val,uchar *ptr)
{
    ptr[0] = Hex_val / 1000;        
    ptr[1] = (Hex_val - ptr[0]*1000)/100;
    ptr[2] = (Hex_val - ptr[0]*1000 - ptr[1]*100)/10;
    ptr[3] = (Hex_val - ptr[0]*1000 - ptr[1]*100 - ptr[2]*10); 
}   
/*******************************************
函数名称：Trans_val
功    能：将16进制ADC转换数据变换成三位10进制
          真实的模拟电压数据，并在液晶上显示
参    数：Hex_Val--16进制数据   
返回值  ：无
********************************************/
void Trans_val(uint Hex_Val,uchar *ptr)
{
    unsigned long caltmp;
    uint Curr_Volt;
    uchar t1;
    
    caltmp = Hex_Val;
    caltmp = (caltmp << 5) + Hex_Val;           //caltmp = Hex_Val * 33
    caltmp = (caltmp << 3) + (caltmp << 1);     //caltmp = caltmp * 10
    Curr_Volt = caltmp >> 12;                   //Curr_Volt = caltmp / 2^n
    ptr[0] = Curr_Volt / 100;                   //Hex->Dec变换
    t1 = Curr_Volt - (ptr[0] * 100);
    ptr[1] = t1 / 10;
    ptr[2] = t1 - (ptr[1] * 10);
}
