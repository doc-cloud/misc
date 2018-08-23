/*****************************************************
�����ܣ����ղ��������Ա�׼���̵Ļ���������ɨ����
Ȼ����1602Һ������ʾ����Back Space������ǰ��ɾ����
ʾ�ַ�����Space�����Ժ���ɾ����ʾ�ַ���

ע����ν�����������ǵ��˼�������ʱ��Ӧ���������ֽ�
��ɨ����İ�������������еġ��ڶ���ɨ���롷
-----------------------------------------------------
�������ã���������J4��1�ź�2�ţ��Ҳ���������̽�
-----------------------------------------------------
����˵�����ö���׼�����ϵİ������۲�Һ����ʾ
*****************************************************/
#include  <msp430x14x.h>
#include "BoardConfig.h"
#include "cry1602.h"
#include "Keyboard.h"
#include "gdata.h"

#define SIDval  P5IN & BIT6

/****************������****************/
void main(void)
{
    uchar disptmp,i;
    uchar x = 0,y = 0;
    uchar first = 1;
    
    WDTCTL = WDTPW + WDTHOLD;       //�رտ��Ź�
    BoardConfig(0x78);              //��4245������5-->3.3,�ر�����ܺ���ˮ��
    
    /*------ѡ��ϵͳ��ʱ��Ϊ8MHz-------*/
    BCSCTL1 &= ~XT2OFF;                 // ��XT2��Ƶ��������
    do
    {
        IFG1 &= ~OFIFG;                 //�������ʧ�ܱ�־
        for (i = 0xFF; i > 0; i--);     // �ȴ�8MHz��������
    }
    while ((IFG1 & OFIFG));             // ����ʧЧ��־��Ȼ���ڣ�
    BCSCTL2 |= SELM_2;                  //��ʱ��ѡ���Ƶ����
    
    LcdReset();                 //��λҺ��
    DispNchar(0,0,15,tishi);    //Һ����ʾ��ʾ��Ϣ
    Init_KB();                  //��ʼ�����̶˿�
    _EINT();                    //��ȫ���ж�
  
    while(1)
    {
        LPM3;                   //����͹���ģʽ
        
        if(first)
        {
            first = 0;
            LcdWriteCommand(0x01, 1);   //��ʾ����
            LcdWriteCommand(0x0f, 1);   //���α�
        }
        
        disptmp = GetChar();    //��ȡ��ֵ��Ӧ��ASCII��
        if(disptmp != 0xff)     //ȡ����һ����Ч�ַ�
        {
            if(disptmp == 8) //������˸��
            {
                if((x == 0) && (y == 0))//����α��ڵ�1�е�1λ
                {
                    x = 15;
                    y = 1;
                    Disp1Char(x,y,0x20); //0x20�ǿո��ASCII��
                    LocateXY(x,y);
                }
                else if((x == 0) && (y == 1))//����α��ڵ�2�е�1λ
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
            else if((disptmp == 9) || (disptmp == 13)) //�����Table����Enter��
            {
                _NOP();   
            }
            else    //�����ַ���ʾ
            {
                Disp1Char(x++,y,disptmp);
                if(x == 16)           //���һ����ʾ���
                {
                    x = 0;
                    y ^= 1;
                    LocateXY(x,y);  //���¶�λ�α�λ��
                }
            }
        }
    }
}

/*******************************************
�������ƣ�PORT1_ISR 
��    �ܣ�P1�˿ڵ��жϷ������������������
          �Լ��̵��ַ�
��    ������
����ֵ  ����
********************************************/
#pragma vector=PORT1_VECTOR
__interrupt void  PORT1_ISR(void)
{
    if(P1IFG & BIT7)            //�����clock���ж�
    {
        P1IFG &=~ BIT7;         //����жϱ�־ 
        
        if(bitcount == 11)        //���յ�1λ
        {
            if(SIDval)          //���������ʼλ
                return;
            else  
                bitcount--;
        } 
        else if(bitcount == 2)    //������żУ��λ
        {   
            if(SIDval)          //���У��λ����1
                pebit = 1;
            else
                pebit = 0;
            bitcount--;
        }
        else if(bitcount == 1)    //����ֹͣλ
        {
            if(SIDval)          //��ֹͣλ��ȷ
            {
                bitcount = 11;    //��λλ��������
                if( Decode(recdata) )    //�����ô˼�ֵ��ASCIIֵ������
                    LPM3_EXIT;           //�˳��͹���ģʽ
                recdata = 0;          //�����������
            }
            else                //�������
            {
                bitcount = 11;
                recdata = 0;    
            }
        }
        else                    //����8������λ
        {
            recdata >>= 1;
            if(SIDval)  recdata |= 0x80;
            bitcount--;
        }
   }
}


