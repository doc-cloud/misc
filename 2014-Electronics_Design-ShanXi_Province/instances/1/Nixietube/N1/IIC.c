#include <msp430x14x.h>
typedef unsigned char uchar;
typedef unsigned int  uint;

#define SCL_H P1OUT |= BIT2
#define SCL_L P1OUT &= ~BIT2
#define SDA_H P1OUT |= BIT3
#define SDA_L P1OUT &= ~BIT3

#define SDA_in  P1DIR &= ~BIT3   //SDA�ĳ�����ģʽ
#define SDA_out P1DIR |= BIT3    //SDA������ģʽ
#define SDA_val P1IN&BIT3        //SDA��λֵ
 
#define TRUE    1
#define FALSE   0

/*******************************************
�������ƣ�delay
��    �ܣ���ʱԼ15us��ʱ��
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
	SDA_L;
	delay();
	SCL_H;
	delay();
	SDA_H;
	delay();	   
}
/*******************************************
�������ƣ�mack
��    �ܣ����IIC������Ӧ�����
��    ������
����ֵ  ����
********************************************/
void mack(void)
{
	SDA_L;
	_NOP(); _NOP();
	SCL_H;
	delay();
	SCL_L;
	_NOP();_NOP();
	SDA_H;     
	delay();
}
/*******************************************
�������ƣ�mnack
��    �ܣ����IIC��������Ӧ�����
��    ������
����ֵ  ����
********************************************/
void mnack(void)
{
	SDA_H;
	_NOP(); _NOP();
	SCL_H;
	delay();
	SCL_L;
	_NOP(); _NOP();
	SDA_L;   
	delay();       
}

/**********���Ӧ���źź���******************/
/*�������ֵΪ1��֤����Ӧ���źţ���֮û��*/
/*******************************************
�������ƣ�check
��    �ܣ����ӻ���Ӧ�����
��    ������
����ֵ  ���ӻ��Ƿ���Ӧ��1--�У�0--��
********************************************/
uchar check(void)
{
	uchar slaveack;
    
	SDA_H;
	_NOP(); _NOP();
	SCL_H;
	_NOP(); _NOP();
        SDA_in;
        _NOP(); _NOP();
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
		else 			    write0();
		wdata <<= 1;
	}                  
	
	SDA_H;
	_NOP();   
}
/*******************************************
�������ƣ�writeNbyte
��    �ܣ���IIC���߷���N���ֽڵ�����
��    ����outbuffer--ָ�������ݴ���׵�ַ
          ��ָ��
          n--���ݵĸ���
����ֵ  �������Ƿ�ɹ��ı�־��1--�ɹ���0--ʧ��
********************************************/
uchar writeNbyte(uchar * outbuffer,uchar n)
{
	uchar i;
    
	for(i = 0;i < n;i++)
	{
		write1byte(* outbuffer);
		if(check())      
		{
			outbuffer++;			
		}
		else 
		{
			stop();
			return FALSE;
		}
	}

	stop();
	return TRUE;			
}
/*******************************************
�������ƣ�read1byte
��    �ܣ���IIC���߶�ȡһ���ֽ�
��    ������
����ֵ  ����ȡ������
********************************************/
uchar read1byte(void)
{
	uchar  rdata = 0x00,i;
    uchar flag;
    
	for(i = 0;i < 8;i++)
	{
		SDA_H;
		delay();
		SCL_H;
        SDA_in;
		delay();
		flag = SDA_val;
		rdata <<= 1;
		if(flag)	rdata |= 0x01;
        SDA_out;
		SCL_L;
		delay();
	}

	return rdata;
}
/*******************************************
�������ƣ�readNbyte
��    �ܣ���IIC���߶�ȡN���ֽڵ�����
��    ����inbuffer--��ȡ�����ݴ�ŵ��׵�ַ
          n--���ݵĸ���
����ֵ  ����
********************************************/
void readNbyte(uchar * inbuffer,uchar n)
{
	uchar i;
    
	for(i = 0;i < n;i++)
	{
		inbuffer[i] = read1byte();
		if(i < (n-1))	mack();
		else            mnack();
	}
	 
	stop();
}
