#include <msp430x14x.h>
typedef unsigned char uchar;
typedef unsigned int  uint;

#define keyin    (P1IN & 0x0f)

/*******************************************
�������ƣ�delay
��    �ܣ�������������ʱ
��    ������
����ֵ  ����
********************************************/
void delay_10ms(void)
{
    uint tmp;
    
    for(tmp = 0x3fff;tmp > 0;tmp--);
}
/*******************************************
�������ƣ�Key4Scan
��    �ܣ�ɨ���ĸ�����ʽ����
��    ������
����ֵ  ����ֵ
********************************************/
uchar Key4Scan(void)
{
    uchar temp,keyval;
    
    if(keyin != 0x0f)       //����м�������
    {
        delay_10ms();            //��ʱ����
        keyval = 0;
        if(keyin != 0x0f)   //�ٴμ�ⰴ��״̬
        {
            temp=keyin;
            while(keyin != 0x0f);   //�ȴ��������ſ�
            switch(temp)    //ת����ֵ    
            {
            case 0x0e:
                        keyval = 1;break;
            case 0x0d:
                        keyval = 2;break;
            case 0x0b:
                        keyval = 3;break;
            case 0x07:
                        keyval = 4;break;
            default:
                        keyval = 0;break;
            }
        }
    }
    else
        keyval = 0;
    
    return keyval;
    
}
