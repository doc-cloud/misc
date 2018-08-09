#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//¼üÅÌ
//#define Key_Menu     PDin(0)
//#define Key_Confirm  PCin(12)  
//#define Key_Add      PCin(11)
//#define Key_Minus    PCin(10)

//#define Key_Start	 PDin(1)

#define KeyOut     PDin(0)
#define KeyConfirm  PCin(12)  
#define KeyDown      PCin(11)
#define KeyUp        PCin(10)

#define KeyStart	 PDin(1)
#define On  0
#define Off	1


void Key_Init(void);
		 				    
#endif
