#include <msp430.h>
#include "eeprom.h"
#include <ctype.h> 

typedef unsigned char uchar;

/*******************************************
�������ƣ�InitUART
��    �ܣ���ʼ��UART�˿�
��    ������
����ֵ  ����
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
�������ƣ�Send1Char
��    �ܣ���PC������һ���ַ�
��    ����sendchar--Ҫ���͵��ַ�
����ֵ  ����
********************************************/
void Send1Char(uchar sendchar)
{
      while (!(IFG1 & UTXIFG0));    //�ȴ����ͼĴ���Ϊ��         
      TXBUF0 = sendchar;   
}
/*******************************************
�������ƣ�PutSting
��    �ܣ���PC�������ַ���
��    ����ptr--ָ�����ַ�����ָ��
����ֵ  ����
********************************************/
void PutString(uchar *ptr)
{
      while(*ptr != '\0')
      {
            Send1Char(*ptr++);                     // ��������
      }
      while (!(IFG1 & UTXIFG0));
      TXBUF0 = '\n';                              //���ͻ���ָ��
}
/*******************************************
�������ƣ�Get1Char
��    �ܣ�����һ������PC�����ַ�
��    ������
����ֵ  �����յ����ַ�
********************************************/
uchar Get1Char(void)
{
    while (!(IFG1 & URXIFG0));    //�ȴ����յ��ַ�        
    return  RXBUF0;
}
/*******************************************
�������ƣ�Get1Char
��    �ܣ�����һ������PC�����ַ�
��    ������
����ֵ  �����յ����ַ�
********************************************/
void DisplayConfigMenu(void)
{
    PutString("Choose Read or Write operation:");
    PutString("R-- Read a char from EEPROM");
    PutString("W-- Write a char from EEPROM");
    PutString("*-- any other key to redispaly the menu");
}
/*******************************************
�������ƣ�HandleConfigMenu
��    �ܣ�����PC�����ú���
��    ����inputvalue--���յ�������PC�����ַ�
����ֵ  ����
********************************************/
void HandleConfigMenu(uchar inputvalue)
{
    uchar addr,wdata,result;
    uchar hi,lo;
    switch(toupper(inputvalue)) 
    {
    case 'R':
              PutString("Please send the memory address to read:");
              addr = Get1Char();
              Send1Char('>'); Send1Char('\n');
              result = Read_1Byte_Randomaddress(addr); 
              Send1Char(0x30);        //��Ļ��ʾ0
              Send1Char(0x78);        //��Ļ��ʾx
              hi = (result & 0xf0) >> 4; 
              if(hi > 0x09)
              {
                  Send1Char(0x37 + hi);    //��Ļ��ʾ��ĸ��A~F��
              }
              else
              {
                  Send1Char(0x30 + hi);     //��Ļ��ʾ����
              }
              lo = result & 0x0f;
              if(lo > 0x09)
              {
                  Send1Char(0x37 + lo);    //��Ļ��ʾ��ĸ��A~F��
              }
              else
              {
                  Send1Char(0x30 + lo);     //��Ļ��ʾ����
              }
              Send1Char('\n');
              break;
    case 'W':
              PutString("Please send the memory address to write:");
              addr = Get1Char();
              Send1Char('>'); Send1Char('\n');
              PutString("Please send the data to write:");
              wdata = Get1Char();
              Send1Char('>'); Send1Char('\n');
              if( Write_1Byte(wdata,addr) )
              {
                  PutString("Write successfully!");    
              }
              else
              {
                  PutString("Fail to write!");
              }
              break;

    default:
              DisplayConfigMenu();  
    }
}

