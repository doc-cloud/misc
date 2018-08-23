#include <msp430.h>
#include "DS1302.h"
#include <ctype.h> 
typedef unsigned char uchar;

uchar stime[7];     //存储用户设置时间的数组
uchar dtime[7];     //保存读取时间的数组

/*******************************************
函数名称：InitUART
功    能：初始化UART端口
参    数：无
返回值  ：无
********************************************/
void InitUART(void)
{
    P3SEL |= 0x30;                            // P3.4,5 = USART0 TXD/RXD
    ME1 |= URXE0 + UTXE0;                             // Enable USART0 T/RXD
    UCTL0 |= CHAR;                            // 8-bit character
    UTCTL0 |= SSEL0;                          // UCLK = ACLK
    UBR00 = 0x03;                             // 32k/9600 - 3.41
    UBR10 = 0x00;                             //
    UMCTL0 = 0x4A;                            // Modulation
    UCTL0 &= ~SWRST;                          // Initialize USART state machine
}
/*******************************************
函数名称：Send1Char
功    能：向PC机发送一个字符
参    数：sendchar--要发送的字符
返回值  ：无
********************************************/
void Send1Char(uchar sendchar)
{
      while (!(IFG1 & UTXIFG0));    //等待发送寄存器为空         
      TXBUF0 = sendchar; 
   
}
/*******************************************
函数名称：PutSting
功    能：向PC机发送字符串
参    数：ptr--指向发送字符串的指针
返回值  ：无
********************************************/
void PutString(uchar *ptr)
{
      while(*ptr != '\0')
      {
            Send1Char(*ptr++);                     // 发送数据
      }
      while (!(IFG1 & UTXIFG0));
      TXBUF0 = '\n';                              //发送换行指令
}
/*******************************************
函数名称：Get1Char
功    能：接收一个来自PC机的字符
参    数：无
返回值  ：接收到的字符
********************************************/
uchar Get1Char(void)
{
    while (!(IFG1 & URXIFG0));    //等待接收到字符        
    return  RXBUF0;
}
/*******************************************
函数名称：DisplayConfigMenu
功    能：显示操作菜单
参    数：无
返回值  ：无
********************************************/
void DisplayConfigMenu(void)
{
    PutString("Operation Menu:");
    PutString("S-- Set time in DS1302");
    PutString("D-- Display current time");
    PutString("*-- any other key to redispaly the menu");
}
/*******************************************
函数名称：SetTime
功    能：显示设置时间菜单并设置DS1302时间
参    数：无
返回值  ：无
********************************************/
void SetTime(void)
{
    PutString("Input the year number(00 ~ 99,BCD format):");
    stime[6] = Get1Char();
    PutString(">");
    PutString("Input the week(01 ~ 07,BCD format):");
    stime[5] = Get1Char();
    PutString(">");
    PutString("Input the month(01 ~ 12,BCD format):");
    stime[4] = Get1Char();
    PutString(">");
    PutString("Input the day(01 ~ 31,BCD format):");
    stime[3] = Get1Char();
    PutString(">");
    PutString("Input the hour(00 ~ 23,BCD format):");
    stime[2] = Get1Char();
    PutString(">");
    PutString("Input the minute(00 ~ 59,BCD format):");
    stime[1] = Get1Char();
    PutString(">");
    PutString("Input the second(00 ~ 59,BCD format):");
    stime[0] = Get1Char();
    PutString(">");
    
    Set_DS1302(stime);
    
    PutString("----DONE----");
}
/*******************************************
函数名称：DisplayTime
功    能：显示从DS1302中读取的时间
参    数：无
返回值  ：无
********************************************/
void DisplayTime(void)
{
    uchar tmp[8],i;
    
    Get_DS1302(dtime);
    
    tmp[0] = ((dtime[6]&0xf0)>>4) + 0x30;
    tmp[1] = (dtime[6]&0x0f) + 0x30;
    tmp[3] = ((dtime[4]&0xf0)>>4) + 0x30;
    tmp[4] = (dtime[4]&0x0f) + 0x30;
    tmp[6] = ((dtime[3]&0xf0)>>4) + 0x30;
    tmp[7] = (dtime[3]&0x0f) + 0x30;
    tmp[5] = '/';
    tmp[2] = '/';
    Send1Char('2');
    Send1Char('0');
    for(i = 0;i < 8;i++)
    {
        Send1Char(tmp[i]);
    }
    Send1Char(' ');
    switch(dtime[5])
    {
    case 0x01:  PutString("Monday");break;
    case 0x02:  PutString("Tuesday");break;
    case 0x03:  PutString("Wednesday");break;
    case 0x04:  PutString("Thursday");break;
    case 0x05:  PutString("Friday");break;
    case 0x06:  PutString("Saturday");break;
    case 0x07:  PutString("Sunday");break; 
    }   
    tmp[6] = ((dtime[0]&0xf0)>>4) + 0x30;
    tmp[7] = (dtime[0]&0x0f) + 0x30;
    tmp[3] = ((dtime[1]&0xf0)>>4) + 0x30;
    tmp[4] = (dtime[1]&0x0f) + 0x30;
    tmp[0] = ((dtime[2]&0xf0)>>4) + 0x30;
    tmp[1] = (dtime[2]&0x0f) + 0x30;
    tmp[5] = ':';
    tmp[2] = ':';
    for(i = 0;i < 8;i++)
    {
        Send1Char(tmp[i]);
    }
    PutString("");
}
    
/*******************************************
函数名称：HandleConfigMenu
功    能：处理PC的配置函数
参    数：inputvalue--接收到的来自PC机的字符
返回值  ：无
********************************************/
void HandleConfigMenu(uchar inputvalue)
{
    switch(toupper(inputvalue)) 
    {
    case 'S':
              SetTime();
              break;
    case 'D':
              DisplayTime();
              break;    
    default:
              DisplayConfigMenu();  
    }
}

