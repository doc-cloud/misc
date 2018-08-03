#ifndef __BEEP_H
#define __BEEP_H	 
#include "sys.h"

//BEEP端口定义
#define Beep PDout(2) //PD2

#define Beep_ON   Beep=0;
#define Beep_OFF  Beep=1;

void Beep_Init(void);//初始化
		 				    
#endif
