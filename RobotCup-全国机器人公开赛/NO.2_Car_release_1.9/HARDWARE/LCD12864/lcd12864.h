#ifndef __LCD12864_H
#define __LCD12864_H
			  	 		    						  
//-----------------12864端口定义----------------  
#define Dis_X_MAX		128-1
#define Dis_Y_MAX		64-1

#define SPI_CS  PDout(6) 
#define SPI_SDA PDout(5) 
#define SPI_SCK PDout(4) 
#define SPI_RES PDout(3) 

//8*16点阵
void LCD_Init(void);
void PutString(unsigned char x,unsigned char y,unsigned char *p);
void ShowVar(unsigned char x,unsigned char y,unsigned short a);
void ClrScreen(void);
		 	 
#endif  
	 



