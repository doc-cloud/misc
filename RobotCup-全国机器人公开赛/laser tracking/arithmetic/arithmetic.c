#include "arithmetic.h"
#include "track.h"
#include "SuperSharkV1.0.h"

extern unsigned char back;

/*
**函数功能：到路口的判断,跑全程
			情况：1---3
**参数说明：back---选择行使参数标志
**			enn ---第enn个路口标示
**参数取值：back==85时---正走 ；否则反走
**			enn >= 1
*/ 
void switch_car(int enn)
{
	int i = 0;

	if(enn == 1)
	{
		DMotor_Control_Par(0,0);
		delay_ms(500);
		mid_stop(5);
		delay_ms(100);
		Track_wheel_right(0,90);
		delay_ms(100);
	}
	else if(enn == 2)
	{
		BEEP_ON();
		DMotor_Control_Par(0,0);
		delay_ms(500);
		mid_stop(45);
		delay_ms(100);
		Track_wheel_left(0,90);
//		while(1);
		delay_ms(100);
	} 
	else if(enn == 3)
	{
		DMotor_Control_Par(0,0);
		delay_ms(300);
		Track_wheel_left(0,30);//前灰度检测左转
		Track_GapBridge(2800,2950);	  //过桥到钓鱼岛
		Track_crash_ward();
		back = 0;
		Track_GapBridge(2790,2790);	  //从钓鱼岛过桥回来
		//过完桥，检测岔路口，不能通用，作特殊处理

		Fork_road_intersection(0);
		
		DMotor_Control_Par(0,0);
		delay_ms(300);
		Track_wheel_right(0,30); //前灰度检测右转
		back = 85;
		i = 2000;
		while(i--)
		{
			Track_steep_low();
		}
		Track_Speaicl_BridgeZM_to(0);// 前往崇明岛完成动作归来
	}
	else if(enn == 4)
	{
		DMotor_Control_Par(0,0);
		delay_ms(100);
		mid_stop(4);
		delay_ms(50);
		Track_wheel_right(1,45);
		back = 0;
		DMotor_Control_Par(-30,-33);
		delay_ms(100); 
		i = 10;
		//过5号门槛
		while(1)
		{
			Track_steep_turn_Moderato_low();
		
			if((D(24) == 0) || (D(25) == 0))
			{
				BEEP_ON();
				DMotor_Control_Par(-30,-33);
			
				while(i--)
				{
					delay_ms(1000);
				}
		
				break;	
			}
		}
		BEEP_OFF();
	}
	else if(enn == 5)
	{
		// 过5好门槛后去夏威夷
		DMotor_Control_Par(0,0);
		delay_ms(100);
		mid_stop(4);
		delay_ms(50);
		Track_wheel_right(0,90);
		back = 85;
		Track_Speaicl_BridgeZM_to(0); //去夏威夷并且回来
	}
	else if(enn == 6)
	{
		//从夏威夷回来的第一个路口
		DMotor_Control_Par(0,0);
		delay_ms(50);
		Track_wheel_left(0,45);
		delay_ms(50);
	}
	else if(enn == 7)
	{
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(4);
		Track_wheel_left(0,90);
		delay_ms(50);
		Track_crash_ward();	   // 去巴厘岛
		back = 0;
	}
	else if(enn == 8)
	{
		//从巴厘岛回来的第一个路口
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(45);
		delay_ms(50);
		Track_wheel_right(0,90);
		delay_ms(50);
		back = 85;
	}
	else if(enn == 9)
	{
		//去太平岛的第一个路口
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(45);
		delay_ms(50);
		Track_wheel_left(0,90);
		delay_ms(50);
	}
	else if(enn == 10)
	{
		//去太平岛 桥前的路口
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(4);
		delay_ms(50);
		Track_wheel_left(0,90);
		delay_ms(50);

		// 过桥
		Track_GapBridge(3080,3200);
	}
	else if(enn == 11)
	{
		//过桥后的第一个路口
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(5);
		delay_ms(50);
		Track_wheel_right(0,90);
		delay_ms(50);
	} 
	else if(enn == 12)
	{
		//过桥后的第二个路口
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(5);
		delay_ms(50);
		Track_wheel_right(0,90);
		delay_ms(50);

		 //可能有减速板  
		//上太平岛
		Track_Taiping_To();
	}
	else if(enn == 13)
	{
		//下太平岛后的第一个路口
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(4);
		delay_ms(50);
		Track_wheel_left(0,90);
	}
	else if(enn == 14)
	{
		//下太平岛后的第二个路口
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(4);
		delay_ms(50);
		Track_wheel_left(0,90);
		//过桥
		Track_GapBridge(3080,3200);
	}
	else if(enn == 15)
	{
		//下太平岛并过桥后的第一个路口
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(5);
		delay_ms(50);
		Track_wheel_right(0,90);
	}
	else if(enn == 16)
	{
		//下太平岛并过桥后的第二个路口
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(4);
		delay_ms(50);
		Track_wheel_left(0,90);
	}
	else if(enn == 17)
	{
		//醉白池前的路口
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(5);
		delay_ms(50);
		Track_wheel_right(0,90);
		Track_crash_ward();//撞醉白池
		back = 0;
	}
	else if(enn == 18)
	{
		//从醉白池回来的路口
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(45);
		delay_ms(50);
		Track_wheel_left(0,90);
		back = 85;
	}
	else if(enn == 19)
	{
		//从醉白池到黄山之间的第一个路口
		delay_ms(200);
	}
	else if(enn == 20)
	{
		//从醉白池到黄山之间的第一个路口
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(5);
		delay_ms(50);
		Track_wheel_right(0,90);
	}
	else if(enn == 21)
	{
		//黄山前的路口
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(4);
		delay_ms(50);
		Track_wheel_left(0,90);
		Track_crash_ward();//撞黄山
		back = 0;
	}
	else if(enn == 22)
	{
		//从黄山回来的路口
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(45);
		delay_ms(50);
		Track_wheel_right(0,90);
		back = 85;
	}
	else if(enn == 23)
	{
		//从黄山回来后到圆之间的路口
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(45);
		delay_ms(50);
		Track_wheel_left(0,90);
	}
	//在此圆部分不当作路口
	else if(enn == 24)
	{
		//过圆后的路口
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(4);
		delay_ms(50);
		Track_wheel_left(0,90);
	}
	else if(enn == 25)
	{
		//香格里拉的路口
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(4);
		delay_ms(50);
		Track_wheel_left(0,90);
		Track_crash_ward();
		back = 0;
	}
	else if(enn == 26)
	{
		//香格里拉的路口
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(45);
		delay_ms(50);
		Track_wheel_right(0,90);
		back = 85;
	}
	else if(enn == 27)
	{
		//波浪弧线前的路口
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(4);
		delay_ms(50);
		Track_wheel_left(0,90);
		//走波浪弧线，并过门槛
		Track_Doorsill_WavyLine();
		//珠穆朗玛峰前的路口
		while(1)
		{
			Track_steep_WavyLine(0);
			if(my_intersection(0))
			{
				DMotor_Control_Par(0,0);
				break;
			}
		}
		mid_stop(4);
		Track_wheel_left(0,90);		

		//上下珠穆朗玛峰
		Track_Qomolangma_To();
	}
	else if(enn == 28)
	{	
		//下珠穆朗玛峰的第一个路口
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(5);
		delay_ms(50);
		Track_wheel_right(0,90);

		//走波浪弧线，并过门槛回去
		Track_Doorsill_WavyLine();

		//走完波浪线的路口
		while(1)
		{
			Track_steep_WavyLine(0);
			if(my_intersection(0))
			{
				DMotor_Control_Par(0,0);
				break;
			}
		}
		mid_stop(5);
		Track_wheel_right(0,90);
	}
	else if(enn == 28)
	{
		delay_ms(200);
	}
	else if(enn == 29)
	{
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(5);
		delay_ms(50);
		Track_wheel_right(0,90);
		//寻找圆路口

		Fork_road_intersection(1);
		//圆路口停止
		DMotor_Control_Par(0,0);
		delay_ms(100);
		DMotor_Control_Par(10,20);
		while(1)
		{
			Track_round(1);

			if(my_intersection(0))
			{
				DMotor_Control_Par(0,0);
				break;
			}
		}
		mid_stop(45);
		Track_wheel_left(0,90);
		//去佘山----平台型景点
		Track_Speaicl_BridgeZM_to(0);
	}
	else if(enn == 30)
	{
		//从佘山回来的园路口
		delay_ms(200);
	}
	else if(enn == 31)
	{
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(45);
		delay_ms(50);
		Track_wheel_right(1,90);
		back = 0;
		//去太湖----平台型景点
		Track_Speaicl_BridgeZM_to(1);
	}
	else if(enn == 32)
	{ 	
		//去天山
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(4);
		delay_ms(50);
		Track_wheel_right(0,30);
		back = 85;
		Track_crash_ward();
		back = 0;
	}
	else if(enn == 33)
	{
		//从天山回来的第一个路口
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(4);
		delay_ms(50);
		Track_wheel_left(0,30);
		//1号过门槛
		Track_Doorsill_Turn();
		//1号门槛和圣母大教堂之间的岔路口
		Fork_road_intersection(0);
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(4);
		delay_ms(50);
		Track_wheel_right(1,30);
	}
	else if(enn == 34)
	{
		//圣母大教堂前的路口
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(4);
		delay_ms(50);
		Track_wheel_right(1,90);
		Track_crash_ward();	//撞圣母大教堂
		back = 85;
	}
	else if(enn == 35)
	{
		//从圣母大教堂回来的第一个路口
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(45);
		delay_ms(50);
		Track_wheel_right(0,90);
	}
	else if(enn == 36)
	{
		//圣母大教堂和唐经幢之间的路口
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(45);
		delay_ms(50);
	}
	else if(enn == 37)
	{
		// 唐经幢前的路口
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(4);
		delay_ms(50);
		Track_wheel_left(0,90);
		Track_crash_ward();//撞唐经幢
		back = 0;
	}
	else if(enn == 38)
	{
		//唐经幢回来的第一个路口
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(45);
		delay_ms(50);
		Track_wheel_left(0,90);
	}
	else if(enn == 39)
	{
		//2号门和3号门的交叉路口
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(45);
		delay_ms(50);
		Track_wheel_right(0,90);
	}
	else if(enn == 40)
	{
		//1号减速板和2好减速板之间的路口
		delay_ms(200);
	}
	else if(enn == 41)
	{
		//回家前的路口
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(45);
		delay_ms(50);
		Track_wheel_left(0,90);
		//回家
		while(1)
		{
			Track_straight_line(1);
	
			if((D(22) == 0)||(D(23) == 0))
			{
				DMotor_Control_Par(0,0);

				DMotor_Control_Par(30,33);
				delay_ms(1500);
				DMotor_Control_Par(0,0);
	
				break;
			}
		}
		DMotor_Control_Par(0,0);
		while(1);
	}
}
	  



