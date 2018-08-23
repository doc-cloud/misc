/***************************************************
�����ܣ���̬��ʾ�����ַ�
----------------------------------------------------
����˵�����۲�Һ����ʾ
****************************************************/
#include  <msp430.h>
#include  "BoardConfig.h" 
#include  "Cry1602.h"

uchar shuzi[] = {"0123456789"};
uchar zimu1[] = {"abcdefghigklmnopqrstuvwxyz"};
uchar zimu2[] = {"ABCDEFGHIGKLMNOPQRSTUVWXYZ"};
uchar *fuhao = "~`!@#$%^&*()_+-=/|,.��;'<>?:""";
uchar *jieshu = "This is the end!";

/***********************������************************/
void main( void )
{
    uchar i;
    WDTCTL = WDT_ADLY_1000;               //�����ʱ������ʱ1000ms
    BoardConfig(0xb8);                   //�ر�����ܡ���ˮ�ƺ͵�ƽת��
    
    LcdReset();
    DispNChar(3,0,10,shuzi);
    //��ʱ2s
    for(i = 0; i < 3; i++)
    {

        IFG1 &= ~WDTIFG;
        while(!(IFG1 & WDTIFG));
        IFG1 &= ~WDTIFG; 
    }
    LcdWriteCommand(0x01, 1);           //�����ʾ
    DispNChar(0,0,26,zimu1);
    //��ʱ2s
    for(i = 0; i < 3; i++)
    {

        IFG1 &= ~WDTIFG;
        while(!(IFG1 & WDTIFG));
        IFG1 &= ~WDTIFG; 
    }
    LcdWriteCommand(0x01, 1);           //�����ʾ
    DispNChar(0,0,26,zimu2);
    //��ʱ2s
    for(i = 0; i < 3; i++)
    {

        IFG1 &= ~WDTIFG;
        while(!(IFG1 & WDTIFG));
        IFG1 &= ~WDTIFG; 
    }
    LcdWriteCommand(0x01, 1);           //�����ʾ
    DispStr(0,0,fuhao);
    //��ʱ2s
    for(i = 0; i < 3; i++)
    {

        IFG1 &= ~WDTIFG;
        while(!(IFG1 & WDTIFG));
        IFG1 &= ~WDTIFG; 
    }
    LcdWriteCommand(0x01, 1);           //�����ʾ
    DispStr(0,0,jieshu);
    while(1);
}
