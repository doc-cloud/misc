//filename:		pick.c
//language:		C.
//usage:		this file provide the main_test for the Robot Competition(Carry Project)
//declaration:	this version is a beta version named 1.0
//				there are lots of declarations of effective function in this file.
//				they are some port for programmer to a certain extent.
//				the specific sentences will be add to this project by the effort of every parts of proj-team.
//version		1.0 by chen

//definitions of the colour value.
#define GREEN 0
#define WHITE 1
#define RED 2
#define BLACK 3
#define BLUE 4

void main_test();
void step0();
void step1();
unsigned char is_center();
void forward_steep();
void forward_low();
void delay_level0();
void turn_degree(signed char radian);
void move_level0();
void test_colour(unsigned char colour);
void move_further();
void place_obj();
void edge_round();
void turn_center(signed char radian);
void turn_edge(signed char radian);
void forward_moderate();
void backward_moderate();
void delay_level1();
unsigned char is_storage();
void track_thick_round();
//unsigned char test_distance0();
void catch_obj();
//void track_back0();
void track_routine0(signed char radian0,signed char radian1);
void track_routine1(signed char radian0,signed char radian1);
void track_routine2(signed char radian0,signed char radian1);
//void track_routine3(signed char radian0,signed char radian1);
void left_area_filter();
void right_area_filter();

void main()
{
	main_test();
}

//this is a test for the function in the main body.
//call the step0 and step1 to test the task one and task two expression.
void main_test()
{
	step0();
	step1();	
}

//usage:	to realize the task one.
//version:	1.0 by chen on 8/13/2014.
void step0()
{
	//label0
	unsigned char ret0,ret1,ret2;
	ret0=ret1=ret2=5;				//prevent the value mixture of the five colours.
	while(!is_center())
		forward_steep();			//go to the center of the round.
	//forward_slow();
	//delay_level0();				
	//the purpose of remark sentences above is place the robot on the center of platform precisely.
	turn_degree(-90);				//turn left,try to measure the colour of the object on the area A.
	move_level0();					//move to the internal round.for more information,please into the declaration of move_level0.
	ret0=test_colour0();			//deliver the colour of object A to ret0.
	if(GREEN==ret0)
	{
		move_further();				//get to the external round to specific purpose,we want to place the object exactly here.
		place_obj();				//place the object on the edge round point precisely.
		backward_moderate();		//backward a little bit distance to release the object.
		delay_level1();				//realize the effects of the sentence above.
		turn_degree(180);			//turn a certain degree for the next sentence. 
		while(!is_center())														 
			forward_moderate();
		turn_degree(-90);
	}
	else
		if(WHITE==ret0)
		{
			turn_degree(180);
			while(!is_center())
				forward_moderate();
			turn_degree(-135);
			move_level0();
			move_further();
			place_obj();
			backward_moderate();
			delay_level1();
			turn_degree(180);
			while(!is_center())
				forward_moderate();
			turn_degree(-135);
		}
		else
			if(BLACK==ret0)
			{
				turn_degree(180);
				while(!is_center())
					forward_moderate();
				turn_degree(-45);
				move_level0()
				move_further();
				place_obj();
				backward_moderate();
				delay_level1();
				turn_degree(180);
				while(!is_center())
					forward_moderate();
				turn_degree(135);
			}
			else
				if(RED==ret0||BULE==ret0)		//if the object on area A is RED or BLUE,push it to a temporary position.
				{								//the position can not be the purpose colour of objects on area C or E.
					turn_degree(180);			//so we choice the opposite position of area C.
					while(!is_center())			//the code following is the process of the realization.
						forward_moderate();
					turn_degree(90);
					move_level0();
					backward_moderate();
					delay_level1();
					turn_degree(180);
					while(!is_center())
						forward_moderate();
				}
	//label1
	//the code between label0 and label1:
	//									if the colour is green,white or black,place the object A on its own position.
	//									if the colour is red or blue,place the object A on the opposite of C for the further process.
	//the purpose of the code block is place object A on its appropriate position.
	//we named this code block 'procedure0'

	move_level0();						
	ret1=test_colour0();				//deliver the colour of object C to ret1.
	if(GREEN==ret1)		
	{
		turn_degree(180);
		while(!is_center())
			forward_moderate();
		turn_degree(90);
		move_level0();
		move_further();
		place_obj();
		backward_moderate();
		delay_level1();
		while(!is_center())
			forward_moderate();
	}
	else
		if(WHITE==ret1)
		{
			turn_degree(180);
			while(!is_center())
				forward_moderate();
			turn_degree(135);
			move_level0();
			move_further();
			place_obj();
			backward_moderate();
			delay_level1();
			turn_degree(180);
			while(!is_center())
				forward_moderate();
			turn_degree(-45);
		}
		else
			if(RED==ret1)
			{
				move_further();
				place_obj();
				backward_moderate();
				delay_level1();
				turn_degree(180);
				while(!is_center())
					forward_moderate();
				turn_degree(-90);
			}
			else
				if(BLACK==ret1)
				{
					turn_degree(180);
					while(!is_center())
						forward_moderate();
					turn_degree(-135);
					move_level0();
					move_further();
					place_obj();
					backward_moderate();
					delay_level1();
					turn_degree(180);
					while(!is_center())
						forward_moderate();
					turn_degree(-135);
				}
				else
					if(BLUE==ret1)
					{
						turn_degree(180);
						while(!is_center())
							forward_moderate();
						turn_degree(90);
						move_level0();
						backward_moderate();
						delay_level1();
						turn_degree(180);
						while(!is_center())
							forward_moderate();
						turn_degree(45);
					}
	//label2
	//the code assemble between label1 and label2:
	//									if the object C colour is green,white,red,black,place the object C on its own position.
	//									if the object C colour is blue,place the object C on the opposite of D for the further process.
	//the purpose of the code assemble is place object C on its appropriate position.
	//we named this code assemble 'procedure1'.

	move_level0();							//third procedure of the step0.
	ret2=test_colour0();					//deliver the colour of object E to ret2.
	if(GREEN==ret2)
	{
		turn_degree(180);
		while(!is_center())
			forward_moderate();
		move_level0();
		move_further();
		place_obj();
		backward_moderate();
		delay_level1();
		turn_degree(180);
		while(!is_center())
			forward_moderate();
		turn_degree(90);
	}
	else
		if(WHITE==ret2)
		{
			turn_degree(180);
			while(!is_center())
				forward_moderate();
			turn_degree(45);
			move_level0();
			move_further();
			place_obj();
			backward_moderate();
			delay_level1();
			turn_degree(180);
			while(!is_center())
				forward_moderate();
			turn_degree(45);
		}
		else
			if(RED==ret2)
			{
				turn_degree(180);
				while(!is_center())
					forward_moderate();
				turn_degree(90);
				move_level0();
				move_further();
				place_obj();
				backward_moderate();
				delay_level1();
				turn_degree(180);
				while(!is_center())
					forward_moderate();
			}
			else
				if(BLACK==ret2)
				{
					turn_degree(180);
					while(!is_center())
						forward_moderate();
					turn_degree(135);
					move_level0();
					move_further();
					place_obj();
					backward_moderate();
					delay_level1();
					turn_degree(180);
					while(!is_center())
						forward_moderate();
					turn_degree(-45);
				}
				else
					if(BLUE==ret2)
					{
						move_level0();
						move_further();
						place_obj();
						backward_moderate();
						delay_level1();
						turn_degree(180);
						while(!is_center())
							forward_moderate();
						turn_degree(-90);
					}
	//label3
	//the code assemble between label2 and label3:
	//									due to the effect of procedure0 and procedure1,
	//									the object E will be place on its own position directly without block.
	//the purpose of this code assemble is place the object E on its own position.
	//we named this code assemble 'procedure2'.

	if(RED==ret0||BLUE==ret0||BLUE==ret1)				//these are three possible situations to lead to the complementary code.
	{		
		//mark0											//list:
		if(RED==ret0)										   //(RED==ret0)	the object A colour is red.
		{													   //(BLUE==ret0)	the object A colour is blue.
			move_level0();									   //(BLUE==ret1) 	the object C colour is blue.
			turn_degree(180);							//in the algorithm of this main_test body.
			while(!is_center())							//positions above have their own possiblility.
				forward_moderate();						
			move_level0();
			move_further();								
			place_obj();								//all code follow will realize the complementary 
			backward_moderate();						//function to place object to its own position.
			delay_level1();
			turn_degree(180);
			while(!is_center())
				forward_moderate();
		}
		else
			if(BLUE==ret0)
			{
				move_level0();
				turn_degree(180);
				while(!is_center())
					forward_moderate();
				turn_degree(90);
				move_level0();
				move_further();
				place_obj();
				backward_moderate();
				delay_level1();
				while(!is_center())
					forward_moderate();
				turn_degree(-90);
			}
		//mark1
		//the code assemble between mark0 and mark1:
		//											if the object A is red or blue,place it on its own position.
		//											due to the effect of procedure0 to procedure2,
		//											the object A will place on its own position directly without block.
		//the purpose of this code assemble is place object A on its own position.
		//we named the code assemble 'process0'.

		if(BLUE==ret1)
		{
			turn_degree(45);
			move_level0();
			turn_degree(180);
			while(!is_center())
				forward_moderate();
			turn_degree(45);
			move_level0();
			move_further();
			place_obj();
			backward_moderate();
			delay_level1();
			turn_degree(180);
			while(!is_center())
				forward_moderate();
			turn_degree(-90);
		}
	}
		//mark2
		//the code assemble between mark1 and mark2:
		//											if the object C is blue,place it on its own position.
		//											due to the effect of procedure0 to procedure2,
		//											the object C will be place on its own position directly without block.
		//we named this code assemble 'process1'.

	move_level0();
	move_level0();
	//move_further();			//go home.
	//the purpose of these sentences is get to home in an opposite direction of the original gesture.
	
	//label4
	//the code assemble between label3 and label4:
	//											if the three bad situation occured,
	//											process the objects on the temporary position to their own position.
	//											due to the effect of the function above,
	//											the objects on the temporary position will be 
	//											place on its own position directly without block.
	//the purpose of this code assemble is to place the objects on the temporary position to their own position.
	//we named this code assemble 'procedure3'
}

void step1()
{
	left_area_filter();
	turn_degree(-90);
	right_area_filter();
}

unsigned char is_center()
{
	//add function sentences here...
	//is_center to judge if the robot in the center of the round.
	//return 1 if the robot is in the center,return 0 if the answer is passive.
	//take full advantage of the feature that the center of the paltform is centrosymmetric.
	//reduce the code size to a large extent.
}

//these three functions following are similar with each other.
//steep,moderate,slow is a relatively concept,adjust these in particular situation.
//adjust the function body or the structure to realize the function.
//the parameter may be not a void type.
void forward_steep()
{
	//add function sentences here...
	//forward_steep to make the robot move forward in a steep speed.
	//be careful about the robot stability.
}

void forward_moderate()
{
	//add function sentences here...
	//forward_moderate to make the robot move forward in a moderate speed.
	//be careful about the robot stability.
}

void forward_slow()
{
	//add function sentences here...
	//forward_slow to make the robot move forward in a slow speed...
	//similar with the function forward_steep and forward_slow.
	//used company with the function delay_level0.
}

void delay_level0()
{
	//add function sentences here...
	//delay_level0 to make the robot place in the precise center of the round.
	//the parameter could may be not void to maintain the stability of the robot.
}

//parameter:	radian is the degree you want to turn and radian is a signed char value.
//version:		
void turn_degree(signed char radian)
{
	//add function sentences here...
	//turn_degree to make the robot turn a specific degree.
	//can be use with the function relevant to line detect.
}

//version:		
void move_level0()
{
	//add function sentences here...
	//move_level0 to make the robot move to the level 0 round rank(internal round of the platform).
	//this function should be used company with line_check.
	//make robot move in a moderate speed fastly and become low in a narrow scope for the usage of test_colour.
}

void test_colour(unsigned char colour)
{
	//add function sentences here...
	//test_colour to test the colour in position A,C,E and some position where can be detected.
	//use the colour sensor belong to the robot to realize the function body.
	//the sensor should be sensitive enough to judge the colour of green,white,red,black,blue.
}

void move_further()
{
	//add function sentences here...
	//move_further to make the robot push the object to the edge round(external round of the platform).
	//make robot move in a moderate speed fastly and become low in a narrow scope for the usage of edge_round_test.
}

//parameter:	colour is the colour of the object the robot is about to push.
//version:		
void place_obj(unsigned char colour)
{
	//add function sentences here...
	//place_obj to make the robot push the object to the correspond little point.
	//edit company with the 'edge_round'.
}

//this function be call in the place_obj body to realize the specific function.
void edge_round()
{
	//add function sentences here...
	//edge_round to detect the edge round with the laser sensors.
	//the main purpose of the function is to place or get object on the correspond little point.
	//this function main purpose is be used in some process function body.
	//remove this function if the process can be simplify.
}

void backward_moderate()
{
	//add function sentences here...
	//backward_moderate to make the robot make a little bit backward distance to release the object.
	//could be use company with the function delay_level1.
	//example as following:
	//						backward_moderate();
	//						delay_level1();
	//robot will release the object in its claw.
}

void delay_level1()
{
	//add function sentences here...
	//delay_level1 is due to adjust the function backward_moderate to realize its specific function.
	//the parameter may be not a void to maintain the stability of the robot.
	//and the realize process of the function.
}

unsigned char is_storage()
{
	//add function sentences here...
	//is_storage to check if the robot is about to get to the storage.
	//be careful about that the profile of home and storage is similar with each other.
}

void track_thick_round()
{
	//add function sentences here...
	//track_thick_round to make the robot track the thick round boundary(external round of the platform).
	//be care for the speed of this body.this speed should be fast appropriately.
}

void catch_obj()
{
	//add function sentences here...
	//catch_obj called by the robot MCU to catch a object random.
	//use company with the function test_distance0.
	//test_distance0 is a function to make the judge if the distance is OK for the test_colour and catch the object.
}

//usage:	left_area_filter to sort the objects in left area.
//			the start point is the original area----home,and the direction of the robot is opposite to origin.
//version:	1.0 edit by chen on 8/13/2014.
void left_area_filter()
{
	turn_degree(90);
	while(!is_storage())
		track_thick_round();
	catch_obj();
	res0=test_colour0();
	if(GREEN==res0)
		track_routine0(-90,135);
	else
		if(WHITE==res0)
			track_routine0(-45,90);
		else
			if(RED==res0)
				track_routine0(0,45);
			else
				if(BLACK==res0)
					track_routine0(45,0);
				else
					if(BLUE==res0)
						track_routine0(90,-45);

	move_level0();
	move_further();
	catch_obj();
	res1=test_colour0();
	if(GREEN==res1)
		track_routine1(-135,135);
	else
		if(WHITE==res1)
			track_routine1(-90,90);
		else
			if(RED==res1)
				track_routine1(-45,45);
			else
				if(BLACK==res1)
					track_routine1(0,0);
				else
					if(BLUE==res1)
						track_routine1(45,-45);


	move_level0();
	move_further();
	catch_obj();
	res2=test_colour0();

	if(GREEN==res2)
		track_routine1(-135,135);
	else
		if(WHITE==res2)
			track_routine1(-90,90);
		else
			if(RED==res2)
				track_routine1(-45,45);
			else
				if(BLACK==res2)
					track_routine1(0,0);
				else
					if(BLUE==res2)
						track_routine1(45,-45);

	move_level0();
	move_further();
	catch_obj();
	res3=test_colour0();

	if(GREEN==res3)
		track_routine1(-135,135);
	else
		if(WHITE==res3)
			track_routine1(-90,90);
		else
			if(RED==res3)
				track_routine1(-45,45);
			else
				if(BLACK==res3)
					track_routine1(0,0);
				else
					if(BLUE==res3)
						track_routine1(45,-45);

	move_level0();
	move_further();
	catch_obj();
	res4=test_colour0();

	if(GREEN==res4)
		track_routine1(-135,135);
	else
		if(WHITE==res4)
			track_routine1(-90,90);
		else
			if(RED==res4)
				track_routine1(-45,45);
			else
				if(BLACK==res4)
					track_routine1(0,0);
				else
					if(BLUE==res4)
						track_routine1(45,-45);
}

//usage:	right_area_filter to sort the objects in right area.
//			the start point is the center of the platform,and the direction of the robot is opposite to the left storage.
//version:	1.0 edit by chen on 8/13/2014.
void right_area_filter()
{
	move_level0();
	move_further();
	catch_obj();
	res0=test_colour0();
	if(GREEN==res0)
		track_routine2(-45,45);
	else
		if(WHITE==res0)
			track_routine2(0,0);
		else
			if(RED==res0)
				track_routine2(45,-45);
			else
				if(BLACK==res0)
					track_routine2(90,-90);
				else
					if(BLUE==res0)
						track_routine2(135,-135);										  

	move_level0();
	move_further();
	catch_obj();
	res1=test_colour0();
	if(GREEN==res1)
		track_routine2(-45,45);
	else
		if(WHITE==res1)
			track_routine2(0,0);
		else
			if(RED==res1)
				track_routine2(45,-45);
			else
				if(BLACK==res1)
					track_routine2(90,-90);
				else
					if(BLUE==res1)
						track_routine2(135,-135);

	move_level0();
	move_further();
	catch_obj();
	res2=test_colour0();
	if(GREEN==res2)
		track_routine2(-45,45);
	else
		if(WHITE==res2)
			track_routine2(0,0);
		else
			if(RED==res2)
				track_routine2(45,-45);
			else
				if(BLACK==res2)
					track_routine2(90,-90);
				else
					if(BLUE==res2)
						track_routine2(135,-135);

	move_level0();
	move_further();
	catch_obj();
	res3=test_colour0();
	if(GREEN==res3)
		track_routine2(-45,45);
	else
		if(WHITE==res3)
			track_routine2(0,0);
		else
			if(RED==res3)
				track_routine2(45,-45);
			else
				if(BLACK==res3)
					track_routine2(90,-90);
				else
					if(BLUE==res3)
						track_routine2(135,-135);

	move_level0();
	move_further();
	catch_obj();
	res4=test_colour0();
	if(GREEN==res4)
		track_routine2(-45,45);
	else
		if(WHITE==res4)
			track_routine2(0,0);
		else
			if(RED==res4)
				track_routine2(45,-45);
			else
				if(BLACK==res4)
					track_routine2(90,-90);
				else
					if(BLUE==res4)
						track_routine2(135,-135);
}

//usage:		the purpose of this function is minish the code size.
//feature:		the regular route can be summary to a function instead code retype.
//parameter:	radian0 is a signed char to deliver the value of the procedure one degree the robot will rotate in the center of platform.
//				radian1 is a signed char to deliver the value of the procedure one degree the robot will rotate in the center of platform.
//				procedure one:		place the object of the robot just catch.
//				procedure two:		make the attempt of back to the storage.
//version:		1.0 by chen on 13/8/2014.
void track_routine0(signed char radian0,signed char radian1)
{
	turn_degree(-180);
	while(!is_storage())
		track_thick_round();
	turn_degree(-90);
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

//usage:	similar to the function track_routine0.do not repeat any more.
void track_routine1(signed char radian0,signed char radian1)
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

//usage:	similar to the function track_routine0,do not repeat any more.
void track_routine2(signed char radian0,signed char radian1)
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