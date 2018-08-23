/*************************************************
程序功能：接收并解码来自标准键盘的基本按键的扫描码
然后通过RS232端口发送给PC机在电脑显示器上显示。
注：所谓基本按键就是当此键被按下时对应产生三个字节
的扫描码的按键，详见光盘中的《第二套扫描码》
--------------------------------------------------
跳线设置：将跳线座J4的1脚和2脚（右侧的两个）短接
--------------------------------------------------
通信格式：N.8.1,  9600
--------------------------------------------------
测试说明：打开串口调试精灵，正确设置通信格式；敲击
键盘上的可显示字符按键，观察PC机屏幕显示
*************************************************/
#include <msp430x14x.h>
#include "BoardConfig.h"
#include "Keyboard.h"
#include "RS232.h"
#include "gdata.h"

#define SIDval  P5IN & BIT6

/****************主函数****************/
void main(void)
{
    uchar i;
  
    WDTCTL = WDTPW + WDTHOLD;       //关闭看门狗
    BoardConfig(0x78);              //打开4245，方向5-->3.3
    
    /*------选择系统主时钟为8MHz-------*/
    BCSCTL1 &= ~XT2OFF;                 // 打开XT2高频晶体振荡器
    do
    {
        IFG1 &= ~OFIFG;                 //清除晶振失败标志
        for (i = 0xFF; i > 0; i--);     // 等待8MHz晶体起振
    }
    while ((IFG1 & OFIFG));             // 晶振失效标志仍然存在？
    BCSCTL2 |= SELM_2;                  //主时钟选择高频晶振
    
    Init_UART0();                       //初始化UART0端口
    Init_KB();                          //初始化键盘端口
    _EINT();                            //打开全局中断
    
    for(i = 0; i < 16; i++) 
    {
        Send_Char(tishi[i]);
    }
    while(1)
    {
        LPM1;                           //进入低功耗模式
        Send_Char(Buffer);
    }
}

/*******************************************
函数名称：PORT1_ISR 
功    能：P1端口的中断服务函数，在这里接收来
          自键盘的字符
参    数：无
返回值  ：无
********************************************/
#pragma vector = PORT1_VECTOR
__interrupt void  PORT1_ISR(void)
{
    if(P1IFG & BIT7)                    //如果是clock的中断
    {
        P1IFG &=~ BIT7;                 //清除中断标志 
        
        if(bitcount == 11)              //接收第1位
        {
            if(SIDval)                  //如果不是起始位
                return;
            else  
                bitcount--;
        } 
        else if(bitcount == 2)          //接收奇偶校验位
        {   
            if(SIDval)                  //如果校验位等于1
                pebit = 1;
            else
                pebit = 0;
            bitcount--;
        }
        else if(bitcount == 1)          //接收停止位
        {
            if(SIDval)                  //若停止位正确
            {
                bitcount = 11;          //复位位计数变量
                if( Decode(recdata) )   //解码获得此键值的ASCII值并保存
                    LPM1_EXIT;          //退出低功耗模式
                recdata = 0;            //清除接收数据
            }
            else                        //如果出错
            {
                bitcount = 11;
                recdata = 0;    
            }
        }
        else                            //接收8个数据位
        {
            recdata >>= 1;
            if(SIDval)  recdata |= 0x80;
            bitcount--;
        }
   }
}


