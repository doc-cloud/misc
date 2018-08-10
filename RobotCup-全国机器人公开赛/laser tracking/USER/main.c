#include "SuperSharkV1.0.h"
//#include "functions.h"
#include "track_jg.h"
#include "arithmetic.h"

int main(void)
{
//	int now = 0;
	/*初始化*/
	SuperShark_Init();
	/*添加代码*/
	while(Key_Start() == 0);

	PutString_cn(32,24,"青锋机器人");

	PutString(0,0,"X-Y:"); 
	PutString(0,10,"X-Z:"); 
	PutString(0,20,"Y-Z:"); 

	while(1){
 

    
//  DMotor(1,20);
//	DMotor(2,20);
//	DMotor(3,20);
//	DMotor(4,20);
//    delay_ms(500);
//	
//    DMotor(1,40);
//	DMotor(2,40);
//	DMotor(3,40);
//	DMotor(4,40);   
//	delay_ms(500);
//
//	DMotor(1,60);
//	DMotor(2,60);
//	DMotor(3,60);
//	DMotor(4,60);   
//	delay_ms(500);
//
//	DMotor(1,80);
//	DMotor(2,80);
//	DMotor(3,80);
//	DMotor(4,80);   
//	delay_ms(500);


		DMotor_Control_Par(-10,10);
		delay_ms(500);
		DMotor_Control_Par(-40,40);
		delay_ms(500);
		DMotor_Control_Par(-60,60);
		delay_ms(500);
		DMotor_Control_Par(-80,80);
		delay_ms(500);
		DMotor_Control_Par(-60,60);
		delay_ms(500);
		DMotor_Control_Par(-40,40);
		delay_ms(500);
		DMotor_Control_Par(-10,10);
		delay_ms(500);							                                                                                                                                                                                    
		DMotor_Control_Par(0,0);
		delay_ms(1000);
		DMotor_Control_Par(10,-10);
		delay_ms(500);
		DMotor_Control_Par(40,-40);
		delay_ms(500);
		DMotor_Control_Par(60,-60);
		delay_ms(500);
		DMotor_Control_Par(80,-80);
		delay_ms(500);
		DMotor_Control_Par(60,-60);
		delay_ms(500);
		DMotor_Control_Par(40,-40);
		delay_ms(500);
		DMotor_Control_Par(10,-10);
		delay_ms(500);							                                                                                                                                                                                    
		DMotor_Control_Par(0,0);
		delay_ms(1000);

    }
}


