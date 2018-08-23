/***************************************************
程序功能：动态显示文字“welcome!”
----------------------------------------------------
测试说明：观察液晶显示
****************************************************/
#include  <msp430.h>
#include  "BoardConfig.h" 
#include  "Cry1602.h"

uchar *s1 = "welcome!";

void main( void )
{
    uchar i;
    WDTCTL = WDTPW + WDTHOLD;               //间隔定时器，定时16ms
    BoardConfig(0xb8);                   //关闭数码管、流水灯和电平转换
    
    LcdReset();
    DispStr(4,0,s1);
    LocateXY(0,9);                      //确定写入字符的显示位置
    LcdWriteCommand(0x07, 1);           //整体显示左移
    for(i = 12; i > 0; i--) 
    {
        LcdWriteData(0x20);
        //延时250ms
        IFG1 &= ~WDTIFG;
        while(!(IFG1 & WDTIFG));
        IFG1 &= ~WDTIFG; 
    }
    while(1)
    {
        LcdWriteCommand(0x05, 1);           //整体显示右移
        
        for(i = 24; i > 0; i--)  
        {
            LcdWriteData(0x20);
            //延时250ms
            IFG1 &= ~WDTIFG;
            while(!(IFG1 & WDTIFG));
            IFG1 &= ~WDTIFG; 
        }
    
        
        LcdWriteCommand(0x07, 1);           //整体显示左移
        
        for(i = 24; i > 0; i--)
        {
            LcdWriteData(0x20);
            //延时250ms
            IFG1 &= ~WDTIFG;
            while(!(IFG1 & WDTIFG));
            IFG1 &= ~WDTIFG; 
        }
    }    
}
