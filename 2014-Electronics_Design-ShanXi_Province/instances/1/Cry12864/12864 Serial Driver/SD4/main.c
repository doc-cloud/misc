/*************************************************************
程序功能：用串行数据传输方式在液晶上综合显示字符、文字和图形
--------------------------------------------------------------
测试说明：观察液晶显示
*************************************************************/
#include  <msp430x14x.h>
#include "BoardConfig.h"
#include "cryfucns.h"
#include "displaydata.h"

uchar flag = 0;
/************************主函数***********************/
void main(void)
{
    uchar i,j;
    
    WDTCTL = WDTPW + WDTHOLD;            //关闭看门狗
    BoardConfig(0xba);                   //关闭数码管、流水灯、4245
    TACTL = TASSEL_1 + MC_1;             //计数时钟ACLK, 增计数模式
    CCR0 = 32768 - 1;
    CCTL0 |= CCIE;                       //使能CCR0比较中断
    _EINT(); 
    
    Ini_Lcd();
    Disp_HZ(0x81,line1,6);
    Disp_HZ(0x8a,line2,4);
    flag = 0;
    while(flag < 3);                    //等待三秒钟
    Send(0,0x01);                       //清屏
    CCR0 = (32768 - 1) / 5;
    flag = 0;
    for(i = 0; i < 4; i++)
    {
        Send(0, 0x0f);                  //打开游标
        switch(i)
        {
        case 0: Send(0,0x81);break;
        case 1: Send(0,0x91);break;
        case 2: Send(0,0x89);break;
        case 3: Send(0,0x99);break;
        }
        for(j = 0; j < 12; j++)
        {
            Send(1, shige[i*12 + j]);
            if(j == 11)
                Send(0, 0x0c);                    //关闭游标
            flag = 0;
            while(!flag);                         //等待1/5秒         
        }   
    }
    CCR0 = 32768 - 1; 
    flag = 0;
    while(flag < 2);                    //等待2秒钟
    Send(0,0x01);                       //清屏
    Draw_PM(school);                    //显示文字型画面             
    flag = 0;
    while(flag < 3);                    //等待三秒钟
    Draw_PM(QQ);                        //显示QQ形象
    flag = 0;
    while(flag < 3);                    //等待三秒钟
    Send(0,0x01);                       //清屏
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
