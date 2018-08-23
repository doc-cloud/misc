/***********************************************
�����ܣ�ɨ��4X4���̲�����ֵ��1602Һ������ʾ
------------------------------------------------
�������ã���������J3�ϵĶ�·ñ����
------------------------------------------------
����˵��������K1~K16�������۲�Һ����ʾ
************************************************/
#include <msp430x14x.h>
#include "BoardConfig.h"
#include "Keypad.h"
#include "cry1602.h"

//�����ⲿ����������    
extern unsigned char key_val;         
extern unsigned char key_Flag; 
/********************������********************/
void main(void)
{
    uchar Strings[]={"Key Value:"};
    uchar temp;
    
    WDTCTL = WDTPW + WDTHOLD;       //�رտ��Ź�
    BoardConfig(0xb8);              //�ر�����ܡ���ˮ�ƺ͵�ƽת��      
    
    LcdReset();                     //��ʼ��LCD
    Init_Keypad();                  //��ʼ�����̶˿�
    DispNChar(2,0,10,Strings);        //��ʾ��ʾ����
    while(1)
    {
        Key_Event();
    
        if(key_Flag == 1)
        {
            key_Flag = 0;
            
            //��ʾʮλ
            temp = key_val / 10;
            if(temp)
                Disp1Char(6,1,0x30+temp);  //���ֵ�ASCII��ֵ�����䱾����ֵ����0x30
            else
                Disp1Char(6,1,0x20);       //0x20�ǿո��Ӧ��ASCII��
            //��ʾ��λ
            temp = key_val % 10;
            Disp1Char(7,1,0x30+temp);   
        }
    }
}

