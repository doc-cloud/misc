#include <msp430x14x.h>
typedef unsigned char uchar;
typedef unsigned int  uint;

extern const unsigned char shuzi_table[];

#define LCD_DataIn    P4DIR=0x00    //���ݿڷ�������Ϊ����
#define LCD_DataOut   P4DIR=0xff    //���ݿڷ�������Ϊ���
#define LCD2MCU_Data  P4IN
#define MCU2LCD_Data  P4OUT
#define LCD_CMDOut    P3DIR|=0x07     //P3�ڵĵ���λ����Ϊ���
#define LCD_RS_H      P3OUT|=BIT0      //P3.0
#define LCD_RS_L      P3OUT&=~BIT0     //P3.0
#define LCD_RW_H      P3OUT|=BIT1      //P3.1
#define LCD_RW_L      P3OUT&=~BIT1     //P3.1
#define LCD_EN_H      P3OUT|=BIT2      //P3.2
#define LCD_EN_L      P3OUT&=~BIT2     //P3.2

/*******************************************
�������ƣ�Delay_1ms
��    �ܣ���ʱԼ1ms��ʱ��
��    ������
����ֵ  ����
********************************************/
void Delay_1ms(void)
{
	uchar i;
    
	for(i = 150;i > 0;i--)  _NOP();
} 
/*******************************************
�������ƣ�Delay_Nms
��    �ܣ���ʱN��1ms��ʱ��
��    ����n--��ʱ����
����ֵ  ����
********************************************/
void Delay_Nms(uint n)
{
    uint i;
    
    for(i = n;i > 0;i--)    Delay_1ms();
}
/*******************************************
�������ƣ�Write_Cmd
��    �ܣ���Һ����д��������
��    ����cmd--��������
����ֵ  ����
********************************************/
void Write_Cmd(uchar cmd)
{
    uchar lcdtemp = 0;
			
    LCD_RS_L;
    LCD_RW_H;
    LCD_DataIn;  
    do                       //��æ
    {    
        LCD_EN_H;
       	_NOP();					
       	lcdtemp = LCD2MCU_Data; 
       	LCD_EN_L;
        
    }
    while(lcdtemp & 0x80); 
    
    LCD_DataOut;    
    LCD_RW_L;  		
    MCU2LCD_Data = cmd; 
    LCD_EN_H;
    _NOP();						  			
    LCD_EN_L;
}
/*******************************************
�������ƣ�Write_Data
��    �ܣ���Һ����д��ʾ����
��    ����dat--��ʾ����
����ֵ  ����
********************************************/
void  Write_Data(uchar dat)
{
    uchar lcdtemp = 0;   
        
    LCD_RS_L;
    LCD_RW_H;  
    LCD_DataIn;   
    do                       //��æ
    {    
        LCD_EN_H;
        _NOP();						
        lcdtemp = LCD2MCU_Data; 
        LCD_EN_L;      
    }
    while(lcdtemp & 0x80);  
    
    LCD_DataOut; 
    LCD_RS_H;
    LCD_RW_L;  
        
    MCU2LCD_Data = dat;
    LCD_EN_H;
    _NOP();
    LCD_EN_L;
}  
/*******************************************
�������ƣ�Ini_Lcd
��    �ܣ���ʼ��Һ��ģ��
��    ������
����ֵ  ����
********************************************/
void Ini_Lcd(void)
{                  
    LCD_CMDOut;    //Һ�����ƶ˿�����Ϊ���
    
    Delay_Nms(500);
    Write_Cmd(0x30);   //����ָ�
    Delay_1ms();
    Write_Cmd(0x02);   // ��ַ��λ
    Delay_1ms();
	Write_Cmd(0x0c);   //������ʾ��,�α�ر�
    Delay_1ms();
	Write_Cmd(0x01);   //�����ʾ
    Delay_1ms();
	Write_Cmd(0x06);   //�α�����
    Delay_1ms();
	Write_Cmd(0x80);   //�趨��ʾ����ʼ��ַ
}
/*******************************************
�������ƣ�Disp_HZ
��    �ܣ�����Һ����ʾ����
��    ����addr--��ʾλ�õ��׵�ַ
          pt--ָ����ʾ���ݵ�ָ��
          num--��ʾ�ַ�����
����ֵ  ����
********************************************/
void Disp_HZ(uchar addr,const uchar * pt,uchar num)
{
    uchar i;
		
    Write_Cmd(addr); 
   	for(i = 0;i < (num*2);i++) 
        Write_Data(*(pt++)); 
} 
/*******************************************
��������:Clear_GDRAM
��    ��:���Һ��GDRAM�е��������
��    ��:��
����ֵ  :��
********************************************/
void Clear_GDRAM(void)
{
    uchar i,j,k;
    
	Write_Cmd(0x34);        //����չָ�
	i = 0x80;            
	for(j = 0;j < 32;j++)
	{
        Write_Cmd(i++);
        Write_Cmd(0x80);
  		for(k = 0;k < 16;k++)
  		{
  		    Write_Data(0x00);
  		}
	}
	i = 0x80;
 	for(j = 0;j < 32;j++)
	{
 	    Write_Cmd(i++);
        Write_Cmd(0x88);	   
  		for(k = 0;k < 16;k++)
  		{
   		    Write_Data(0x00);
   		} 
	}   
	Write_Cmd(0x30);        //�ص�����ָ�
}
/*******************************************
��������:Draw_PM
��    ��:������Һ����Ļ�ϻ�ͼ
��    ��:��
����ֵ  :��
********************************************/
void Draw_PM(const uchar *ptr)
{
    uchar i,j,k;
    
	Write_Cmd(0x34);        //����չָ�
	i = 0x80;            
	for(j = 0;j < 32;j++)
	{
        Write_Cmd(i++);
        Write_Cmd(0x80);
  		for(k = 0;k < 16;k++)
  		{
  		    Write_Data(*ptr++);
  		}
	}
	i = 0x80;
 	for(j = 0;j < 32;j++)
	{
 	    Write_Cmd(i++);
        Write_Cmd(0x88);	   
  		for(k = 0;k < 16;k++)
  		{
   		    Write_Data(*ptr++);
   		} 
	}  
    Write_Cmd(0x36);        //�򿪻�ͼ��ʾ
	Write_Cmd(0x30);        //�ص�����ָ�
}
/*******************************************
�������ƣ�Draw_TX
��    �ܣ���ʾһ��16*16��С��ͼ��
��    ����Yaddr--Y��ַ
          Xaddr--X��ַ
          dp--ָ��ͼ�����ݴ�ŵ�ַ��ָ��
����ֵ  ����
********************************************/
void Draw_TX(uchar Yaddr,uchar Xaddr,const uchar * dp) 
{
    uchar j;
    uchar k=0;
 
    Write_Cmd(0x01);  //����,ֻ�����DDRAM
    Write_Cmd(0x34);  //ʹ����չָ����رջ�ͼ��ʾ
    for(j=0;j<16;j++)
    {
        Write_Cmd(Yaddr++);       //Y��ַ
  		Write_Cmd(Xaddr);    //X��ַ
  		Write_Data(dp[k++]);  
  		Write_Data(dp[k++]);
    }
    Write_Cmd(0x36);  //�򿪻�ͼ��ʾ
    Write_Cmd(0x30);  //�ص�����ָ�ģʽ
}
