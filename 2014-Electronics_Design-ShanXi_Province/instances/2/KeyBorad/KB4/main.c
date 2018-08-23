/*********************************************************
程序功能：用学习板上的4X4键盘模拟手机上按键输入的功能
----------------------------------------------------------
跳线设置：
          1、拔掉跳线座J3上的跳线帽
          2、将跳线座J4的3脚和2脚短接(靠左边的两个)
          3、连接好1602液晶
----------------------------------------------------------
测试说明：1.上电后，默认配置处于显示介绍信息界面，此时按动
          K1~K16中的任意一个键都可以退出信息界面，进入输入
          模式。在输入模式下，液晶第一行的最右侧的字母显示
          提示了当前处于的输入状态：默认是处于字母输入状态，
          "BC"表示当前处于大写字母输入，"SC"表示当前处于小
          写字母输入，按动一次K15键可以在大小写间切换。按动
           一次K14键，将在字母输入与数字输入间切换。在数字
          输入状态，K14键不可用。
          2.在字符输入状态（大/小写均可），按动K1~K9键将输
          入字母，对于每个按键根据按键次数的不同将输入不同
          的字母，用户可以自行测试。按动K10将直接输入符号'!'
          3.在数字输入状态，按动K1~K10键将输入1~9和0，此状态
          不支持多次按键，每按动一次按键将输入一个数字。
          4.无论在何种输入状态下，按K11键将向前消除一个字符，
          按K12键将向后消除一个字符，按K16键将消除输入的全部
          字符。这三个按键都不支持多次按键。
          5.在输入状态下随时可以按动K13键退出输入状态回到介绍
          信息界面。
*********************************************************/
#include "includes.h"
#include "msp430.h"
#include "BoardConfig.h"

//<<<<<<<<<<<<<<<键盘扫描开启标志>>>>>>>>>>>>>>>>>>>>>
unsigned char b_KeyScan=0;		//0--不扫描；1--扫描。
extern unsigned char b_Introduce;	//介绍关闭标志，当置零时，介绍就会停止显示。
//<<<<<<<<<<<<<<<按键计数清除>>>>>>>>>>>>>>>>>>>>>>>>>>
unsigned char uc_CleanCount=0;		//清除按键计数时间计数。
extern unsigned char b_CleanClick;	//清除按键计数标志，定义在KeyProcess.c中
					//0--不清除；1--清除。
extern unsigned char uc_ClickCount;	//按键连续点击计数，定义在KeyProcess.c中。
extern unsigned char uc_KeyTemp;	//按键键码暂存，定义在KeyProcess.c中。

void delay(void);	

/******************主函数*****************/
void main(void)
{
    
    WDTCTL = WDTPW + WDTHOLD;   //关闭看门狗
    BoardConfig(0xb8);          //关闭74LVC4245，数码管和流水灯
	
    P1DIR = 0xf0;
    P1IES = 0x0f;               //低四位选择下降沿中断
    P1IE  = 0x0f;               //使能低四位的中断

    TACCR0 = 1639;              //定时50ms
    TACCTL0 |= CCIE;            //使能比较中断
    TACTL = TASSEL_1 + MC_1;    //计数时钟选择ACLK,up mode
    
    _EINT();                    //使能全局中断
     
    LcdReset();                 //复位液晶
    vIntroduce();		//显示介绍。

    while(1)
    {
        if(b_KeyScan==1)    //如果有按键按下，则进行按键扫描和键码处理。
        {
            b_KeyScan=0;
            vKeyProcess(ucKeyScan());
        }
    }
}
/*******************************************
函数名称：PORT1_ISR
功    能：按键消抖和开启键盘扫描程序
参    数：无
返回值  ：无
********************************************/ 
#pragma vector=PORT1_VECTOR 
__interrupt void PORT1_ISR(void)
{
    P1IFG = 0x00;
        
    if(b_Introduce)
        b_Introduce=0;
    delay();
    if((P1IN&0x0f) != 0x0f)
    {
        b_KeyScan=1;   
    }
} 				
/*******************************************
函数名称：Timer_A
功    能：按键计数及清除
参    数：无
返回值  ：无
********************************************/ 
#pragma vector = TIMERA0_VECTOR
__interrupt void Timer_A(void)
{  
  if(b_CleanClick==1)
    {
        if(uc_CleanCount >= 30)
        {
            b_CleanClick=0;		//关闭改计数。

            uc_CleanCount=1;		//恢复计数初值。

            uc_ClickCount=1;		//清除按键计数。

            uc_KeyTemp=0;
        }
        else
            uc_CleanCount++;
    }
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
    
    for(tmp = 12000;tmp > 0;tmp--);
}
