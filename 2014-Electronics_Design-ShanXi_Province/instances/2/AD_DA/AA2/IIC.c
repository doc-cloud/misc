#include <msp430x14x.h>
typedef unsigned char uchar;
typedef unsigned int  uint;

#define SCL_H P1OUT |= BIT1
#define SCL_L P1OUT &= ~BIT1
#define SDA_H P1OUT |= BIT0
#define SDA_L P1OUT &= ~BIT0

#define SCL_out P1DIR |= BIT1    //SCL����Ϊ���ģʽ
#define SDA_in  P1DIR &= ~BIT0   //SDA�ĳ�����ģʽ
#define SDA_out P1DIR |= BIT0    //SDA������ģʽ
#define SDA_val P1IN&BIT0        //SDA��λֵ
 
#define TRUE    1
#define FALSE   0

/*******************************************
�������ƣ�Set_IO
��    �ܣ�����IIC��ӦIOΪ�����������ߵ�ƽ
��    ������
����ֵ  ����
********************************************/
void Set_IO(void)
{
    SCL_out;
    SDA_out;
    SCL_H;
    SDA_H;
}
/*******************************************
�������ƣ�delay
��    �ܣ���ʱԼ100us��ʱ��
��    ������
����ֵ  ����
********************************************/
void delay(void)
{
    uchar i;
    
    for(i = 0;i < 15;i++)
        _NOP();
}	
/*******************************************
�������ƣ�start
��    �ܣ����IIC����ʼ��������
��    ������
����ֵ  ����
********************************************/
void start(void)
{
    SCL_H;
    SDA_H;
    delay();
    SDA_L;
    delay();
    SCL_L;
    delay();
}
/*******************************************
�������ƣ�stop
��    �ܣ����IIC����ֹ��������
��    ������
����ֵ  ����
********************************************/
void stop(void)
{
    SCL_H;
    SDA_L;	
    delay();
    SDA_H;
    delay();	   
}
/*******************************************
�������ƣ�check
��    �ܣ����ӻ���Ӧ�����
��    ������
����ֵ  ���ӻ��Ƿ���Ӧ��1--�У�0--��
********************************************/
uchar check(void)
{
    uchar slaveack;

    SDA_in;
    SCL_H;
    delay();
    slaveack = SDA_val;   //����SDA��ֵ
    SCL_L;
    delay();
    SDA_out;
    if(slaveack)    return FALSE;
    else            return TRUE;
}
/*******************************************
�������ƣ�write1
��    �ܣ���IIC���߷���һ��1
��    ������
����ֵ  ����
********************************************/
void write1(void)
{
    SDA_H;
    delay();
    SCL_H;
    delay();
    SCL_L;				
    delay();
}
/*******************************************
�������ƣ�write0
��    �ܣ���IIC���߷���һ��0
��    ������
����ֵ  ����
********************************************/
void write0(void)
{
    SDA_L;
    delay();
    SCL_H;
    delay();			 
    SCL_L;				
    delay();
}
/*******************************************
�������ƣ�write1byte
��    �ܣ���IIC���߷���һ���ֽڵ�����
��    ����wdata--���͵�����
����ֵ  ����
********************************************/
void write1byte(uchar wdata)
{
    uchar i;

    for(i = 8;i > 0;i--)
    {
        if(wdata & 0x80)	write1();
        else 			write0();
        wdata <<= 1;
    }                    
}
