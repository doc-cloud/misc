/*****************************************************
程序功能：在1602液晶上显示用MCU的TimerA模拟的数字
          式实时时钟。
-----------------------------------------------------
测试说明：观察液晶显示
*****************************************************/
#include <msp430x14x.h>
#include "BoardConfig.h"
#include "cry1602.h"
#include "clock.h"

uchar tishi[]={"Current Time is"};   //提示信息
extern uchar second,minute,hour,hour0;
extern uchar pmin,phour,ps1;

#define SetTime(H,M,S) {second=S;minute=M;hour=H;hour0=H;}

/*************************主函数************************/
void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;   //关闭看门狗
    BoardConfig(0xb8);          //关闭74LVC4245，数码管和流水灯
	
    CCR0 = 32768 - 1;           //设置定时器A的中断时间为1S
    TACTL = TASSEL_1 + MC_1;    //计数时钟ACLK, 增计数模式
    CCTL0 |= CCIE;              //使能CCR0比较中断
    _EINT();                    //打开全局中断
    
    //请在此处设置正确时间
    SetTime(8,26,50);           //顺序：时，分，秒，格式：BCD码
      
    LcdReset(); 
    DispNChar(0,0,15,tishi);     //显示提示文字
    Disp1Char(6,1,':');          //显示字符 :
    Disp1Char(9,1,':');
    
    while(1)
    {
        LPM3;                    //进入LPM3低功耗模式
        Display();         
    }    
}

/*******************************************
函数名称：TimerA_ISR
功    能：定时器A的中断服务函数
参    数：无
返回值  ：无
********************************************/
#pragma vector=TIMERA0_VECTOR
__interrupt void TimerA_ISR(void)
{
    Clock();
    LPM3_EXIT;
}
