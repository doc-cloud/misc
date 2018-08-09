#include "compass.h" 
//#include "lcd12864.h"

#define	WriteDeviceAddress   0xE0	  //����������IIC�����еĵ�ַ
#define	ReadDviceAddress     0xE1     //������IIC�����е�ַ+1

void AT24C04_Start(void);
void AT24C04_Stop(void);
void AT24C04_SendACK(u8 ack);
u8  AT24C04_RecvACK(void);
void AT24C04_SendByte(u8 dat);
u8 AT24C04_RecvByte(void);
void AT24C04_ReadPage(void);
void AT24C04_WritePage(void);
u16 read_cmp(void);


//��ʼ��IIC
void Compass_Init(void)
{	
	//ָ����			     							 
	GPIOE->CRL&=0XF0FFFFFF;//PE6 �������
	GPIOE->CRL|=0X03000000;	   
	GPIOE->ODR|=1<<6;     //PE6 �����

	GPIOC->CRH&=0XFF0FFFFF;//PC13 �������
	GPIOC->CRH|=0X00300000;	   
	GPIOC->ODR|=1<<13;     //PC13 �����  
}

/*
**�������ܣ���ȡָ���봫���������Ƕ�ֵ
**����ֵ  ��temp---���ؽǶ�ֵ
*/
u16 read_cmp(void)
{   
	u16 temp = 0,temp1;

    AT24C04_Start();                          //��ʼ�ź�
    AT24C04_SendByte(WriteDeviceAddress);     //�����豸��ַ+д�ź�
    AT24C04_SendByte(0x00);                   //0��ʾ���� 
    AT24C04_SendByte(0x31);                   //����һ�β����Ƕ�
    AT24C04_Stop();                           //ֹͣ�ź�

	delay_ms(100);

    AT24C04_Start();                          //��ʼ�ź�
    AT24C04_SendByte(WriteDeviceAddress);     //�����豸��ַ+д�ź�
	AT24C04_SendByte(0x01);                   //���ʹ洢��Ԫ��ַ����0��ʼ	
	delay_us(10);
	AT24C04_Start();						   //��ʼ�ź�
	delay_us(10);                
    AT24C04_SendByte(WriteDeviceAddress+1);   //�����豸��ַ+���ź�
	delay_us(8);
	temp = AT24C04_RecvByte();
	AT24C04_SendACK(0); 
	temp = temp << 8;
	delay_us(10);	
	temp1 = AT24C04_RecvByte();
	delay_us(10);
	temp = temp | temp1;	
    AT24C04_SendACK(1);                //���һ��������Ҫ��NOACK    
	delay_us(10);
	AT24C04_Stop();					  //ֹͣ�ź�                       
	return temp;
}  

/**************************************
��ʼ�ź�
**************************************/
void AT24C04_Start()
{
	SDA_OUT();
    SDA = 1;                    //����������
    SCL = 1;                    //����ʱ����
    delay_us(8);                 //��ʱ
    SDA = 0;                    //�����½���
    delay_us(8);               //��ʱ
    SCL = 0;                    //����ʱ����
}

/**************************************
ֹͣ�ź�
**************************************/
void AT24C04_Stop()
{
	SDA_OUT();
	SDA = 0;
	SCL = 1; 
	delay_us(8);                    //����������                   //����ʱ����                //��ʱ
    SDA = 1;                    //����������
    delay_us(8);                 //��ʱ
}

/**************************************
����Ӧ���ź�
��ڲ���:ack (0:ACK 1:NAK)
**************************************/
void AT24C04_SendACK(u8 ack)
{
	SDA_OUT();
	SCL = 0;                    //����ʱ����
    delay_us(8);                 //��ʱ
    SDA = ack;                  //дӦ���ź�
    SCL = 1;                    //����ʱ����
    delay_us(8);                  //��ʱ
    SCL = 0;                    //����ʱ����
    delay_us(8);                 //��ʱ
}

/**************************************
����Ӧ���ź�
**************************************/
u8 AT24C04_RecvACK()
{
	u8 ucErrTime=0;

 	SDA_IN();      //SDA����Ϊ����  
	SDA=1;delay_us(4);	   
	SCL=1;delay_us(4);
		 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			AT24C04_Stop();
			return 1;
		}
	}
	SCL=0;//ʱ�����0 	   
	return 0;  
}

/**************************************
��IIC���߷���һ���ֽ�����
**************************************/
void AT24C04_SendByte(u8 dat)
{
	u8 t; 
	SDA_OUT(); 	    
    SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        SDA=(dat&0x80)>>7;
        dat<<=1; 	  
		delay_us(5);   //��TEA5767��������ʱ���Ǳ����
		SCL=1;
		delay_us(5); 
		SCL=0;	
		delay_us(5);
    }	
    AT24C04_RecvACK();
}

/**************************************
��IIC���߽���һ���ֽ�����
**************************************/	

u8 AT24C04_RecvByte()
{
	int i = 0;
	u8 byte = 0;
	SDA_IN();//SDA����Ϊ����
	for(i = 0;i < 8;i++)
	{
		SCL = 0;
		SDA = 1;
		delay_us(20);
		SCL = 1;
		delay_us(20);
		byte <<= 1;
		if(1 == READ_SDA)		
		{
			byte |= 0x01;
		}
		delay_us(20);
	}
	return byte;
}

//*********************************************************

/*
**�������ܣ�У׼ָ���봫����
*/
void cal_on(void)
{                                             
    AT24C04_Start();                          //��ʼ�ź�
    AT24C04_SendByte(WriteDeviceAddress);     //�����豸��ַ+д�ź�
    AT24C04_SendByte(0x00);                   //0��ʾ���� 
    AT24C04_SendByte(0xC0);                   //����У׼����
    AT24C04_Stop();                           //����ֹͣ�ź�
}

/*
**�������ܣ��ر�ָ�����У׼
*/
void cal_off(void)                            
{
    AT24C04_Start();                          //��ʼ�ź�
    AT24C04_SendByte(WriteDeviceAddress);     //�����豸��ַ+д�ź�
    AT24C04_SendByte(0x00);                   //0��ʾ���� 
    AT24C04_SendByte(0xC1);                   //����ֹͣУ׼����
    AT24C04_Stop();                           //����ֹͣ�ź�
}

/*
**�������ܣ��ָ���������
*/
void recovery_factory(void)                   
{
    AT24C04_Start();                          //��ʼ�ź�
    AT24C04_SendByte(WriteDeviceAddress);     //�����豸��ַ+д�ź�
    AT24C04_SendByte(0x00);                   //0��ʾ���� 
    AT24C04_SendByte(0xA0);                   //��������0xA0
    AT24C04_Stop();                           //����ֹͣ�ź�

    AT24C04_Start();                          //��ʼ�ź�
    AT24C04_SendByte(WriteDeviceAddress);     //�����豸��ַ+д�ź�
    AT24C04_SendByte(0x00);                   //0��ʾ���� 
    AT24C04_SendByte(0xAA);                   //��������0xAA
    AT24C04_Stop();                           //����ֹͣ�ź�

    AT24C04_Start();                          //��ʼ�ź�
    AT24C04_SendByte(WriteDeviceAddress);     //�����豸��ַ+д�ź�
    AT24C04_SendByte(0x00);                   //0��ʾ���� 
    AT24C04_SendByte(0xA5);                   //��������0xA5
    AT24C04_Stop();                           //����ֹͣ�ź�

	AT24C04_Start();                          //��ʼ�ź�
    AT24C04_SendByte(WriteDeviceAddress);     //�����豸��ַ+д�ź�
    AT24C04_SendByte(0x00);                   //0��ʾ���� 
    AT24C04_SendByte(0xC5);                   //����0xC5,�ָ���������
    AT24C04_Stop();                           //����ֹͣ�ź�

}

/*
**�������ܣ��޸�ָ�����ƫ��ֵ
*/
void CMP_OFFS(void)                        
{
    AT24C04_Start();                        //��ʼ�ź�
    AT24C04_SendByte(WriteDeviceAddress);   //�����豸��ַ+д�ź�
    AT24C04_SendByte(0x03);                 //0��ʾ���� 
    AT24C04_SendByte(0x00);                 //��ƫ�Ǹ�8λ��д��0
    AT24C04_Stop();                         //����ֹͣ�ź�

    AT24C04_Start();                        //��ʼ�ź�
    AT24C04_SendByte(WriteDeviceAddress);   //�����豸��ַ+д�ź�
    AT24C04_SendByte(0x04);                 //0��ʾ���� 
    AT24C04_SendByte(0x73);                 //��ƫ�ǵ�8λ��д��100��ʵ����10.0�ȣ�
    AT24C04_Stop();                         //����ֹͣ�ź�
}






