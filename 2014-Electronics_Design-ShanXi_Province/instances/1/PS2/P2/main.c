/*****************************************************
�����ܣ����ղ��������Ա�׼���̵Ļ���������ɨ����
Ȼ��0~9��a~f��A~F�ַ������������ʾ

ע����ν�����������ǵ��˼�������ʱ��Ӧ���������ֽ�
��ɨ����İ�������������еġ��ڶ���ɨ���롷
-----------------------------------------------------
�������ã���������J4��1�ź�2�ţ��Ҳ���������̽�
-----------------------------------------------------
����˵�����ö���׼�����ϵİ������۲��������ʾ
*****************************************************/
#include  <msp430x14x.h>
#include "BoardConfig.h"
#include "Keyboard.h"
#include "gdata.h"

#define SIDval  P5IN & BIT6

//�����7λ���룺0--f,�Ͳ���ʾ�ַ�(0x00)
uchar scandata[17] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
                      0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x00};
//����ܵ���ʾ����
uchar DispBuf = 16;

/****************������****************/
void main(void)
{
    uchar disptmp,i,j;
    
    WDTCTL = WDTPW + WDTHOLD;         //�رտ��Ź�
    BoardConfig(0x48);                // ��4245������5-->3.3,����ܺ͹ر���ˮ��
    
    /*------ѡ��ϵͳ��ʱ��Ϊ8MHz-------*/
    BCSCTL1 &= ~XT2OFF;                 // ��XT2��Ƶ��������
    do
    {
        IFG1 &= ~OFIFG;                 // �������ʧ�ܱ�־
        for (i = 0xFF; i > 0; i--);     // �ȴ�8MHz��������
    }
    while ((IFG1 & OFIFG));             // ����ʧЧ��־��Ȼ���ڣ�
    BCSCTL2 |= SELM_2;                  // ��ʱ��ѡ���Ƶ����
    
    P4DIR = 0xff;                 //����P4��P5��IO����Ϊ���
    P5DIR = 0x3f;                 
  
    P4OUT = 0x00;                 //����P4��P5�������ֵ
    P5OUT = 0x00;
    
    P6DIR = BIT7;
    P6OUT = BIT7;
    
    Init_KB();                  //��ʼ�����̶˿�
    _EINT();                    //��ȫ���ж�
  
    while(1)
    {
        LPM1;                   //����͹���ģʽ
        disptmp = GetChar();    //��ȡ��ֵ��Ӧ��ASCII��
        
        if((disptmp > 0x2f)&&(disptmp < 0x3a)) //������յ����ַ���0~9
        {
            DispBuf = disptmp - 0x30; //�õ�ʵ�ʵ�����
        }
        else if((disptmp > 0x40)&&(disptmp < 0x47))//������յ����ַ���A~F
        {
            DispBuf = disptmp - 0x37; //�õ�ʵ�ʵ���ĸ      
        }
        else if((disptmp > 0x60)&&(disptmp < 0x67))//������յ����ַ���a~f
        {
            DispBuf = disptmp - 0x57; //�õ�ʵ�ʵ���ĸ 
        }
        else
        {
            DispBuf = 16;             //��������ܲ���ʾ
            
            P6OUT = 0;                //������������ʾ����
            for(i = 255; i > 0; i--)
              for(j = 80; j > 0; j--);
            P6OUT = BIT7;    
        }
        P4OUT = scandata[DispBuf];
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


