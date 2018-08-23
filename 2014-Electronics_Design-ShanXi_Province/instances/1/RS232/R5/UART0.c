#include <msp430.h>
#include <ctype.h> 
typedef unsigned char uchar;

//数码管7位段码：0--f
static uchar scandata[16] = 
{0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
 0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};

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
函数名称：Get1Char
功    能：接收一个来自PC机的字符
参    数：无
返回值  ：接收到的字符
********************************************/
void DisplayConfigMenu(void)
{
    PutString("Choose a frequency to drive the Buzzer:");
    PutString("0-- 100Hz");
    PutString("1-- 200Hz");
    PutString("2-- 400Hz");
    PutString("3-- 800Hz");
    PutString("4-- 1000Hz");
    PutString("5-- 2000Hz");
    PutString("6-- 3000Hz");
    PutString("7-- 4000Hz");
    PutString("8-- 5000Hz");
    PutString("9-- 6000Hz");
    PutString("A-- 7000Hz");
    PutString("B-- 8000Hz");
    PutString("C-- 9000Hz");
    PutString("D-- 10000Hz");
    PutString("E-- 15000Hz");
    PutString("F-- 20000Hz");
    PutString("S-- stop the Buzzer...");
    PutString("*-- any other key to redispaly the menu");
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
    case '0':
              TACCR0 = 5000;  
              TACTL |= MC0;
              P4OUT = scandata[0];
              break;
    case '1':
              TACCR0 = 2500;  
              TACTL |= MC0;
              P4OUT = scandata[1];
              break;
    case '2':
              TACCR0 = 1250;  
              TACTL |= MC0;
              P4OUT = scandata[2];
              break;
    case '3':
              TACCR0 = 625;  
              TACTL |= MC0;
              P4OUT = scandata[3];
              break;
    case '4':
              TACCR0 = 500;  
              TACTL |= MC0;
              P4OUT = scandata[4];
              break;
    case '5':
              TACCR0 = 250;  
              TACTL |= MC0;
              P4OUT = scandata[5];
              break;
    case '6':
              TACCR0 = 167;  
              TACTL |= MC0;
              P4OUT = scandata[6];
              break;
    case '7':
              TACCR0 = 125;  
              TACTL |= MC0;
              P4OUT = scandata[7];
              break;
    case '8':
              TACCR0 = 100;  
              TACTL |= MC0;
              P4OUT = scandata[8];
              break;
    case '9':
              TACCR0 = 83;  
              TACTL |= MC0;
              P4OUT = scandata[9];
              break;
    case 'A':
              TACCR0 = 71;  
              TACTL |= MC0;
              P4OUT = scandata[10];
              break;
    case 'B':
              TACCR0 = 63;  
              TACTL |= MC0;
              P4OUT = scandata[11];
              break;
    case 'C':
              TACCR0 = 56;  
              TACTL |= MC0;
              P4OUT = scandata[12];
              break;
    case 'D':
              TACCR0 = 50;  
              TACTL |= MC0;
              P4OUT = scandata[13];
              break;
    case 'E':
              TACCR0 = 33;  
              TACTL |= MC0;
              P4OUT = scandata[14];
              break;
    case 'F':
              TACCR0 = 25;  
              TACTL |= MC0;
              P4OUT = scandata[15];
              break;
    case 'S':  
              TACTL &= ~MC0;
              P6OUT = BIT7;
              P4OUT = 0x00;
              break;
    default:
              DisplayConfigMenu();  
              P4OUT = 0x00;
    }
}

