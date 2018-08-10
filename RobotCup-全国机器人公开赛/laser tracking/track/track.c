/*
**作	者：韦荣伟
**日	期：2014-3-28
**说	明：
**1		  ：调用.lib文件函数说明
**			u8 AnalogIn(u8 channel)	 获取模拟口通道值，参数为通道数；返回模拟值
**			u16 DigitalIn(u8 channel) 获取数字口通道值，参数为通道数；返回数字值，0或1	
**
**2		  ：控制器与传感器的连接（前为控制器后为传感器）
**			循迹传感器：	前：A0---A1   A1---A2   A2---A3
**								A3---A4   A4---A5   A5---A6   前瞻：A6---A0
**			循迹传感器：	后：A7---A1   A8---A2   A9---A3
**								A10--A4   A11--A5   A12--A6   前瞻：A13---A0
**			红外避障  ：	前：D20			后：D21
**			前瞻激光  ：	左：D22			右：D23
**			后瞻激光  ：	左：D24			右：D25
*/
#include "track.h"
//#include  <math.h>    //Keil library  
//#include  <stdio.h>   //Keil library

unsigned char back = 85;



/*
**函数功能：模拟通道值转数字值
**参	数：channel-----模拟通道
**			num1--------模拟下限值
**			num2--------模拟上限值
*/
u8 An_to_Di(u8 channel,u16 num1,u16 num2)
{
	u8 ret = 1;
	if((AnalogIn(channel) > num1)&&(AnalogIn(channel) < num2))	
	{
		ret = 0;
	}
	else
	{
		ret = 1;
	}
	
	return ret;	
}

/*
**函数功能：电机控制函数
**参	数:	Dx---代表电机x
**			DPx--代表对应电机PWM占空比 
*/
void DMotor_Control(u8 D1,s8 DP1,u8 D2,s8 DP2,u8 D3,s8 DP3,u8 D4,s8 DP4)
{
	DMotor(D1,DP1);
	DMotor(D2,DP2);
	DMotor(D3,DP3);
	DMotor(D4,DP4);
}

/*
**函数功能：电机双列并行控制
**参	数: left-----小车左边电机
**			right----小车右边电机
*/

void DMotor_Control_Par(s8 left,s8 right)
{
	DMotor_Control(1,left,2,left,3,-right,4,-right);
}								  

/*
**函数功能：直线前进单循迹	
**传感器：采集模拟值
**控制板接口：A0~A5
**			  A6为前测距通道
*/

void Track_steep_line(void)
{
	if((An_to_Di(2,1200,1600)==0)&&(An_to_Di(3,1200,1600) == 0))
	{
		DMotor_Control_Par(75,80);			   //(85,90)  	  (75,80)		(86,88)
	}										   
	else if(An_to_Di(2,1600,2700) == 0)
	{
		DMotor_Control_Par (75,82);				 //(85,95)	   (75,82)			  (86,89)
	}
	else if(An_to_Di(3,1600,2700) == 0)
	{
		DMotor_Control_Par (77,80);				    //(83,88)	 (77,80)		   (87,88)
	}
	else if(An_to_Di(1,1600,2500) == 0)
	{
		DMotor_Control_Par (75,83);				    //(82,90)	  (75,83)		   (86,90)
	}
	else if(An_to_Di(4,1600,2700) == 0)
	{
		DMotor_Control_Par(79,80);					  //(88,90)		(79,80)		 (88,88)
	}
}

/*
**函数功能：直线单向前进中速循迹
*/				 
void Track_steep_Moderato(void)
{
		if((An_to_Di(2,1000,1600)==0)&&(An_to_Di(3,1000,1600) == 0))
		{
		  DMotor_Control_Par(46,50);		      //46,50
		}
		else if(An_to_Di(2,1500,2700) == 0)   
		{
			DMotor_Control_Par(45,52);					//46,52
		}
		else if(An_to_Di(3,1500,2900) == 0)
		{
			DMotor_Control_Par(48,49);					//48,50
		}
		else if(An_to_Di(1,1400,2700) == 0)
		{
			DMotor_Control_Par(44,53);					//46,54
		}
		else if(An_to_Di(4,1400,2800) == 0)
		{
			DMotor_Control_Par(49,48);					//50,50
		}										   
		else if(An_to_Di(0,1200,2200) == 0)
		{
			DMotor_Control_Par(43,55);					//45,54
		} 
		else if(An_to_Di(5,1200,2300) == 0)
		{
			DMotor_Control_Par(51,47);					//50,49
		} 
}  
 /*
void Track_steep_Moderato(void)
{
		if((An_to_Di(2,1000,2000)==0)&&(An_to_Di(3,1000,2000) == 0))
		{
		  DMotor_Control_Par(60,62);		      //46,50
		}
		else if(An_to_Di(2,1600,3000) == 0)   
		{
			DMotor_Control_Par(60,65);					//46,52
		}
		else if(An_to_Di(3,1600,3000) == 0)
		{
			DMotor_Control_Par(62,62);					//48,50
		}
		else if(An_to_Di(1,1300,3000) == 0)
		{
			DMotor_Control_Par(58,65);					//46,54
		}
		else if(An_to_Di(4,1300,3000) == 0)
		{
			DMotor_Control_Par(62,59);					//50,50
		}
		else if(An_to_Di(0,1000,3000) == 0)
		{
			DMotor_Control_Par(59,67);					//45,54
		} 
		else if(An_to_Di(5,1000,3000) == 0)
		{
			DMotor_Control_Par(64,61);					//50,49
		} 
}  */

/*
**函数功能：直线单向前进慢速循迹
*/
void Track_steep_low(void)
{
	if((An_to_Di(2,1200,1600)==0)&&(An_to_Di(3,1200,1600) == 0))
	{
		DMotor_Control_Par(30,33);		
	}
	else if(An_to_Di(2,1600,2700) == 0)
	{
		DMotor_Control_Par(30,35);
	}
	else if(An_to_Di(3,1600,2700) == 0)
	{
		DMotor_Control_Par(30,30);
	}
	else if(An_to_Di(1,1500,2800) == 0)
	{
		DMotor_Control_Par(29,36);
	}
	else if(An_to_Di(4,1500,2800) == 0)
	{
		DMotor_Control_Par(35,32);
	}
	else if(An_to_Di(0,1400,2200) == 0)
	{
		DMotor_Control_Par(28,40);
	} 
	else if(An_to_Di(5,1200,2000) == 0)
	{
		DMotor_Control_Par(42,31);
	} 
}

/*
**函数功能：直线后退快速单循迹
传感器：采集模拟值
**控制板接口：A7~A12
**			  A13为前测距通道
*/
void Track_steep_turn(void)
{
	if((An_to_Di(9,1500,2000)==0)&&(An_to_Di(10,1500,2000) == 0))
	{
		DMotor_Control_Par(-81,-90);		
	}						 
	else if(An_to_Di(9,2000,2700) == 0)
	{
		DMotor_Control_Par(-84,-87);
	}
	else if(An_to_Di(10,2000,2700) == 0)
	{
		DMotor_Control_Par(-78,-93);
	}
	else if(An_to_Di(8,1700,2700) == 0)
	{
		DMotor_Control_Par(-85,-86);
	}
	else if(An_to_Di(11,1800,2400) == 0)
	{
		DMotor_Control_Par(-77,-94);
	}
	else if(An_to_Di(7,1500,2200) == 0)
	{
		DMotor_Control_Par(-85,-84);
	} 
	else if(An_to_Di(12,1800,2700) == 0)
	{
		DMotor_Control_Par(-75,-94);
	}
}

/*
**函数功能：直线后退中速单循迹	
传感器：采集模拟值
**控制板接口：A7~A12
**			  A13为前测距通道
*//*
void Track_steep_turn_Moderato(void)
{
	if((An_to_Di(9,1200,1500)==0)&&(An_to_Di(10,1200,1500) == 0))
	{
		DMotor_Control_Par(-50,-55);		
	}						 
	else if(An_to_Di(9,1500,2700) == 0)
	{
		DMotor_Control_Par(-52,-54);
	}
	else if(An_to_Di(10,1500,2700) == 0)
	{
		DMotor_Control_Par(-49,-57);
	}
	else if(An_to_Di(8,1600,2800) == 0)
	{
		DMotor_Control_Par(-52,-52);
	}
	else if(An_to_Di(11,1800,2400) == 0)
	{
		DMotor_Control_Par(-47,-56);
	}
	else if(An_to_Di(7,1400,2200) == 0)
	{
		DMotor_Control_Par(-58,-51);
	} 
	else if(An_to_Di(12,1200,2700) == 0)
	{
		DMotor_Control_Par(-46,-58);
	}
}	  */

void Track_steep_turn_Moderato(void)
{  
	#define monixia 100
	#define monishang 900

	if((An_to_Di(2,monixia,monishang)==1)&&(An_to_Di(3,monixia,monishang) == 1)&&(An_to_Di(9,monixia,monishang)==1)&&(An_to_Di(10,monixia,monishang)==1))
	{
		DMotor_Control_Par(-60,-64);		 
	}
	else if(An_to_Di(9,monixia,monishang) == 1)
	{
		DMotor_Control_Par(-61,-63);			  
		while((An_to_Di(9,monixia,monishang)==1)&&(An_to_Di(10,monixia,monishang) == 1))
		{
			if(An_to_Di(2,monixia,monishang) == 1)
			DMotor_Control_Par(-61,-63);
			else if((An_to_Di(3,monixia,monishang) == 1))
			DMotor_Control_Par(-59,-65);
			else if((An_to_Di(1,monixia,monishang) == 1))
			DMotor_Control_Par(-62,-62);
			else if((An_to_Di(4,monixia,monishang) == 1))
			DMotor_Control_Par(-58,-66);
			else if((An_to_Di(0,monixia,monishang) == 1))
			DMotor_Control_Par(-62,-62);
			else if((An_to_Di(5,monixia,monishang) == 1))
			DMotor_Control_Par(-58,-66);
		}		 				 		
	}
	else if(An_to_Di(10,monixia,monishang) == 1)
	{
		DMotor_Control_Par(-59,-65);			
		while((An_to_Di(9,monixia,monishang)==1)&&(An_to_Di(10,monixia,monishang) == 1))
		{
			if(An_to_Di(2,monixia,monishang) == 1)
			DMotor_Control_Par(-61,-63);
			else if((An_to_Di(3,monixia,monishang) == 1))
			DMotor_Control_Par(-59,-65);
			else if((An_to_Di(1,monixia,monishang) == 1))
			DMotor_Control_Par(-62,-62);
			else if((An_to_Di(4,monixia,monishang) == 1))
			DMotor_Control_Par(-58,-66);
			else if((An_to_Di(0,monixia,monishang) == 1))
			DMotor_Control_Par(-62,-62);
			else if((An_to_Di(5,monixia,monishang) == 1))
			DMotor_Control_Par(-58,-66);
		}		 				 		
	}
	else if(An_to_Di(8,monixia,monishang) == 1)		 
	{
		DMotor_Control_Par(-62,-64);		  
	}
	else if(An_to_Di(11,monixia,monishang) == 1)
	{
		DMotor_Control_Par(-58,-66);		
	}  
	else if(An_to_Di(7,monixia,monishang) == 1)
	{
		DMotor_Control_Par(-62,-64);	   
	} 
	else if(An_to_Di(12,monixia,monishang) == 1)
	{
		DMotor_Control_Par(-58,-66);			
	}
}

/*
**函数功能：直线后退慢速单循迹
*/
void Track_steep_turn_low(void)
{
	if((An_to_Di(9,1200,1900)==0)&&(An_to_Di(10,1200,1900) == 0))	  //(9,1500,2000)  (10,1500,2000)
	{
		DMotor_Control_Par(-30,-30);		//	 (-33,-30)
	}
	else if(An_to_Di(9,1900,2700) == 0)		// (9,2000,2700)
	{
		DMotor_Control_Par(-32,-28);	  //(-35,-30)
	}
	else if(An_to_Di(10,1900,2700) == 0)	//(10,1500,2700)
	{
		DMotor_Control_Par(-28,-32);		// (-30,-30)
	}
	else if(An_to_Di(8,1800,2500) == 0)	//	(8,1500,2500) 
	{
		DMotor_Control_Par(-35,-25);	//	  (-36,-29)
	}
	else if(An_to_Di(11,1900,2700) == 0)	 //  (11,1800,2700) 
	{
		DMotor_Control_Par(-25,-35);
	} 
}

/*
**函数功能：指南针走直线
**参数说明：num--- 行驶速度选择	   back--选择正反行驶
**			floor---指南针下限值	 
**			upper_limit---指南针上限值
**参数取值：
**			num == 0, 稍快
**			num == 1, 稍慢
**			floor--->0~3600	 
**			upper_limit--->0~3600
**					floor			upper_limit
**去钓鱼岛：快速--->2800			2950
**			慢速--->2840			2900
**从钓鱼岛：快速--->2790			2970
**回	来：慢速--->2790			2970
*/
void Track_steep_cmp(unsigned char num,unsigned int floor,unsigned int upper_limit)
{
	if(back == 85)
	{
		if(num == 0)
		{
			if((read_cmp()> floor)&&(read_cmp()<upper_limit))
			{
				DMotor_Control_Par(18,22);
			}
			else if(read_cmp() < floor)   //1560
			{
				DMotor_Control_Par(18,10);
			}
			else if(read_cmp()> upper_limit)
			{
				DMotor_Control_Par(10,22);
			}
		}
		else if(num == 1)
		{
			if((read_cmp()> floor)&&(read_cmp()<upper_limit))
			{
				DMotor_Control_Par(10,13);	//10,12
			}
			else if(read_cmp()< floor)   //1560
			{
				DMotor_Control_Par(10,7);  //10,5
			}
			else if(read_cmp()>upper_limit)
			{
				DMotor_Control_Par(5,10);  //5,12
			}
		}
		
	}
	else
	{
		if(num == 0)
		{
			if((read_cmp()> floor)&&(read_cmp()<upper_limit))
			{
				DMotor_Control_Par(-18,-20);
			}
			else if(read_cmp()< floor)   //1560
			{
				DMotor_Control_Par(-10,-18);
			}
			else if(read_cmp()>upper_limit)
			{
				DMotor_Control_Par(-20,-10);
			}
		}
		else if(num == 1)
		{
			if((read_cmp()> floor)&&(read_cmp()<upper_limit))
			{
				DMotor_Control_Par(-10,-12);
			}
			else if(read_cmp()< floor)   //1560
			{
				DMotor_Control_Par(-5,-10);
			}
			else if(read_cmp()>upper_limit)
			{
				DMotor_Control_Par(-12,-5);
			}
		}
	}
	
}

/*
**函数功能：直线单向前进中慢速循迹
*/				 
void Track_steep_Moderato_low(void)
{
		if((An_to_Di(2,1000,1600)==0)&&(An_to_Di(3,1000,1600) == 0))
		{
		  DMotor_Control_Par(46,50);		      //46,50
		}
		else if(An_to_Di(2,1500,2700) == 0)   
		{
			DMotor_Control_Par(45,52);					//46,52
		}
		else if(An_to_Di(3,1500,2900) == 0)
		{
			DMotor_Control_Par(48,49);					//48,50
		}
		else if(An_to_Di(1,1400,2700) == 0)
		{
			DMotor_Control_Par(44,53);					//46,54
		}
		else if(An_to_Di(4,1400,2800) == 0)
		{
			DMotor_Control_Par(49,48);					//50,50
		}										   
		else if(An_to_Di(0,1200,2200) == 0)
		{
			DMotor_Control_Par(43,55);					//45,54
		} 
		else if(An_to_Di(5,1200,2300) == 0)
		{
			DMotor_Control_Par(51,47);					//50,49
		} 
} 

/*
**函数功能：直线后退中慢速单循迹	
传感器：采集模拟值
**控制板接口：A7~A12
**			  A13为前测距通道
*/
void Track_steep_turn_Moderato_low(void)
{
	if((An_to_Di(9,1200,1500)==0)&&(An_to_Di(10,1200,1500) == 0))
	{
		DMotor_Control_Par(-50,-55);		
	}						 
	else if(An_to_Di(9,1500,2700) == 0)
	{
		DMotor_Control_Par(-52,-54);
	}
	else if(An_to_Di(10,1500,2700) == 0)
	{
		DMotor_Control_Par(-49,-57);
	}
	else if(An_to_Di(8,1600,2800) == 0)
	{
		DMotor_Control_Par(-52,-52);
	}
	else if(An_to_Di(11,1800,2400) == 0)
	{
		DMotor_Control_Par(-47,-56);
	}
	else if(An_to_Di(7,1400,2200) == 0)
	{
		DMotor_Control_Par(-58,-51);
	} 
	else if(An_to_Di(12,1200,2700) == 0)
	{
		DMotor_Control_Par(-46,-58);
	}
} 

/*
**函数功能：波浪线循迹
**参	数：direction == 0		前灰度循迹
**			direction == 1		后灰度循迹
*/				 
void Track_steep_WavyLine(unsigned char direction)
{  
    #define	monixia	  100
    #define	monishang  900

	if(0 == direction)
	{ 	  
		if((An_to_Di(2,monixia,monishang)==1)&&(An_to_Di(3,monixia,monishang) == 1))
		{
			DMotor_Control_Par(30,35);		 //30,35 	
		}
		else if(An_to_Di(2,monixia,monishang) == 1)
		{
			DMotor_Control_Par(23,42);		//	23,41
		}
		else if(An_to_Di(3,monixia,monishang) == 1)
		{
			DMotor_Control_Par(37,28);		// 36,28
		}
		else if(An_to_Di(1,monixia,monishang) == 1)
		{
			DMotor_Control_Par(20,45);		 //23,42
		}
		else if(An_to_Di(4,monixia,monishang) == 1)
		{									
			DMotor_Control_Par(37,28);	   //  36,28   (37,28)
		}
		else if(An_to_Di(0,monixia,monishang) == 1)
		{
			DMotor_Control_Par(19,48);	 //	23,48
		} 
		else if(An_to_Di(5,monixia,monishang) == 1)
		{
			DMotor_Control_Par(48,19);	 //36,28
		} 
	} 
	else if(1 == direction)
	{ 		  
		if((An_to_Di(9,monixia,monishang)==1)&&(An_to_Di(10,monixia,monishang) == 1))
		{
			DMotor_Control_Par(-35,-30);		 // 30,35 	
		}
		else if(An_to_Di(9,monixia,monishang) == 1)
		{
			DMotor_Control_Par(-42,-23);		//	 (23,42)
		}
		else if(An_to_Di(10,monixia,monishang) == 1)
		{
			DMotor_Control_Par(-28,-36);		// 36,28
		}
		else if(An_to_Di(8,monixia,monishang) == 1)
		{
			DMotor_Control_Par(-20,-45);		 //20,45
		}
		else if(An_to_Di(11,monixia,monishang) == 1)
		{									
			DMotor_Control_Par(-28,-37);	   //    (37,28)
		}
		else if(An_to_Di(7,monixia,monishang) == 1)
		{
			DMotor_Control_Par(-48,-19);	 //	(19,48)
		} 
		else if(An_to_Di(12,monixia,monishang) == 1)
		{
			DMotor_Control_Par(-19,-48);	 //(49 ,19)
		} 
	}
}


/*
**函数功能：走大圆
**参	数：direction----行驶方向选择
**参数取值：direction == 0	顺时针行驶
**			direction == 1	逆时针行驶 
*/
void Track_round(unsigned char direction)
{
	if(0 == direction)
	{ 
			if((An_to_Di(2,monixia,monishang)==1)&&(An_to_Di(3,monixia,monishang) == 1))
			{
				DMotor_Control_Par(33,30);		
			}
			else if(An_to_Di(2,monixia,monishang)==1)
			{
				DMotor_Control_Par(33,32);
			}
			else if(An_to_Di(3,monixia,monishang)==1)
			{
				DMotor_Control_Par(36,27);
			}
			else if(An_to_Di(1,monixia,monishang)==1)
			{
				DMotor_Control_Par(37,30);
			}
			else if(An_to_Di(4,monixia,monishang)==1)
			{
				DMotor_Control_Par(36,26);
			}
//			else if(An_to_Di(0,monixia,monishang)==1)
//			{
//				DMotor_Control_Par(32,36);
//			} 
			else if(An_to_Di(5,monixia,monishang)==1)
			{
				DMotor_Control_Par(37,25);
			} 
	}
	if(1 == direction)
	{ 
				if((An_to_Di(2,monixia,monishang)==1)&&(An_to_Di(3,monixia,monishang) == 1))
			{
				DMotor_Control_Par(30,35);		
			}
			else if(An_to_Di(2,monixia,monishang)==1)
			{
				DMotor_Control_Par(30,36);
			}
			else if(An_to_Di(3,monixia,monishang)==1)
			{
				DMotor_Control_Par(30,34);
			}
			else if(An_to_Di(1,monixia,monishang)==1)
			{
				DMotor_Control_Par(30,37);
			}
			else if(An_to_Di(4,monixia,monishang)==1)
			{
				DMotor_Control_Par(35,33);
			}
			else if(An_to_Di(0,monixia,monishang)==1)
			{
				DMotor_Control_Par(30,38);
			} 
			else if(An_to_Di(5,monixia,monishang)==1)
			{
				DMotor_Control_Par(30,32);
			} 
	}
}


/*
**函数功能：走直线
**参数说明：back---选择行使参数标志	 speed---速度选择
**参数取值：back==85时---正走 ；否则反走
**			speed==0---快速
**			speed==1---中速
**			speed==2---慢速
*/
void Track_straight_line(unsigned char speed)
{
	if( back == 85)
	{
		if(0 == speed)
		{ 
			Track_steep_line();
		}
		
		if(1 == speed)
		{ 
			Track_steep_Moderato();
		}
		
		if(2 == speed)
		{ 
			Track_steep_low();
		}				
	}
	else 
	{
		if(0 == speed)
		{
			Track_steep_turn();
		}

		if(1 == speed)
		{
			Track_steep_turn_Moderato();
		}

		if(2 == speed)
		{
			Track_steep_turn_low();
		}
	}
}


/*
**函数功能：左转弯
**参	数：angle---左转度数
**			参数取值：angle == 90	十字路口左转
**					  angle == 45	45度左转
**					  angle == 30	30度左转
**					  angle == 30	180度左转
**					  num == 0		前灰度检查
**					  num == 1		后灰度检查 
**接口：	D18---左边单通道灰度传感器
**			D19---右边单通道灰度传感器
*/
void Track_wheel_left(unsigned char num,unsigned char angle)
{
	if(num == 0)
	{
		if(90 == angle)
		{
			DMotor_Control_Par(-45,45);
			delay_ms(8);
			while(An_to_Di(0,800,2700));		//750
			DMotor_Control_Par(-30,30);
			while(An_to_Di(1,1400,2700));		//750
			DMotor_Control_Par(-10,10);
			while(An_to_Di(2,1400,2700));		//750
			DMotor_Control_Par(0,0);
			DMotor_Control_Par(50,-50);
			DMotor_Control_Par(0,0); 
			delay_ms(10);
		}

		if(30 == angle)
		{
			DMotor_Control_Par(-30,34);
			delay_ms(50);
			while(An_to_Di(0,1000,2700));		//750
			DMotor_Control_Par(-15,15);
			while(An_to_Di(1,1000,2700));		//750
			while(An_to_Di(2,1000,2700));		//750
			DMotor_Control_Par(0,0);
			delay_ms(10);		
		}

		if(angle == 45)
		{
			DMotor_Control(1,-45,2,-30,3,45,4,30);
			delay_ms(10);
			while(An_to_Di(0,1000,2700));		//750
			while(An_to_Di(1,1000,2700));		//750
//			while(An_to_Di(2,1000,2700));		//750
			DMotor_Control_Par(0,0);
			delay_ms(10);
		}
	}
	else if(num == 1)
	{
	}
}

/*
**函数功能：180度左转
*/
void Track_wheel_left180(void)
{
/*	DMotor_Control_Par(-50,50);	
	delay_ms(430);
	DMotor_Control_Par(0,0);  */

	DMotor_Control_Par(-100,100);	
	delay_ms(230);
	DMotor_Control_Par(0,0); 
}

/*
**函数功能：右直角转弯
**参	数：angle---左转度数	  num---转时前灰度检查还是后灰度检查
**			参数取值：angle == 90	90度右转
**					  angle == 45	45度右转
**					  angle == 30	30度右转
**					  num == 0		前灰度检查
**					  num == 1		后灰度检查 
**接口：	D18---左边单通道灰度传感器
**			D19---右边单通道灰度传感器
*/	
void Track_wheel_right(unsigned char num,unsigned char angle)
{
	if(num == 0)
	{
		if(90 == angle)
		{
			DMotor_Control_Par(45,-45);
			delay_ms(8);
			while(An_to_Di(5,1000,2700));
			DMotor_Control_Par(30,-30);
			while(An_to_Di(4,1400,2700));
			while(An_to_Di(3,1400,2700));
	//		while(An_to_Di(2,1400,2700));
			DMotor_Control_Par(0,0);
			DMotor_Control_Par(-50,50);
			DMotor_Control_Par(0,0);
			delay_ms(10);
		}
	
		if(angle == 30)
		{
//			DMotor_Control_Par(30,-34);
			DMotor_Control(1,20,2,30,3,-20,4,-32);
			delay_ms(50);
			while(An_to_Di(5,1000,2700));		//750
//			DMotor_Control_Par(15,-15);
			while(An_to_Di(4,1450,2700));		//750
			while(An_to_Di(3,1450,2700));		//750
			DMotor_Control_Par(0,0);
			delay_ms(10);
		}
	}
	else if(num == 1)
	{
		if(90 == angle)
		{
			DMotor_Control_Par(45,-45);
			delay_ms(8);
			while(An_to_Di(12,1000,2700));
			DMotor_Control_Par(30,-30);
			while(An_to_Di(11,1400,2700));
			while(An_to_Di(10,1400,2700));
	//		while(An_to_Di(9,1400,2700));
			DMotor_Control_Par(0,0);
			DMotor_Control_Par(-50,50);
			DMotor_Control_Par(0,0);
			delay_ms(10);
		}

		if(angle == 30)
		{
			DMotor_Control_Par(30,-34);
			delay_ms(50);
			while(An_to_Di(9,1000,2700));		//750
			DMotor_Control_Par(15,-15);
			while(An_to_Di(10,1000,2700));		//750
			while(An_to_Di(11,1000,2700));		//750
			DMotor_Control_Par(0,0);
			delay_ms(10);
		}

		if(angle == 45)
		{
			DMotor_Control(1,45,2,30,3,-45,4,-30);
			delay_ms(10);
			while(An_to_Di(12,1000,2700));		//750
			while(An_to_Di(11,1000,2700));		//750
//			while(An_to_Di(10,1000,2700));		//750
			DMotor_Control_Par(0,0);
			delay_ms(10);
		}
	}
}

/*
**函数功能：判断识别路口
**参数说明：back --- 选择行使参数标志
**			view --- 第enn个路口标示
**参数取值：back == 85时 --- 正走 ；否则反走
**			view >= 1
*/
int my_intersection(int view)
{
	#define FRONT_Value_MIN 1700
	#define LATER_Value_MIN 1450
	int f1,f2,f3,f4,f5,f6;
	
	f1=f2=f3=f4=f5=f6=0;
	/*判断小车行使状态---前进/后退*/
	if(back == 85)
	{
		if(An_to_Di(0,1400,2700) == 0)					f1 = 1;
		if(An_to_Di(1,FRONT_Value_MIN,2700) == 0)		f2 = 1;
		if(An_to_Di(2,FRONT_Value_MIN,2700) == 0)		f3 = 1;
		if(An_to_Di(3,FRONT_Value_MIN,2700) == 0)		f4 = 1;
		if(An_to_Di(4,FRONT_Value_MIN,2700) == 0)		f5 = 1;
		if(An_to_Di(5,1400,2700) == 0)					f6 = 1;
	}
	else
	{
		if(An_to_Di(7,LATER_Value_MIN,2700)  == 0)	f1 = 1;
		if(An_to_Di(8,LATER_Value_MIN,2700) == 0)	f2 = 1;
		if(An_to_Di(9,LATER_Value_MIN,2700) == 0)	f3 = 1;
		if(An_to_Di(10,LATER_Value_MIN,2700) == 0)	f4 = 1;
		if(An_to_Di(11,LATER_Value_MIN,2700) == 0)	f5 = 1;
		if(An_to_Di(12,LATER_Value_MIN,2700) == 0)	f6 = 1;
	}

	if(((f1==1)&&(f2==1))
	||((f1==1)&&(f2==1)&&(f3==1))
	||((f1==1)&&(f2==1)&&(f3==1)&&(f4==1))
	||((f1==1)&&(f2==1)&&(f3==1)&&(f4==1)&&(f5==1))
	||((f1==1)&&(f2==1)&&(f3==1)&&(f4==1)&&(f5==1)&&(f6==1))
	||((f2==1)&&(f3==1)&&(f4==1)&&(f5==1)&&(f6==1))
	||((f3==1)&&(f4==1)&&(f5==1)&&(f6==1))
	||((f4==1)&&(f5==1)&&(f6==1))
	||((f5==1)&&(f6==1)))
		view++;

	f1=f2=f3=f4=f5=f6=0;

	return view;
}  

/*
**函数功能：路口停止
**参数说明：back---选择行使参数标志
**			r1-----单通道灰度检测标志
**参数取值：back == 85时---正走；否则反走
**			r1 == 45时---左右两边的灰度都检测到
**			r1 == 4 时---左边灰度检测到
**			r1 == 5 时---右边灰度检测到
*/ 
void mid_stop(int r1)
{
	int i =1000;
	int r2 = 0;
	int r3 = 0;

	DMotor_Control_Par(0,0);
	delay_us(10);
	/*确定是否找到线*/ 
	while(i--)
	{
		if(D(18) == 0)	r2 = 1;
		if(D(19) == 0)	r3 = 1;		
	}
	/*前进情况*/	
	if(back == 85)
	{		
		if(r1 == 45)
		{
			while(1)
			{
				if(D(18) == 0 && D(19) == 0)
				{
					DMotor_Control_Par(0,0);
//					delay_ms(500);
//					if(D(18) == 0 && D(19) == 0)
//					while(1);
						break;
				}
				else if((D(18) == 0)&&(r3 == 1))
				{
					DMotor_Control_Par(0,-30);	 //0,-30
				}
				else if((D(18) == 0)&&(r3 == 0))
				{
					DMotor_Control_Par(0,30);	//0,30
				}
				else if((D(19) == 0)&&(r2 == 1))
				{
					DMotor_Control_Par(-30,0); //-30,0
				}
				else if((D(19) == 0)&&(r2 == 0))
				{
					DMotor_Control_Par(30,0);	//30,0
				}
				else if((r2 == 1)&&(r3 == 1))
				{
					DMotor_Control_Par(-20,-20);//30,30	
				}
				else if((r2 == 0)&&(r3 == 0))
				{
					LED_ON();
					DMotor_Control_Par(20,20); //30,30
				}
			}
		}
		else if(r1 == 4)
		{
			while(1)
			{
				if(D(18) == 0)
				{
					DMotor_Control_Par(0,0);
					break;
				}
				else if(r2 == 1)
				{
					DMotor_Control_Par(-40,-40);
				}
				else if(r2 == 0)
					DMotor_Control_Par(40,40);
			}
		}
		else if(r1 == 5)
		{
			while(1)
			{
				if(D(19) == 0)
				{
					DMotor_Control_Par(0,0);
					break;
				}
				else if(r3 == 1)
				{
					DMotor_Control_Par(-30,-30);
				}
				else if(r3 == 0)
					DMotor_Control_Par(10,10);	
			}
		}	
	}
	else 		  /*后退情况*/ 
	{
		if(r1 == 45)
		{
			while(1)
			{
				if(D(18) == 0 && D(19) == 0)
				{
					DMotor_Control_Par(0,0);
					break;
				}
				else if((D(18) == 0)&&(r3 == 1))
				{
					DMotor_Control_Par(0,30);
				}
				else if((D(18) == 0)&&(r3 == 0))
				{
					DMotor_Control_Par(0,-30);
				}
				else if((D(19) == 0)&&(r2 == 1))
				{
					DMotor_Control_Par(30,0);
				}
				else if((D(19) == 0)&&(r2 == 0))
				{
					DMotor_Control_Par(-30,0);
				}
				else if((r2 == 1)&&(r3 == 1))
				{
					DMotor_Control_Par(40,40);	
				}
				else if((r2 == 0)&&(r3 == 0))
				{
					DMotor_Control_Par(-40,-40);
				}
			}
		}
		else if(r1 == 4)
		{
			while(1)
			{
				if(D(18) == 0)
				{
					DMotor_Control_Par(0,0);
					break;
				}
				else if(r2 == 1)
				{
					DMotor_Control_Par(40,40);
				}
				else if(r2 == 0)
					DMotor_Control_Par(-40,-40);
			}
		}
		else if(r1 == 5)
		{
			while(1)
			{
				if(D(19) == 0)
				{
					DMotor_Control_Par(0,0);
					break;
				}
				else if(r3 == 1)
				{
					DMotor_Control_Par(40,40);
				}
				else if(r3 == 0)
					DMotor_Control_Par(-40,-40);	
			}
		}
	}

} 

/*
**函数功能：碰撞 (前后红外壁障检测)
**参数说明：back---选择行使参数标志
**参数取值：back==85时---正走 ；否则反走
**返回值  ：无
*/
void Track_crash_ward(void)
{
	if(back == 85)
	{
		while(D(20) != 0)
		{
			Track_straight_line(1);		
		}
		DMotor_Control_Par(0,0);
		BEEP_ON();
		delay_ms(300);
		BEEP_OFF();
		back = ~back;
	}
	else 
	{
		while(D(21) != 0)
		{
			Track_straight_line(1);	
		}
		DMotor_Control_Par(0,0);
		BEEP_ON();
		delay_ms(300);
		BEEP_OFF();
		back = 85;
	}	
}

/*
**函数功能：指南针碰撞景点 (前红外壁障检测)
**参数说明：num--- 行驶速度选择	   back--选择正反行驶
**			floor---指南针下限值	 
**			upper_limit---指南针上限值
**参数取值：
**			num == 0, 稍快
**			num == 1, 稍慢
**			floor--->0~3600	 
**			upper_limit--->0~3600
**返回值  ：无
*/
void Track_cmp_ward(unsigned char num,unsigned int floor,unsigned int upper_limit)
{
	while(D(20) != 0)
	{
		Track_steep_cmp(num,floor,upper_limit);		
	}
	DMotor_Control_Par(0,0);
	BEEP_ON();
	delay_ms(300);
	BEEP_OFF();
}

/*
**函数功能：判断小车在障碍物的位置
**参	数：判断选择
**			flag == 0 --> 前灰度判断
**			flag == 1 --> 后灰度判断
**返回	值：返回0时，小车还在障碍物上面
**			返回1时，且flag==0，小车前灰度已经开始离开障碍物
**			返回1时，且flag==1，小车后灰度已经离开障碍物，即小车完全离开障碍物
*/
int Track_JudgeBarrier_Place(int flag)
{
	#define VALUE_Q		1000
	#define VALUE_H		1000
	int ret = 1;
	int f1,f2,f3,f4,f5,f6;
	f1=f2=f3=f4=f5=f6=0;

	if(0 == flag)
	{
		if(An_to_Di(0,VALUE_Q,3000) == 0)		f1 = 1;
		if(An_to_Di(1,VALUE_Q,3000) == 0)		f2 = 1;
		if(An_to_Di(2,VALUE_Q,3000) == 0)		f3 = 1;
		if(An_to_Di(3,VALUE_Q,3000) == 0)		f4 = 1;
		if(An_to_Di(4,VALUE_Q,3000) == 0)		f5 = 1;
		if(An_to_Di(5,VALUE_Q,3000) == 0)		f6 = 1;

		if((f1 == 1)&&(f2 == 1)&&(f3 == 1)&&(f4 == 1)&&(f5 == 1)&&(f6 == 1))
		{
			ret = 0;
		}
	}
	else if(1 == flag)
	{
		if(An_to_Di(7,VALUE_H,3000)  == 0)	f1 = 1;
		if(An_to_Di(8,VALUE_H,3000) == 0)	f2 = 1;
		if(An_to_Di(9,VALUE_H,3000) == 0)	f3 = 1;
		if(An_to_Di(10,VALUE_H,3000) == 0)	f4 = 1;
		if(An_to_Di(11,VALUE_H,3000) == 0)	f5 = 1;
		if(An_to_Di(12,VALUE_H,3000) == 0)	f6 = 1;

		if((f1 == 1)&&(f2 == 1)&&(f3 == 1)&&(f4 == 1)&&(f5 == 1)&&(f6 == 1))
		{
			ret = 0;
		}
	}

	f1=f2=f3=f4=f5=f6=0;

	return ret;
}

/*
**函数功能：过桥函数
**参	数：floor---指南针下限值
**			upper_limit---指南针上限值
*/

void Track_GapBridge(unsigned int floor,unsigned int upper_limit)
{
	if(back == 85)
	{
		while(1)
		{
			Track_straight_line(2);
			
			if((D(22) == 0) || (D(23) == 0))
			{
				BEEP_OFF();
				while(1)
				{
					if(Track_JudgeBarrier_Place(1) == 0)
					{	
						while(1)
						{
							BEEP_ON();
							if(Track_JudgeBarrier_Place(0) == 0)	//还在桥上
							{
								Track_steep_cmp(0,floor,upper_limit);	//去钓鱼岛过桥  稍快	
							}
	
							if(Track_JudgeBarrier_Place(0) == 1)  //前灰度开始离开桥
							{
								Track_steep_cmp(1,floor,upper_limit);	// 去钓鱼岛过桥	稍慢	
							}
	
							if(Track_JudgeBarrier_Place(1) == 1)//小车全部离开桥
							{
								break;
							}
						}
						break;
					}
					else
					{
						Track_steep_cmp(0,floor,upper_limit);	//去钓鱼岛过桥  稍快
					}
				}

				break;
			}	
		}

	}
	else
	{
		while(1)
		{
			Track_straight_line(1);
			
			if((D(24) == 0) || (D(25) == 0))
			{
				BEEP_OFF();
				while(1)
				{
					if(Track_JudgeBarrier_Place(0) == 0)
					{	
						while(1)
						{
							BEEP_ON();
							if(Track_JudgeBarrier_Place(1) == 0) //小车还在桥上
							{
								Track_steep_cmp(0,floor,upper_limit);	//从钓鱼岛回来过桥  稍快	
							}
	
							if(Track_JudgeBarrier_Place(1) == 1)  //后灰度开始离开桥
							{
								Track_steep_cmp(1,floor,upper_limit);	//从钓鱼岛回来过桥	稍慢	
							}
	
							if(Track_JudgeBarrier_Place(0) == 1)//前灰度离开桥，小车完全离开桥
							{
								break;	
							}
						}
						BEEP_OFF();
						break;
					}
					else
					{
						Track_steep_cmp(0,floor,upper_limit);	//从钓鱼岛回来过桥  稍快
					}
				}

				break;
			}	
		}
	}
}

/*
**函数功能：作岔路口检测
**			这个岔路口不能通用检查
**参	数：岔路口选择
**参数取值：flag == 0		从钓鱼岛回来的岔路口
**			flag == 1		珠穆朗玛峰侧面的圆路口
*/
void Fork_road_intersection(unsigned char flag)
{
	#define FRONT_Value_MIN 1700
	#define LATER_Value_MIN 1450
	int f1,f2,f3,f4,f5,f6;

	if(flag == 0)  //从钓鱼岛回来的岔路口
	{
		while(1)
		{
			Track_steep_turn_low();	
			f1=f2=f3=f4=f5=f6=0;

		/*判断小车行使状态---前进/后退*/

			if(An_to_Di(7,LATER_Value_MIN,2700)  == 0)	f1 = 1;
			if(An_to_Di(8,LATER_Value_MIN,2700) == 0)	f2 = 1;
			if(An_to_Di(9,LATER_Value_MIN,2700) == 0)	f3 = 1;
			if(An_to_Di(10,LATER_Value_MIN,2700) == 0)	f4 = 1;
			if(An_to_Di(11,LATER_Value_MIN,2700) == 0)	f5 = 1;
			if(An_to_Di(12,LATER_Value_MIN,2700) == 0)	f6 = 1;
	
			if(((f1==1)&&(f2==1))
			||((f1==1)&&(f2==1)&&(f3==1))
			||((f1==1)&&(f2==1)&&(f3==1)&&(f4==1))
			||((f1==1)&&(f2==1)&&(f3==1)&&(f4==1)&&(f5==1))
			||((f1==1)&&(f2==1)&&(f3==1)&&(f4==1)&&(f5==1)&&(f6==1))
			||((f2==1)&&(f3==1)&&(f4==1)&&(f5==1)&&(f6==1))
			||((f3==1)&&(f4==1)&&(f5==1)&&(f6==1))
			||((f4==1)&&(f5==1)&&(f6==1))
			||((f5==1)&&(f6==1))
	/*		||((f1==1)&&(f3==1))||((f1==1)&&(f4==1))*/)
			{
				break;
			}
				
		}
	}
	else if(flag == 1)//	珠穆朗玛峰侧面的圆路口
	{
		while(1)
		{
			Track_steep_Moderato_low();
			f1=f2=f3=f4=f5=f6=0;

			if(An_to_Di(0,1400,2700) == 0)					f1 = 1;
			if(An_to_Di(1,FRONT_Value_MIN,2700) == 0)		f2 = 1;
			if(An_to_Di(2,FRONT_Value_MIN,2700) == 0)		f3 = 1;
			if(An_to_Di(3,FRONT_Value_MIN,2700) == 0)		f4 = 1;
			if(An_to_Di(4,FRONT_Value_MIN,2700) == 0)		f5 = 1;
			if(An_to_Di(5,1400,2700) == 0)					f6 = 1;

			if(((f1 == 1)&&(f2 == 1))
			||((f1 == 1)&&(f3 == 1))||((f1 == 1)&&(f4 == 1))
			||((f2==1)&&(f3==1))||((f2==1)&&(f3==1)&&(f4 == 1)))
			{
				break;
			}
		}
	}
} 

/*
**函数功能：去低平台景点
**参	数：flag == 0			前进型去低平台景点
**			flag == 1			后退型去低平台景点
*/ 
void Track_Speaicl_BridgeZM_to(unsigned char flag)
{
	if(flag == 0)
	{
		while(1)
		{
			Track_straight_line(1);
	
			if((D(22) == 0)||(D(23) == 0))
			{
				DMotor_Control_Par(0,0);
				while(D(20) != 0)
				{
					DMotor_Control_Par(30,33);
				}
				DMotor_Control_Par(0,0);
				BEEP_ON();
				delay_ms(300);
				BEEP_OFF();
	
				break;
			}
		}

		DMotor_Control_Par(-20,-23);
		delay_ms(100);
		Track_wheel_left180();	//180度左转
	
		while(1)
		{
			DMotor_Control_Par(20,23);
			if(Track_JudgeBarrier_Place(0) == 1)
			{
				while(1)
				{
					Track_steep_low();
	
					if(Track_JudgeBarrier_Place(1) == 1)
					{
						break;
					}
				}
	
				break;
			}
		}
	}
	else if(flag == 1)
	{
		while(1)
		{
			Track_straight_line(1);
	
			if((D(22) == 0)||(D(23) == 0))
			{
				DMotor_Control_Par(0,0);
				while(D(20) != 0)
				{
					DMotor_Control_Par(-30,-33);
				}
				DMotor_Control_Par(0,0);
				BEEP_ON();
				delay_ms(300);
				BEEP_OFF();
	
				break;
			}
		}

		DMotor_Control_Par(20,23);
		delay_ms(100);
		Track_wheel_left180();	//180度左转
	
		while(1)
		{
			DMotor_Control_Par(-20,-23);
			if(Track_JudgeBarrier_Place(1) == 1)
			{
				while(1)
				{
					Track_steep_low();
	
					if(Track_JudgeBarrier_Place(0) == 1)
					{
						break;
					}
				}
	
				break;
			}
		}
	}
}

/*
**函数功能：上太平岛
*/
void Track_Taiping_To(void)
{
	while(1)
	{
		Track_steep_Moderato_low();	//检测到太平岛阶梯前为中慢速行驶

		if((D(22) == 0)||(D(23) == 0))
		{
			while(1)
			{
				DMotor_Control_Par(20,23);

				if((ADXL345(1) < 170) &&(ADXL345(3) > 192))
				{
					break;
				}
			}
			Track_cmp_ward(0,1470,1590);//撞景点

			DMotor_Control_Par(-20,-23); //后退一点，有利于180度转弯
			delay_ms(100);
			Track_wheel_left180();	//180度左转
			while(1)
			{					
				Track_steep_cmp(1,3067,3207);

				if((Track_JudgeBarrier_Place(0) == 1)
				&&((Track_JudgeBarrier_Place(1) == 1)))
				{
					break;
				}
			}
			break;
		}
	}
}

/*
**函数功能：倒退过门槛
*/
void Track_Doorsill_Turn(void)
{
/*	int i = 10;
	while(1)
	{
		Track_steep_turn_Moderato_low();
	
		if((D(24) == 0) && (D(25) == 0))
		{
			BEEP_ON();
			DMotor_Control_Par(-30,-33);
		
			while(i--)
			{
				delay_ms(100);
			}
	
			break;	
		}  
	}
	BEEP_OFF();*/
	while(1)
	{
		Track_steep_turn_Moderato_low();
	
		if((D(24) == 0) && (D(25) == 0))
		{
			BEEP_ON();
			while(1)
			{
				Track_steep_turn_low();
		
				if((ADXL345(1) > 195)&&(ADXL345(3) > 195))
				{
					DMotor_Control_Par(0,0);
					while(1)
					{
						DMotor_Control_Par(-30,-30);
						if((ADXL345(1) < 177)&&(ADXL345(1) > 160)
						&&(ADXL345(3) > 183)&&(ADXL345(3) < 200))
						{
							break;
						}
					} 
					break;
				}
			}
	
			break;	
		}
	}
	BEEP_OFF();	 
}

/*
**函数功能：前进过门槛
**
*/
void Track_Doorsill_line(void)
{
	while(1)
	{
		Track_steep_Moderato_low();

		if((D(22) == 0)&&(D(23) == 0))
		{
			while(1)
			{
				Track_steep_low();
				if((ADXL345(1) < 170)&&(ADXL345(3) > 190))
				{
					while(1)
					{
						DMotor_Control_Par(30,30);
						if((ADXL345(1) > 195)&&(ADXL345(3) > 195))
						{
							break;
						}
					}
					break;
				}
			}
			break;
		}
	}
}

/*
**函数功能：过波浪线门槛
*/
void Track_Doorsill_WavyLine(void)
{
	while(1)
	{
		Track_steep_WavyLine(0);

		if((D(22) == 0)&&(D(23) == 0))
		{
			while(1)
			{
				Track_steep_low();
				if((ADXL345(1) < 170)&&(ADXL345(3) > 190))
				{
					while(1)
					{
						DMotor_Control_Par(30,30);
						if((ADXL345(1) > 195)&&(ADXL345(3) > 195))
						{
							break;
						}
					}
					break;
				}
			}
			break;
		}
	}
}

/*
**函数功能：上珠穆朗玛峰并下来
*/
void Track_Qomolangma_To(void)
{
	//上珠穆朗玛峰
	while(1)
	{
		Track_steep_Moderato_low();
		BEEP_ON();

		if((ADXL345(1) < 172)&&(ADXL345(3) > 190))
		{	
			while(1)
			{
				Track_steep_cmp(0,1500,1750);

//				if((ADXL345(1) < 158)&&(ADXL345(1) > 150)
//				&&(ADXL345(1) > 202)&&(ADXL345(3) < 208))
				if((ADXL345(1) > 172)&&(ADXL345(3) < 190))
				{
					break;
				}
			}
			
			break;
		}
	}
	BEEP_OFF();
/*	while(1)
	{
		DMotor_Control_Par(25,28);
		if((ADXL345(1) < 172)&&(ADXL345(3) > 190))
		{	
			while(1)
			{
				Track_steep_cmp(0,1650,1730);

				if((ADXL345(1) < 158)&&(ADXL345(1) > 150)
				&&(ADXL345(1) > 202)&&(ADXL345(3) < 208))
				{
					break;
				}
			}
			
			break;
		}
	}  */
//	BEEP_ON();
	Track_cmp_ward(0,1430,1520);//撞景点
	DMotor_Control_Par(-20,-23); //后退一点，有利于180度转弯
	delay_ms(100);
	Track_wheel_left180();
	//下珠穆朗玛峰
	//下珠穆朗玛峰
	BEEP_ON();
	while(1)
	{
		Track_steep_cmp(1,3161,3274);

		if((ADXL345(1) > 186)&&(ADXL345(3) > 186))
		{
			while(1)
			{
				Track_steep_cmp(1,3408,3460);  //3523

				if((ADXL345(1) < 186)&&(ADXL345(3) < 186))
				{
					break;
				}
			}
			break;
		}
	}
	//到中间平台调出上面程序
	DMotor_Control_Par(15,18);
	BEEP_OFF();
	while(1)
	{
		if((ADXL345(1) > 186)&&(ADXL345(3) > 186))
		{
			while(1)
			{
				Track_steep_cmp(1,3408,3460);  //3523

				if((Track_JudgeBarrier_Place(0) == 1)
				&&(Track_JudgeBarrier_Place(1) == 1)
				&&(ADXL345(1) < 186)&&(ADXL345(3) < 186))
				{
					break;
				}
			}
			break;
		}
	}	 
}

/*
**函数功能：三轴X-Z轴上下坡
**参数说明：
**			floor---三轴X-Z轴下限值	 
**			upper_limit---三轴X-Z轴上限值
**参数记录：		floor				upper_limit
**上珠	峰：		171						188
**上珠	峰：		171						187
*/
void Track_Triaxial_Uphill(unsigned int floor,unsigned int upper_limit)
{
	while(1)
	{
		if((ADXL345(1) < 170)&&(ADXL345(3) > 190))//上坡
		{
			if((ADXL345(2) < upper_limit)&&(ADXL345(2) > floor))
			{
				DMotor_Control_Par(25,28);
			}
			else if(ADXL345(2) >= upper_limit)
			{
				DMotor_Control_Par(25,20);
			}
			else if(ADXL345(2) <= floor)
			{
				DMotor_Control_Par(20,28);
			}
		}
	}
}





