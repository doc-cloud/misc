/***********************************************************
程序功能：在液晶上用串行数据通信方式依次显示常用ASCII码
------------------------------------------------------------
测试说明：观察液晶显示
************************************************************/
#include  <msp430x14x.h>
#include "BoardConfig.h"
#include "cryfucns.h"

void main(void)
{
    uchar i;
    
    WDTCTL = WDTPW + WDTHOLD;            //关闭看门狗
    BoardConfig(0xba);                   //关闭数码管、流水灯、4245
    
    Ini_Lcd();                           //初始化液晶
    
    Send(0,0x80);                        //显示的起始地址
    for(i = 0; i < 16; i++)
    {
        Send(1,0x00+i);                  //0x00~0x0f对应的ASCII字符
    }
    Send(0,0x90);                        //显示的起始地址
    for(i = 0; i < 16; i++)
    {
        Send(1,0x10+i);                  //0x10~0x1f对应的ASCII字符
    }
    Send(0,0x88);                        //显示的起始地址
    for(i = 0; i < 16; i++)
    {
        Send(1,0x20+i);                  //0x20~0x2f对应的ASCII字符
    }
    Send(0,0x98);                        //显示的起始地址
    for(i = 0; i < 16; i++)
    {
        Send(1,0x30+i);                  //0x30~0x3f对应的ASCII字符
    }
    
    _NOP();                              //此处设置断点观察液晶屏幕显示
    
    Send(0,0x80);                        //显示的起始地址
    for(i = 0; i < 16; i++)
    {
        Send(1,0x40+i);                  //0x40~0x4f对应的ASCII字符
    }
    
    Send(0,0x90);                        //显示的起始地址
    for(i = 0; i < 16; i++)
    {
        Send(1,0x50+i);                  //0x50~0x5f对应的ASCII字符
    }
    
    Send(0,0x88);                        //显示的起始地址
    for(i = 0; i < 16; i++)
    {
        Send(1,0x60+i);                  //0x60~0x6f对应的ASCII字符
    }
    
    Send(0,0x98);                        //显示的起始地址
    for(i = 0; i < 16; i++)
    {
        Send(1,0x70+i);                  //0x70~0x7f对应的ASCII字符
    }
    
    LPM4;
}
    
