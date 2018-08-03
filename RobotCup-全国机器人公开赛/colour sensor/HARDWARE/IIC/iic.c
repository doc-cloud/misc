#include "iic.h" 

void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�
void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);

//��ʼ��IIC
void IIC_Init(void)
{	
	//EEPROM
	GPIOE->CRL&=0XFF00FFFF;//PE4/5 �������
	GPIOE->CRL|=0X00330000;	   
	GPIOE->ODR|=1<<4;     //PE4/5 �����
	GPIOE->ODR|=1<<5;
}
//����IIC��ʼ�ź�
void IIC_Start()
{
	SDA_OUT2();     //sda�����
	IIC_SDA2=1;	  	  
	IIC_SCL2=1;
	delay_us(4);
 	IIC_SDA2=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL2=0;//ǯסI2C���ߣ�׼�����ͻ�������� 	
}	  
//����IICֹͣ�ź�
void IIC_Stop()
{
	SDA_OUT2();//sda�����
	IIC_SCL2=0;
	IIC_SDA2=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL2=1; 
	IIC_SDA2=1;//����I2C���߽����ź�
	delay_us(4);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_Wait_Ack()
{
	u8 ucErrTime=0;

	SDA_IN2();      //SDA����Ϊ����  
	IIC_SDA2=1;delay_us(1);	   
	IIC_SCL2=1;delay_us(1);	 
	while(READ_SDA2)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL2=0;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void IIC_Ack()
{
	IIC_SCL2=0;
	SDA_OUT2();
	IIC_SDA2=0;
	delay_us(2);
	IIC_SCL2=1;
	delay_us(2);
	IIC_SCL2=0;	
}
//������ACKӦ��		    
void IIC_NAck()
{	
	IIC_SCL2=0;
	SDA_OUT2();
	IIC_SDA2=1;
	delay_us(2);
	IIC_SCL2=1;
	delay_us(2);
	IIC_SCL2=0;
	
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t; 
	SDA_OUT2(); 	    
    IIC_SCL2=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        IIC_SDA2=(txd&0x80)>>7;
        txd<<=1; 	  
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		IIC_SCL2=1;
		delay_us(2); 
		IIC_SCL2=0;	
		delay_us(2);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;

	SDA_IN2();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        IIC_SCL2=0; 
        delay_us(2);
		IIC_SCL2=1;
        receive<<=1;
        if(READ_SDA2)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK  	
    return receive;
}

//EEPROM����

//��AT24C02ָ����ַ����һ��16λ������  0~127
u16 EEPROM_Read(u8 ReadAddr)
{				  
	u16 temp=0;		  	    																 
    IIC_Start();  
	IIC_Send_Byte(0XA0);   //����������ַ0XA0,д���� 	   
	IIC_Wait_Ack(); 
    IIC_Send_Byte(ReadAddr*2);   //���͵�ַ
	IIC_Wait_Ack();	    
	IIC_Start();  	 	   
	IIC_Send_Byte(0XA1);           //�������ģʽ			   
	IIC_Wait_Ack();	 
    temp=IIC_Read_Byte(0);		   
    IIC_Stop();//����һ��ֹͣ����
	
	IIC_Start();  
	IIC_Send_Byte(0XA0);   //����������ַ0XA0,д���� 	   
	IIC_Wait_Ack(); 
    IIC_Send_Byte(ReadAddr*2+1);   //���͵�ַ
	IIC_Wait_Ack();	    
	IIC_Start();  	 	   
	IIC_Send_Byte(0XA1);           //�������ģʽ			   
	IIC_Wait_Ack();
	temp = temp << 8;	 
    temp = temp | IIC_Read_Byte(0);		   
    IIC_Stop();//����һ��ֹͣ����	    
	return temp;
}
//��AT24C02ָ����ַд��һ��16λ����
void EEPROM_Write(u8 WriteAddr,u16 DataToWrite)
{
	u8 temp;				   	  	    																 
    IIC_Start();  
	IIC_Send_Byte(0XA0);   //����������ַ0XA0,д���� 	 
	IIC_Wait_Ack();	   
    IIC_Send_Byte(WriteAddr*2);   //���͵�ַ
	IIC_Wait_Ack(); 
	temp = (DataToWrite&0xff00) >> 8;	 										  		   
	IIC_Send_Byte(temp);     //���͵��ֽ�							   
	IIC_Wait_Ack();  		    	   
    IIC_Stop();//����һ��ֹͣ���� 
	delay_ms(10);	
	
	IIC_Start();  
	IIC_Send_Byte(0XA0);   //����������ַ0XA0,д���� 	 
	IIC_Wait_Ack();	   
    IIC_Send_Byte(WriteAddr*2+1);   //���͵�ַ
	IIC_Wait_Ack(); 
	temp = DataToWrite&0x00ff;										  		   
	IIC_Send_Byte(temp);     //�����ֽ�							   
	IIC_Wait_Ack();  		    	   
    IIC_Stop();//����һ��ֹͣ���� 
	delay_ms(10);	  
}
