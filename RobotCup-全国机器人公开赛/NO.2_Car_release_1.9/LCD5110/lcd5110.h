#ifndef __5110_H
#define __5110_H

#include "sys.h"

#define N5110_CE_H()   GPIOA->BSRR|=1<<11; //
#define N5110_CE_L()   GPIOA->BRR|=1<<11;
#define N5110_RST_H()     GPIOC->BSRR|=1<<6; //
#define N5110_RST_L()     GPIOC->BRR|=1<<6;
#define N5110_DC_D()    GPIOA->BSRR|=1<<12; //
#define N5110_DC_C()    GPIOA->BRR|=1<<12;
#define N5110_DIN_H()     GPIOA->BSRR|=1<<13; //
#define N5110_DIN_L()     GPIOA->BRR|=1<<13;
#define N5110_CLK_H()     GPIOD->BSRR|=1<<6; //
#define N5110_CLK_L()     GPIOD->BRR|=1<<6;
//#define N5110_BL_ON()  GPIOD->BSRR|=1<<13; //
//#define N5110_BL_OFF()  GPIOD->BRR|=1<<13;
#define uint u16
#define uchar u8

void Write_Data(uchar DC,uchar Data);
void write_zuobiao(uchar X,uchar Y);
void Clean_Screen(void);
void write_char(char c);
void write_string(char *string);
void delay_5110(uint x);
void N5110_Init(void);
void display_word(uchar x ,uchar y , uchar *p);
void display_num_v(uchar x , uchar y , uint num);
void display_num_add(uchar x , uchar y , uint num);
void display_num_ad(uchar x , uchar y , uint num);
void display_num_a(uchar x , uchar y , uint num);
void gp_Init(void);//³õÊ¼»¯

void show_string(uchar x , uchar y ,char *string);

#endif


