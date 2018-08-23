#include "IIC.h"
typedef unsigned char uchar;
typedef unsigned int  uint;

#define deviceaddress 0xa0  //AT24C02���豸��ַ

/*******************************************
�������ƣ�delay_10ms
��    �ܣ���ʱԼ6ms���ȴ�EEPROM����ڲ�д��
��    ������
����ֵ  ����
********************************************/
void delay_10ms(void)
{
	uint i = 1000;
	while(i--);
}
/*******************************************
�������ƣ�Write_1Byte
��    �ܣ���EEPROM��д��1���ֽڵ�����
��    ����Wdata--д�������
          dataaddress--���ݵ�д���ַ
����ֵ  ��д������1--�ɹ���0--ʧ��
********************************************/
uchar Write_1Byte(uchar wdata,uchar dataaddress)
{
	start();
	write1byte(deviceaddress);
	if(check()) 
        write1byte(dataaddress);
	else 
        return 0;
	if(check()) 
        write1byte(wdata);
	else 
        return 0;
	if(check())	    stop();
	else            return 0;
    
    delay_10ms();       //�ȴ�EEPROM����ڲ�д��
	return 1; 
}
/*******************************************
�������ƣ�Write_NByte
��    �ܣ���EEPROM��д��N���ֽڵ�����
��    ����outbuf--ָ��д�����ݴ���׵�ַ��ָ��
          n--���ݸ���������ܳ���8����ҳ��ַ
             ��������󳤶�
          dataaddress--����д����׵�ַ
����ֵ  ��д������1--�ɹ���0--ʧ��
********************************************/
uchar Write_NByte(uchar * outbuf,uchar n,uchar dataaddress)
{
	uchar  flag; 
    
	start();
	write1byte(deviceaddress);                  //д��������ַ
	if(check() == 1) 
        write1byte(dataaddress);                //д�������ֵ�ַ
	else 
        return 0;
	if(check()) 
        flag=writeNbyte(outbuf,n);
	else 
        return 0;
    delay_10ms();       //�ȴ�EEPROM����ڲ�д��
	if(flag)    return 1;
	else        return 0;

}
/*******************************************
�������ƣ�Read_1Byte_currentaddress
��    �ܣ���EEPROM�ĵ�ǰ��ַ��ȡ1���ֽڵ�����
��    ������
����ֵ  ����ȡ������
********************************************/
uchar Read_1Byte_currentaddress(void)
{
	uchar temp;
    
	start();
	write1byte((deviceaddress|0x01));
	if(check())	
        temp = read1byte();
	else 
        return 0;
	mnack();
	stop();
	return temp;
}
/*******************************************
�������ƣ�Read_NByte_currentaddress
��    �ܣ���EEPROM�ĵ�ǰ��ַ��ȡN���ֽڵ�����
��    ����readbuf--ָ�򱣴����ݵ�ַ��ָ��
          n--��ȡ���ݵĸ���
����ֵ  ����ȡ�����1--�ɹ���0--ʧ��
********************************************/
uchar Read_NByte_currentaddress(uchar * readbuf,uchar n)
{   
    start();
	write1byte((deviceaddress|0x01));
	if(check()) 
        readNbyte(readbuf,n);
	else 
        return 0;
    
	return  1;
}

/*******************************************
�������ƣ�Read_1Byte_Randomaddress
��    �ܣ���EEPROM��ָ����ַ��ȡ1���ֽڵ�����
��    ����dataaddress--���ݶ�ȡ�ĵ�ַ
����ֵ  ����ȡ������
********************************************/
uchar Read_1Byte_Randomaddress(uchar dataaddress)
{
	uchar temp;
    
	start();
	write1byte(deviceaddress);
	if(check())	
        write1byte(dataaddress);
	else 
        return 0;
	if(check()) 
	{
		start();
		write1byte((deviceaddress|0x01));
	}
	else    
        return 0;
	if(check())	
        temp = read1byte();
	else 
        return 0;

	mnack();
	stop();
	return temp;
}
/*******************************************
�������ƣ�Read_NByte_Randomaddress
��    �ܣ���EEPROM��ָ����ַ��ȡN���ֽڵ�����
��    ����readbuf--ָ�򱣴����ݵ�ַ��ָ��
          n--��ȡ���ݵĸ���
          dataaddress--���ݶ�ȡ���׵�ַ
����ֵ  ����ȡ�����1--�ɹ���0--ʧ��
********************************************/
uchar Read_NByte_Randomaddress(uchar * readbuf,uchar n,uchar dataaddress)
{
	start();
	write1byte(deviceaddress);
	if(check())	
        write1byte(dataaddress);
	else 
        return 0;
	if(check()) 
	{
		start();
		write1byte(deviceaddress|0x01);
	}
	else 
        return 0;
	if(check()) 
        readNbyte(readbuf,n);
	else 
        return 0;
	
	return 1;	
}
