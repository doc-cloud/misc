/**************************************************************
程序功能：用并行数据传输方式在液晶上综合显示字符、文字和图形
---------------------------------------------------------------
测试说明：观察液晶显示
***************************************************************/
#include <msp430x14x.h>
#include "BoardConfig.h"
#include "subfuncs.h"
#include "dispdata.h"

uchar flag = 0;
/*************************主函数***************************/
int main( void )
{
    WDTCTL = WDTPW + WDTHOLD;            //关闭看门狗
    BoardConfig(0xbe);                   //关闭数码管、流水灯、4245
    
    TACTL = TASSEL_1 + MC_1;             //计数时钟ACLK, 增计数模式
    CCR0 = 32768 - 1;
    CCTL0 |= CCIE;                       //使能CCR0比较中断
    _EINT(); 
    
    Ini_Lcd();                          //显示文字
    Disp_HZ(0x81,line1,6);
    Disp_HZ(0x92,line2,4);
    Disp_HZ(0x8a,line3,4);
    Disp_HZ(0x98,line4,8);
    
    flag = 0;
    while(flag < 5);                    //等待5秒钟
    Write_Cmd(0x01);                    //清屏
    Draw_PM(zifu);                      //显示文字型图片
    flag = 0;
    while(flag < 5);                    //等待5秒钟
    Write_Cmd(0x01);                    //清屏
    Draw_PM(zhu);                       //显示可爱猪的图片
    flag = 0;
    while(flag < 5);                    //等待5秒钟
    Write_Cmd(0x01);                    //清屏
    Disp_HZ(0x92,jieshu,4);             //结束文字 
    while(1);
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
    flag++;    
}
