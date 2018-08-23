/*********************************************************
程序功能：用按键控制蜂鸣器发音的音调。
          K1按下后用2KHz方波驱动蜂鸣器
          K2按下后用4KHz方波驱动蜂鸣器
          K3按下后用6KHz方波驱动蜂鸣器
          K4按下后停止发音
----------------------------------------------------------
测试说明：按动K1~k4四个按键，聆听蜂鸣器发声频率
**********************************************************/
#include <msp430.h>
#include "BoardConfig.h"


#define keyin    (P1IN & 0x0f)

uchar step = 0xff;

void main( void )
{
    uchar i;
    
    WDTCTL = WDTPW + WDTHOLD;           //关狗
    BoardConfig(0xb0);                  //关数码管和电平转换,打开流水灯
    
    /*------选择系统主时钟为8MHz-------*/
    BCSCTL1 &= ~XT2OFF;                 //打开XT2高频晶体振荡器
    do
    {
        IFG1 &= ~OFIFG;                 //清除晶振失败标志
        for (i = 0xFF; i > 0; i--);     //等待8MHz晶体起振
    }
    while ((IFG1 & OFIFG));             //晶振失效标志仍然存在？
    BCSCTL2 |= SELM_2 + SELS;           //MCLK和SMCLK选择高频晶振
    
    TACTL |= TASSEL_2 + ID_3 + MC_1;    //计数时钟选择SMLK=8MHz，1/8分频后为1MHz
    
    P1IES = 0x0f;                       // P1.0~P1.3选择下降沿中断
    P1IE = 0x0f;                        // 打开中断使能
    P1DIR = BIT7;                       //设置P1.0~P.3为输入状态，P.7为输出
    P1OUT = 0;
    P2DIR = 0xff;
    P2OUT = 0xff;
    P6DIR |= BIT7;                      //蜂鸣器对应IO设置为输出
    P6OUT |= BIT7;
    
    _EINT();
    LPM1;
}
// Timer A0 interrupt service routine
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
  P6OUT ^= BIT7;                        // Toggle P6.7
}
/*******************************************
函数名称：delay
功    能：用于消抖的延时
参    数：无
返回值  ：无
********************************************/
void delay(void)
{
    uint tmp;
    uchar i;
    
    for(i = 7; i > 0; i--)
    {
        for(tmp = 12000;tmp > 0;tmp--);
    }
}
/*******************************************
函数名称：PORT1_ISR 
功    能：P1端口的中断服务函数
参    数：无
返回值  ：无
********************************************/
#pragma vector=PORT1_VECTOR
__interrupt void  PORT1_ISR(void)
{
    if(P1IFG & 0x0f)
    {
        switch(P1IFG)
        {
        case 0x01:
                    if(keyin == 0x0e)   //如果是第一个按键被按下
                    {
                        delay();
                        if(keyin == 0x0e)
                        {
                            while(keyin != 0x0f);       //等待按键放开
                            TACCR0 = 250;               // 2KHz
                            TACCTL0 |= CCIE; 
                            P2OUT = 0xfe;
                            P1IFG = 0;
                            return;
                        }
                    }
        case 0x02:
                    if(keyin == 0x0d)   //如果是第二个按键被按下
                    {
                        delay();
                        if(keyin == 0x0d)
                        {
                            while(keyin != 0x0f);       //等待按键放开
                            TACCR0 = 125;               // 4KHz
                            TACCTL0 |= CCIE;                            
                            P2OUT = 0x0fd;
                            P1IFG = 0;
                            return;
                        }
                    }
        case 0x04:
                    if(keyin == 0x0b)   //如果是第三个按键被按下
                    {
                        delay();
                        if(keyin == 0x0b)
                        {
                            while(keyin != 0x0f);       //等待按键放开
                            TACCR0 = 83;               // 6KHz
                            TACCTL0 |= CCIE;                            
                            P2OUT = 0xfb;
                            P1IFG = 0;
                            return;
                        }
                    }
        case 0x08:
                    if(keyin == 0x07)   //如果是第四个按键被按下
                    {
                        delay();
                        if(keyin == 0x07)
                        {
                            while(keyin != 0x0f);       //等待按键放开
                            P6OUT |= BIT7; 
                            TACCTL0 &= ~CCIE;             //停止发声
                            P2OUT = 0xf7;                 
                            P1IFG = 0;
                            return;
                        }
                    }
        default:
                    while(keyin != 0x0f);       //等待按键放开
                    P1IFG = 0;
                    return;
        }
    }
    
    P1IFG = 0;
}
