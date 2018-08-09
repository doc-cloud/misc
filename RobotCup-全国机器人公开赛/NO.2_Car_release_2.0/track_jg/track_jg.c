
#include "track_jg.h"
#include "getsensor.h"

#define GREEN 0	  //定义颜色标识
#define WHITE 1
#define RED 2
#define BLACK 3
#define BLUE 4

unsigned char ret0 = 5 ,ret1 = 5, ret2 = 5;

unsigned char res0,res1;
						  
static int flag_1;
static int flag_3;

void main_test()
{
	step0();
	step1();
}

void procedure0_former()
{
	place_obj();
	PASS_SOUTHERN_CROSSROAD								//pass the small round around home.
	PASS_SOUTHERN_CROSSROAD								
	turn_degree(-90);									//external to internal.			
	PASS_SOUTHERN_CROSSROAD							         
	PASS_NORTHERN_CROSSROAD							//get to the position of object A.
	catch_obj(); 
	test_colour();
	if(GREEN == ret0|| WHITE == ret0 || BLACK == ret0 )			//object A will be placed in its own position in these three situation.
	{
		if(GREEN == ret0)
		{
			turn_catch_degree(-90);
			internal_push_back(ret0);
			turn_degree(-90);
			PASS_LEFT_NORTHERN_CROSSROAD
			PASS_LEFT_NORTHERN_CROSSROAD
		}
		else
			if(WHITE == ret0)
			{
				PASS_LEFT_NORTHERN_CROSSROAD_CATCH
				turn_catch_degree(-90);
				internal_push_back(ret0);
				turn_degree(-90);
				PASS_LEFT_NORTHERN_CROSSROAD
			}
			else
			{
				turn_catch_degree(180);
				PASS_SOUTHERN_CROSSROAD_CATCH
				turn_catch_degree(-90);
				pass_center();
				internal_push_back(ret0);
				turn_degree(90);
				PASS_NORTHERN_CROSSROAD
			}
	}
	else							//object A will be placed in the opposite internal round point of area D.
	{
		turn_catch_degree(180);
		PASS_SOUTHERN_CROSSROAD_CATCH
		backward_moderate();
		delay_level0();
		turn_degree(-180);
		PASS_NORTHERN_CROSSROAD
		PASS_LEFT_NORTHERN_CROSSROAD
		PASS_LEFT_NORTHERN_CROSSROAD
	}
}

//usage:	finish the second procedure of the first task.
//purpose:	place the object C on its appropriate position and make the robot face to the object E
//			face south to the object E.
//			appropriate position:	center of the platform for the unfortunate situation.
//									object's own position for the fortunate situation.
//			unfortunate situation:	the object C is blue.
//			fortunate situation:	the object C is not blue.
//			provide a interface for the procedure2_former.
//version:	1.0 by chen on 8/17/2014.
void procedure1_former()
{
	unsigned char i;
	catch_obj();
	test_colour();
	if(GREEN == ret1)
	{
		if(BLACK!=ret0)							//the direction of robot(western or eastern) will decided by the colour of object A.
			turn_catch_degree(180);					//if the object A is black,robot will face to west.
		else									//else					  ,robot will face to east. 
			;									//adjust the direction of robot by sentences like this type.
		PASS_NORTHERN_CROSSROAD_CATCH
		PASS_RIGHT_NORTHERN_CROSSROAD_CATCH
		turn_catch_degree(90);
		internal_push_back(ret1);
	}
	else
		if(WHITE==ret1)
		{
			if(BLACK!=ret0)
				turn_catch_degree(180);
			else
				;
			PASS_NORTHERN_CROSSROAD_CATCH
			turn_catch_degree(90);
			internal_push_back(ret1);
		}
		else
			if(RED==ret1)
			{
				if(BLACK!=ret0)
					turn_catch_degree(-90);
				else
					turn_catch_degree(90);
				internal_push_back(ret1);
			}
			else
				if(BLACK == ret1)								//if the colour of object C is black,
				{												//the colour of object A will not be black.
					PASS_LEFT_NORTHERN_CROSSROAD_CATCH			//so go straight to the area D.
					turn_catch_degree(-90);
					internal_push_back(ret1);
				}
				else
				{
					if(BLACK!=ret0)
						turn_catch_degree(90);
					else
						turn_catch_degree(-90);
					while(!is_pre_center())			//place object E on the center of the platform.
						forward_steep();
					backward_moderate();
					delay_level0();
					turn_degree(180);
					PASS_NORTHERN_CROSSROAD
				}
	
	if(BLUE != ret1)									//adjust the robot's direction and position.
	{												//provide a interface for the procedure2_former.
		turn_degree(-90);
		for(i= 4 - ret1 ; i > 0 ; i --)
			PASS_LEFT_NORTHERN_CROSSROAD
	}
	else
	{
		turn_degree(90);
		PASS_LEFT_NORTHERN_CROSSROAD
		PASS_LEFT_NORTHERN_CROSSROAD
	}
}

//usage:	finish the third procedure of the first task.
//purpose:	place the object E on its own position and make the robot face to the center of platform.
//			due to the efforts of function procedure0_former and procedure1_former,
//			object E will not be blocked by any object.
//version:	1.0 by chen on 8/16/2014.
void procedure2_former()
{
	unsigned char i;
	catch_obj();
	test_colour();
	//adjust the direction firstly.
	if(BLUE!=ret2)						//processing batch if the object E is not blue.
	{
		turn_catch_degree(180);
		if(GREEN!=ret2)
		{
			for(i=4-ret2;i>0;i--)
				PASS_NORTHERN_CROSSROAD_CATCH
		}
		else
		{
			for(i=3;i>0;i--)
				PASS_NORTHERN_CROSSROAD_CATCH
			PASS_RIGHT_NORTHERN_CROSSROAD_CATCH
		}
		turn_catch_degree(90);
	}
	else								//process alone if the object E is blue.
		turn_catch_degree(-90);
	internal_push_back(ret2);
}

//usage:	finish the fourth procedure of the first task if it is necessary.
//purpose:	place the object on the temporary position to its own position if the unfortunate situation occurred.
unsigned char a[6],b[6];
//			skip this function if the fortunate situation occurred.
//			unfortunate situation:	object A is red or blue | object C is blue.
//			fortunate situation:	the contradiction of the unfortunate situation.
//version:	1.0 by chen on 8/17/2014.
void procedure3_latter()
{
	unsigned char i;
	if(RED==ret0||BLUE==ret0||BLUE==ret1)						//unfortunate situation.
	{
		if(BLUE==ret1)											//place the blue object C to its own position.
		{														//the object C is blue,the object A is not blue,
			while(!is_pre_center())								//process object C firstly.
				forward_steep();
			turn_catch_degree(180);
			PASS_NORTHERN_CROSSROAD_CATCH
			turn_catch_degree(90);
			for(i=4-ret2;i>0;i--)
				PASS_LEFT_NORTHERN_CROSSROAD_CATCH
			turn_catch_degree(-90);
			internal_push_back(BLUE);
			if(RED==ret0)									//the object A may be red,
			{												//place the red object A to its own position.
				turn_degree(-90);
				for(i=3;i>0;i--)
					PASS_SOUTHERN_CROSSROAD
				catch_obj();
				PASS_NORTHERN_CROSSROAD_CATCH
				for(i=2;i>0;i--)
					PASS_LEFT_NORTHERN_CROSSROAD_CATCH
				turn_catch_degree(-90);
				internal_push_back(RED);
			}
		}
		else
		{
			//adjust the robot position.
			if(BLUE!=ret2)											//get to the position of the temporary position.
			{														//opposite to the area D.
				turn_degree(90);
				if(BLACK==ret2)
				{
					PASS_NORTHERN_CROSSROAD
					PASS_NORTHERN_CROSSROAD
					PASS_RIGHT_NORTHERN_CROSSROAD
					PASS_SOUTHERN_CROSSROAD
				}
				else
					if(RED==ret2)
					{
						PASS_NORTHERN_CROSSROAD
						PASS_RIGHT_NORTHERN_CROSSROAD
						PASS_SOUTHERN_CROSSROAD
					}
					else
						if(WHITE==ret2)
						{
							PASS_RIGHT_NORTHERN_CROSSROAD
							PASS_SOUTHERN_CROSSROAD
						}
						else
							PASS_SOUTHERN_CROSSROAD
			}
			else
			{
				turn_degree(-90);
				for(i=3;i>0;i--)
					PASS_SOUTHERN_CROSSROAD
			}
			//place the correspond object to its own position.
			catch_obj();
			if(RED==ret0)										//if the object A is red,place it on its own position.
			{
				if(BLUE!=ret2)
					turn_catch_degree(180);
				PASS_NORTHERN_CROSSROAD_CATCH
				for(i=2;i>0;i--)
					PASS_LEFT_NORTHERN_CROSSROAD_CATCH
				turn_catch_degree(-90);
				internal_push_back(RED);
			}
			else												//the object A is blue,place it on its own position.
			{													//notice that if the object A is blue,
																//									the object E will not be blue.
				for(i=2;i>0;i--)
					PASS_SOUTHERN_CROSSROAD_CATCH
				PASS_NORTHERN_CROSSROAD_CATCH
				turn_catch_degree(90);
				internal_push_back(BLUE);
			}
		}
	}
}

//usage:	finish the first task of this competition.
void step0()
{
	procedure0_former();	
	procedure1_former();
	procedure2_former();
	procedure3_latter();
}

//usage:	can be effective after step0.
//purpose:	adjust the robot's direction,make it face to the left storage.
//version:	1.0 by chen on 8/17/2014.
void face_to_left_storage()
{
	unsigned char i;
	if(RED==ret0||BLUE==ret0||BLUE==ret1)			//if the unfortunate situation occurred,get to this code assemble.
	{												
		if(BLUE==ret1)								//if the object C is blue
		{
			if(RED!=ret0)							//and the object A is not red.
			{										//it mean that the robot is face to west.
				turn_degree(-90);
				for(i=3;i>0;i--)
					PASS_SOUTHERN_CROSSROAD
				turn_degree(-90);
			}
			else									//or the object A is red,
			{										//it mean that the robot is face to south.
				turn_degree(90);					
				PASS_NORTHERN_CROSSROAD
				PASS_RIGHT_NORTHERN_CROSSROAD
				PASS_SOUTHERN_CROSSROAD
				turn_degree(90);
			}
		}
		else
		{
			if(RED==ret0)							//if the object A is red,
			{										//it mean that the robot is face to south.
				turn_degree(90);
				PASS_NORTHERN_CROSSROAD
				PASS_RIGHT_NORTHERN_CROSSROAD
				PASS_SOUTHERN_CROSSROAD
				turn_degree(90);
			}
			else									//if the object A is not red,
			{										//it mean that the robot is face to west.
				turn_degree(-90);
				for(i=3;i>0;i--)
					PASS_SOUTHERN_CROSSROAD
				turn_degree(-90);
			}
		}
	}
	else											//if the fortunate situation is occurred,get to this code assemble.
	{
		if(BLUE!=ret2)											
		{													
			turn_degree(90);
			if(BLACK==ret2)
			{
				PASS_NORTHERN_CROSSROAD
				PASS_NORTHERN_CROSSROAD
				PASS_RIGHT_NORTHERN_CROSSROAD
				PASS_SOUTHERN_CROSSROAD
			}
			else
				if(RED==ret2)
				{
					PASS_NORTHERN_CROSSROAD
					PASS_RIGHT_NORTHERN_CROSSROAD
					PASS_SOUTHERN_CROSSROAD
				}
				else
					if(WHITE==ret2)
					{
						PASS_RIGHT_NORTHERN_CROSSROAD
						PASS_SOUTHERN_CROSSROAD
					}
					else
						PASS_SOUTHERN_CROSSROAD
			turn_degree(90);
		}
		else
		{
			turn_degree(-90);
			for(i=3;i>0;i--)
				PASS_SOUTHERN_CROSSROAD
			turn_degree(-90);
		}
	}
}

//usage:	finish the second mask of this competition and go home.
void step1()
{
	face_to_left_storage();
	left_storage_filter();
	right_storage_filter();
	PASS_SOUTHERN_CROSSROAD
	PASS_SOUTHERN_CROSSROAD
}

//usage:	filter the left storage of the second task company with function track_routine0.
void left_storage_filter()
{
	unsigned char i;
	for(i=5;i>0;i--)					//five times filter of objects.
		track_routine0(i);
}

//usage:	filter the right storage of the second task company with function track_routine1
void right_storage_filter()
{
	unsigned char i;
	for(i=5;i>0;i--)					//five times filter of objects.
		track_routine1(i);
}

//usage:	called by left_storage filter to filter the objects on the left storage regularly.
//purpose:	get a object and place it on its own position,
//			and get to the original position and direction in the first four times filter.
//			make the robot face to the right storage,provide a interface for track_routine1.
//version:	1.0 by chen on 8/17/2014.
void track_routine0(unsigned char i)
{
	//add process sentences here...
	//to a specific distance from the left storage.
	unsigned char ii;
	unsigned int iii;
	iii=40000;
	while(iii--)
		forward_steep();
	while(!is_storage())
		forward_slow();				//sentences aim to get a random object in storage.
	drag_obj(i);
	test_colour();																																																								res0=a[i];
	PASS_SOUTHERN_CROSSROAD
	if(BLUE!=res0)						//if the object's colour is not blue,
	{
		turn_catch_degree(-90);				//robot will adopt clockwise route.
		PASS_NORTHERN_CROSSROAD
		for(ii=res0;ii>0;ii--)
			PASS_LEFT_NORTHERN_CROSSROAD
		turn_catch_degree(-90);		
	}
	else								//if the object's colour is blue,
	{
		turn_catch_degree(90);				//robot will adopt anticlockwise route.
		for(ii=2;ii>0;ii--)
			PASS_SOUTHERN_CROSSROAD
		PASS_NORTHERN_CROSSROAD
		turn_catch_degree(90);
	}
	internal_push_back(res0);				//place the object and face to the center of this platform.
	if(BLUE!=res0)						//if robot is not in the internal round point correspond to blue.
	{
		if(1!=i)						//in the first four times of five,
		{
			turn_degree(90);
			if(BLACK==res0)
			{
				PASS_NORTHERN_CROSSROAD
				PASS_NORTHERN_CROSSROAD
				PASS_RIGHT_NORTHERN_CROSSROAD
				PASS_SOUTHERN_CROSSROAD
			}
			else
				if(RED==res0)
				{
					PASS_NORTHERN_CROSSROAD
					PASS_RIGHT_NORTHERN_CROSSROAD
					PASS_SOUTHERN_CROSSROAD
				}
				else
					if(WHITE==res0)
					{
						PASS_RIGHT_NORTHERN_CROSSROAD
						PASS_SOUTHERN_CROSSROAD
					}
					else
						PASS_SOUTHERN_CROSSROAD
			turn_degree(90);
		}
		else							//in the last time of five,
		{
			if(GREEN==res0)				//if the object's colour is green,
			{
				turn_degree(90);		//robot will adopt anticlockwise route to get to face to the right storage.
				for(ii=3;ii>0;ii--)
					PASS_SOUTHERN_CROSSROAD
				turn_degree(90);
			}
			else						//if the object's colour is not green,
			{		
				turn_degree(-90);		//robot will adopt clockwise route to get to face to the right storage.
				for(ii=4-res0;ii>0;ii--)
					PASS_LEFT_NORTHERN_CROSSROAD
				PASS_SOUTHERN_CROSSROAD
				turn_degree(-90);
			}
		}
	}
	else							//if robot is in the internal round point correspond to blue.
	{
		if(1!=i)					//in the first four times of five,
		{
			turn_degree(-90);		//robot will get back to face to the left storage.
			for(ii=3;ii>0;ii--)
				PASS_SOUTHERN_CROSSROAD
			turn_degree(-90);
		}
		else						//in the last time of five,
		{
			turn_degree(-90);		//robot will get to face to the right storage.
			PASS_SOUTHERN_CROSSROAD
			turn_degree(-90);	
		}
	}
}

//usage:	called by right_storage filter to filter the objects on the right storage regularly.
//purpose:	get a object and place it on its own position,
//			and get to the original position and direction in the first four times filter.
//			make the robot face to home,provide a interface for go_home.
//version:	1.0 by chen on 8/17/2014.
void track_routine1(unsigned char i)
{
	unsigned char ii;
	unsigned int iii;
	iii=40000;
	while(iii--)
		forward_steep();
	while(is_storage())
		forward_slow();
	drag_obj(i);
	test_colour();																																										res1=b[i];
	PASS_SOUTHERN_CROSSROAD
	if(GREEN!=res1)
	{
		turn_catch_degree(90);
		for(ii=5-res1;ii>0;ii--)
			PASS_NORTHERN_CROSSROAD
		turn_catch_degree(90);		
	}
	else
	{
		turn_catch_degree(-90);
		for(ii=2;ii>0;ii--)
			PASS_SOUTHERN_CROSSROAD
		PASS_NORTHERN_CROSSROAD
		turn_catch_degree(-90);
	}
	internal_push_back(res1);
	if(GREEN!=res1)
	{
		if(1!=i)
		{
			turn_degree(-90);
			for(ii=4-res1;ii>0;ii--)
				PASS_LEFT_NORTHERN_CROSSROAD
			PASS_SOUTHERN_CROSSROAD
			turn_degree(-90);
		}
		else											//little distinguish between track_routine1
		{
			if(2<res1)
			{
				turn_degree(-90);
				if(BLACK==res1)
				{
					PASS_LEFT_NORTHERN_CROSSROAD
					PASS_SOUTHERN_CROSSROAD
					PASS_SOUTHERN_CROSSROAD
				}
				else
				{
					PASS_SOUTHERN_CROSSROAD
					PASS_SOUTHERN_CROSSROAD
				}
				turn_degree(-90);
			}
			else
			{
				turn_degree(90);
				if(RED==res1)
				{
					PASS_NORTHERN_CROSSROAD
					PASS_RIGHT_NORTHERN_CROSSROAD
					PASS_SOUTHERN_CROSSROAD
					PASS_SOUTHERN_CROSSROAD
				}
				else
					if(WHITE==res1)
					{
						PASS_RIGHT_NORTHERN_CROSSROAD
						PASS_SOUTHERN_CROSSROAD
						PASS_SOUTHERN_CROSSROAD
					}
				turn_degree(90);
			}
		}
	}
	else
	{
		if(1!=i)
		{
			turn_degree(90);
			for(i=3;i>0;i--)
				PASS_SOUTHERN_CROSSROAD
			turn_degree(90);
		}
		else
		{
			if(2<res1)
			{
				turn_degree(-90);
				if(BLACK==res1)
				{
					PASS_LEFT_NORTHERN_CROSSROAD
					PASS_SOUTHERN_CROSSROAD
					PASS_SOUTHERN_CROSSROAD
				}
				else
				{
					PASS_SOUTHERN_CROSSROAD
					PASS_SOUTHERN_CROSSROAD
				}
				turn_degree(-90);
			}
			else
			{
				turn_degree(90);
				if(RED==res1)
				{
					PASS_NORTHERN_CROSSROAD
					PASS_RIGHT_NORTHERN_CROSSROAD
					PASS_SOUTHERN_CROSSROAD
					PASS_SOUTHERN_CROSSROAD
				}
				else
					if(WHITE==res1)
					{
						PASS_RIGHT_NORTHERN_CROSSROAD
						PASS_SOUTHERN_CROSSROAD
						PASS_SOUTHERN_CROSSROAD
					}
				turn_degree(90);
			}
		}
	}
}

//usage:	call this function if you want the robot track the line on the way to the target position.
//purpose:	adjust the pulse width of the left motor and right motor to micro process the robot.
//version:	1.0 by zong on 8/19/2014.
void forward_steep()
{
	if(j1==1&&j2==0&&j3==0 && !j7 && !j8)	  				   //  1             
		DMotor_Control_Par(-36,66);
	else if(j1==1&&j2==1&&j3==0 && !j7 && !j8)			   //  1 2
		DMotor_Control_Par(-35,65);
	else if(j1==0&&j2==1&&j3==0 && !j7 && !j8)			   //  2
		DMotor_Control_Par(-34,64);
	else if(j1==0&&j2==1&&j3==1 && !j7 && !j8)			   //  2 3
		DMotor_Control_Par(-33,63);	   
	else if(!j1 && j2==0&&j3==1&&j4==0 && !j7 && !j8)			   //  3
		DMotor_Control_Par(-32,62);
	else if(!j1 && j2==0&&j3==1&&j4==1 && !j7 && !j8)			   //  3 4
		DMotor_Control_Par(-31,61);
	else if(!j1 && !j2 && j3==0 && j4==1 && j5==0 && !j6 && !j7)			   //  4
		DMotor_Control_Par(-30,60);
	else if( !j1 && !j2 && j3==0 && j4==1 && j5==1 && j6 == 0 )			   //  4 5	 
		DMotor_Control_Par(60,60);
	else if(!j1 && !j2 && j4==0 && j5==1 && j6==0 && !j7 && !j8)			   //  5
		DMotor_Control_Par(60,-30);
	else if(!j1 && !j2 && j4==0 && j5==1 && j6 == 1 && !j7 && !j8)			   //  5 6
		DMotor_Control_Par(61,-31);
	else if( !j1 && !j2 && j5==0 && j6==1 && j7==0 && !j8)			   //  6
		DMotor_Control_Par(62,-32);
	else if( !j1 && !j2 && j5==0 && j6==1 && j7==1 && !j8)			   //  6 7
		DMotor_Control_Par(63,-33);
	else if( !j1 && !j2 && j6==0 && j7==1 && j8==0 )			   //  7
		DMotor_Control_Par(64,-34);
	else if( !j1 && !j2 && j6==0&&j7==1&&j8==1)			   //  7 8
		DMotor_Control_Par(65,-35);
	else if( !j1 && !j2 && j6==0&&j7==0&&j8==1)			       //  8
		DMotor_Control_Par(66,-36);

	else if( ( j1 || j2 || j3 ) && !j7 && !j8)
		DMotor_Control_Par(40,40);
	else if( !j1 && !j2 && (j6 || j7 || j8))
		DMotor_Control_Par(40,40);

	else if( (j1 + j3 + j5 + j7 >= 2) && (j2 + j4 + j6 + j8 >=2) )
	    DMotor_Control_Par(40,40);
	else if( (j1 + j2 + j7 + j8 >= 2) && (j2 + j3 + j5 + j6 >=2) )
	    DMotor_Control_Par(40,40);
	else if( (j1 + j2 + j5 + j6 >= 2) && (j2 + j3 + j7 + j8 >=2) )
	    DMotor_Control_Par(40,40);
	else if( (j1 + j2 + j3 + j4 >= 2) && (j5 + j6 + j7 + j8 >=2) )
	    DMotor_Control_Par(40,40);
	else if( (j1 + j3 + j5 + j6 >= 2) && (j2 + j4 + j7 + j8 >=2) )
	    DMotor_Control_Par(40,40);
	else if( (j1 + j4 + j5 + j6 >= 2) && (j3 + j4 + j5 + j8 >=2) )
	    DMotor_Control_Par(40,40);
	else if( !j1 && !j2 && !j3 && !j4 && !j5 && !j6 && !j7 && !j8)
		DMotor_Control_Par(40,40);
}

void forward_slow()
{
	if(j1==1&&j2==0&&j3==0 && !j7 && !j8)	  				   //  1             
		DMotor_Control_Par(-36,37);
	else if(j1==1&&j2==1&&j3==0 && !j7 && !j8)			   //  1 2
		DMotor_Control_Par(-35,36);
	else if(j1==0&&j2==1&&j3==0 && !j7 && !j8)			   //  2
		DMotor_Control_Par(-34,35);
	else if(j1==0&&j2==1&&j3==1 && !j7 && !j8)			   //  2 3
		DMotor_Control_Par(-33,34);	   
	else if(!j1 && j2==0&&j3==1&&j4==0 && !j7 && !j8)			   //  3
		DMotor_Control_Par(-32,33);
	else if(!j1 && j2==0&&j3==1&&j4==1 && !j7 && !j8)			   //  3 4
		DMotor_Control_Par(-31,32);
	else if(!j1 && !j2 && j3==0 && j4==1 && j5==0 && !j6 && !j7)			   //  4
		DMotor_Control_Par(-30,31);
	else if( !j1 && !j2 && j3==0 && j4==1 && j5==1 && j6 == 0 )			   //  4 5	 
		DMotor_Control_Par(30,30);
	else if(!j1 && !j2 && j4==0 && j5==1 && j6==0 && !j7 && !j8)			   //  5
		DMotor_Control_Par(31,-30);
	else if(!j1 && !j2 && j4==0 && j5==1 && j6 == 1 && !j7 && !j8)			   //  5 6
		DMotor_Control_Par(32,-31);
	else if( !j1 && !j2 && j5==0 && j6==1 && j7==0 && !j8)			   //  6
		DMotor_Control_Par(33,-32);
	else if( !j1 && !j2 && j5==0 && j6==1 && j7==1 && !j8)			   //  6 7
		DMotor_Control_Par(34,-33);
	else if( !j1 && !j2 && j6==0 && j7==1 && j8==0 )			   //  7
		DMotor_Control_Par(35,-34);
	else if( !j1 && !j2 && j6==0&&j7==1&&j8==1)			   //  7 8
		DMotor_Control_Par(36,-35);
	else if( !j1 && !j2 && j6==0&&j7==0&&j8==1)			       //  8
		DMotor_Control_Par(37,-36);

}

void turn_degree(signed int radian)
{
	unsigned int i,ii;
	i=0;
	ii=1024;					//time-delay for the track-adjustment.		
	if(-180==radian||180==radian)
	{
		if((j1&&j7)||(j2&&j8)||(j1&&j8))
		{
			while((j1&&j7)||(j2&&j8)||(j1&&j8))
				DMotor_Control_Par(-80,-80);
			delay_ms(64);
			if(!(j1||j2||j3))								//a little offset generated by the propagation of the backward error.
			{
				DMotor_Control_Par(-55,-65);				//offer asymmetric pulse width for the adjustment of the robot.
				delay_ms(81);								//time-delay for this adjustment.
			}
			else
				if(!(j8||j7||j6))							//symmetric situation of this sentences above.
				{
					DMotor_Control_Par(-65,-55);
					delay_ms(81);
				}
			if(!(j1||j2))									//a large offset occur.
			{
				DMotor_Control_Par(-60,-70);
				delay_ms(81);
			}
			else
				if(!(j8||j7))
				{
					DMotor_Control_Par(-70,-60);
					delay_ms(81);
				}
			if(!j1&&j2)
			{
				DMotor_Control_Par(-66,-77);
				delay_ms(81);
			}
			else
				if(!j8&&j7)
				{
					DMotor_Control_Par(-77,-66);
					delay_ms(81);
				}
		}
		else
		{
			DMotor_Control_Par(-80,-80);
			delay_ms(81);
		}
	}
	//offer a main pulse width and time-delay for the negative radian.
	if(-180==radian)							
	{											
		DMotor_Control_Par(-60,60);
		for(i=114;i>0;i--)						
			delay_ms(10);				
	}
	else if(-90==radian)
	{
		DMotor_Control_Par(-60,60);
		for(i=58;i>0;i--)
			delay_ms(10);
		DMotor_Control_Par(60,60);
		delay_ms(225);
		delay_ms(100);
	}
	//offer a pulse width for the positive radian.
	else if(90==radian)
	{
		DMotor_Control_Par(60,-60);
		for(i=58;i>0;i--)
			delay_ms(10);
		DMotor_Control_Par(60,60);
		delay_ms(219);
		delay_ms(100);
	}
	else if(180==radian)
	{
		DMotor_Control_Par(60,-60);
		for(i=116;i>0;i--)
			delay_ms(10);
	}
	//offer a micro adjustment for the negative radian.
	if(-90==radian||-180==radian)
	{
		for(i=3;i>0;i--)						//get into a for-body in the consideration of the twinkle laser light.
		{
			while(1==j1&&0==j2)					//adjustments after the main time-delay.
				DMotor_Control_Par(-70,70);		//anticlockwisely.
			while(1==j1&&1==j2)
				DMotor_Control_Par(-67,67);
			while(1==j1&&1==j2&&1==j3)
				DMotor_Control_Par(-63,63);
			while(0==j1&&1==j2&&1==j3)
				DMotor_Control_Par(-58,58);
			while(1==j2&&1==j3)
				DMotor_Control_Par(-53,53);
			while(1==j2&&1==j3&&1==j4)
				DMotor_Control_Par(-50,50);
			while(0==j2&&1==j3&&1==j4)
				DMotor_Control_Par(-48,48);
			while(1==j3&&1==j4)
				DMotor_Control_Par(-42,42);
			while(1==j3&&1==j4&&1==j5)
				DMotor_Control_Par(-38,38);
			if(1==j4&&1==j5)
				DMotor_Control_Par(0,0);
		}
		for(i=2;i>0;i--)
		{
			while(1==j8&&0==j7)					//clockwisely.
				DMotor_Control_Par(70,-70);
			while(1==j8&&1==j7)
				DMotor_Control_Par(67,-67);
			while(1==j8&&1==j7&&1==j6)
				DMotor_Control_Par(63,-63);
			while(0==j8&&1==j7&&1==j6)
				DMotor_Control_Par(58,-58);
			while(1==j7&&1==j6)
				DMotor_Control_Par(50,-50);
			while(1==j7&&1==j6&&1==j5)
				DMotor_Control_Par(48,-48);
			while(0==j7&&1==j6&&1==j5)
				DMotor_Control_Par(45,-45);
			while(1==j6&&1==j5)
				DMotor_Control_Par(42,-42);
			if(1==j6&&1==j5&&1==j4)
				DMotor_Control_Par(38,-38);
			if(1==j5&&1==j4)
				DMotor_Control_Par(0,0);
		}
	}
	else											//offer a micro adjustment for the positive radian.
	{
		for(i=3;i>0;i--)
		{
			while(1==j8&&0==j7)					//clockwisely.
				DMotor_Control_Par(70,-70);
			while(1==j8&&1==j7)
				DMotor_Control_Par(67,-67);
			while(1==j8&&1==j7&&1==j6)
				DMotor_Control_Par(63,-63);
			while(0==j8&&1==j7&&1==j6)
				DMotor_Control_Par(58,-58);
			while(1==j7&&1==j6)
				DMotor_Control_Par(50,-50);
			while(1==j7&&1==j6&&1==j5)
				DMotor_Control_Par(48,-48);
			while(0==j7&&1==j6&&1==j5)
				DMotor_Control_Par(45,-45);
			while(1==j6&&1==j5)
				DMotor_Control_Par(42,-42);
			if(1==j6&&1==j5&&1==j4)
				DMotor_Control_Par(38,-38);
			if(1==j5&&1==j4)
				DMotor_Control_Par(0,0);
		}
		for(i=2;i>0;i--)
		{
			while(1==j1&&0==j2)					//adjustments after the main time-delay.
				DMotor_Control_Par(-70,70);		//anticlockwisely.
			while(1==j1&&1==j2)
				DMotor_Control_Par(-67,67);
			while(1==j1&&1==j2&&1==j3)
				DMotor_Control_Par(-63,63);
			while(0==j1&&1==j2&&1==j3)
				DMotor_Control_Par(-58,58);
			while(1==j2&&1==j3)
				DMotor_Control_Par(-53,53);
			while(1==j2&&1==j3&&1==j4)
				DMotor_Control_Par(-50,50);
			while(0==j2&&1==j3&&1==j4)
				DMotor_Control_Par(-48,48);
			while(1==j3&&1==j4)
				DMotor_Control_Par(-42,42);
			while(1==j3&&1==j4&&1==j5)
				DMotor_Control_Par(-38,38);
			if(1==j4&&1==j5)
				DMotor_Control_Par(0,0);
		}
	}
	//offer a micro forward distance for the next track movement and crossroad judgement.
	if(-180==radian||180==radian)
	{
		DMotor_Control_Par(55,55);
			delay_ms(300);
		while(ii--)
			forward_steep();
	}
	//an instant stop after the adjustments above.
	DMotor_Control_Par(0,0);
}

void turn_catch_degree(signed int radian)
{
	unsigned int i,ii;
	i=0;
	ii=1024;					//time-delay for the track-adjustment.		
	if(-180==radian||180==radian)
	{
		if((j1&&j7)||(j2&&j8)||(j1&&j8))
		{
			while((j1&&j7)||(j2&&j8)||(j1&&j8))
			{DMotor_Control_Par(-80,-80);
			  catch_obj();}
			delay_ms(64);
			if(!(j1||j2||j3))								//a little offset generated by the propagation of the backward error.
			{
				DMotor_Control_Par(-55,-65);				//offer asymmetric pulse width for the adjustment of the robot.
				catch_obj();
				delay_ms(81);								//time-delay for this adjustment.
			}
			else
				if(!(j8||j7||j6))							//symmetric situation of this sentences above.
				{
					DMotor_Control_Par(-65,-55);
					catch_obj();
					delay_ms(81);
				}
			if(!(j1||j2))									//a large offset occur.
			{
				DMotor_Control_Par(-60,-70);
				catch_obj();
				delay_ms(81);
			}
			else
				if(!(j8||j7))
				{
					DMotor_Control_Par(-70,-60);
					catch_obj();
					delay_ms(81);
				}
			if(!j1&&j2)
			{
				DMotor_Control_Par(-66,-77);
				catch_obj();
				delay_ms(81);
			}
			else
				if(!j8&&j7)
				{
					DMotor_Control_Par(-77,-66);
					catch_obj();
					delay_ms(81);
				}
		}
		else
		{
			DMotor_Control_Par(-80,-80);
			catch_obj();
			delay_ms(81);
		}
	}
	//offer a main pulse width and time-delay for the negative radian.
	if(-180==radian)							
	{											
		DMotor_Control_Par(-60,60);
		catch_obj();
		for(i=113;i>0;i--)						
			delay_ms(10);				
	}
	else if(-90==radian)
	{
		DMotor_Control_Par(-60,60);
		catch_obj();
		for(i=58;i>0;i--)
			delay_ms(10);
		DMotor_Control_Par(60,60);
		catch_obj();
		delay_ms(225);
	}
	//offer a pulse width for the positive radian.
	else if(90==radian)
	{
		DMotor_Control_Par(60,-60);
		catch_obj();
		for(i=58;i>0;i--)
			delay_ms(10);
		DMotor_Control_Par(60,60);
		catch_obj();
		delay_ms(219);
	}
	else if(180==radian)
	{
		DMotor_Control_Par(60,-60);
		catch_obj();
		for(i=116;i>0;i--)
			delay_ms(10);
	}
	//offer a micro adjustment for the negative radian.
	if(-90==radian||-180==radian)
	{
		for(i=3;i>0;i--)						//get into a for-body in the consideration of the twinkle laser light.
		{
			while(1==j1&&0==j2)					//adjustments after the main time-delay.
			{DMotor_Control_Par(-70,70);		//anticlockwisely.
			catch_obj();}
			while(1==j1&&1==j2)
			{DMotor_Control_Par(-67,67);
			catch_obj();}
			while(1==j1&&1==j2&&1==j3)
			{DMotor_Control_Par(-63,63);
			catch_obj();}
			while(0==j1&&1==j2&&1==j3)
			{DMotor_Control_Par(-58,58);
			catch_obj();}
			while(1==j2&&1==j3)
			{DMotor_Control_Par(-53,53);
			catch_obj();}
			while(1==j2&&1==j3&&1==j4)
			{DMotor_Control_Par(-50,50);
			catch_obj();}
			while(0==j2&&1==j3&&1==j4)
			{DMotor_Control_Par(-48,48);
			catch_obj();}
			while(1==j3&&1==j4)
			{DMotor_Control_Par(-42,42);
			catch_obj();}
			while(1==j3&&1==j4&&1==j5)
			{DMotor_Control_Par(-38,38);
			catch_obj();}
			if(1==j4&&1==j5)
			{DMotor_Control_Par(0,0);
			catch_obj();}
		}
		for(i=2;i>0;i--)
		{
			while(1==j8&&0==j7)					//clockwisely.
			{DMotor_Control_Par(70,-70);
			catch_obj();}
			while(1==j8&&1==j7)
			{DMotor_Control_Par(67,-67);
			catch_obj();}
			while(1==j8&&1==j7&&1==j6)
			{DMotor_Control_Par(63,-63);
			catch_obj();}
			while(0==j8&&1==j7&&1==j6)
			{DMotor_Control_Par(58,-58);
			catch_obj();}
			while(1==j7&&1==j6)
			{DMotor_Control_Par(50,-50);
			catch_obj();}
			while(1==j7&&1==j6&&1==j5)
			{DMotor_Control_Par(48,-48);
			catch_obj();}
			while(0==j7&&1==j6&&1==j5)
			{DMotor_Control_Par(45,-45);
			catch_obj();}
			while(1==j6&&1==j5)
			{DMotor_Control_Par(42,-42);
			catch_obj();}
			if(1==j6&&1==j5&&1==j4)
			{DMotor_Control_Par(38,-38);
			catch_obj();}
			if(1==j5&&1==j4)
			{DMotor_Control_Par(0,0);
			catch_obj();}
		}
	}
	else											//offer a micro adjustment for the positive radian.
	{
		for(i=3;i>0;i--)
		{
			while(1==j8&&0==j7)					//clockwisely.
			{DMotor_Control_Par(70,-70);
			catch_obj();}
			while(1==j8&&1==j7)
			{DMotor_Control_Par(67,-67);
			catch_obj();}
			while(1==j8&&1==j7&&1==j6)
			{DMotor_Control_Par(63,-63);
			catch_obj();}
			while(0==j8&&1==j7&&1==j6)
			{DMotor_Control_Par(58,-58);
			catch_obj();}
			while(1==j7&&1==j6)
			{DMotor_Control_Par(50,-50);
			catch_obj();}
			while(1==j7&&1==j6&&1==j5)
			{DMotor_Control_Par(48,-48);
			catch_obj();}
			while(0==j7&&1==j6&&1==j5)
			{DMotor_Control_Par(45,-45);
			catch_obj();}
			while(1==j6&&1==j5)
			{DMotor_Control_Par(42,-42);
			catch_obj();}
			if(1==j6&&1==j5&&1==j4)
			{DMotor_Control_Par(38,-38);
			catch_obj();}
			if(1==j5&&1==j4)
			{DMotor_Control_Par(0,0);
			catch_obj();}
		}
		for(i=2;i>0;i--)
		{
			while(1==j1&&0==j2)					//adjustments after the main time-delay.
			{DMotor_Control_Par(-70,70);		//anticlockwisely.
			catch_obj();}
			while(1==j1&&1==j2)
			{DMotor_Control_Par(-67,67);
			catch_obj();}
			while(1==j1&&1==j2&&1==j3)
			{DMotor_Control_Par(-63,63);
			catch_obj();}
			while(0==j1&&1==j2&&1==j3)
			{DMotor_Control_Par(-58,58);
			catch_obj();}
			while(1==j2&&1==j3)
			{DMotor_Control_Par(-53,53);
			catch_obj();}
			while(1==j2&&1==j3&&1==j4)
			{DMotor_Control_Par(-50,50);
			catch_obj();}
			while(0==j2&&1==j3&&1==j4)
			{DMotor_Control_Par(-48,48);
			catch_obj();}
			while(1==j3&&1==j4)
			{DMotor_Control_Par(-42,42);
			catch_obj();}
			while(1==j3&&1==j4&&1==j5)
			{DMotor_Control_Par(-38,38);
			catch_obj();}
			if(1==j4&&1==j5)
			{DMotor_Control_Par(0,0);
			catch_obj();}
		}
	}
	//offer a micro forward distance for the next track movement and crossroad judgement.
	if(-180==radian||180==radian)
	{
		DMotor_Control_Par(55,55);
		catch_obj();
			delay_ms(100);
		while(ii--)
			forward_steep();
	}
	//an instant stop after the adjustments above.
	DMotor_Control_Par(0,0);
	catch_obj();
}

void internal_push_back(unsigned char colour_val)
{
	while(!is_edge(colour_val))
		forward_steep();
	DMotor_Control_Par(0,0);
	delay_ms(200);
	catch_obj();
	delay_ms(500);
		
	backward_moderate();
	delay_level0();
	turn_degree(180);
	if(GREEN == colour_val)
		PASS_LEFT_NORTHERN_CROSSROAD
	else
		PASS_RIGHT_NORTHERN_CROSSROAD
}

unsigned char is_pre_center()
{
	unsigned char i,ii,iii;
	unsigned char flag0;
	i=255;
	ii=144;
	iii=64;
	flag0=0;
	if(1==j1&&0==j2&&0==j3&&1==j4&&1==j5&&0==j6&&0==j7&&1==j8)
		flag0=1;
	else if(1==j1&&0==j2&&0==j3&&0==j6&&1==j7&&1==j8)
		flag0=1;
	else if(1==j1&&1==j2&&0==j3&&0==j6&&0==j7&&1==j8)
		flag0=1;
	else if(1==j1&&1==j2&&0==j3&&0==j6&&1==j7&&1==j8)
		flag0=1;
	if(0==flag0)
		return 0;
	else
	{
		if(1==j1&&0==j2&&0==j3&&1==j4&&1==j5&&0==j6&&0==j7&&1==j8)
		{
			while(i--)
				DMotor_Control_Par(40,40);
		}
		else if(1==j1&&0==j2&&0==j3&&0==j6&&1==j7&&1==j8)
		{
			while(ii--)
				DMotor_Control_Par(30,40);
		}
		else if(1==j1&&1==j2&&0==j3&&0==j6&&0==j7&&1==j8)
		{
			while(ii--)
				DMotor_Control_Par(40,30);
		}
		else if(1==j1&&1==j2&&0==j3&&0==j6&&1==j7&&1==j8)
		{
			while(iii--)
				DMotor_Control_Par(30,30);
		}
		DMotor_Control_Par(0,0);
		return 1;
	}
}

//usage:	call this function if you want to move to correspond edge(in the internal_push_back function body).
//return:	return 1 if the robot is about on the edge of the external round.
//version:	1.0 by chen on 8/14/2014(this function is not finished).
unsigned char is_edge(unsigned char push_colour)
{
	unsigned char flag0 = 0;
	if( WHITE == push_colour || RED==push_colour )
	{
		while( !j9 && j10)
			DMotor_Control_Par(60,-10);			   
		while( j9 && !j10)
		 	DMotor_Control_Par(-10,60);
		if( j9 && j10)   
			return 1;
	}
	else
	{
		while( !j9 && j10)
			DMotor_Control_Par(60,-10);			   
		while( j9 && !j10)
		 	DMotor_Control_Par(-10,60);
		if( j9 && j10)
			return 1;				
	}
	return flag0;
}

void place_obj()
{
	servo3(-15);
	servo4(15);
	delay_ms(1000);
}

void delay_level1()
{
	delay_ms(2000);
}

void backward_moderate()
{
	DMotor_Control_Par(-40,-40);
	delay_ms(400);	
}

void delay_level0()
{
	DMotor_Control_Par(-40,-40);
	delay_ms(300);
}

unsigned char test_colour()
{
	unsigned short r,g,b;
	TCS_Power_On();
	r=TCS230_Read_Colour(3);
	b=TCS230_Read_Colour(1);
	g=TCS230_Read_Colour(4);
	if((r>4500)&&(g>4660)&&(b>4700))
		return GREEN;
	else if((r>4000)&&(g>4100)&&(b>4400))
		return WHITE;
	else if((r>3600)&&(g>3800)&&(b>3980))
		return RED;
	else if((r>3200)&&(g>3320)&&(b>3560))
		return BLACK;
	else if((r>2400)&&((g>2700))&&(b>3100))
		return BLUE;
	else
		return 5;
}

void TCS_Power_On()
//      D	   C	  E	     B	    A
{a[0]=5;a[1]=4;a[2]=3;a[3]=2;a[4]=1;a[5]=0;
b[0]=5;b[1]=4;b[2]=2;b[3]=3;b[4]=0;b[5]=1;
ret0=a[5];ret1=a[2];ret2=a[3];}
	
void pass_center()
{
	while(!(j1||j8))
		forward_steep();
	while(j1&&!j8)
		DMotor_Control_Par(-40,40);	 
	while(j8&&!j1)
		DMotor_Control_Par(40,-40);
	DMotor_Control_Par(40,40);
	while(!(j1 + j2 + j3 + j4 + j5 + j6 + j7 + j8 >= 6))
		DMotor_Control_Par(60,60);
	DMotor_Control_Par(60,60);
	delay_ms(700);
	PASS_NORTHERN_CROSSROAD
}

unsigned char is_storage()
{
	if(0==j9&&0==j10)
		return 0;
	else
	{
		if(0==j9&&1==j10)
		{
			delay_ms(3);
			if(0==j9&&1==j10)
			{
				while(1)
				{
					DMotor_Control_Par(12,0);
					if(!(0==j9&&1==j10))
					{
						delay_us(512);
						if(!(0==j9&&1==j10))
							break;
					}
				}
				while(1)
				{
					DMotor_Control_Par(0,12);
					if(!(1==j9&&0==j10))
					{
						delay_us(512);
						if(!(1==j9&&0==j10))
							break;
					}
				}
			}
		}
		else
			if(1==j9&&0==j10)
			{
				delay_ms(3);
				if(1==j9&&0==j10)
				{
					while(1)
					{
						DMotor_Control_Par(0,12);
						if(!(1==j9&&0==j10))
						{
							delay_us(512);
							if(!(1==j9&&0==j10))
								break;
						}
					}
					while(1)
					{
						DMotor_Control_Par(12,0);
						if(!(0==j9&&1==j10))
						{
							delay_us(512);
							if(!(0==j9&&1==j10))
								break;
						}
					}
				}
			}
		while(1)
		{
			DMotor_Control_Par(12,12);
			if(!(1==j9&&1==j10))
			{
				delay_us(512);
				if(!(1==j9&&1==j10))
					break;
			}
		}
		if(0==j9&&1==j10)
		{
			delay_ms(2);
			if(0==j9&&1==j10)
			{
				while(1)
				{
					DMotor_Control_Par(0,12);
					if(!(0==j9&&1==j10))
					{
						delay_us(512);
						if(!(0==j9&&1==j10))
							break;
					}
				}
				if(1==j9&&0==j10)
				{
					while(1)
					{
						DMotor_Control_Par(12,0);
						if(!(1==j9&&0==j10))
						{
							delay_us(512);
							if(!(1==j9&&0==j10))
								break;
						}
					}
				}
			}
		}
		else
			if(1==j9&&0==j10)
			{
				delay_ms(2);
				if(1==j9&&0==j10)
				{
					while(1)
					{
						DMotor_Control_Par(12,0);
						if(!(1==j9&&0==j10))
						{
							delay_us(512);
							if(!(1==j9&&0==j10))
								break;
						}
					}
					if(0==j9&&1==j10)
					{
						while(1)
						{
							DMotor_Control_Par(0,12);
							if(!(0==j9&&1==j10))
							{
								delay_us(512);
								if(!(0==j9&&1==j10))
									break;
							}
						}
					}
				}
			}
		return 1;
	}
}

/*//this function do not use forward laser sensors.abandon this function body temporarily.
unsigned char is_northern_crossroad()
{
	if( (j1 + j2 + j3 + j4 + j5 + j6 + j7 + j8 >= 3)
	&& (j1 && j8)
	)
		flag_2 = 1;
	else 
		return 0;						 
	if(flag_2 == 1){
		while( !(!(j1 + j2 + j3 + j4 + j5 + j6 + j7 + j8 >= 3) && (!j1 && !j8)) )
			DMotor_Control_Par(60,60);
		DMotor_Control_Par(0,0);
		flag_2 = 0;			
		return 1;
	}
	return 0;
}
*/

unsigned char is_southern_crossroad()
{

	if( (j1 + j2 + j3 + j4 + j5 + j6 + j7 + j8 >= 5)
	    && (j1 && j8) )
		flag_1 = 1;
	else 
		return 0;
	if(flag_1 == 1){
		while( !(!(j1 + j2 + j3 + j4 + j5 + j6 + j7 + j8 >= 5) && (!j1 && !j8)) )
			DMotor_Control_Par(60,60);
		DMotor_Control_Par(0,0);
		flag_1 = 0;			
		return 1;
	}
	return 0;
}

unsigned char is_northern_crossroad()
{
		if(j9 || j10){
		while( !j9 && j10)
			DMotor_Control_Par(60,-10);			   
		while( j9 && !j10)
		 	DMotor_Control_Par(-10,60);
		if( j9 && j10){
			DMotor_Control_Par(60,60);   
			delay_ms(340);
		flag_3 = 1;   
	    }		   
	}
	else 
		return 0;	
	if(flag_3 == 1){
		DMotor_Control_Par(56,60);
		delay_ms(80);
		while( j1 + j2 + j3 + j4 + j5 + j6 + j7 + j8 >= 4 )
			DMotor_Control_Par(40,40);
		DMotor_Control_Par(60,90);
		delay_ms(50);
		DMotor_Control_Par(0,0);
		flag_3 = 0;			
		return 1;
	}
	return 0;
}

unsigned char is_left_northern_crossroad()
{
	if(j9 || j10){
		while( !j9 && j10)
			DMotor_Control_Par(60,-10);			   
		while( j9 && !j10)
		 	DMotor_Control_Par(-10,60);
		if( j9 && j10){
			DMotor_Control_Par(60,60);   
			delay_ms(340);
		flag_3 = 1;   
	    }		   
	}
	else 
		return 0;	
	if(flag_3 == 1){
		DMotor_Control_Par(60,56);
		delay_ms(80);
		while( j1 + j2 + j3 + j4 + j5 + j6 + j7 + j8 >= 4 )
			DMotor_Control_Par(40,40);
		DMotor_Control_Par(90,60);
		delay_ms(50);
		DMotor_Control_Par(0,0);
		flag_3 = 0;			
		return 1;
	}
	return 0;
}

unsigned char is_right_northern_crossroad()
{
	if(j9 || j10){
		while( !j9 && j10)
			DMotor_Control_Par(60,-10);			   
		while( j9 && !j10)
		 	DMotor_Control_Par(-10,60);
		if( j9 && j10){
			DMotor_Control_Par(60,60);   
			delay_ms(340);
		flag_3 = 1;   
	    }		   
	}
	else 
		return 0;	
	if(flag_3 == 1){
		DMotor_Control_Par(60,56);
		delay_ms(80);
		while( j1 + j2 + j3 + j4 + j5 + j6 + j7 + j8 >= 4 )
			DMotor_Control_Par(40,40);
		DMotor_Control_Par(90,60);
		delay_ms(100);
		DMotor_Control_Par(0,0);
		flag_3 = 0;			
		return 1;
	}
	return 0;
}

void drag_obj(unsigned char i)
{
//	switch(i)
//	{
//		case 5:
//		{
//			DMotor_Control_Par(20,20);
//			servo3(40);	//add specific radian.
//			servo4(15);	//add specific radian.
//			delay_ms(1000);
//			delay_ms(600);
//			DMotor_Control_Par(0,0);	//add specific speed.
//			catch_storage_5_obj();
//			DMotor_Control_Par(-20,-20);
//			catch_storage_5_obj();
//			delay_ms(1000);
//			turn_catch_degree(180);
//			DMotor_Control_Par(0,0);
//			delay_ms(400);	//add specific micro second.	symetrical with former.
//		}
//		break;
//		case 4:
//		{
//			DMotor_Control_Par(20,20);
//			servo3(-15);	//add specific radian.
//			servo4(-35);	//add specific radian.		symmetrical PWM with the former.
//			delay_ms(1000);
//			delay_ms(700);
//			DMotor_Control_Par(0,0);	//add specific speed.
//			catch_storage_4_obj();
//			DMotor_Control_Par(-20,-20);
//			catch_storage_4_obj();
//			delay_ms(1000);
//			turn_catch_degree(180);
//			DMotor_Control_Par(0,0);	//add specific speed,symmetrical PWM with the former.
//			delay_ms(400);	//add specific micro second.	symetrical with former.
//		}
//		break;
//		case 3:
//		{
//			DMotor_Control_Par(23,20);
//			servo3(48);	//add specific radian.
//			servo4(18);	//add specific radian.
//			delay_ms(1000);
//			delay_ms(1000);
//			delay_ms(500);
//			DMotor_Control_Par(0,0);	//add specific speed.
//			catch_storage_3_obj();
//			DMotor_Control_Par(-23,-20);
//			catch_storage_3_obj();
//			delay_ms(1000);
//			turn_catch_degree(180);
//			DMotor_Control_Par(0,0);
//			delay_ms(400);	//add specific micro second.	symetrical with former.
//		}
//		break;
//		case 2:
//		{
//			DMotor_Control_Par(25,20);
//			servo3(-18);	//add specific radian.
//			servo4(-43);	//add specific radian.
//			delay_ms(1000);
//			delay_ms(1000);
//			delay_ms(800);
//			DMotor_Control_Par(0,0);	//add specific speed.
//			catch_storage_2_obj();
//			DMotor_Control_Par(-25,-20);
//			catch_storage_2_obj();
//			delay_ms(1000);
//			turn_catch_degree(180);
//			DMotor_Control_Par(0,0);
//			delay_ms(400);	//add specific micro second.	symetrical with former.
//		}
//		break;
//		case 1:
//		{
//			DMotor_Control_Par(20,20);
//			servo3(0);	//add specific radian.
//			servo4(0);	//add specific radian.
//			delay_ms(1000);
//			delay_ms(1000);
//			delay_ms(1000);
//			delay_ms(200);
//			DMotor_Control_Par(0,0);	//add specific speed.
//			catch_storage_1_obj();
//			DMotor_Control_Par(-20,-20);
//			catch_storage_2_obj();
//			delay_ms(1000);
//			delay_ms(1000);
//			turn_catch_degree(180);
//			DMotor_Control_Par(0,0);
//			delay_ms(400);	//add specific micro second.	symetrical with former.
//		}
//		break;
//		default:
//			break;
//	}


	switch(i)
	{
		case 5:
		{
//			DMotor_Control_Par(40,40);
//			servo3(28);	//add specific radian.
//			servo4(15);	//add specific radian.
//			delay_ms(800);
//			DMotor_Control_Par(0,0);	//add specific speed.
//			catch_obj();
			
			
			
			DMotor_Control_Par(20,20);
			servo3(40);	//add specific radian.
			servo4(15);	//add specific radian.
			delay_ms(1000);
			delay_ms(600);
			DMotor_Control_Par(0,0);	//add specific speed.
      catch_storage_5_obj();
			DMotor_Control_Par(-20,-20);
			catch_storage_5_obj();
			delay_ms(1000);
			delay_ms(500);
			turn_catch_degree(180);
			DMotor_Control_Par(0,0);
			delay_ms(400);	//add specific micro second.	symetrical with former.
		}
		break;
		case 4:
		{
			DMotor_Control_Par(23,20);
			servo3(-15);	//add specific radian.
			servo4(-30);	//add specific radian.		symmetrical PWM with the former.
			delay_ms(1000);
			delay_ms(700);
			DMotor_Control_Par(0,0);	//add specific speed.
			catch_storage_4_obj();
			DMotor_Control_Par(-20,-20);
			catch_storage_4_obj();
			delay_ms(1000);
			delay_ms(500);
			turn_catch_degree(180);
			DMotor_Control_Par(0,0);	//add specific speed,symmetrical PWM with the former.
			delay_ms(400);	//add specific micro second.	symetrical with former.
		}
		break;
		case 3:
		{
			DMotor_Control_Par(26,20);
			servo3(48);	//add specific radian.
			servo4(18);	//add specific radian.
			delay_ms(1000);
			delay_ms(1000);
			delay_ms(500);
			DMotor_Control_Par(0,0);	//add specific speed.
      catch_storage_3_obj();
			DMotor_Control_Par(-23,-20);
			catch_storage_3_obj();
			delay_ms(1000);
			delay_ms(500);
			turn_catch_degree(180);
			DMotor_Control_Par(0,0);
//			DMotor_Control_Par(20,20);
			delay_ms(400);	//add specific micro second.	symetrical with former.
		}
		break;
		case 2:
		{
			DMotor_Control_Par(25,20);
			servo3(-18);	//add specific radian.
			servo4(-43);	//add specific radian.
			delay_ms(1000);
			delay_ms(1000);
			delay_ms(800);
			DMotor_Control_Par(0,0);	//add specific speed.
      catch_storage_2_obj();
			DMotor_Control_Par(-25,-20);
			catch_storage_2_obj();
			delay_ms(1000);
			delay_ms(500);
			turn_catch_degree(180);
			DMotor_Control_Par(0,0);
			delay_ms(400);	//add specific micro second.	symetrical with former.
		}
		break;
		case 1:
		{
			DMotor_Control_Par(20,20);
			servo3(0);	//add specific radian.
			servo4(0);	//add specific radian.
			delay_ms(1000);
			delay_ms(1000);
			delay_ms(1000);
			delay_ms(200);
			DMotor_Control_Par(0,0);	//add specific speed.
      catch_storage_1_obj();
			DMotor_Control_Par(-20,-20);
			catch_storage_1_obj();
			delay_ms(1000);
			delay_ms(1000);
			turn_catch_degree(180);
			DMotor_Control_Par(0,0);
			delay_ms(400);	//add specific micro second.	symetrical with former.
		}
		break;
		default:
			break;
	}
}

void catch_obj()
{
	servo3(30);
	servo4(-30);
}

//fetch object A in left storage.
void catch_storage_5_obj(void)
{
		servo3(50);	
		servo4(-5);
}

//fetch object B in left storage.
void catch_storage_4_obj(void)
{
		servo3(5);	
		servo4(-50);
}

//fetch object E in left storage.
void catch_storage_3_obj(void)
{
		servo3(60);	
		servo4(-15);
}

//fetch object C in left storage.
void catch_storage_2_obj(void)
{
		servo3(15);	
		servo4(-60);
}

//fetch object D in left storage
void catch_storage_1_obj(void)
{
		servo3(30);	
		servo4(-30);
}
