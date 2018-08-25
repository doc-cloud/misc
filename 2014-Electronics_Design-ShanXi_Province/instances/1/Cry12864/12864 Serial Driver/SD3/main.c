/***************************************************
�����ܣ��ô�������ͨ�ŷ�ʽ��ʾ����ͼƬ
----------------------------------------------------
�������ã���������J5��2�ź�3��(-)�ö�·ñ�̽�
----------------------------------------------------
����˵�����۲�Һ����ʾ
****************************************************/
#include  <msp430x14x.h>
#include "BoardConfig.h"
#include "cryfucns.h"
#include "monkey.h"

/****************������****************/
void main(void)
{    
    WDTCTL = WDTPW + WDTHOLD;            //�رտ��Ź�
    BoardConfig(0xb8);                   //�ر�����ܡ���ˮ�ơ�4245
    
    Ini_Lcd();
    Clear_GDRAM();
    
    Draw_PM(monkey1);                    //��ʾ�����ʽ�ĺ��ӻ���             
    
    _NOP();                              //���öϵ�۲�
    
    Draw_PM(monkey2);                    //��ʾ�����ʽ�ĺ��ӻ���               
    
    LPM4;
}