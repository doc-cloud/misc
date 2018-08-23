/*****************************************************
程序功能：接收并解码来自标准键盘的基本按键的扫描码
然后在1602液晶上显示。按Back Space键可以前向删除显
示字符，按Space键可以后向删除显示字符。

注：所谓基本按键就是当此键被按下时对应产生三个字节
的扫描码的按键，详见光盘中的《第二套扫描码》
-----------------------------------------------------
跳线设置：将跳线座J4的1脚和2脚（右侧的两个）短接
-----------------------------------------------------
测试说明：敲定标准键盘上的按键，观察液晶显示
*****************************************************/
#include  <msp430x14x.h>
#include "BoardConfig.h"
#include "cry1602.h"
#include "Keyboard.h"
#include "gdata.h"

#define SIDval  P5IN & BIT6

/****************主函数****************/
void main(void)
{
    uchar disptmp,i;
    uchar x = 0,y = 0;
    uchar first = 1;
    
    WDTCTL = WDTPW + WDTHOLD;       //关闭看门狗
    BoardConfig(0x78);              //打开4245，方向5-->3.3,关闭数码管和流水灯
    
    /*------选择系统主时钟为8MHz-------*/
    BCSCTL1 &= ~XT2OFF;                 // 打开XT2高频晶体振荡器
    do
    {
        IFG1 &= ~OFIFG;                 //清除晶振失败标志
        for (i = 0xFF; i > 0; i--);     // 等待8MHz晶体起振
    }
    while ((IFG1 & OFIFG));             // 晶振失效标志仍然存在？
    BCSCTL2 |= SELM_2;                  //主时钟选择高频晶振
    
    LcdReset();                 //复位液晶
    DispNchar(0,0,15,tishi);    //液晶显示提示信息
    Init_KB();                  //初始化键盘端口
    _EINT();                    //打开全局中断
  
    while(1)
    {
        LPM3;                   //进入低功耗模式
        
        if(first)
        {
            first = 0;
            LcdWriteCommand(0x01, 1);   //显示清屏
            LcdWriteCommand(0x0f, 1);   //打开游标
        }
        
        disptmp = GetChar();    //读取键值对应的ASCII码
        if(disptmp != 0xff)     //取出了一个有效字符
        {
            if(disptmp == 8) //如果是退格键
            {
                if((x == 0) && (y == 0))//如果游标在第1行第1位
                {
                    x = 15;
                    y = 1;
                    Disp1Char(x,y,0x20); //0x20是空格的ASCII码
                    LocateXY(x,y);
                }
                else if((x == 0) && (y == 1))//如果游标在第2行第1位
                {
                    x = 15;
                    y = 0;
                    Disp1Char(x,y,0x20); 
                    LocateXY(x,y);
                }
                else
                {
                    Disp1Char(--x,y,0x20); 
                    LocateXY(x,y);
                }
            }
            else if((disptmp == 9) || (disptmp == 13)) //如果是Table键或Enter键
            {
                _NOP();   
            }
            else    //其余字符显示
            {
                Disp1Char(x++,y,disptmp);
                if(x == 16)           //如果一行显示完毕
                {
                    x = 0;
                    y ^= 1;
                    LocateXY(x,y);  //重新定位游标位置
                }
            }
        }
    }
}

/*******************************************
函数名称：PORT1_ISR 
功    能：P1端口的中断服务函数，在这里接收来
          自键盘的字符
参    数：无
返回值  ：无
********************************************/
#pragma vector=PORT1_VECTOR
__interrupt void  PORT1_ISR(void)
{
    if(P1IFG & BIT7)            //如果是clock的中断
    {
        P1IFG &=~ BIT7;         //清除中断标志 
        
        if(bitcount == 11)        //接收第1位
        {
            if(SIDval)          //如果不是起始位
                return;
            else  
                bitcount--;
        } 
        else if(bitcount == 2)    //接收奇偶校验位
        {   
            if(SIDval)          //如果校验位等于1
                pebit = 1;
            else
                pebit = 0;
            bitcount--;
        }
        else if(bitcount == 1)    //接收停止位
        {
            if(SIDval)          //若停止位正确
            {
                bitcount = 11;    //复位位计数变量
                if( Decode(recdata) )    //解码获得此键值的ASCII值并保存
                    LPM3_EXIT;           //退出低功耗模式
                recdata = 0;          //清除接收数据
            }
            else                //如果出错
            {
                bitcount = 11;
                recdata = 0;    
            }
        }
        else                    //接收8个数据位
        {
            recdata >>= 1;
            if(SIDval)  recdata |= 0x80;
            bitcount--;
        }
   }
}


