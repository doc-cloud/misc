#include "arithmetic.h"
#include "track.h"
#include "SuperSharkV1.0.h"

extern unsigned char back;

/*
**�������ܣ���·�ڵ��ж�,��ȫ��
			�����1---3
**����˵����back---ѡ����ʹ������־
**			enn ---��enn��·�ڱ�ʾ
**����ȡֵ��back==85ʱ---���� ��������
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
		Track_wheel_left(0,30);//ǰ�Ҷȼ����ת
		Track_GapBridge(2800,2950);	  //���ŵ����㵺
		Track_crash_ward();
		back = 0;
		Track_GapBridge(2790,2790);	  //�ӵ��㵺���Ż���
		//�����ţ�����·�ڣ�����ͨ�ã������⴦��

		Fork_road_intersection(0);
		
		DMotor_Control_Par(0,0);
		delay_ms(300);
		Track_wheel_right(0,30); //ǰ�Ҷȼ����ת
		back = 85;
		i = 2000;
		while(i--)
		{
			Track_steep_low();
		}
		Track_Speaicl_BridgeZM_to(0);// ǰ����������ɶ�������
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
		//��5���ż�
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
		// ��5���ż���ȥ������
		DMotor_Control_Par(0,0);
		delay_ms(100);
		mid_stop(4);
		delay_ms(50);
		Track_wheel_right(0,90);
		back = 85;
		Track_Speaicl_BridgeZM_to(0); //ȥ�����Ĳ��һ���
	}
	else if(enn == 6)
	{
		//�������Ļ����ĵ�һ��·��
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
		Track_crash_ward();	   // ȥ���嵺
		back = 0;
	}
	else if(enn == 8)
	{
		//�Ӱ��嵺�����ĵ�һ��·��
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
		//ȥ̫ƽ���ĵ�һ��·��
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(45);
		delay_ms(50);
		Track_wheel_left(0,90);
		delay_ms(50);
	}
	else if(enn == 10)
	{
		//ȥ̫ƽ�� ��ǰ��·��
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(4);
		delay_ms(50);
		Track_wheel_left(0,90);
		delay_ms(50);

		// ����
		Track_GapBridge(3080,3200);
	}
	else if(enn == 11)
	{
		//���ź�ĵ�һ��·��
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(5);
		delay_ms(50);
		Track_wheel_right(0,90);
		delay_ms(50);
	} 
	else if(enn == 12)
	{
		//���ź�ĵڶ���·��
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(5);
		delay_ms(50);
		Track_wheel_right(0,90);
		delay_ms(50);

		 //�����м��ٰ�  
		//��̫ƽ��
		Track_Taiping_To();
	}
	else if(enn == 13)
	{
		//��̫ƽ����ĵ�һ��·��
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(4);
		delay_ms(50);
		Track_wheel_left(0,90);
	}
	else if(enn == 14)
	{
		//��̫ƽ����ĵڶ���·��
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(4);
		delay_ms(50);
		Track_wheel_left(0,90);
		//����
		Track_GapBridge(3080,3200);
	}
	else if(enn == 15)
	{
		//��̫ƽ�������ź�ĵ�һ��·��
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(5);
		delay_ms(50);
		Track_wheel_right(0,90);
	}
	else if(enn == 16)
	{
		//��̫ƽ�������ź�ĵڶ���·��
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(4);
		delay_ms(50);
		Track_wheel_left(0,90);
	}
	else if(enn == 17)
	{
		//��׳�ǰ��·��
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(5);
		delay_ms(50);
		Track_wheel_right(0,90);
		Track_crash_ward();//ײ��׳�
		back = 0;
	}
	else if(enn == 18)
	{
		//����׳ػ�����·��
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(45);
		delay_ms(50);
		Track_wheel_left(0,90);
		back = 85;
	}
	else if(enn == 19)
	{
		//����׳ص���ɽ֮��ĵ�һ��·��
		delay_ms(200);
	}
	else if(enn == 20)
	{
		//����׳ص���ɽ֮��ĵ�һ��·��
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(5);
		delay_ms(50);
		Track_wheel_right(0,90);
	}
	else if(enn == 21)
	{
		//��ɽǰ��·��
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(4);
		delay_ms(50);
		Track_wheel_left(0,90);
		Track_crash_ward();//ײ��ɽ
		back = 0;
	}
	else if(enn == 22)
	{
		//�ӻ�ɽ������·��
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(45);
		delay_ms(50);
		Track_wheel_right(0,90);
		back = 85;
	}
	else if(enn == 23)
	{
		//�ӻ�ɽ������Բ֮���·��
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(45);
		delay_ms(50);
		Track_wheel_left(0,90);
	}
	//�ڴ�Բ���ֲ�����·��
	else if(enn == 24)
	{
		//��Բ���·��
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(4);
		delay_ms(50);
		Track_wheel_left(0,90);
	}
	else if(enn == 25)
	{
		//���������·��
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
		//���������·��
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(45);
		delay_ms(50);
		Track_wheel_right(0,90);
		back = 85;
	}
	else if(enn == 27)
	{
		//���˻���ǰ��·��
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(4);
		delay_ms(50);
		Track_wheel_left(0,90);
		//�߲��˻��ߣ������ż�
		Track_Doorsill_WavyLine();
		//���������ǰ��·��
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

		//�������������
		Track_Qomolangma_To();
	}
	else if(enn == 28)
	{	
		//�����������ĵ�һ��·��
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(5);
		delay_ms(50);
		Track_wheel_right(0,90);

		//�߲��˻��ߣ������ż���ȥ
		Track_Doorsill_WavyLine();

		//���겨���ߵ�·��
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
		//Ѱ��Բ·��

		Fork_road_intersection(1);
		//Բ·��ֹͣ
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
		//ȥ��ɽ----ƽ̨�;���
		Track_Speaicl_BridgeZM_to(0);
	}
	else if(enn == 30)
	{
		//����ɽ������԰·��
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
		//ȥ̫��----ƽ̨�;���
		Track_Speaicl_BridgeZM_to(1);
	}
	else if(enn == 32)
	{ 	
		//ȥ��ɽ
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
		//����ɽ�����ĵ�һ��·��
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(4);
		delay_ms(50);
		Track_wheel_left(0,30);
		//1�Ź��ż�
		Track_Doorsill_Turn();
		//1���ż���ʥĸ�����֮��Ĳ�·��
		Fork_road_intersection(0);
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(4);
		delay_ms(50);
		Track_wheel_right(1,30);
	}
	else if(enn == 34)
	{
		//ʥĸ�����ǰ��·��
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(4);
		delay_ms(50);
		Track_wheel_right(1,90);
		Track_crash_ward();	//ײʥĸ�����
		back = 85;
	}
	else if(enn == 35)
	{
		//��ʥĸ����û����ĵ�һ��·��
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(45);
		delay_ms(50);
		Track_wheel_right(0,90);
	}
	else if(enn == 36)
	{
		//ʥĸ����ú��ƾ���֮���·��
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(45);
		delay_ms(50);
	}
	else if(enn == 37)
	{
		// �ƾ���ǰ��·��
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(4);
		delay_ms(50);
		Track_wheel_left(0,90);
		Track_crash_ward();//ײ�ƾ���
		back = 0;
	}
	else if(enn == 38)
	{
		//�ƾ��������ĵ�һ��·��
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(45);
		delay_ms(50);
		Track_wheel_left(0,90);
	}
	else if(enn == 39)
	{
		//2���ź�3���ŵĽ���·��
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(45);
		delay_ms(50);
		Track_wheel_right(0,90);
	}
	else if(enn == 40)
	{
		//1�ż��ٰ��2�ü��ٰ�֮���·��
		delay_ms(200);
	}
	else if(enn == 41)
	{
		//�ؼ�ǰ��·��
		DMotor_Control_Par(0,0);
		delay_ms(50);
		mid_stop(45);
		delay_ms(50);
		Track_wheel_left(0,90);
		//�ؼ�
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
	  



