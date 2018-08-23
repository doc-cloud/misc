/****************************************************
�����ܣ���1602Һ������ʾһ����������������ͨ��
          �ĸ����������ø��ֲ���
-----------------------------------------------------
����˵������1����K1����������ģʽ������ѡ����Ĳ�
               ����λ�ã�
          ��2����K2��������������ֵ
          ��3����K3��������ǰ�޸Ļص�����ģʽ
          ��4����K4�����浱ǰ��ֵ�ص�����ģʽ
           ʵ�ʰ����۲���ԡ�
******************************************************/
#include <msp430x14x.h>
#include "BoardConfig.h"
#include "cry1602.h"
#include "DS1302.h"

//˳���룬�֣�ʱ���գ��£����ڣ��ꣻ��ʽ��BCD
uchar times[7];
//Һ����ʾ���ֱ���
uchar shuzi[] = {"0123456789"};
//�α�λ�ñ���
uchar PP = 0;
//�Ƿ����޸�״̬��־��1--�ǣ�0--��
uchar cflag = 0;

uchar Key4Scan(void);
void ShowTime(void);
/****************������****************/
void main(void)
{    
    WDTCTL = WDTPW + WDTHOLD;   //�رտ��Ź�
    BoardConfig(0xb8);          // �ر�����ܡ���ˮ�ơ���ƽת��
    
    P1DIR = 0x80;               //P1.7����Ϊ���������Ϊ����
    P1OUT = 0x00;
    
    Reset_DS1302();             //��ʼ��DS1302
    LcdReset();                 //��ʼ��Һ��
    while(1)
    {
        if(!cflag)
        {
            Get_DS1302(times);          //��ȡʱ������
            ShowTime();                 //ת����ʾ
        }
        
        switch(Key4Scan())
        {
        case 0x01:
                    switch(PP++)      //ȷ���α��ַ
                    {
                    case 0: LocateXY(4,0);break;
                    case 1: LocateXY(7,0);break;
                    case 2: LocateXY(10,0);break;
                    case 3: LocateXY(13,0);break;
                    case 4: LocateXY(4,1);break;
                    case 5: LocateXY(7,1);break;
                    case 6: LocateXY(10,1);break;
                    default:break;
                    }                  
                    LcdWriteCommand(0x0f, 1);   //���α�
                    if(PP == 7) PP = 0;
                    cflag = 1;          //��־��λ
                    break;
        case 0x02:
                    if(cflag)
                    {
                        switch(PP)
                        {
                        case 1:         //��
                                times[6]++;
                                if((times[6]&0x0f) == 0x0a)
                                {
                                    times[6] += 0x06;       
                                }
                                if(times[6] > 0x99)
                                {
                                    times[6] = 0x00;    
                                }
                                Disp1Char(3,0,shuzi[times[6]>>4]);
                                Disp1Char(4,0,shuzi[times[6]&0x0f]);
                                LocateXY(4,0); 
                                break;
                        case 2:         //��
                                times[4]++;
                                if((times[4]&0x0f) == 0x0a)
                                {
                                    times[4] += 0x06;       
                                }
                                if(times[4] > 0x12)
                                {
                                    times[4] = 0x01;    
                                }
                                Disp1Char(6,0,shuzi[times[4]>>4]);
                                Disp1Char(7,0,shuzi[times[4]&0x0f]);
                                LocateXY(7,0);
                                break;
                         case 3:         //��
                                times[3]++;
                                if((times[3]&0x0f) == 0x0a)
                                {
                                    times[3] += 0x06;       
                                }
                                if(times[3] > 0x31)
                                {
                                    times[3] = 0x01;    
                                }
                                Disp1Char(9,0,shuzi[times[3]>>4]);
                                Disp1Char(10,0,shuzi[times[3]&0x0f]);
                                LocateXY(10,0);
                                break;
                         case 4:         //��
                                times[5]++;
                                if((times[5]&0x0f) == 0x08)
                                {
                                    times[5] = 0x01;       
                                }
                                Disp1Char(13,0,shuzi[times[5]]);
                                LocateXY(13,0);
                                break;
                         case 5:         //ʱ
                                times[2]++;
                                if((times[2]&0x0f) == 0x0a)
                                {
                                    times[2] += 0x06;       
                                }
                                if(times[2] > 0x23)
                                {
                                    times[2] = 0x00;    
                                }
                                Disp1Char(3,1,shuzi[times[2]>>4]);
                                Disp1Char(4,1,shuzi[times[2]&0x0f]);
                                LocateXY(4,1);
                                break;
                         case 6:         //��
                                times[1]++;
                                if((times[1]&0x0f) == 0x0a)
                                {
                                    times[1] += 0x06;       
                                }
                                if(times[1] > 0x59)
                                {
                                    times[1] = 0x00;    
                                }
                                Disp1Char(6,1,shuzi[times[1]>>4]);
                                Disp1Char(7,1,shuzi[times[1]&0x0f]);
                                LocateXY(7,1);
                                break;
                         case 0:         //ʱ
                                times[0]++;
                                if((times[0]&0x0f) == 0x0a)
                                {
                                    times[0] += 0x06;       
                                }
                                if(times[0] > 0x59)
                                {
                                    times[0] = 0x00;    
                                }
                                Disp1Char(9,1,shuzi[times[0]>>4]);
                                Disp1Char(10,1,shuzi[times[0]&0x0f]);
                                LocateXY(10,1);
                                break;
                        default:
                                break;                            
                                
                        }
                    }
                    break;
        case 0x03:
                    if(cflag)
                    {
                        cflag = 0;
                        PP = 0;
                        LcdWriteCommand(0x0c, 1);   //�ر��α�
                    }
                    break;
        case 0x04:
                    if(cflag)
                    {
                        cflag = 0;
                        PP = 0;
                        LcdWriteCommand(0x0c, 1);   //�ر��α�
                        Set_DS1302(times);
                    }
                    break; 
        default:
                    break;                    
        }
    }
}
/*******************************************
�������ƣ�ShowTime
��    �ܣ���DS1302��ʱ��ת����10������ʾ
��    ������
����ֵ  ����
********************************************/    
void ShowTime(void)
{
    uchar h1[14];       //��1����ʾ����
    uchar h2[8];        //��2����ʾ����
    
    h1[0] = shuzi[2];
    h1[1] = shuzi[0];
    h1[2] = shuzi[times[6]>>4];     //��
    h1[3] = shuzi[times[6]&0x0f];
    h1[4] = 0x2d;       //"-"
    h1[5] = shuzi[times[4]>>4];     //��
    h1[6] = shuzi[times[4]&0x0f];
    h1[7] = 0x2d;       //"-"
    h1[8] = shuzi[times[3]>>4];     //��
    h1[9] = shuzi[times[3]&0x0f];
    h1[10] = 0x20;      //" "
    h1[11] = 0x2a;      //"*"
    h1[12] = shuzi[times[5]];       //��
    h1[13] = 0x2a;      //"*"
    DispNChar(1,0,14,h1);           //�ڵ�һ����ʾ
   
    h2[0] = shuzi[times[2]>>4];     //ʱ
    h2[1] = shuzi[times[2]&0x0f];
    h2[2] = 0x3a;       //":"
    h2[3] = shuzi[times[1]>>4];     //��
    h2[4] = shuzi[times[1]&0x0f];
    h2[5] = 0x3a;       //":"
    h2[6] = shuzi[times[0]>>4];     //��
    h2[7] = shuzi[times[0]&0x0f];
    DispNChar(3,1,8,h2);           //�ڵڶ�����ʾ
}
