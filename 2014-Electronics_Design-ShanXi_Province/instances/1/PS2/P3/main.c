/*****************************************************
程序功能：接收并解码来自标准键盘的基本按键的扫描码
然后控制蜂鸣器的鸣叫频率和流水灯电路的显示。

十六进制数字0~9对应10种频率，按键S将停止蜂鸣器发声

注：所谓基本按键就是当此键被按下时对应产生三个字节
的扫描码的按键，详见光盘中的《第二套扫描码》
-----------------------------------------------------
跳线设置：将跳线座J4的1脚和2脚（右侧的两个）短接
*****************************************************/
#include  <msp430x14x.h>
#include "BoardConfig.h"
#include "Keyboard.h"
#include "gdata.h"

#define SIDval  P5IN & BIT6

/****************主函数****************/
void main(void)
{
    uchar disptmp,i;
    
    WDTCTL = WDTPW + WDTHOLD;   //关闭看门狗
    BoardConfig(0x70);          // 打开4245，方向5-->3.3,数码管和关闭流水灯
    
    /*------选择系统主时钟为8MHz-------*/
    BCSCTL1 &= ~XT2OFF;                 // 打开XT2高频晶体振荡器
    do
    {
        IFG1 &= ~OFIFG;                 // 清除晶振失败标志
        for (i = 0xFF; i > 0; i--);     // 等待8MHz晶体起振
    }
    while ((IFG1 & OFIFG));             // 晶振失效标志仍然存在？
    BCSCTL2 |= SELM_2 + SELS;           // MCLK和SMCLK选择高频晶振
    
    TACCTL0 |= CCIE;                    //使能比较中断
    TACTL |= TASSEL_2 + ID_3 ;          //计数时钟选择SMLK=8MHz，1/8分频后为1MHz
    P6DIR = BIT7;                       //蜂鸣器对应IO设置为输出
    P6OUT = BIT7;
    P2DIR = 0xff;
    
    Init_KB();                  //初始化键盘端口
    _EINT();                    //打开全局中断
  
    while(1)
    {
        LPM1;                   //进入低功耗模式
        disptmp = GetChar();    //读取键值对应的ASCII码
        
        if((disptmp > 0x2f)&&(disptmp < 0x3a)) //如果接收到的字符是0~9
        {
          //  uchar inputvalue;
            
          //  inputvalue = disptmp - 0x30;
            switch(disptmp) 
            {
              case '0':
                        TACCR0 = 5000;  
                        TACTL |= MC0;
                        P2OUT = ~1;
                        break;
              case '1':
                        TACCR0 = 2500;  
                        TACTL |= MC0;
                        P2OUT = ~2;
                        break;
              case '2':
                        TACCR0 = 1250;  
                        TACTL |= MC0;
                        P2OUT = ~3;
                        break;
              case '3':
                        TACCR0 = 625;  
                        TACTL |= MC0;
                        P2OUT = ~4;
                        break;
              case '4':
                        TACCR0 = 500;  
                        TACTL |= MC0;
                        P2OUT = ~5;
                        break;
              case '5':
                        TACCR0 = 250;  
                        TACTL |= MC0;
                        P2OUT = ~6;
                        break;
              case '6':
                        TACCR0 = 167;  
                        TACTL |= MC0;
                        P2OUT = ~7;
                        break;
              case '7':
                        TACCR0 = 125;  
                        TACTL |= MC0;
                        P2OUT = ~8;
                        break;
              case '8':
                        TACCR0 = 100;  
                        TACTL |= MC0;
                        P2OUT = ~9;
                        break;
              case '9':
                        TACCR0 = 83;  
                        TACTL |= MC0;
                        P2OUT = ~10;
                        break;
              default:
                        _NOP();
              }
          }
        else if(disptmp == 's')
        {
            TACTL &= ~MC0;  //停止发声
            P6OUT = BIT7;
            P2OUT = 0xff;
        }
        
    }
} 
/*******************************************
函数名称：Timer_A
功    能：定时器A的中断服务函数，在这里驱动
          蜂鸣器发声
参    数：无
返回值  ：无
********************************************/
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
  P6OUT ^= BIT7;                            // Toggle P6.7
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


