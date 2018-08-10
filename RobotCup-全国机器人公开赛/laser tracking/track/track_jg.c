#include "track_jg.h"

#define	j1 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_7)	
#define	j2 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_8)
#define	j3 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_9)
#define	j4 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_10)
#define	j5 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_11)
#define	j6 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_12)
#define	j7 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_13)
#define	j8 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_14) 
#define	j9 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_15)  

/*
**函数功能：电机控制函数
**参	数:	Dx---代表电机x
**			DPx--代表对应电机PWM占空比 
*/

//void DMotor_Control(u8 D1,s8 DP1,u8 D2,s8 DP2,u8 D3,s8 DP3,u8 D4,s8 DP4)
//{
//	DMotor(D1,DP1);
//	DMotor(D2,DP2);
//	DMotor(D3,DP3);
//	DMotor(D4,DP4);
//}
//
///*
//**函数功能：电机双列并行控制
//**参	数: left-----小车左边电机
//**			right----小车右边电机
//*/
//void DMotor_Control_Par(s8 left,s8 right)
//{
//	DMotor_Control(1,left,2,left,3,right,4,right);
//}								  

void Test()
{
	if(j9 == 1)
	DMotor_Control_Par(20,20);
	else
	DMotor_Control_Par(0,0);
}

void Track_wheel_left_90()
{
	DMotor_Control_Par(0,82);	
	delay_ms(500);
	DMotor_Control_Par(0,0); 
}

void Track_wheel_right_90()
{
	DMotor_Control_Par(82,0);	
	delay_ms(500);
	DMotor_Control_Par(0,0); 
}

void Track_wheel_left_45_2()
{
	DMotor_Control_Par(-30,30);	
	delay_ms(250);
	DMotor_Control_Par(-19,29);	
	delay_ms(250);
	DMotor_Control_Par(0,0); 
}

void Track_wheel_right_45_2()
{
	DMotor_Control_Par(30,-30);	
	delay_ms(250);
	DMotor_Control_Par(19,-19);	
	delay_ms(250);
	DMotor_Control_Par(0,0); 
} 

void Track_wheel_round_left()
{
    DMotor_Control_Par(20,20); 
	delay_ms(180);
	if(j1 == 1 && j2 == 1 && j3 == 1 && j4 == 1 || j3 == 1 && j4 == 1 && j5 == 1 && j6 == 1)
	Track_wheel_left_45_2();

}

void Track_steep_line_jg(void)
{

	if(j1==1&&j2==0&&j3==0)				   //  1
		DMotor_Control_Par(15,40);
	else if(j1==1&&j2==1&&j3==0)			   //  1 2
		DMotor_Control_Par(20,40);
	else if(j1==0&&j2==1&&j3==0)			   //  2
		DMotor_Control_Par(25,40);
	else if(j1==0&&j2==1&&j3==1)			   //  2 3
		DMotor_Control_Par(30,40);	   
	else if(j2==0&&j3==1&&j4==0)			   //  3
		DMotor_Control_Par(33,40);
	else if(j2==0&&j3==1&&j4==1)			   //  3 4
		DMotor_Control_Par(35,40);
	else if(j3==0&&j4==1&&j5==0)			   //  4
		DMotor_Control_Par(37,40);
	else if(j3==0&&j4==1&&j5==1)			   //  4 5	 直线
		DMotor_Control_Par(40,40);
	else if(j4==0&&j5==1&&j6==0)			   //  5
		DMotor_Control_Par(40,37);
	else if(j4==0&&j5==1&&j6==1)			   //  5 6
		DMotor_Control_Par(40,35);
	else if(j5==0&&j6==1&&j7==0)			   //  6
		DMotor_Control_Par(40,33);
	else if(j5==0&&j6==1&&j7==1)			   //  6 7
		DMotor_Control_Par(40,30);
	else if(j6==0&&j7==1&&j8==0)			   //  7
		DMotor_Control_Par(40,25);
	else if(j6==0&&j7==1&&j8==1)			   //  7 8
		DMotor_Control_Par(40,20);
	else if(j6==0&&j7==0&&j8==1)			       //  8
		DMotor_Control_Par(40,15);
	else if(j1 == 1 && j2 == 1 && j3 == 1 && j4 == 1 && j5 == 1 && j6 == 1 && j7 == 1 && j8 == 1)
		DMotor_Control_Par(20,20);

}


void Track_steep_round_jg(void)
{

	if( j1 == 1 && j2 == 0 && j3 == 0 )	 //  1
		DMotor_Control_Par(0,40);
	else 
	    if(j1 == 1 && j2 == 1 && j3 == 0)			   //  1 2
		DMotor_Control_Par(8,40);
	else
	    if(j1==0&&j2==1&&j3==0)			   //  2
		DMotor_Control_Par(15,40);
	else 
	    if(j1==0&&j2==1&&j3==1)			   //  2 3
		DMotor_Control_Par(21,40);	   
	else 
	    if(j2==0&&j3==1&&j4==0)			   //  3
		DMotor_Control_Par(27,40);
	else 
	    if(j2==0&&j3==1&&j4==1)			   //  3 4
		DMotor_Control_Par(33,40);
	else 
	    if(j3==0&&j4==1&&j5==0)			   //  4
		DMotor_Control_Par(35,40);
	else 
	    if(j3==0&&j4==1&&j5==1)			   //  4 5	 直线
		DMotor_Control_Par(40,40);
	else 
	    if(j4==0&&j5==1&&j6==0)			   //  5
		DMotor_Control_Par(40,35);
	else 
	    if(j4==0&&j5==1&&j6==1)			   //  5 6
		DMotor_Control_Par(40,33);
	else 
	    if(j5==0&&j6==1&&j7==0)			   //  6
		DMotor_Control_Par(40,27);
	else 
	    if(j5==0&&j6==1&&j7==1)			   //  6 7
		DMotor_Control_Par(40,21);
	else 
	    if(j6==0&&j7==1&&j8==0)			   //  7
		DMotor_Control_Par(40,15);
	else 
	    if(j6==0&&j7==1&&j8==1)			   //  7 8
		DMotor_Control_Par(40,8);
	else 
	    if(j6==0&&j7==0&&j8==1)			       //  8
		DMotor_Control_Par(40,0);
	else 
	    if(j3==0&&j4==0&&j5==0&&j6==0)			       //  8
		DMotor_Control_Par(20,20);
	else 
	    if(j3==1&&j4==1&&j5==1&&j6==1)			       //  8
		DMotor_Control_Par(20,20);
	else 
	    if(j3 == 1 && j4 == 1 )			       //  8
		Track_wheel_round_left();

}


