/*****************************************************
程序功能：接收并解码来自标准键盘的基本按键的扫描码
然后将0~9、a~f和A~F字符在数码管上显示

注：所谓基本按键就是当此键被按下时对应产生三个字节
的扫描码的按键，详见光盘中的《第二套扫描码》
-----------------------------------------------------
跳线设置：将跳线座J4的1脚和2脚（右侧的两个）短接
-----------------------------------------------------
测试说明：敲定标准键盘上的按键，观察数码管显示
*****************************************************/
#include  <msp430x14x.h>
#include "BoardConfig.h"
#include "Keyboard.h"
#include "gdata.h"

#define SIDval  P5IN & BIT6

//数码管7位段码：0--f,和不显示字符(0x00)
uchar scandata[17] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
                      0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x00};
//数码管的显示缓存
uchar DispBuf = 16;

/****************主函数****************/
void main(void)
{
    uchar disptmp,i,j;
    
    WDTCTL = WDTPW + WDTHOLD;         //关闭看门狗
    BoardConfig(0x48);                // 打开4245，方向5-->3.3,数码管和关闭流水灯
    
    /*------选择系统主时钟为8MHz-------*/
    BCSCTL1 &= ~XT2OFF;                 // 打开XT2高频晶体振荡器
    do
    {
        IFG1 &= ~OFIFG;                 // 清除晶振失败标志
        for (i = 0xFF; i > 0; i--);     // 等待8MHz晶体起振
    }
    while ((IFG1 & OFIFG));             // 晶振失效标志仍然存在？
    BCSCTL2 |= SELM_2;                  // 主时钟选择高频晶振
    
    P4DIR = 0xff;                 //设置P4，P5的IO方向为输出
    P5DIR = 0x3f;                 
  
    P4OUT = 0x00;                 //设置P4，P5的输出初值
    P5OUT = 0x00;
    
    P6DIR = BIT7;
    P6OUT = BIT7;
    
    Init_KB();                  //初始化键盘端口
    _EINT();                    //打开全局中断
  
    while(1)
    {
        LPM1;                   //进入低功耗模式
        disptmp = GetChar();    //读取键值对应的ASCII码
        
        if((disptmp > 0x2f)&&(disptmp < 0x3a)) //如果接收到的字符是0~9
        {
            DispBuf = disptmp - 0x30; //得到实际的数字
        }
        else if((disptmp > 0x40)&&(disptmp < 0x47))//如果接收到的字符是A~F
        {
            DispBuf = disptmp - 0x37; //得到实际的字母      
        }
        else if((disptmp > 0x60)&&(disptmp < 0x67))//如果接收到的字符是a~f
        {
            DispBuf = disptmp - 0x57; //得到实际的字母 
        }
        else
        {
            DispBuf = 16;             //控制数码管不显示
            
            P6OUT = 0;                //蜂鸣器发生提示错误
            for(i = 255; i > 0; i--)
              for(j = 80; j > 0; j--);
            P6OUT = BIT7;    
        }
        P4OUT = scandata[DispBuf];
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


