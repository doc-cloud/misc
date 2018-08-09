#include "track_jg.h"

#define	j1 GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_8)	
#define	j2 GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_9)
#define	j3 GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_10)
#define	j4 GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_11)
#define	j5 GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_12)
#define	j6 GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_13)
#define	j7 GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_14)
#define	j8 GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_15)  

//filename:		pick.c
//language:		C.
//usage:		this file provide the main_test for the Robot Competition(Carry Project)
//declaration:	this version is a beta version named 1.0
//				there are lots of declarations of effective function in this file.
//				they are some port for programmer to a certain extent.
//				the specific sentences will be add to this project by the effort of every parts of proj-team.
//version		1.0 by chen on 13/8/2014.


#define GREEN 0
#define WHITE 1
#define RED 2
#define BLACK 3
#define BLUE 4

u8 res[5];



void circle0_to_aim_to_center()
{
		move_further();				//get to the external round to specific purpose,we want to place the object exactly here.
		place_obj();				//refer to the declaration of place_obj.
		backward_moderate();		//same to the remarks above.
		delay_level1();
		turn_degree(-180);
		delay_ms(500);
//		while(!is_center())
//			forward_moderate();
		aim_to_center();
}

void center_to_aim_to_center()
{
//		move_level0();
//		move_further();
		move_long();
		place_obj();
		backward_moderate();
		delay_level1();
		turn_degree(-180);
	  delay_ms(500);
		while(!is_center())
			forward_moderate();
}

void circle0_to_center()
{
		turn_degree(180);
	  while(!is_center())
			forward_moderate();
}

void special_center_to_circle0_to_center()
{
		move_level0();
		backward_moderate();
		delay_level1();
		turn_degree(180);
		while(!is_center())
			forward_moderate();
}

void center_to_circle0_to_center()
{
		move_level0();									   //(BLUE==ret1) 	the second object colour is blue.
		turn_degree(180);							//in the algorithm of this main_test body.
		while(!is_center())							//positions above have their own possiblility.
			forward_moderate();		
}


void main_test()
{
	step0();
	turn_degree(45);
	step1();	
}

//usage:	to realize the task one.
//version:	1.0 by chen on 8/13/2014.
void step0()
{
	unsigned char ret0,ret1,ret2;
	ret0=ret1=ret2=5;				//prevent the value mixture of the five colours.
	while(!is_center())
		forward_steep();			//go to the center of the round.
	//forward_slow();
	//delay_level0();
	turn_degree(-90);				//turn left,try to measure the colour of the object on the area A.
	move_level0();					//move to an internal round.for more information,please into the declaration of move_level0
	ret0=test_colour();
	if(GREEN==ret0)
	{
		circle0_to_aim_to_center();
		turn_degree(-90);
	}
	else
		if(WHITE==ret0)
		{
			circle0_to_center();
			turn_degree(-135);
			center_to_aim_to_center();
			turn_degree(-135);
		}
		else
			if(RED==ret0||BLUE==ret0)		//if the object on area A is RED or BLUE,push it to a temporary position.
			{								//the position can not be the purpose colour of objects on area C or E.
        circle0_to_center();
				turn_degree(90);
				special_center_to_circle0_to_center();
				turn_degree(90);
			}
			else
				if(BLACK==ret0)
				{
					circle0_to_center();
					turn_degree(-45);
					center_to_aim_to_center();
					turn_degree(135);
				}

	move_level0();							//we realize the first procedure of step0 above.
	ret1=test_colour();					//you can refer to the graph paper to get more information of the linker code of first procedure and second procedure.
	if(GREEN==ret1)							
	{
		circle0_to_center();
		turn_degree(90);
		center_to_aim_to_center();
	}
	else
		if(WHITE==ret1)
		{
		circle0_to_center();
			turn_degree(135);
    center_to_aim_to_center();
			turn_degree(-45);
		}
		else
			if(RED==ret1)
			{
				circle0_to_aim_to_center();
				turn_degree(-90);
			}
			else
				if(BLACK==ret1)
				{
		      circle0_to_center();
					turn_degree(-135);
					center_to_aim_to_center();
					turn_degree(-135);
				}
				else
					if(BLUE==ret1)
					{
            circle0_to_center();
						turn_degree(45);
					  special_center_to_circle0_to_center();
						turn_degree(135);
					}


	move_level0();							//third procedure of the step0.
	ret2=test_colour();
	if(GREEN==ret2)
	{
    circle0_to_center();
		center_to_aim_to_center();
		turn_degree(90);
	}
	else
		if(WHITE==ret2)
		{
      circle0_to_center();
			turn_degree(45);
		  center_to_aim_to_center();
			turn_degree(45);
		}
		else
			if(RED==ret2)
			{
        circle0_to_center();
				turn_degree(90);
		    center_to_aim_to_center();
			}
			else
				if(BLACK==ret2)
				{
          circle0_to_center();
					turn_degree(135);
		      center_to_aim_to_center();
					turn_degree(-45);
				}
				else
					if(BLUE==ret2)
					{
            circle0_to_aim_to_center();
						turn_degree(-90);
					}


	if(RED==ret0||BLUE==ret0||BLUE==ret1)				//these are three possible situations to lead to the complementary code.
	{													//list:
		if(RED==ret0)										   //(RED==ret0)	the first object colour is red.
		{
      center_to_circle0_to_center();			//(BLUE==ret0)	the first object colour is blue.					
      center_to_aim_to_center();
		}
		else
			if(BLUE==ret0)
			{
        center_to_circle0_to_center();
				turn_degree(90);
        center_to_aim_to_center();
				turn_degree(-90);
			}


		if(BLUE==ret1)
		{
			turn_degree(45);
      center_to_circle0_to_center();
			turn_degree(45);
      center_to_aim_to_center();
			turn_degree(-90);
		}
	}
	move_level0();
	move_level0();
	//move_further();			//go home.
	
}

void step1()
{
	left_area_filter();
	turn_degree(-90);
	right_area_filter();
}

unsigned char is_center()
{
//	u8 temp0=0,temp1=0;
//	if(!(((j1&&(j8||j7))||(j2&&(j8||j7)))&&!(j3||j4||j5||j6)))
//		return 0;
//	else 
//	{
//		temp0=1;
//	delay_ms(500);
//		if(((j1&&(j8||j7))||(j2&&(j8||j7)))&&!(j3||j4||j5||j6))
//		{
//			temp1=1;
//			return (temp0&&temp1);
//		}
//		else
//			return 0;
//	}
	
	/*
	u8 temp0=0,temp1=0;
	if(!(((j1&&(j8||j7))||(j2&&(j8||j7)))&&!(j3||j4||j5||j6)))
		return 0;
	else 
	{
		temp0=1;
	delay_ms(500);
		if(((j1&&(j8||j7))||(j2&&(j8||j7)))&&!(j3||j4||j5||j6))
		{
			temp1=1;
			return (temp0&&temp1);
		}
		else
			return 0;
	}
	*/
	//unsigned int i;
	unsigned char flag0;
	//i=1000;
	flag0=0;
	//flag1=0;
	//if(j1&&j8&&!(j2&&j7))
		//tmp=1;
	//if(j1&&j8&&j2&&j7&&!(j3&&j6))
		//flag0=1;
	//if(!(j1&&j8)&&j2&&j7&&!(j3&&j6))
		//flag0=1;
	if(1==j1&&0==j2&&0==j3&&0==j6&&1==j7&&1==j8)
		flag0=1;
	if(1==j1&&1==j2&&0==j3&&0==j6&&0==j7&&1==j8)
		flag0=1;
	if(1==j1&&1==j2&&0==j3&&0==j6&&1==j7&&1==j8)
		flag0=1;
	if(0==flag0)
		return 0;
	else
	{
		while(!(j1&&j2&&j3&&j4&&j5&&j6&&j7&&j8))
			  DMotor_Control_Par(30,30);
		while(j1&&j2&&j4&&j5&&j6&&j7&&j8)
				DMotor_Control_Par(30,30);
		if(1==j1&&0==j2&&0==j3&&j4==0&&j5==0&&0==j6&&0==j7&&1==j8)
			DMotor_Control_Par(-30,-30);
		else if(1==j1&&1==j2&&0==j3&&j4==0&&j5==0&&0==j6&&0==j7&&1==j8)
			DMotor_Control_Par(-30,-30);
		else if(1==j1&&1==j2&&0==j3&&0==j6&&1==j7&&1==j8)
			DMotor_Control_Par(-30,-30);
		else return 0;
		delay_ms(300);
		DMotor_Control_Par(0,0);
					
		//while(i--)
			//;
		/*
		if(0==j1&&1==j2&&1==j6&&0==j7&&0==j8)
			flag1=1;
		if(0==j1&&0==j2&&1==j3&&1==j7&&0==j8)
			flag1=1;
		if(0==j1&&0==j2&&0==j3&&1==j4&&0==j7&&0==j8)
			flag1=1;
		if(0==j1&&0==j2)
			flag1=1;
		if(0==j1&&0==j2&&0==j3)
			flag1=1;
		if(0==j3&&0==j7&&0==j8)
			flag1=1;
		if(0==j1&&0==j8&&(j3||j7))
			flag1=1;
		*/
		return 1;
	}
	//return flag0&&flag1;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////by hps

//	u8 i=0;
//	if(j1&&j2&&j3&&j4&&j5&&j6&&j7&&j8)
//	{
//		while(j1&&j2&&j3&&j4&&j5&&j6&&j7&&j8)
//		DMotor_Control_Par(30,30);
//		i++;
//	}
//	if(i==0)
//		forward_moderate();
//	else if(i==1)
//	{
//		DMotor_Control_Par(30,30);
//		delay_ms(500);
//		forward_moderate();
//	}
//	else if(i==2)
//	{
//		DMotor_Control_Par(-30,-30);
//		delay_ms(300);
//		DMotor_Control_Par(0,0);
//	}
}

void aim_to_center()
{
	static u8 i=0;
	if(j1&&j2&&j3&&j4&&j5&&j6&&j7&&j8)
	{
		while(j1&&j2&&j3&&j4&&j5&&j6&&j7&&j8)
		DMotor_Control_Par(30,30);
		i++;
	}
	if(i==0)
		forward_moderate();
	else if(i==1)
	{
		DMotor_Control_Par(30,30);
		delay_ms(500);
		forward_moderate();
	}
	else if(i==2)
	{
		DMotor_Control_Par(-30,-30);
		delay_ms(800);
		DMotor_Control_Par(0,0);
	}
}

void forward_steep()
{
	if(j1==1&&j2==0&&j3==0)	  				   //  1                                                 //慢速
		DMotor_Control_Par(38,70);
	else if(j1==1&&j2==1&&j3==0)			   //  1 2
		DMotor_Control_Par(37,65);
	else if(j1==0&&j2==1&&j3==0)			   //  2
		DMotor_Control_Par(36,64);
	else if(j1==0&&j2==1&&j3==1)			   //  2 3
		DMotor_Control_Par(35,63);	   
	else if(j2==0&&j3==1&&j4==0)			   //  3
		DMotor_Control_Par(34,62);
	else if(j2==0&&j3==1&&j4==1)			   //  3 4
		DMotor_Control_Par(32,61);
	else if(j3==0&&j4==1&&j5==0)			   //  4
		DMotor_Control_Par(30,60);
	else if(j3==0&&j4==1&&j5==1)			   //  4 5	 直线
		DMotor_Control_Par(58,60);
	else if(j4==0&&j5==1&&j6==0)			   //  5
		DMotor_Control_Par(60,30);
	else if(j4==0&&j5==1&&j6==1)			   //  5 6
		DMotor_Control_Par(61,32);
	else if(j5==0&&j6==1&&j7==0)			   //  6
		DMotor_Control_Par(62,34);
	else if(j5==0&&j6==1&&j7==1)			   //  6 7
		DMotor_Control_Par(63,35);
	else if(j6==0&&j7==1&&j8==0)			   //  7
		DMotor_Control_Par(64,36);
	else if(j6==0&&j7==1&&j8==1)			   //  7 8
		DMotor_Control_Par(65,37);
	else if(j6==0&&j7==0&&j8==1)			       //  8
		DMotor_Control_Par(70,38);
}

void forward_moderate()
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////by yanzong
//	if(j1==1&&j2==0&&j3==0)	  				   //  1                                       //快速
//		DMotor_Control_Par(43,60);
//	else if(j1==1&&j2==1&&j3==0)			   //  1 2
//		DMotor_Control_Par(42,60);
//	else if(j1==0&&j2==1&&j3==0)			   //  2
//		DMotor_Control_Par(42,59);
//	else if(j1==0&&j2==1&&j3==1)			   //  2 3
//		DMotor_Control_Par(41,58);	   
//	else if(j2==0&&j3==1&&j4==0)			   //  3
//		DMotor_Control_Par(41,57);
//	else if(j2==0&&j3==1&&j4==1)			   //  3 4
//		DMotor_Control_Par(40,56);
//	else if(j3==0&&j4==1&&j5==0)			   //  4
//		DMotor_Control_Par(40,55);
//	else if(j3==0&&j4==1&&j5==1)			   //  4 5	 直线
//		DMotor_Control_Par(58,60);
//	else if(j4==0&&j5==1&&j6==0)			   //  5
//		DMotor_Control_Par(55,40);
//	else if(j4==0&&j5==1&&j6==1)			   //  5 6
//		DMotor_Control_Par(56,40);
//	else if(j5==0&&j6==1&&j7==0)			   //  6
//		DMotor_Control_Par(57,41);
//	else if(j5==0&&j6==1&&j7==1)			   //  6 7
//		DMotor_Control_Par(58,41);
//	else if(j6==0&&j7==1&&j8==0)			   //  7
//		DMotor_Control_Par(59,42);
//	else if(j6==0&&j7==1&&j8==1)			   //  7 8
//		DMotor_Control_Par(60,42);
//	else if(j6==0&&j7==0&&j8==1)			       //  8
//		DMotor_Control_Par(60,43);



//	if(j1==1&&j2==0&&j3==0)	  				   //  1
//		DMotor_Control_Par(38,70);
//	else if(j1==1&&j2==1&&j3==0)			   //  1 2
//		DMotor_Control_Par(37,65);
//	else if(j1==0&&j2==1&&j3==0)			   //  2
//		DMotor_Control_Par(36,64);
//	else if(j1==0&&j2==1&&j3==1)			   //  2 3
//		DMotor_Control_Par(35,63);	   
//	else if(j2==0&&j3==1&&j4==0)			   //  3
//		DMotor_Control_Par(34,62);
//	else if(j2==0&&j3==1&&j4==1)			   //  3 4
//		DMotor_Control_Par(32,61);
//	else if(j3==0&&j4==1&&j5==0)			   //  4
//		DMotor_Control_Par(30,60);
//	else if(j3==0&&j4==1&&j5==1)			   //  4 5	 直线
//		DMotor_Control_Par(58,60);
//	else if(j4==0&&j5==1&&j6==0)			   //  5
//		DMotor_Control_Par(60,30);
//	else if(j4==0&&j5==1&&j6==1)			   //  5 6
//		DMotor_Control_Par(61,32);
//	else if(j5==0&&j6==1&&j7==0)			   //  6
//		DMotor_Control_Par(62,34);
//	else if(j5==0&&j6==1&&j7==1)			   //  6 7
//		DMotor_Control_Par(63,35);
//	else if(j6==0&&j7==1&&j8==0)			   //  7
//		DMotor_Control_Par(64,36);
//	else if(j6==0&&j7==1&&j8==1)			   //  7 8
//		DMotor_Control_Par(65,37);
//	else if(j6==0&&j7==0&&j8==1)			       //  8
//		DMotor_Control_Par(70,38);
	
	
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////by hps	
	
	
	
	
//		if(j1==1&&j2==0&&j3==0)	  				   //  1                                       //快速
//		DMotor_Control_Par(-12,60);
//	else if(j1==1&&j2==1&&j3==0)			   //  1 2
//		DMotor_Control_Par(0,60);
//	else if(j1==0&&j2==1&&j3==0)			   //  2
//		DMotor_Control_Par(10,60);
//	else if(j1==0&&j2==1&&j3==1)			   //  2 3
//		DMotor_Control_Par(24,60);	   
//	else if(j2==0&&j3==1&&j4==0)			   //  3
//		DMotor_Control_Par(36,60);
//	else if(j2==0&&j3==1&&j4==1)			   //  3 4
//		DMotor_Control_Par(46,60);
//	else if(j3==0&&j4==1&&j5==0)			   //  4
//		DMotor_Control_Par(54,60);
//	else if(j3==0&&j4==1&&j5==1)			   //  4 5	 直线
//		DMotor_Control_Par(60,60);
//	else if(j4==0&&j5==1&&j6==0)			   //  5
//		DMotor_Control_Par(60,54);
//	else if(j4==0&&j5==1&&j6==1)			   //  5 6
//		DMotor_Control_Par(60,46);
//	else if(j5==0&&j6==1&&j7==0)			   //  6
//		DMotor_Control_Par(60,36);
//	else if(j5==0&&j6==1&&j7==1)			   //  6 7
//		DMotor_Control_Par(60,24);
//	else if(j6==0&&j7==1&&j8==0)			   //  7
//		DMotor_Control_Par(60,10);
//	else if(j6==0&&j7==1&&j8==1)			   //  7 8
//		DMotor_Control_Par(60,0);
//	else if(j6==0&&j7==0&&j8==1)			       //  8
//		DMotor_Control_Par(60,-12);
	
	
//			if(j1==1&&j2==0&&j3==0)	  				   //  1                                       //快速
//		DMotor_Control_Par(-30,60);
//	else if(j1==1&&j2==1&&j3==0)			   //  1 2
//		DMotor_Control_Par(-16,60);
//	else if(j1==0&&j2==1&&j3==0)			   //  2
//		DMotor_Control_Par(0,60);
//	else if(j1==0&&j2==1&&j3==1)			   //  2 3
//		DMotor_Control_Par(16,60);	   
//	else if(j2==0&&j3==1&&j4==0)			   //  3
//		DMotor_Control_Par(30,60);
//	else if(j2==0&&j3==1&&j4==1)			   //  3 4
//		DMotor_Control_Par(42,60);
//	else if(j3==0&&j4==1&&j5==0)			   //  4
//		DMotor_Control_Par(52,60);
//	else if(j3==0&&j4==1&&j5==1)			   //  4 5	 直线
//		DMotor_Control_Par(60,60);
//	else if(j4==0&&j5==1&&j6==0)			   //  5
//		DMotor_Control_Par(60,52);
//	else if(j4==0&&j5==1&&j6==1)			   //  5 6
//		DMotor_Control_Par(60,42);
//	else if(j5==0&&j6==1&&j7==0)			   //  6
//		DMotor_Control_Par(60,30);
//	else if(j5==0&&j6==1&&j7==1)			   //  6 7
//		DMotor_Control_Par(60,16);
//	else if(j6==0&&j7==1&&j8==0)			   //  7
//		DMotor_Control_Par(60,0);
//	else if(j6==0&&j7==1&&j8==1)			   //  7 8
//		DMotor_Control_Par(60,-16);
//	else if(j6==0&&j7==0&&j8==1)			       //  8
//		DMotor_Control_Par(60,-30);


///////////////////////////////////////////////////////////////////////////////////////////////////////by chen


//	if(1==j4&&1==j5&&0==j3&&0==j6)
//		DMotor_Control_Par(63,63);					//the most possiblitiy,the ideal situation in other word.
//													//we named this situation S0.
//	
//	else if(1==j4&&0==j3&&0==j5)
//		DMotor_Control_Par(60,65);
//	else if(1==j5&&0==j4&&0==j6)
//		DMotor_Control_Par(65,60);					//the lower possibility compare to S0,process travel after the S0.
//													//we named this situation S1.
//	
//	else if(1==j3&&1==j4)
//		DMotor_Control_Par(55,68);
//	else if(1==j5&&1==j6)
//		DMotor_Control_Par(68,55);					//the lower possibility compare to S1,process travel after the S1.
//													//we named this situation S2.
//	
//	else if(1==j3&&0==j2&&0==j4)
//		DMotor_Control_Par(50,70);
//	else if(1==j6&&0==j5&&0==j7)
//		DMotor_Control_Par(70,50);					//the lower possibility compare to S2,process travel after the S2.
//													//we named this situation S3.
//	
//	else if(1==j2&&1==j3)
//		DMotor_Control_Par(44,73);
//	else if(1==j6&&1==j7)
//		DMotor_Control_Par(73,44);					//the lower possibility compare to S3,process travel after the S3.
//													//we named this situation S4.
//	
//	else if(1==j3&&1==j4&&1==j5)
//		DMotor_Control_Par(42,75);
//	else if(1==j4&&1==j5&&1==j6)
//		DMotor_Control_Par(75,42);					//the lower possibility compare to S4,process travel after the S4.
//													//we named this situation S5.
//	
//	else if(1==j2&&1==j3&&1==j4)								
//		DMotor_Control_Par(40,77);
//	else if(1==j5&&1==j6&&1==j7)
//		DMotor_Control_Par(77,40);					//the lower possibility compare to S5,process travel after the S5.
//													//we named this situation S6.
//	
//	else if(1==j1&&1==j2)								
//		DMotor_Control_Par(41,79);
//	else if(1==j7&&1==j8)
//		DMotor_Control_Par(79,41);					//the lower possibility compare to S6,process travel after the S6.
//													//we named this situation S7.


/////////////////////////////////////////////////////////////////////////////////////////////////////by yanzong and binglan

	if(j1==1&&j2==0&&j3==0)	  				   //  1                                       //快速
		DMotor_Control_Par(-20,50);
	else if(j1==1&&j2==1&&j3==0)			   //  1 2
		DMotor_Control_Par(-10,50);
	else if(j1==0&&j2==1&&j3==0)			   //  2
		DMotor_Control_Par(10,51);
	else if(j1==0&&j2==1&&j3==1)			   //  2 3
		DMotor_Control_Par(16,52);	   
	else if(j2==0&&j3==1&&j4==0)			   //  3
		DMotor_Control_Par(30,53);
	else if(j2==0&&j3==1&&j4==1)			   //  3 4
		DMotor_Control_Par(20,54);
	else if(j3==0&&j4==1&&j5==0)			   //  4
		DMotor_Control_Par(-10,45);
	else if(j3==0&&j4==1&&j5==1)			   //  4 5	 直线
		DMotor_Control_Par(60,60);
	else if(j4==0&&j5==1&&j6==0)			   //  5
		DMotor_Control_Par(45,-10);
	else if(j4==0&&j5==1&&j6==1)			   //  5 6
		DMotor_Control_Par(54,20);
	else if(j5==0&&j6==1&&j7==0)			   //  6
		DMotor_Control_Par(53,30);
	else if(j5==0&&j6==1&&j7==1)			   //  6 7
		DMotor_Control_Par(52,16);
	else if(j6==0&&j7==1&&j8==0)			   //  7
		DMotor_Control_Par(51,10);
	else if(j6==0&&j7==1&&j8==1)			   //  7 8
		DMotor_Control_Par(50,-10);
	else if(j6==0&&j7==0&&j8==1)			       //  8
		DMotor_Control_Par(50,-20);
	else if((j3 == 1 && j4 == 1 && j5 == 1 )|| (j3 == 1 && j4 == 1 && j6 == 1)){
		DMotor_Control_Par(40,40);
		delay_ms(200);
		}
	else if((j3 == 0 && j4 == 0 && j5 == 0 ) || (j3 == 0 && j4 == 0 && j6 == 0) ){
		DMotor_Control_Par(40,40);
		delay_ms(200);
		}
}

void forward_slow()
{

}

void delay_level0()
{

}
	
void turn_degree(signed int radian)
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////by chen (wrong)
//unsigned int i;
//	
//	//offer a pulse width for the negative radian.
//	if(-180==radian)							
//	{											//due to the lack of the robot.
////		DMotor_Control_Par(-46,46);
////		for(i=175;i>0;i--)						//we choose the method of delay here to rotate a specific degree.
////			delay_ms(10);						//the efforts of the real-time debugging is most inportant to a large extent.
////		DMotor_Control_Par(0,0);				//several delay plan should be made before the competition.
//		DMotor_Control_Par(-30,30);
//		for(i=245;i>0;i--)
//			delay_ms(10);
//			delay_ms(3);
//		DMotor_Control_Par(0,0);
//		
//		
//	}
//	else if(-135==radian)
//	{
//		DMotor_Control_Par(-46,46);
//		for(i=123;i>0;i--)
//			delay_ms(10);
//		DMotor_Control_Par(0,0);
//	}
//	else if(-90==radian)
//	{
//		DMotor_Control_Par(-46,46);
//		for(i=80;i>0;i--)
//			delay_ms(10);
//		DMotor_Control_Par(0,0);
//	}
//	else if(-45==radian)
//	{
//		DMotor_Control_Par(-46,46);
//		for(i=50;i>0;i--)
//			delay_ms(10);
//		DMotor_Control_Par(0,0);
//	}
//	
//	//offer a pulse width for the positive radian.
//	else if(45==radian)
//	{
//		DMotor_Control_Par(46,-46);
//		for(i=30;i>0;i--)
//			delay_ms(10);
//		DMotor_Control_Par(0,0);
//	}
//	else if(90==radian)
//	{
//		DMotor_Control_Par(46,-46);
//		for(i=80;i>0;i--)
//			delay_ms(10);
//		DMotor_Control_Par(0,0);
//	}
//	else if(135==radian)
//	{
//		DMotor_Control_Par(46,-46);
//		for(i=130;i>0;i--)
//			delay_ms(10);
//		DMotor_Control_Par(0,0);
//	}
//	else if(180==radian)
//	{
//		DMotor_Control_Par(46,-46);
//		for(i=180;i>0;i--)
//			delay_ms(10);
//		DMotor_Control_Par(0,0);
//	}


///////////////////////////////////////////////////////////////////////////////////////////////////////////by zichen fixed


	unsigned int i;
	
	//offer a pulse width for the negative radian.
	if(-180==radian)							
	{											//due to the lack of the robot.
		DMotor_Control_Par(-30,30);
		for(i=245;i>0;i--)						//we choose the method of delay here to rotate a specific degree.
			delay_ms(10);						//the efforts of the real-time debugging is most inportant to a large extent.
		delay_ms(3);
		DMotor_Control_Par(0,0);				//several delay plan should be made before the competition.
	}
	else if(-135==radian)
	{
		DMotor_Control_Par(-30,30);
		for(i=183;i>0;i--)
			delay_ms(10);
		DMotor_Control_Par(0,0);
	}
	else if(-90==radian)
	{
		DMotor_Control_Par(-30,30);
		for(i=124;i>0;i--)
			delay_ms(10);
		DMotor_Control_Par(0,0);
	}
	else if(-45==radian)
	{
		DMotor_Control_Par(-30,30);
		for(i=65;i>0;i--)
			delay_ms(10);
		delay_ms(5);
		DMotor_Control_Par(0,0);
	}
	
	//offer a pulse width for the positive radian.
	else if(45==radian)
	{
		DMotor_Control_Par(30,-30);
		for(i=64;i>0;i--)
			delay_ms(10);
		DMotor_Control_Par(0,0);
	}
	else if(90==radian)
	{
		DMotor_Control_Par(30,-30);
		for(i=122;i>0;i--)
			delay_ms(10);
		DMotor_Control_Par(0,0);
	}
	else if(135==radian)
	{
		DMotor_Control_Par(30,-30);
		for(i=183;i>0;i--)
			delay_ms(10);
		delay_ms(3);
		DMotor_Control_Par(0,0);
	}
	else if(180==radian)
	{
		DMotor_Control_Par(30,-30);
		for(i=245;i>0;i--)
			delay_ms(10);
		DMotor_Control_Par(0,0);
	}

}
	
void move_level0()
{
		while(!(j1&&j2&&j7&&j8))
		forward_moderate();
		DMotor_Control_Par(0,0);

}

//u8 is_circle0()
//{
//		if((j1&&j2&&!j3&&!j4&&!j5&&j6&&j7&&j8)||(j1&&j2&&j3&&!j4&&!j5&&!j6&&j7&&j8))
//			return 1;
//		else 
//			return 0;
//}

u8 test_colour()
{

	return 0;
}

void move_further()
{
		while(!(j1&&j8))
		forward_moderate();
	  DMotor_Control_Par(0,0);
}

void move_long()
{
//		while(!(j1&&j2&&j7&&j8))
			while(!(j1&&j8))
				forward_moderate();
		  while(j1&&j8)
				forward_moderate();
			while(!(j1&&j8))
				forward_moderate();
}

//u8 is_aim()
//{
//		if((j1&&!j2&&!j3&&!j4&&!j5&&j6&&j7&&j8)||(j1&&j2&&j3&&!j4&&!j5&&!j6&&j7&&j8))
//			return 1;
//		else 
//			return 0;
//}


		
void place_obj()
{

}


void edge_round()
{

}

void backward_moderate()
{
		DMotor_Control_Par(-30,-30);
		delay_ms(1000);
		DMotor_Control_Par(0,0);
}

void delay_level1()
{

}

void track_thick_round()
{

}

void catch_obj()
{

}

void track_routine1(signed int radian0,signed int radian1)
{
	turn_degree(180);
	while(!is_center())
		forward_moderate();
	turn_degree(radian0);
	move_level0();
	move_further();
	backward_moderate();
	delay_level1();
	turn_degree(180);
	while(!is_center())
		forward_moderate();
	turn_degree(radian1);
}


void track_routine2(signed int radian0,signed int radian1)
{
	turn_degree(-180);
	while(!is_center())
		forward_moderate();
	turn_degree(radian0);
	move_level0();
	move_further();
	place_obj();
	backward_moderate();
	delay_level1();
	turn_degree(180);
	while(!is_center())
		forward_moderate();
	turn_degree(radian1);
}



void left_area_filter()
{
	u8 i;
	for(i=0;i<5;i++)
	{
	move_level0();
	move_further();
	catch_obj();
	res[i]=test_colour();
	if(GREEN==res[i])
		track_routine1(-135,135);
	else
		if(WHITE==res[i])
			track_routine1(-90,90);
		else
			if(RED==res[i])
				track_routine1(-45,45);
			else
				if(BLACK==res[i])
					track_routine1(0,0);
				else
					if(BLUE==res[i])
						track_routine1(45,-45);
	}
}



void right_area_filter()
{
	u8 i;
	for(i=0;i<5;i++)
	{
	move_level0();
	move_further();
	catch_obj();
	res[i]=test_colour();
	if(GREEN==res[i])
		track_routine2(-45,45);
	else
		if(WHITE==res[i])
			track_routine2(0,0);
		else
			if(RED==res[i])
				track_routine2(45,-45);
			else
				if(BLACK==res[i])
					track_routine2(90,-90);
				else
					if(BLUE==res[i])
						track_routine2(135,-135);		
	
	}
}						





void Track_wheel_left_90()
{
	DMotor_Control_Par(-40,40);	
	delay_ms(500);
	DMotor_Control_Par(0,0); 
	delay_ms(2000);
}

void Track_wheel_right_90()
{
	DMotor_Control_Par(82,0);	
	delay_ms(500);
	DMotor_Control_Par(0,0); 

}

void Track_wheel_left_45_2()
{
//	DMotor_Control_Par(-30,30);	
//	delay_ms(250);
//	DMotor_Control_Par(-19,29);	
//	delay_ms(250);
//	DMotor_Control_Par(0,0); 
	
	
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
		DMotor_Control_Par(40,15);
	else if(j1==1&&j2==1&&j3==0)			   //  1 2
		DMotor_Control_Par(40,20);
	else if(j1==0&&j2==1&&j3==0)			   //  2
		DMotor_Control_Par(40,25);
	else if(j1==0&&j2==1&&j3==1)			   //  2 3
		DMotor_Control_Par(40,30);	   
	else if(j2==0&&j3==1&&j4==0)			   //  3
		DMotor_Control_Par(40,33);
	else if(j2==0&&j3==1&&j4==1)			   //  3 4
		DMotor_Control_Par(40,35);
	else if(j3==0&&j4==1&&j5==0)			   //  4
		DMotor_Control_Par(40,37);
	else if(j3==0&&j4==1&&j5==1)			   //  4 5	 直线
		DMotor_Control_Par(40,40);
	else if(j4==0&&j5==1&&j6==0)			   //  5
		DMotor_Control_Par(37,40);
	else if(j4==0&&j5==1&&j6==1)			   //  5 6
		DMotor_Control_Par(35,40);
	else if(j5==0&&j6==1&&j7==0)			   //  6
		DMotor_Control_Par(33,40);
	else if(j5==0&&j6==1&&j7==1)			   //  6 7
		DMotor_Control_Par(30,40);
	else if(j6==0&&j7==1&&j8==0)			   //  7
		DMotor_Control_Par(25,40);
	else if(j6==0&&j7==1&&j8==1)			   //  7 8
		DMotor_Control_Par(20,40);
	else if(j6==0&&j7==0&&j8==1)			       //  8
		DMotor_Control_Par(15,40);
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


