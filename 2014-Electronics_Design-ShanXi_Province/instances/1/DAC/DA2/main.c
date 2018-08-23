/****************************************************
程序功能：用ADC采样DAC输出的模拟电压数据，
          将两个模拟电压值在1602液晶上显示
----------------------------------------------------
跳线设置：将跳线座J1的2脚和3脚（靠下面的两个）短接
-----------------------------------------------------
测试说明：按动S3键可以减小DAC的输出电压；
          按动S4键可以增加DAC的输出电压。
          观察液晶显示变化。
******************************************************/
#include <msp430x14x.h>
#include "BoardConfig.h"
#include "IIC.h"
#include "cry1602.h"

uint    ADC_tmp[16];      //存放ADC数值的缓冲区
uchar   cnt = 0;          //计数变量
uint    ADC_Val = 0;      //一次ADC转换的平均值
uchar   DAC_Val;          //DAC输出数据

uchar shuzi[] = {"0123456789."};
uchar tishi1[] = {"DAC volt: "};
uchar tishi2[] = {"ADC volt: "};
void Init_ADC(void);
uchar Write_DAC(uchar wdata);
void Trans_val(uint Hex_Val,uchar n);

/****************主函数****************/
void main(void)
{
    
    WDTCTL = WDTPW + WDTHOLD;   //停止看门狗
    BoardConfig(0xb8);
    P1DIR |= 0x03 + BIT7;       //设置DAC的控制IO为输出状态
    P1OUT  = 0x03;
    P1IE  |= BIT2 + BIT3;       //允许P1.2和P1.3中断
    
    LcdReset();
    DispNChar(0,0,10,tishi1);   //显示提示文字
    Disp1Char(15,0,0x56);       //0x56是字符V的ASCII码值       
    DispNChar(0,1,10,tishi2);
    Disp1Char(15,1,0x56);
    
    DAC_Val = 0;
    Write_DAC(DAC_Val);
    Trans_val(DAC_Val,8);
    
    Init_ADC();
    _EINT();
    while(1)
    {       
        ADC12CTL0 |= ADC12SC;           //开始一次转换
        LPM0;
        Trans_val(ADC_Val,12);          //在液晶上提示
    }
}
/*******************************************
函数名称：ADC12_ISR
功    能：ADC的中断服务函数
参    数：无
返回值  ：无
*******************************************/
#pragma vector=ADC_VECTOR
__interrupt void ADC12_ISR(void)
{   
    ADC_tmp[cnt++] = ADC12MEM0;
    
    if(cnt == 16)
    {
        unsigned long ADC_sum = 0;
        uchar i;
        
        for(i = 0;i < 16;i++)           //求16次采样的均值
            ADC_sum += ADC_tmp[i];
        
        ADC_Val = ADC_sum >> 4;        
        cnt = 0;
        LPM0_EXIT;
    }
    else
    {
        ADC12CTL0 |= ADC12SC;           //开始一次转换
    }
}
/*******************************************
函数名称：Port1_ISR
功    能：端口P1的中断服务函数
参    数：无
返回值  ：无
********************************************/
#pragma vector=PORT1_VECTOR
__interrupt void Port1_ISR(void)
{
    
    _DINT();
    
    if(P1IFG & BIT2)
    {
        P1IFG = 0x00;           //清中断标志 
        DAC_Val -= 10;          //DAC的输出减少10个偏置量
        Write_DAC(DAC_Val);     //写入DAC
        Trans_val(DAC_Val,8);   //在液晶上提示
    }
    else if(P1IFG & BIT3)
    {
        P1IFG = 0x00;           //清中断标志
        DAC_Val += 10;          //DAC的输出增加10个偏置量
        Write_DAC(DAC_Val);     //写入DAC
        Trans_val(DAC_Val,8);   //在液晶上提示
    }
    else
        _NOP();
    
    P1IFG = 0x00;           //清中断标志
    _EINT();
}

/*******************************************
函数名称：Init_ADC
功    能：初始化ADC寄存器
参    数：无
返回值  ：无
********************************************/
void Init_ADC(void)    
{
    P6SEL |= BIT1;                  //P6.1选做ADC输入端口
    ADC12CTL0 = SHT0_2 + ADC12ON;   //设置采样时间，打开ADC
    ADC12CTL1 = SHP;                //使用采样定时器，选择SMCLK
    ADC12IE = BIT0;                 //使能采样中断
    ADC12MCTL0 = INCH_1;            //选择采样通道1
    ADC12CTL0 |= ENC;               //打开转换使能
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
/*******************************************
函数名称：Trans_val
功    能：将16进制数据变换成三位10进制数据，
          并在液晶上显示
参    数：Hex_Val--16进制数据
          n--变换时的分母等于2的n次方       
返回值  ：写入结果：1--成功，0--失败
********************************************/
void Trans_val(uint Hex_Val,uchar n)
{
    unsigned long caltmp;
    uint Curr_Volt;
    uchar t1,i;
    uchar ptr[4];
    
    caltmp = Hex_Val;
    caltmp = (caltmp << 5) + Hex_Val;           //caltmp = Hex_Val * 33
    caltmp = (caltmp << 3) + (caltmp << 1);     //caltmp = caltmp * 10
    Curr_Volt = caltmp >> n;                    //Curr_Volt = caltmp / 2^n
    ptr[0] = Curr_Volt / 100;                   //Hex->Dec变换
    t1 = Curr_Volt - (ptr[0] * 100);
    ptr[2] = t1 / 10;
    ptr[3] = t1 - (ptr[2] * 10);
    if(n == 8)          //如果是DAC的数据
        t1 = 0;
    else                //如果是ADC的数据
        t1 = 1;
    
    ptr[1] = 10;            //shuzi表中第10位对应符号"."
    _DINT();
    //在液晶上显示变换后的结果
    for(i = 0;i < 4;i++)
      Disp1Char((10 + i),t1,shuzi[ptr[i]]);
    _EINT();
}
