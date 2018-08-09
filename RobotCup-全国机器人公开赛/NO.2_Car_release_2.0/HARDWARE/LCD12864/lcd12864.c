#include "lcd12864.h" 	 
#include "delay.h"
#include "sys.h"

void SPI_SSSet(unsigned char Status);
void SPI_Send(unsigned char Data);
void FontMode(unsigned char Cover,unsigned char Color);
void FontSet(unsigned char Font_NUM,unsigned char Color);
void PutChar(unsigned char x,unsigned char y,unsigned char a);
void SetBackLight(unsigned char Deg);  

unsigned char X_Witch=6;
unsigned char Y_Witch=10;
unsigned char Dis_Zero=0;

//========================================================================
// 函数: void LCD_Init(void)
// 描述: LCD初始化程序，主要在里面完成端口初始化以及LCD模块的复位

void LCD_Init(void)
{
	GPIOD->CRL&=0XF0000FFF; 
	GPIOD->CRL|=0X03333000;   	 
    GPIOD->ODR|=1<<3;      
	GPIOD->ODR|=1<<4;     
	GPIOD->ODR|=1<<5;      
	GPIOD->ODR|=1<<6;      	
	
	//SS和SCK预先设置为高电平
	SPI_SCK = 1;
	SPI_CS = 1;
	
	//复位LCD模块
	SPI_RES = 0;
	delay_ms(2);			//保持低电平大概2ms左右
	SPI_RES = 1;
	delay_ms(10);				    	//延时大概10ms左右
	SetBackLight(5);			//设置背光打开 
	FontMode(1,0) ;
	FontSet(0,1);
	ClrScreen();
}
//========================================================================
// 函数: void SPI_SSSet(unsigned char Status)
// 描述: 置SS线状态
// 参数: Status   =1则置高电平，=0则置低电平 
 
void SPI_SSSet(unsigned char Status)
{
	if(Status)				//判断是要置SS为低还是高电平？//SS置高电平
		SPI_CS = 1;
	else   //SS置低电平
		SPI_CS = 0;
}
//========================================================================
// 函数: void SPI_Send(unsigned char Data)
// 描述: 通过串行SPI口输送一个byte的数据置模组
// 参数: Data 要传送的数据 

void SPI_Send(unsigned char Data)
{
	unsigned char i=0;
	for(i=0;i<8;i++)
	{
		//SCK置低
		SPI_SCK = 0;
		if(Data&0x0080)
			SPI_SDA = 1;			
		else SPI_SDA = 0;//
		//SCK上升沿触发串行数据采样
		SPI_SCK = 1;
		Data = Data<<1;							//数据左移一位
	}
}

//========================================================================
// 函数: void FontMode(unsigned char Cover,unsigned char Color)
// 描述: 设置字符显示覆盖模式
// 参数: Cover  字符覆盖模式设置，0或1
//		 Color 覆盖模式为1时字符显示时的背景覆盖色 
// 返回: 无
// 备注: 
// 版本:
//      2008/11/27      First version
//========================================================================
void FontMode(unsigned char Cover,unsigned char Color)
{
	unsigned char ucTemp=0;
	ucTemp = (Cover<<4)|Color;
	//设置ASCII字符的字型
	SPI_SSSet(0);					//SS置低电平			
	SPI_Send(0x89);					//传送指令0x81
	SPI_Send(ucTemp);				//选择8X16的ASCII字体,字符色为黑色
	SPI_SSSet(1);					//完成操作置SS高电平	
}

//========================================================================
// 函数: void FontSet(unsigned char Font_NUM,unsigned char Color)
// 描述: ASCII字符字体设置
// 参数: Font_NUM 字体选择,以驱动所带的字库为准
//		 Color  文本颜色,仅作用于ASCII字库  

void FontSet(unsigned char Font_NUM,unsigned char Color)
{
	unsigned char ucTemp=0;
	if(Font_NUM==0)
	{
		X_Witch = 6;//7;
		Y_Witch = 10;
	}
	else
	{
		X_Witch = 8;
		Y_Witch = 16;
	}
	ucTemp = (Font_NUM<<4)|Color;
	//设置ASCII字符的字型
	SPI_SSSet(0);					//SS置低电平			
	SPI_Send(0x81);					//传送指令0x81
	SPI_Send(ucTemp);				//选择8X16的ASCII字体,字符色为黑色
	SPI_SSSet(1);					//完成操作置SS高电平	
}

//========================================================================
// 函数: void PutChar(unsigned char x,unsigned char y,unsigned char a) 
// 描述: 写入一个标准ASCII字符
// 参数: x  X轴坐标     y  Y轴坐标
//		 a  要显示的字符在字库中的偏移量  
// 返回: 无
// 备注: ASCII字符可直接输入ASCII码即可

void PutChar(unsigned char x,unsigned char y,unsigned char a) 
{
	//显示ASCII字符
	SPI_SSSet(0);					//SS置低电平	
	SPI_Send(7);					//传送指令0x07
	SPI_Send(x);					//要显示字符的左上角的X轴位置
	SPI_Send(y);					//要显示字符的左上角的Y轴位置
	SPI_Send(a);					//要显示字符ASCII字符的ASCII码值
	SPI_SSSet(1);					//完成操作置SS高电平
}
//========================================================================
// 函数: void PutString(int x,int y,char *p)
// 描述: 在x、y为起始坐标处写入一串标准ASCII字符
// 参数: x  X轴坐标     y  Y轴坐标
//		 p  要显示的字符串  
// 返回: 无
// 备注: 仅能用于自带的ASCII字符串显示

void PutString(unsigned char x,unsigned char y,unsigned char *p)
{
	while(*p!=0)
	{
		PutChar(x,y,*p);
		x += X_Witch;
		if((x + X_Witch) > Dis_X_MAX)
		{
			x = Dis_Zero;
			if((Dis_Y_MAX - y) < Y_Witch) break;
			else y += Y_Witch;
		}
		p++;
	}
}

//========================================================================
// 函数: void ClrScreen(void)
// 描述: 清屏函数，执行全屏幕清除

void ClrScreen(void)
{
	//清屏操作
	SPI_SSSet(0);					//SS置低电平
	SPI_Send(0x80);					//送指令0x80
	SPI_SSSet(1);					//完成操作置SS高电平
}

//========================================================================
// 函数: void ShowShort(unsigned char x,unsigned char y,unsigned short Num)
// 描述: 在x、y的位置为显示区域的左上角，显示一个unsigned short型数（16位宽度）
// 参数: x  X轴坐标     y  Y轴坐标    Num  要显示的16位宽度的数据  

void ShowVar(unsigned char x,unsigned char y,unsigned short a)
{
	//显示ASCII字符
	SPI_SSSet(0);					//SS置低电平	
	SPI_Send(12);					//传送指令0x0C
	SPI_Send(x);					//要显示字符的左上角的X轴位置
	SPI_Send(y);					//要显示字符的左上角的Y轴位置
	SPI_Send((unsigned char)(a>>8));
	SPI_Send((unsigned char)a);
	SPI_Send(0);					//要显示字符ASCII字符的ASCII码值
	SPI_SSSet(1);					//完成操作置SS高电平
}
//========================================================================
// 函数: void SetBackLight(unsigned char Deg)
// 描述: 设置背光亮度等级
// 参数: Grade  0~127的等级

void SetBackLight(unsigned char Deg) 
{
	//显示ASCII字符
	SPI_SSSet(0);					//SS置低电平	
	SPI_Send(0x8a);					//传送指令0x07
	SPI_Send(Deg);					//要显示字符的左上角的X轴位置
	SPI_SSSet(1);					//完成操作置SS高电平
}
