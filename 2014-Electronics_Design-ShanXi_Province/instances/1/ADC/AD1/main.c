/*************************************************************
程序功能：对P6.0对应的模拟通道进行多次转换后，将32次平均值
          在数码管上显示（数码管显示的只是ADC的转换结果而不
          是真实的模拟电压）
--------------------------------------------------------------
特别说明：如果不进行32次平均，我们会看到最低位不停的跳变。
--------------------------------------------------------------
测试说明：调节电位器R7的调整旋钮，观察显示数字的变化
*************************************************************/
#include  <msp430x14x.h>
#include  "BoardConfig.h"

uint Results[32];         //存放ADC的转换结果
uint Average; 
//数码管7位段码：0--f
uchar scandata[16] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
                      0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
uchar DispBuf[4] = {0,0,0,0};
                                                                                   
//记录显示位数的全局变量
uchar cnt = 0;

void main(void)
{
    WDTCTL = WDT_ADLY_1_9;                    // 设置内部看门狗工作在定时器模式，1.9ms中断一次
    IE1 |= WDTIE;                             // 使能看门狗中断
    BoardConfig(0x88);                        // 打开数码管，关闭流水灯和电平转换
    P6SEL |= 0x01;                            // Enable A/D channel A0
    ADC12CTL0 = ADC12ON + SHT0_15 + MSC;      // Turn on ADC12, set sampling time
    ADC12CTL1 = SHP + CONSEQ_2;               // Use sampling timer, set mode
    ADC12IE = 0x01;                           // Enable ADC12IFG.0
    ADC12CTL0 |= ENC;                         // Enable conversions
    ADC12CTL0 |= ADC12SC;                     // Start conversion
    
    P4DIR = 0xff;
    P5DIR = 0xff;
    
    _EINT();
    while(1)
    {
        _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0, Enable interrupts
        DispBuf[0] = Average / 1000;              //更新数码管显示
        DispBuf[1] = (Average - DispBuf[0]*1000)/100;
        DispBuf[2] = (Average - DispBuf[0]*1000 - DispBuf[1]*100)/10;
        DispBuf[3] = (Average - DispBuf[0]*1000 - DispBuf[1]*100 - DispBuf[2]*10);    
    }
}
/*******************************************
函数名称：ADC12ISR
功    能：ADC12的中断服务函数
参    数：无
返回值  ：无
********************************************/
#pragma vector=ADC_VECTOR
__interrupt void ADC12ISR (void)
{
    static uchar index = 0;
    float tmp;
    Results[index++] = ADC12MEM0;                      // Move results, IFG is cleared
    if(index == 31)
    {
         uchar i;
         
         Average = 0;
         for(i = 0; i < 32; i++)
            Average += Results[i];
         Average >>= 5; 
         tmp = Average;//除以32求平均值
         tmp = tmp*3.6/4096;
         Average = tmp*1000;
         index = 0;
        _BIC_SR_IRQ(LPM0_bits);                   // Clear LPM0
    }
}
/*******************************************
函数名称：watchdog_timer
功    能：看门狗中断服务函数，在这里输出数码管的
          段选和位选信号
参    数：无
返回值  ：无
********************************************/
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{ 
    P5OUT = 0xff;
    P4OUT = scandata[DispBuf[cnt]];        //输出段选信号
    P5OUT &= ~(1 << cnt);           //输出位选信号
  
    cnt++;                        //位计数变量在0~3之间循环
    if(cnt == 4) cnt = 0;
}
