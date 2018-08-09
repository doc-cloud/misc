#include "track.h"
#include "getsensor.h"
#include "driver.h"
#include "delay.h"
#include "lcd5110.h"
#include "beep.h"
#include "distance.h"
#include "compass.h" 

int back = 85;
char Gray[7]={0,0,0,0,0,0,0};

/*
**�������ܣ�ֱ��ǰ����ѭ��	
**��������SEN1660-D	 	�����߷���0
**���ư�ӿڣ�D1~D8
**			  D8Ϊǰ���ͨ��
*/
void Track_steep_line(void)
{
		if((D4 == 0)&&((D3 != 0)||(D5 != 0)))
		{
			speed(100,100);
		}
		else if(((D3 == 0)&&(D4 == 0)) || (D3 == 0))
		{
			speed(80,100);
		}
		else if(((D5 == 0)&&(D4 == 0)) || (D5 == 0))
		{
			speed(100, 80);
		}
		else if(D2 == 0)
		{
			speed(50, 100);		
		}
		else if(D6 == 0)
		{
			speed(100, 50);
		}	
		else if(D1 == 0)
		{
			speed(30, 100);
		}
		else if(D7 == 0)
		{
			speed(100, 30);
		}
}


/*
**�������ܣ�ֱ�ߵ���ǰ������ѭ��
*/
void Track_steep_low(void)
{
	  if((D4 == 0)&&((D3 != 0)||(D5 != 0)))
		{
			speed(40,40);
		}
		else if(((D3 == 0)&&(D4 == 0)) || (D3 == 0))
		{
			speed(25,40);
		}
		else if(((D5 == 0)&&(D4 == 0)) || (D5 == 0))
		{
			speed(40, 25);
		}
		else if(D2 == 0)
		{
			speed(20, 40);		
		}
		else if(D6 == 0)
		{
			speed(40, 20);
		}	
		else if(D1 == 0)
		{
			speed(0, 30);
		}
		else if(D7 == 0)
		{
			speed(30, 0);
		}	
}

/*
**�������ܣ�ֱ�ߺ��˵�ѭ��	
**��������SEN1660-D	 	�����߷���0
**�������ӿڣ�D9~D16
**			  D16Ϊ����ͨ��
*/
void Track_steep_turn(void)
{
	if((D12 == 0)&&((D11 != 0)||(D13 != 0)))
	{
		speed(-100,-100);
	}
	else if(((D11 == 0)&&(D12 == 0))||(D11 == 0))
	{
		speed(-100,-80);
	}
	else if(((D13 == 0)&&(D12 == 0))||(D13 == 0))
	{
		speed(-80,-100);
	}
	else if(D10 == 0)
	{
		speed(-100,-50);
	}
	else if(D14 == 0)
	{
		speed(-50,-100);
	}
	else if(D9 == 0)
	{
		speed(-100,-30);
	}
	else if(D15 == 0)
	{
		speed(-30,-100);
	}
}

/*
**�������ܣ���ֱ��
**����˵����back---ѡ����ʹ������־
**����ȡֵ��back==85ʱ---���� ��������
*/
void Track_straight_line(void)
{
	if( back == 85)
	{
		Track_steep_line();		
	}
	else 
	{
		Track_steep_turn();
	}
}

/*
**�������ܣ���ֱ��ת��
**�ӿڣ�	D17---��ߵ�ͨ���Ҷȴ�����
**			D18---�ұߵ�ͨ���Ҷȴ�����
*/
void Track_wheel_left(void)
{
	speed(-100,100);
	delay_ms(500);
	while(D1 == 0);
	while(D2 == 0);
	while(D3 == 0);
	delay_ms(5);
	while(D4 == 0);
//	speed(50,-50);
//	delay_ms(20);
	speed(0,0);
	delay_ms(10); 
}

/*
**�������ܣ���ֱ��ת��
**�ӿڣ�	D17---��ߵ�ͨ���Ҷȴ�����
**			D18---�ұߵ�ͨ���Ҷȴ�����
*/
void Track_wheel_right(void)
{
	speed(100,-100);
	delay_ms(475);
	while(D7 == 0);
	while(D6 == 0);
	while(D5 == 0);
	delay_ms(5);
	while(D4 == 0);
//	speed(-50,50);
//	delay_ms(20);
	speed(0,0);
	delay_ms(10);
}

/*
**�������ܣ��ж�ʶ��·��
**����˵����back---ѡ����ʹ������־
**			view---��enn��·�ڱ�ʾ
**����ȡֵ��back==85ʱ---���� ��������
**			view>= 1
*/
int intersection(int view)
{
	
	int i = 0;
	int f1,f2,f3,f4,f5,f6,f7,f8;

	f1=f2=f3=f4=f5=f6=f7=f8=0;
	Track_straight_line();

	if(back == 85)
	{
		if(D1 == 0)
			Gray[0] = 1;
		if(D2 == 0)
			Gray[1] = 1;
		if(D3 == 0)
			Gray[2] = 1;
		if(D4 == 0)
			Gray[3] = 1;
		if(D5 == 0)
			Gray[4] = 1;
		if(D6 == 0)
			Gray[5] = 1;
		if(D7 == 0)
			Gray[6] = 1;		
	}
	else
	{
		if(D9 == 0)
			Gray[0] = 1;
		if(D10 == 0)
			Gray[1] = 1;
		if(D11 == 0)
			Gray[2] = 1;
		if(D12 == 0)
			Gray[3] = 1;
		if(D13 == 0)
			Gray[4] = 1;
		if(D14 == 0)
			Gray[5] = 1;
		if(D15 == 0)
			Gray[6] = 1;
	}

	for(i=0;i<=7;i++)
	{
	    
		if(i%2==1)		    // ������1357
		f1=f1+Gray[i];
			
		if(i%2==0)		    //ż����2468
		f2=f2+Gray[i];
		
		if(i%3==1)		    // ��3:��1��147
		f3=f3+Gray[i];	 
		
		if(i%3==2)		    //��3��2��258
		f4=f4+Gray[i];
		
		if(i%3==0)		    //��3��0��36
		f5=f5+Gray[i];	   									 
	}	
	f7=Gray[0]+Gray[1]+Gray[2];
	f8=Gray[6]+Gray[4]+Gray[4];
	f6=f1+f2;		    //����
	if(f6>3||f1>2||f2>2||f4>1||f5>1||f3>1||f7>2||f8>2)		
	view=view+1;
	for(i=0;i<8;i++)//����0000000000
	Gray[i]=0;
	f1=f2=f3=f4=f5=f6=f7=f8=0;

	return view;
}

/*
**�������ܣ��ж�ʶ��·��
**����˵����back---ѡ����ʹ������־
**			view---��enn��·�ڱ�ʾ
**����ȡֵ��back==85ʱ---���� ��������
**			view>= 1
*/
int my_intersection(int view)
{
	int f1,f2,f3,f4,f5,f6,f7;
	
	f1=f2=f3=f4=f5=f6=f7=0;

	/*�ж�С����ʹ״̬---ǰ��/����*/
	if(back == 85)
	{
		if(D1 == 0)		f1 = 1;
		if(D2 == 0)		f2 = 1;
		if(D3 == 0)		f3 = 1;
		if(D4 == 0)		f4 = 1;
		if(D5 == 0)		f5 = 1;
		if(D6 == 0)		f6 = 1;
		if(D7 == 0)		f7 = 1;
	}
	else
	{
		if(D9  == 0)	f1 = 1;
		if(D10 == 0)	f2 = 1;
		if(D11 == 0)	f3 = 1;
		if(D12 == 0)	f4 = 1;
		if(D13 == 0)	f5 = 1;
		if(D14 == 0)	f6 = 1;
		if(D15 == 0)	f7 = 1;
	}

	if(((f1==1)&&(f2==1))||((f1==1)&&(f2==1)&&(f3==1))
	||((f1==1)&&(f2==1)&&(f3==1)&&(f4==1))
	||((f1==1)&&(f2==1)&&(f3==1)&&(f4==1)&&(f5==1))
	||((f1==1)&&(f2==1)&&(f3==1)&&(f4==1)&&(f5==1)&&(f6==1))
	||((f1==1)&&(f2==1)&&(f3==1)&&(f4==1)&&(f5==1)&&(f6==1)&&(f7==1))
	||((f2==1)&&(f3==1)&&(f4==1)&&(f5==1)&&(f6==1)&&(f7==1))
	||((f3==1)&&(f4==1)&&(f5==1)&&(f6==1)&&(f7==1))
	||((f4==1)&&(f5==1)&&(f6==1)&&(f7==1))
	||((f5==1)&&(f6==1)&&(f7==1))||((f6==1)&&(f7==1))
		/*�޹켣·��*/	
	||/*((f1==1)&&(f2==1)&&(f3==1))||*/((f2==1)&&(f3==1)&&(f4==1))
	||((f3==1)&&(f4==1)&&(f5==1))||((f4==1)&&(f5==1)&&(f6==1))
/*	||((f5==1)&&(f6==1)&&(f7==1))*/)
		view++;
	f1=f2=f3=f4=f5=f6=f7=0;

//	ShowVar(90,10,view);

	return view;
}

/*
**�������ܣ�·��ֹͣ
**����˵����back---ѡ����ʹ������־
**			r1-----��ͨ���Ҷȼ�ֱ�־
**����ȡֵ��back==85ʱ---���ߣ�������
**			r1 == 45ʱ---�������ߵĻҶȶ���⵽
**			r1 == 4 ʱ---��߻Ҷȼ�⵽
**			r1 == 5 ʱ---�ұ߻Ҷȼ�⵽
*/ 
void mid_stop(int r1)
{
	int i =1000;
	int r2 = 0;
	int r3 = 0;

	speed(0,0);
	delay_us(10);
	/*ȷ���Ƿ��ҵ���*/
	while(i--)
	{
		if(D17 == 0)	r2 = 1;
		if(D18 == 0)	r3 = 1;		
	}
	/*ǰ�����*/
	if(back == 85)
	{		
		if(r1 == 45)
		{
			while(1)
			{
				if(D17 == 0 && D18 == 0)
				{
					speed(0,0);
					break;
				}
				else if((D17 == 0)&&(r3 == 1))
				{
					speed(0,-30);
				}
				else if((D17 == 0)&&(r3 == 0))
				{
					speed(0,30);
				}
				else if((D18 == 0)&&(r2 == 1))
				{
					speed(-30,0);
				}
				else if((D18 == 0)&&(r2 == 0))
				{
					speed(30,0);
				}
				else if((r2 == 1)&&(r3 == 1))
				{
					speed(-50,-50);	
				}
				else if((r2 == 0)&&(r3 == 0))
				{
					speed(50,50);
				}
			}
		}
		else if(r1 == 4)
		{
			while(1)
			{
				if(D17 == 0)
				{
					speed(0,0);
					break;
				}
				else if(r2 == 1)
				{
					speed(-50,-50);
				}
				else if(r2 == 0)
					speed(50,50);
			}
		}
		else if(r1 == 5)
		{
			while(1)
			{
				if(D18 == 0)
				{
					speed(0,0);
					break;
				}
				else if(r3 == 1)
				{
					speed(-50,-50);
				}
				else if(r3 == 0)
					speed(50,50);	
			}
		}	
	}
	else 		  /*�������*/
	{
		if(r1 == 45)
		{
			while(1)
			{
				if(D17 == 0 && D18 == 0)
				{
					speed(0,0);
					break;
				}
				else if((D17 == 0)&&(r3 == 1))
				{
					speed(0,30);
				}
				else if((D17 == 0)&&(r3 == 0))
				{
					speed(0,-30);
				}
				else if((D18 == 0)&&(r2 == 1))
				{
					speed(30,0);
				}
				else if((D18 == 0)&&(r2 == 0))
				{
					speed(-30,0);
				}
				else if((r2 == 1)&&(r3 == 1))
				{
					speed(50,50);	
				}
				else if((r2 == 0)&&(r3 == 0))
				{
					speed(-50,-50);
				}
			}
		}
		else if(r1 == 4)
		{
			while(1)
			{
				if(D17 == 0)
				{
					speed(0,0);
					break;
				}
				else if(r2 == 1)
				{
					speed(50,50);
				}
				else if(r2 == 0)
					speed(-50,-50);
			}
		}
		else if(r1 == 5)
		{
			while(1)
			{
				if(D18 == 0)
				{
					speed(0,0);
					break;
				}
				else if(r3 == 1)
				{
					speed(50,50);
				}
				else if(r3 == 0)
					speed(-50,-50);	
			}
		}
	}

} 

/*
**�������ܣ��޹켣·�η���·��ֹͣ
*/
void mid_stop_nottrack(void)
{
	int i =500;
	int r2 = 0;
	int r3 = 0;

	speed(0,0);
	delay_us(10);
	
	
	while(1)
	{
		i = 500;
		/*ȷ���Ƿ��ҵ���*/
		while(i--)
		{
			if(D17 == 0)	r2 = 1;
			if(D18 == 0)	r3 = 1;		
		}

		if(D17 == 0 && D18 == 0)
		{
			speed(0,0);
			break;
		}
		else if((D17 == 0)&&(r3 == 1))
		{
			speed(-20,30);
		}
		else if((D17 == 0)&&(r3 == 0))
		{
			speed(20,-30);
		}
		else if((D18 == 0)&&(r2 == 1))
		{
			speed(30,-20);
		}
		else if((D18 == 0)&&(r2 == 0))
		{
			speed(-30,20);
		}
		else if((r2 == 1)&&(r3 == 1))
		{
			speed(30,30);	
		}
		else if((r2 == 0)&&(r3 == 0))
		{
			speed(-30,-30);
		}
	}
}

/*
**�������ܣ�תֱ�Ǻ�ֹͣ  ���޹켣·�Σ�
**����    ��ת��ѡ��
**����ȡֵ��flag==0		����ת
**			flag==1		����ת
*/
void Track_path_stop(unsigned char flag)
{
/*	int i = 1500;
	int r1 = 0;
	int r2 = 0;
*/
	speed(0,0);
	delay_us(10);
	/*ȷ���Ƿ��ҵ���*/

	if( flag == 0 )
	{
		speed(100,-100);
		delay_ms(575);
	}
	else if(flag == 1)
	{
		speed(-100,100);
		delay_ms(650);
	}
	
/*
	while(i--)
	{
		if(D17 == 0)	r1 = 1;	
		if(D18 == 0)	r2 = 1;	
	}
	while(1)
	{
		if(D17 == 0&&D18 == 0)
		{
			speed(0,0);
			break;
		}
		else if((D17 == 0)&&(r2 == 1))
		{
			speed(0,-40);
		}
		else if((D17 == 0)&&(r2 == 0))
		{
			speed(0,40);
		}
		else if((D18 == 0)&&(r1 == 1))
		{
			speed(-40,0);
		}
		else if((D18 == 0)&&(r1 == 0))
		{
			speed(40,0);
		}
		else if((r1 == 1)&&(r2 == 1))
		{
			speed(-50,-50);	
		}
		else if((r1 == 0)&&(r2 == 0))
		{
			speed(50,50);
		}
	}*/	
}

/*
**�������ܣ���ײ (�Ҷȵ�8ͨ����⣬�鲡��)
**����˵����back---ѡ����ʹ������־
**����ȡֵ��back==85ʱ---���� ��������
**����ֵ  �����ظı���backֵ��
*/
void Track_crash_ward(void)
{
	if(back == 85)
	{
		while(D8 != 0)
		{
			Track_straight_line();		
		}
		speed(0,0);
		Beep_ON;
		delay_ms(300);
		Beep_OFF;
		back = ~back;
	}
	else 
	{
		while(D16 != 0)
		{
			Track_straight_line();	
		}
		speed(0,0);
		Beep_ON;
		delay_ms(300);
		Beep_OFF;
		back = 85;
	}	
}

/*
**�������ܣ������ඨ��20cm��Բ��ƽ̨
**����˵����flag---ѡ������ִ��ǰ��
**����ȡֵ��flag==0----ѭ��ִ��
**			flag==1----�޹켣ִ��
*/
void Trcak_ranging_point(unsigned char flag)
{
	if(flag == 0)
	{
		while (distance(15) < 2265)
		{
			Track_steep_low();					
		}
	}
	else if(flag == 1)
	{
	/*	while(distance(15) > 2280)
		{
			speed(30,30);
		}
		while(distance(15) < 1760)
		{
			speed(30,30);
		}
		while(distance(15) > 1650)
		{
			speed(30,30);
		}  */

		while(D8 != 0)
		{
			speed(30,30);
		}
	}
	
	speed(0,0);
	Beep_ON;
	delay_ms(300);
	Beep_OFF;	
}

/*
**�������ܣ����20cm�ٸ�
*/
void Track_rear_20cm(void)
{
/*	servo1(-120);
	servo2(-90);
	servo3(-20);
	delay_ms(100);
	servo1(-90);
	servo2(-80);
	servo3(-20);
	delay_ms(100);
	servo1(-85);
	servo2(-70);
	servo3(-20);
	delay_ms(100);	*/

	servo1(-60);
	delay_ms(50);
	servo4(-55);
	delay_ms(50);
	servo3(-20);	
}

/*
**�������ܣ����50cm�ٸ�
*/
void Track_rear_50cm(void)
{	
/*	servo1(-60);
	servo2(-55);
	servo3(-20);
	delay_ms(50);

	servo1(-30);
	servo2(0);
	servo3(70);
	delay_ms(50);

	servo1(10);
	servo2(30);
	servo3(70);
	delay_ms(100);

	servo1(50);
	servo2(60);
	servo3(70);
	delay_ms(50);

	servo1(70);
	servo2(90);
	servo3(70);
	delay_ms(50);
*/	
//	delay_ms(500);			 
	servo1(90);
	delay_ms(50);
	servo4(90);
	delay_ms(50);
	servo3(70);
}

/*
**�������ܣ��гֱ��Ӿٸ�
**����˵����flag---��ͬ�߶�ѡ���־
**����ȡֵ��flag=20��flag=50��
**			����20ʱ����20cm��ƽ̨�ϼгֱ���
**			����50ʱ����50cm��ƽ̨���ͷű���
*/
void Track_rear_clamp(int flag)
{
	if(flag == 20)
	{
		servo3(70);
		delay_ms(100);
//		servo2(-40);		
	}

	if(flag == 50)
	{
		servo1(90);
		servo4(90);
		delay_ms(300);
		servo3(50);
		delay_ms(1000);
		servo3(-20);
		delay_ms(100);				
	}
}

/*
**�������ܣ��������Ɑ��
*/
void Trcak_ranging_cup(void)
{
	while(distance(16) < 2130)
	{
		Track_steep_low();
	}	

	while (distance(16) > 1780)
	{
		Track_steep_low();		
	}
	
	speed(0,0);
	Beep_ON;
	delay_ms(300);
	Beep_OFF;	
}

/*
**�������ܣ���ԲȦ�߽�ֹͣ
**����˵����flag---ѡ����ʻ����
**����ȡֵ��flag==0�����������ʻ
**			flag==1�������ұ���ʻ
*/
void Track_round_stop(unsigned char flag)
{
/*	int i = 500;
	int r1 = 0;
	int r2 = 0;

	while(1)
	{
		i = 500;
		while(i--)
		{
			if(D1 == 0) r1 = 1;
			if(D7 == 0) r2 = 1;	
		}

		if((D1 == 0)&&(D7 == 0))
		{
			speed(0,0);
			break;
		}
		else if((D1 == 0)&&(r2 == 0))
		{
			speed(-5,30);
		}
		else if((D1 == 0)&&(r2 == 1))
		{
			speed(5,-30);
		}
		else if((D7 == 0)&&(r1 == 0))
		{
			speed(30,-5);
		}
		else if((D7 == 0)&&(r1 == 1))
		{
			speed(-30,5);
		}
		else if((r1 == 1)&&(r2 == 1))
		{
			speed(-30,-30);
		}
		else if((r1 == 0)&&(r2 == 0))
		{
			Track_steep_cmp(flag);
		}		
	}*/

		while(1)
		{
			if((D1==0)||(D2==0)||(D3==0)||(D4==0)
				||(D5==0)||(D6==0)||(D7==0))
			{
				while((D17 != 0)||(D18 != 0))
				{
					if((D17 != 0)&&(D18 != 0))
					{
						speed(30,30);
					}
					else if((D17 != 0)&&(D18 == 0))
					{
						speed(40,-30);
					}
					else if((D17 == 0)&&(D18 != 0))
					{
						speed(-30,40);
					}
				}
				break;
			}
			else 
			{
				Track_steep_cmp(flag);
			}
			
		}
}

/*
**�������ܣ�ָ������ֱ��
**����˵����flag---ѡ����ʻ����
**����ȡֵ��flag==0�����������ʻ
**			flag==1�������ұ���ʻ
*/
void Track_steep_cmp(unsigned char flag)
{
//	ShowVar(20,20,read_cmp());
	if(flag == 0)
	{
		if((read_cmp()>2100)&&(read_cmp()<2350))
		{
			speed(60,60);
		}
		else if(read_cmp()<2100)   //1560
		{
			speed(30,0);
		}
		else if(read_cmp()>2350)
		{
			speed(0,30);
		}
	}
	else if(flag == 1)
	{
		if((read_cmp()>2030)&&(read_cmp()<2300))
		{
			speed(60,60);
		}
		else if(read_cmp()<2030)   //1560
		{
			speed(30,0);
		}
		else if(read_cmp()>2300)
		{
			speed(0,30);
		}		
	}
}

/*
**�������ܣ���·�ڵ��ж�,��ȫ��
			�����1---3
**����˵����back---ѡ����ʹ������־
**			enn ---��enn��·�ڱ�ʾ
**����ȡֵ��back==85ʱ---���� ��������
**			enn >= 1
*/
void switch_car1(int enn)
{
	if(enn == 1)
	{
		delay_ms(200);
//		Track_rear_20cm();
	}
	else if(enn == 2)
	{
		speed(0,0);
		mid_stop(45);
		delay_ms(100);
		Track_wheel_left();
	}
	else if(enn == 3)
	{
		speed(0,0);
		mid_stop(4);		
		delay_ms(100);
		Track_wheel_left();		//��ת
		Track_crash_ward();		//��һ����ײ�鷿	
	}
	else if(enn == 4)
	{
		speed(0,0);
		mid_stop(4);
		delay_ms(100);
		Track_wheel_left();		//��ת
		back = 85; 
	}
	else if(enn == 5)
	{
		delay_ms(200);
	} 
	else if(enn == 6)
	{
		speed(0,0);
		mid_stop(5);
		delay_ms(100);
		Track_wheel_right();	//��ת
		Track_crash_ward();		//�ڶ�����ײ�鷿
	}
	else if(enn == 7)
	{
		speed(0,0);
		mid_stop(5);
		delay_ms(100);
		Track_wheel_right();
		back = 85;
	}
	else if(enn == 8)
	{
		speed(0,0);
		mid_stop(45);
		delay_ms(100);
		Track_wheel_right();
	}            
	else if(enn == 9)
	{
		speed(0,0);
		mid_stop(45);
		delay_ms(100);
		Track_wheel_left();
	}
	else if(enn == 10)
	{
		speed(0,0);
		mid_stop(5);
		delay_ms(100);
		Track_wheel_right();
	}
	else if(enn == 11)
	{
		speed(0,0);
		mid_stop(45);	 //·��ֹͣ
		delay_ms(100);
		Track_wheel_left();	 //��ת

		Track_rear_20cm();

		Trcak_ranging_point(0);	 //������

		speed(0,0);
//		Trcak_ranging_cup();		//�������Ɑ��	
		
		Track_rear_clamp(20);		//�гֱ���
		delay_ms(200);
		Track_rear_50cm();	//�����ֱ�
		delay_ms(500);
		back = ~back;
	}
	else if(enn == 12)
	{
		delay_ms(300);
		
	}
	else if(enn == 13)
	{
		speed(0,0);
		delay_ms(500);
		Track_path_stop(0);	//С·����ת���޹켣��
		
		
		speed(50,50);
		delay_ms(50);	
		Track_round_stop(0);	 //��Բ�߽�ֹͣ
/*		//��Բ�߽�ֹͣ
		while(1)
		{
			if((D1==0)||(D2==0)||(D3==0)||(D4==0)
				||(D5==0)||(D6==0)||(D7==0))
			{
				while((D17 != 0)||(D18 != 0))
				{
					if((D17 != 0)&&(D18 != 0))
					{
						speed(30,30);
					}
					else if((D17 != 0)&&(D18 == 0))
					{
						speed(40,-30);
					}
					else if((D17 == 0)&&(D18 != 0))
					{
						speed(-30,40);
					}
				}
				break;
			}
			else 
			{
				Track_steep_cmp(0);
			}
			
		}
		 */
		Trcak_ranging_point(1);	//�����Բ����
		speed(0,0);
		Track_rear_clamp(50);  //�ͷű���

		while(1)  //ָ����������򷵻�
		{
			if((read_cmp() > 2000)&&(read_cmp() < 2100))
			{				//1360
				speed(-50,-50);
				break;
			}
			else if(read_cmp() < 2000)
			{
				speed(-0,-30);
			}
			else if(read_cmp() > 2100)
			{
				speed(-30,0);
			}
		} 
		speed(-50,-50);
		delay_ms(500);	

		Track_rear_20cm();//�����ֱ�	
	} 
	else if(enn == 14)
	{
		speed(0,0);
		mid_stop(45);		 //·��ֹͣ���ع�ѭ��

//		mid_stop_nottrack(); //·��ֹͣ���ع�ѭ��
		Track_wheel_right();
		back = 85;

		while(1)
		{
			Track_steep_line();
			if(distance(15) > 2250)
			{
				speed(0,0);
				break;				
			}	
		}
		Beep_ON;
		delay_ms(300);
		Beep_OFF;

		speed(0,0);
		
		Track_rear_clamp(20);		//�гֱ���
		delay_ms(200);
		Track_rear_50cm();	//�����ֱ�
		delay_ms(500);

		back = ~back;		
	} 
	else if(enn == 15)
	{
		delay_ms(200);
	}
	else if(enn == 16)
	{
		speed(0,0);
		delay_ms(500);
		Track_path_stop(1);
		
		speed(50,50);
		delay_ms(50);	
		Track_round_stop(1);	 //��Բ�߽�ֹͣ,�����ұ���ʻ
		
		Trcak_ranging_point(1);	//�����Բ����
		speed(0,0);
		Track_rear_clamp(50);  //�ͷű���

		while(1)  //ָ����������򷵻�
		{
			if((read_cmp() > 2000)&&(read_cmp() < 2100))
			{
				speed(-50,-50);
				break;
			}
			else if(read_cmp() < 2000)
			{
				speed(-0,-30);
			}
			else if(read_cmp() > 2100)
			{
				speed(-30,0);
			}
		} 
		
		speed(-50,-50);
		delay_ms(500);	

		Track_rear_20cm();//�����ֱ�
		servo1(-120);
		servo4(-100);
		servo3(-20);			
	}
	else if(enn == 17)
	{
		speed(0,0);
		mid_stop(45);
		Track_wheel_right();

		back = 85;

		while(1)
		{
			Track_steep_line();
			if(distance(15) > 2250)
			{
				speed(0,0);
				break;
			}
		}
		Beep_ON;
		delay_ms(300);
		Beep_OFF;
		
		back = ~back;
	}
	else if(enn == 18)
	{
		speed(0,0);
		mid_stop(5);
		delay_ms(100);
		Track_wheel_right();
		back = 85;
	}
	else if(enn == 19)
	{
		speed(0,0);
		mid_stop(5);
		delay_ms(100);
		Track_wheel_right();
	}
	else if(enn == 20)
	{
		speed(0,0);
		mid_stop(4);
		delay_ms(100);
		Track_wheel_left();
	}
	else if(enn == 21)
	{
		delay_ms(200);
	}
	else if(enn == 22)
	{
		while((D12 != 0)&&(D9 != 0)&&(D15 != 0));
		delay_ms(800);
		speed(0,0);
		while(1);
	}
}

/*
**�������ܣ���·�ڵ��ж�,��ȫ��
			�����1---2
**����˵����back---ѡ����ʹ������־
**			enn ---��enn��·�ڱ�ʾ
**����ȡֵ��back==85ʱ---���� ��������
**			enn >= 1
*/
void switch_car2(int enn)
{
	if(enn == 1)
	{
		delay_ms(200);
		Track_rear_20cm();
	}
	else if(enn == 2)
	{
		speed(0,0);
		mid_stop(45);
		delay_ms(100);
		Track_wheel_left();
	}
	else if(enn == 3)
	{
		speed(0,0);
		mid_stop(4);		
		delay_ms(100);
		Track_wheel_left();		//��ת
		Track_crash_ward();		//��һ����ײ�鷿	
	}
	else if(enn == 4)
	{
		speed(0,0);
		mid_stop(4);
		delay_ms(100);
		Track_wheel_left();		//��ת
		back = 85; 
	}
	else if(enn == 5)
	{
		delay_ms(200);
	} 
	else if(enn == 6)
	{
		speed(0,0);
		mid_stop(5);
		delay_ms(100);
		Track_wheel_right();	//��ת
		Track_crash_ward();		//�ڶ�����ײ�鷿
	}
	else if(enn == 7)
	{
		speed(0,0);
		mid_stop(5);
		delay_ms(100);
		Track_wheel_right();
		back = 85;
	}
	else if(enn == 8)
	{
		speed(0,0);
		mid_stop(45);
		delay_ms(100);
		Track_wheel_right();
	}            
	else if(enn == 9)
	{
		speed(0,0);
		mid_stop(45);
		delay_ms(100);
		Track_wheel_left();
	}
	else if(enn == 10)
	{
		speed(0,0);
		mid_stop(5);
		delay_ms(100);
		Track_wheel_right();
	}
	else if(enn == 11)
	{
		speed(0,0);
		mid_stop(45);	 //·��ֹͣ
		delay_ms(100);
		Track_wheel_left();	 //��ת

		Track_rear_20cm();

		Trcak_ranging_point(0);	 //������

		speed(0,0);
//		Trcak_ranging_cup();		//�������Ɑ��	
		
		Track_rear_clamp(20);		//�гֱ���
		delay_ms(200);
		Track_rear_50cm();	//�����ֱ�
		delay_ms(500);

		back = ~back;
	}
	else if(enn == 12)
	{
		delay_ms(300);
		
	}
	else if(enn == 13)
	{
		speed(0,0);
		delay_ms(500);
		
		Track_path_stop(0);	//С·����ת���޹켣��
		
		
		speed(50,50);
		delay_ms(50);	
		Track_round_stop(0);	 //��Բ�߽�ֹͣ
		
		Trcak_ranging_point(1);	//�����Բ����
		speed(0,0);
		Track_rear_clamp(50);  //�ͷű���

		while(1)  //ָ����������򷵻�
		{
			if((read_cmp() > 2000)&&(read_cmp() < 2100))
			{
				speed(-50,-50);
				break;
			}
			else if(read_cmp() < 2000)
			{
				speed(-0,-30);
			}
			else if(read_cmp() > 2100)
			{
				speed(-30,0);
			}
		} 
		speed(-50,-50);
		delay_ms(500);	

		Track_rear_20cm();//�����ֱ�	
	} 
	else if(enn == 14)
	{
		speed(0,0);
		mid_stop(45);
		Track_wheel_right();
		back = 85;

		while(1)
		{
			Track_steep_line();
			if(distance(15) > 2250)
			{
				speed(0,0);
				break;				
			}	
		}
		Beep_ON;
		delay_ms(300);
		Beep_OFF;

//		Trcak_ranging_cup();		//�������Ɑ��	
		
		Track_rear_clamp(20);		//�гֱ���
		delay_ms(200);
		Track_rear_50cm();	//�����ֱ�
		delay_ms(500);

		back = ~back;		
	} 
	else if(enn == 15)
	{
		delay_ms(300);
	}
	else if(enn == 16)
	{
		delay_ms(300);
	}
	else if(enn == 17)
	{
		speed(0,0);
		delay_ms(500);
		Track_path_stop(1);
		
		speed(50,52);
		delay_ms(50);	
		Track_round_stop(1);	 //��Բ�߽�ֹͣ,�����ұ���ʻ
		
		Trcak_ranging_point(1);	//�����Բ����
		speed(0,0);
		Track_rear_clamp(50);  //�ͷű���

		while(1)  //ָ����������򷵻�
		{
			if((read_cmp() > 2000)&&(read_cmp() < 2100))
			{
				speed(-50,-50);
				break;
			}
			else if(read_cmp() < 2000)
			{
				speed(-0,-30);
			}
			else if(read_cmp() > 2100)
			{
				speed(-30,0);
			}
		} 
		
		speed(-50,-50);
		delay_ms(500);	

//		Track_rear_20cm();//�����ֱ�
		servo1(-120);
		servo4(-90);
		servo3(-20);			
	}
	else if(enn == 18)
	{
		speed(0,0);
		mid_stop(45);
		Track_wheel_right();

		back = 85;

		while(1)
		{
			Track_steep_line();
			if(distance(15) > 2250)
			{
				speed(0,0);
				break;
			}
		}
		Beep_ON;
		delay_ms(300);
		Beep_OFF;
		
		back = ~back;
	}
	else if(enn == 19)
	{
		speed(0,0);
		mid_stop(5);
		delay_ms(100);
		Track_wheel_right();
		back = 85;
	}
	else if(enn == 20)
	{
		speed(0,0);
		mid_stop(5);
		delay_ms(100);
		Track_wheel_right();
	}
	else if(enn == 21)
	{
		speed(0,0);
		mid_stop(4);
		delay_ms(100);
		Track_wheel_left();
	}
	else if(enn == 22)
	{
		delay_ms(200);
	}
	else if(enn == 23)
	{
		while((D12 != 0)&&(D9 != 0)&&(D15 != 0));
		delay_ms(800);
		speed(0,0);
		
		while(1);
	}
}

/*
**�������ܣ���·�ڵ��ж�,��ȫ��
			�����2---3
**����˵����back---ѡ����ʹ������־
**			enn ---��enn��·�ڱ�ʾ
**����ȡֵ��back==85ʱ---���� ��������
**			enn >= 1
*/
void switch_car3(int enn)
{
	if(enn == 1)
	{
		delay_ms(200);
		Track_rear_20cm();
	}
	else if(enn == 2)
	{
		speed(0,0);
		mid_stop(45);
		delay_ms(100);
		Track_wheel_left();
	}
	else if(enn == 3)
	{
		speed(0,0);
		mid_stop(4);		
		delay_ms(100);
		Track_wheel_left();		//��ת
		Track_crash_ward();		//��һ����ײ�鷿	
	}
	else if(enn == 4)
	{
		speed(0,0);
		mid_stop(4);
		delay_ms(100);
		Track_wheel_left();		//��ת
		back = 85; 
	}
	else if(enn == 5)
	{
		delay_ms(200);
	} 
	else if(enn == 6)
	{
		speed(0,0);
		mid_stop(5);
		delay_ms(100);
		Track_wheel_right();	//��ת
		Track_crash_ward();		//�ڶ�����ײ�鷿
	}
	else if(enn == 7)
	{
		speed(0,0);
		mid_stop(5);
		delay_ms(100);
		Track_wheel_right();
		back = 85;
	}
	else if(enn == 8)
	{
		speed(0,0);
		mid_stop(45);
		delay_ms(100);
		Track_wheel_right();
	}            
	else if(enn == 9)
	{
		speed(0,0);
		mid_stop(45);
		delay_ms(100);
		Track_wheel_left();
	}
	else if(enn == 10)
	{
		speed(0,0);
		mid_stop(5);
		delay_ms(100);
		Track_wheel_right();
	}
	else if(enn == 11)
	{
		speed(0,0);
		mid_stop(45);	 //·��ֹͣ
		delay_ms(100);
		Track_wheel_left();	 //��ת

		Track_rear_20cm();

		Trcak_ranging_point(0);	 //������

		speed(0,0);
//		Trcak_ranging_cup();		//�������Ɑ��	
		
		Track_rear_clamp(20);		//�гֱ���
		delay_ms(200);
		Track_rear_50cm();	//�����ֱ�
		delay_ms(500);

		back = ~back;
	}
	else if(enn == 12)
	{
		delay_ms(300);
		
	}
	else if(enn == 13)
	{
		delay_ms(300);
		
	}
	else if(enn == 14)
	{
		speed(0,0);
		delay_ms(500);
		
		Track_path_stop(0);	//С·����ת���޹켣��
		
		
		speed(50,50);
		delay_ms(50);	
		Track_round_stop(0);	 //��Բ�߽�ֹͣ
		
		Trcak_ranging_point(1);	//�����Բ����
		speed(0,0);
		Track_rear_clamp(50);  //�ͷű���

		while(1)  //ָ����������򷵻�
		{
			if((read_cmp() > 2000)&&(read_cmp() < 2100))
			{
				speed(-50,-55);
				break;
			}
			else if(read_cmp() < 2000)
			{
				speed(-0,-30);
			}
			else if(read_cmp() > 2100)
			{
				speed(-30,0);
			}
		} 
		speed(-50,-50);
		delay_ms(500);	

		Track_rear_20cm();//�����ֱ�	
	} 
	else if(enn == 15)
	{
		speed(0,0);
		mid_stop(45);
		Track_wheel_right();
		back = 85;

		while(1)
		{
			Track_steep_line();
			if(distance(15) > 2250)
			{
				speed(0,0);
				break;				
			}	
		}
		Beep_ON;
		delay_ms(300);
		Beep_OFF;

//		Trcak_ranging_cup();		//�������Ɑ��	
		
		Track_rear_clamp(20);		//�гֱ���
		delay_ms(200);
		Track_rear_50cm();	//�����ֱ�
		delay_ms(500);

		back = ~back;		
	} 
	else if(enn == 16)
	{
		delay_ms(300);
	}
	else if(enn == 17)
	{
		speed(0,0);
		delay_ms(500);

		Track_path_stop(1);
		
		speed(50,50);
		delay_ms(50);	
		Track_round_stop(1);	 //��Բ�߽�ֹͣ,�����ұ���ʻ
		
		Trcak_ranging_point(1);	//�����Բ����
		speed(0,0);
		Track_rear_clamp(50);  //�ͷű���

		while(1)  //ָ����������򷵻�
		{
			if((read_cmp() > 2000)&&(read_cmp() < 2300))
			{
				speed(-50,-55);
				break;
			}
			else if(read_cmp() < 2000)
			{
				speed(-0,-30);
			}
			else if(read_cmp() > 2300)
			{
				speed(-30,0);
			}
		} 
		
		speed(-50,-50);
		delay_ms(500);	

//		Track_rear_20cm();//�����ֱ�
		servo1(-120);
		servo4(-90);
		servo3(-20);			
	}
	else if(enn == 18)
	{
		speed(0,0);
		mid_stop(45);
		Track_wheel_right();

		back = 85;

		while(1)
		{
			Track_steep_line();
			if(distance(15) > 2250)
			{
				speed(0,0);
				break;
			}
		}
		Beep_ON;
		delay_ms(300);
		Beep_OFF;
		
		back = ~back;
	}
	else if(enn == 19)
	{
		speed(0,0);
		mid_stop(5);
		delay_ms(100);
		Track_wheel_right();
		back = 85;
	}
	else if(enn == 20)
	{
		speed(0,0);
		mid_stop(5);
		delay_ms(100);
		Track_wheel_right();
	}
	else if(enn == 21)
	{
		speed(0,0);
		mid_stop(4);
		delay_ms(100);
		Track_wheel_left();
	}
	else if(enn == 22)
	{
		delay_ms(200);
	}
	else if(enn == 23)
	{
		while((D12 != 0)&&(D9 != 0)&&(D15 != 0));
		delay_ms(800);
		speed(0,0);
		
		while(1);
	}
}

/*
**�������ܣ���·�ڵ��ж�,��ȫ��
**			�����3---1
**����˵����back---ѡ����ʹ������־
**			enn ---��enn��·�ڱ�ʾ
**����ȡֵ��back==85ʱ---���� ��������
**			enn >= 1
*/
void switch_car4(int enn)
{
	if(enn == 1)
	{
		delay_ms(200);
		Track_rear_20cm();
	}
	else if(enn == 2)
	{
		speed(0,0);
		mid_stop(45);
		delay_ms(100);
		Track_wheel_left();
	}
	else if(enn == 3)
	{
		speed(0,0);
		mid_stop(4);		
		delay_ms(100);
		Track_wheel_left();		//��ת
		Track_crash_ward();		//��һ����ײ�鷿	
	}
	else if(enn == 4)
	{
		speed(0,0);
		mid_stop(4);
		delay_ms(100);
		Track_wheel_left();		//��ת
		back = 85; 
	}
	else if(enn == 5)
	{
		delay_ms(200);
	} 
	else if(enn == 6)
	{
		speed(0,0);
		mid_stop(5);
		delay_ms(100);
		Track_wheel_right();	//��ת
		Track_crash_ward();		//�ڶ�����ײ�鷿
	}
	else if(enn == 7)
	{
		speed(0,0);
		mid_stop(5);
		delay_ms(100);
		Track_wheel_right();
		back = 85;
	}
	else if(enn == 8)
	{
		speed(0,0);
		mid_stop(45);
		delay_ms(100);
		Track_wheel_right();
	}            
	else if(enn == 9)
	{
		speed(0,0);
		mid_stop(45);
		delay_ms(100);
		Track_wheel_left();
	}
	else if(enn == 10)
	{
		speed(0,0);
		mid_stop(5);
		delay_ms(100);
		Track_wheel_right();
	}
	else if(enn == 11)
	{
		speed(0,0);
		mid_stop(45);	 //·��ֹͣ
		delay_ms(100);
		Track_wheel_left();	 //��ת

		Track_rear_20cm();

		Trcak_ranging_point(0);	 //������

		speed(0,0);
//		Trcak_ranging_cup();		//�������Ɑ��	
		
		Track_rear_clamp(20);		//�гֱ���
		delay_ms(200);
		Track_rear_50cm();	//�����ֱ�
		delay_ms(500);

		back = ~back;
	}
	else if(enn == 12)
	{
		delay_ms(300);
		
	}
	else if(enn == 13)
	{
		delay_ms(300);
		
	}
	else if(enn == 14)
	{
		delay_ms(300);
	}
	else if(enn == 15)
	{
		speed(0,0);
		delay_ms(500);
		
		Track_path_stop(0);	//С·����ת���޹켣��
		
		
		speed(50,50);
		delay_ms(50);	
		Track_round_stop(0);	 //��Բ�߽�ֹͣ
		
		Trcak_ranging_point(1);	//�����Բ����
		speed(0,0);
		Track_rear_clamp(50);  //�ͷű���

		while(1)  //ָ����������򷵻�
		{
			if((read_cmp() > 2000)&&(read_cmp() < 2100))
			{
				speed(-50,-55);
				break;
			}
			else if(read_cmp() < 2000)
			{
				speed(-0,-30);
			}
			else if(read_cmp() > 2100)
			{
				speed(-30,0);
			}
		} 
		speed(-50,-50);
		delay_ms(500);	

		Track_rear_20cm();//�����ֱ�	
	} 
	else if(enn == 16)
	{
		speed(0,0);
		mid_stop(45);
		Track_wheel_right();
		back = 85;

		while(1)
		{
			Track_steep_line();
			if(distance(15) > 2250)
			{
				speed(0,0);
				break;				
			}	
		}
		Beep_ON;
		delay_ms(300);
		Beep_OFF;

//		Trcak_ranging_cup();		//�������Ɑ��	
		
		Track_rear_clamp(20);		//�гֱ���
		delay_ms(200);
		Track_rear_50cm();	//�����ֱ�
		delay_ms(500);

		back = ~back;		
	} 
	else if(enn == 17)
	{
		delay_ms(300);
	}
	else if(enn == 18)
	{
		delay_ms(300);
	}
	else if(enn == 19)
	{
		delay_ms(300);
	}
	else if(enn == 20)
	{
		speed(0,0);
		delay_ms(500);

		Track_path_stop(1);
		
		speed(50,50);
		delay_ms(50);	
		Track_round_stop(1);	 //��Բ�߽�ֹͣ,�����ұ���ʻ
		
		Trcak_ranging_point(1);	//�����Բ����
		speed(0,0);
		Track_rear_clamp(50);  //�ͷű���

		while(1)  //ָ����������򷵻�
		{
			if((read_cmp() > 2000)&&(read_cmp() < 2300))
			{
				speed(-50,-55);
				break;
			}
			else if(read_cmp() < 2000)
			{
				speed(-0,-30);
			}
			else if(read_cmp() > 2300)
			{
				speed(-30,0);
			}
		} 
		
		speed(-50,-50);
		delay_ms(500);	

//		Track_rear_20cm();//�����ֱ�
		servo1(-120);
		servo4(-90);
		servo3(-20);			
	}
	else if(enn == 21)
	{
		speed(0,0);
		mid_stop(45);
		Track_wheel_right();

		back = 85;

		while(1)
		{
			Track_steep_line();
			if(distance(15) > 2250)
			{
				speed(0,0);
				break;
			}
		}
		Beep_ON;
		delay_ms(300);
		Beep_OFF;
		
		back = ~back;
	}
	else if(enn == 22)
	{
		speed(0,0);
		mid_stop(5);
		delay_ms(100);
		Track_wheel_right();
		back = 85;
	}
	else if(enn == 23)
	{
		speed(0,0);
		mid_stop(5);
		delay_ms(100);
		Track_wheel_right();
	}
	else if(enn == 24)
	{
		speed(0,0);
		mid_stop(4);
		delay_ms(100);
		Track_wheel_left();
	}
	else if(enn == 25)
	{
		delay_ms(200);
	}
	else if(enn == 26)
	{
		while((D12 != 0)&&(D9 != 0)&&(D15 != 0));
		delay_ms(800);
		speed(0,0);
		
		while(1);
	}	
}

/*
**�������ܣ���·�ڵ��ж�,��ȫ��
			�����2---1
**����˵����back---ѡ����ʹ������־
**			enn ---��enn��·�ڱ�ʾ
**����ȡֵ��back==85ʱ---���� ��������
**			enn >= 1
*/
void switch_car5(int enn)
{
	if(enn == 1)
	{
		delay_ms(200);
		Track_rear_20cm();
	}
	else if(enn == 2)
	{
		speed(0,0);
		mid_stop(45);
		delay_ms(100);
		Track_wheel_left();
	}
	else if(enn == 3)
	{
		speed(0,0);
		mid_stop(4);		
		delay_ms(100);
		Track_wheel_left();		//��ת
		Track_crash_ward();		//��һ����ײ�鷿	
	}
	else if(enn == 4)
	{
		speed(0,0);
		mid_stop(4);
		delay_ms(100);
		Track_wheel_left();		//��ת
		back = 85; 
	}
	else if(enn == 5)
	{
		delay_ms(200);
	} 
	else if(enn == 6)
	{
		speed(0,0);
		mid_stop(5);
		delay_ms(100);
		Track_wheel_right();	//��ת
		Track_crash_ward();		//�ڶ�����ײ�鷿
	}
	else if(enn == 7)
	{
		speed(0,0);
		mid_stop(5);
		delay_ms(100);
		Track_wheel_right();
		back = 85;
	}
	else if(enn == 8)
	{
		speed(0,0);
		mid_stop(45);
		delay_ms(100);
		Track_wheel_right();
	}            
	else if(enn == 9)
	{
		speed(0,0);
		mid_stop(45);
		delay_ms(100);
		Track_wheel_left();
	}
	else if(enn == 10)
	{
		speed(0,0);
		mid_stop(5);
		delay_ms(100);
		Track_wheel_right();
	}
	else if(enn == 11)
	{
		speed(0,0);
		mid_stop(45);	 //·��ֹͣ
		delay_ms(100);
		Track_wheel_left();	 //��ת

		Track_rear_20cm();

		Trcak_ranging_point(0);	 //������

		speed(0,0);
//		Trcak_ranging_cup();		//�������Ɑ��	
		
		Track_rear_clamp(20);		//�гֱ���
		delay_ms(200);
		Track_rear_50cm();	//�����ֱ�
		delay_ms(500);

		back = ~back;
	}
	else if(enn == 12)
	{
		delay_ms(300);
		
	}
	else if(enn == 13)
	{
		delay_ms(300);
	}
	else if(enn == 14)
	{
		speed(0,0);
		delay_ms(500);
		
		Track_path_stop(0);	//С·����ת���޹켣��
		
		
		speed(50,50);
		delay_ms(50);	
		Track_round_stop(0);	 //��Բ�߽�ֹͣ
		
		Trcak_ranging_point(1);	//�����Բ����
		speed(0,0);
		Track_rear_clamp(50);  //�ͷű���

		while(1)  //ָ����������򷵻�
		{
			if((read_cmp() > 2000)&&(read_cmp() < 2100))
			{
				speed(-50,-50);
				break;
			}
			else if(read_cmp() < 2000)
			{
				speed(-0,-30);
			}
			else if(read_cmp() > 2100)
			{
				speed(-30,0);
			}
		} 
		speed(-50,-50);
		delay_ms(500);	

		Track_rear_20cm();//�����ֱ�	
	} 
	else if(enn == 15)
	{
		speed(0,0);
		mid_stop(45);
		Track_wheel_right();
		back = 85;

		while(1)
		{
			Track_steep_line();
			if(distance(15) > 2250)
			{
				speed(0,0);
				break;				
			}	
		}
		Beep_ON;
		delay_ms(300);
		Beep_OFF;

//		Trcak_ranging_cup();		//�������Ɑ��	
		
		Track_rear_clamp(20);		//�гֱ���
		delay_ms(200);
		Track_rear_50cm();	//�����ֱ�
		delay_ms(500);

		back = ~back;		
	} 
	else if(enn == 16)
	{
		delay_ms(300);
	}
	else if(enn == 17)
	{
		delay_ms(300);
	}
	else if(enn == 18)
	{
		delay_ms(300);
	}
	else if(enn == 19)
	{
		speed(0,0);
		delay_ms(500);
		Track_path_stop(1);
		
		speed(50,52);
		delay_ms(50);	
		Track_round_stop(1);	 //��Բ�߽�ֹͣ,�����ұ���ʻ
		
		Trcak_ranging_point(1);	//�����Բ����
		speed(0,0);
		Track_rear_clamp(50);  //�ͷű���

		while(1)  //ָ����������򷵻�
		{
			if((read_cmp() > 2000)&&(read_cmp() < 2100))
			{
				speed(-50,-50);
				break;
			}
			else if(read_cmp() < 2000)
			{
				speed(-0,-30);
			}
			else if(read_cmp() > 2100)
			{
				speed(-30,0);
			}
		} 
		
		speed(-50,-50);
		delay_ms(500);	

//		Track_rear_20cm();//�����ֱ�
		servo1(-120);
		servo4(-90);
		servo3(-20);			
	}
	else if(enn == 20)
	{
		speed(0,0);
		mid_stop(45);
		Track_wheel_right();

		back = 85;

		while(1)
		{
			Track_steep_line();
			if(distance(15) > 2250)
			{
				speed(0,0);
				break;
			}
		}
		Beep_ON;
		delay_ms(300);
		Beep_OFF;
		
		back = ~back;
	}
	else if(enn == 21)
	{
		speed(0,0);
		mid_stop(5);
		delay_ms(100);
		Track_wheel_right();
		back = 85;
	}
	else if(enn == 22)
	{
		speed(0,0);
		mid_stop(5);
		delay_ms(100);
		Track_wheel_right();
	}
	else if(enn == 23)
	{
		speed(0,0);
		mid_stop(4);
		delay_ms(100);
		Track_wheel_left();
	}
	else if(enn == 24)
	{
		delay_ms(200);
	}
	else if(enn == 25)
	{
		while((D12 != 0)&&(D9 != 0)&&(D15 != 0));
		delay_ms(800);
		speed(0,0);
		
		while(1);
	}
}

/*
**�������ܣ���·�ڵ��ж�,��ȫ��
			�����1---2
**����˵����back---ѡ����ʹ������־
**			enn ---��enn��·�ڱ�ʾ
**����ȡֵ��back==85ʱ---���� ��������
**			enn >= 1
*/
void switch_car6(int enn)
{
	if(enn == 1)
	{
		delay_ms(200);
		Track_rear_20cm();
	}
	else if(enn == 2)
	{
		speed(0,0);
		mid_stop(45);
		delay_ms(100);
		Track_wheel_left();
	}
	else if(enn == 3)
	{
		speed(0,0);
		mid_stop(4);		
		delay_ms(100);
		Track_wheel_left();		//��ת
		Track_crash_ward();		//��һ����ײ�鷿	
	}
	else if(enn == 4)
	{
		speed(0,0);
		mid_stop(4);
		delay_ms(100);
		Track_wheel_left();		//��ת
		back = 85; 
	}
	else if(enn == 5)
	{
		delay_ms(200);
	} 
	else if(enn == 6)
	{
		speed(0,0);
		mid_stop(5);
		delay_ms(100);
		Track_wheel_right();	//��ת
		Track_crash_ward();		//�ڶ�����ײ�鷿
	}
	else if(enn == 7)
	{
		speed(0,0);
		mid_stop(5);
		delay_ms(100);
		Track_wheel_right();
		back = 85;
	}
	else if(enn == 8)
	{
		speed(0,0);
		mid_stop(45);
		delay_ms(100);
		Track_wheel_right();
	}            
	else if(enn == 9)
	{
		speed(0,0);
		mid_stop(45);
		delay_ms(100);
		Track_wheel_left();
	}
	else if(enn == 10)
	{
		speed(0,0);
		mid_stop(5);
		delay_ms(100);
		Track_wheel_right();
	}
	else if(enn == 11)
	{
		speed(0,0);
		mid_stop(45);	 //·��ֹͣ
		delay_ms(100);
		Track_wheel_left();	 //��ת

		Track_rear_20cm();

		Trcak_ranging_point(0);	 //������

		speed(0,0);
//		Trcak_ranging_cup();		//�������Ɑ��	
		
		Track_rear_clamp(20);		//�гֱ���
		delay_ms(200);
		Track_rear_50cm();	//�����ֱ�
		delay_ms(500);

		back = ~back;
	}
	else if(enn == 12)
	{
		delay_ms(300);
		
	}
	else if(enn == 13)
	{
		delay_ms(300);
	}
	else if(enn == 14)
	{
		delay_ms(300);
	}
	else if(enn == 15)
	{
		speed(0,0);
		delay_ms(500);
		
		Track_path_stop(0);	//С·����ת���޹켣��
		
		
		speed(50,50);
		delay_ms(50);	
		Track_round_stop(0);	 //��Բ�߽�ֹͣ
		
		Trcak_ranging_point(1);	//�����Բ����
		speed(0,0);
		Track_rear_clamp(50);  //�ͷű���

		while(1)  //ָ����������򷵻�
		{
			if((read_cmp() > 2000)&&(read_cmp() < 2100))
			{
				speed(-50,-50);
				break;
			}
			else if(read_cmp() < 2000)
			{
				speed(-0,-30);
			}
			else if(read_cmp() > 2100)
			{
				speed(-30,0);
			}
		} 
		speed(-50,-50);
		delay_ms(500);	

		Track_rear_20cm();//�����ֱ�	
	} 
	else if(enn == 16)
	{
		speed(0,0);
		mid_stop(45);
		Track_wheel_right();
		back = 85;

		while(1)
		{
			Track_steep_line();
			if(distance(15) > 2250)
			{
				speed(0,0);
				break;				
			}	
		}
		Beep_ON;
		delay_ms(300);
		Beep_OFF;

//		Trcak_ranging_cup();		//�������Ɑ��	
		
		Track_rear_clamp(20);		//�гֱ���
		delay_ms(200);
		Track_rear_50cm();	//�����ֱ�
		delay_ms(500);

		back = ~back;		
	} 
	else if(enn == 17)
	{
		delay_ms(300);
	}
	else if(enn == 18)
	{
		delay_ms(300);
	}
	else if(enn == 19)
	{
		speed(0,0);
		delay_ms(500);
		Track_path_stop(1);
		
		speed(50,52);
		delay_ms(50);	
		Track_round_stop(1);	 //��Բ�߽�ֹͣ,�����ұ���ʻ
		
		Trcak_ranging_point(1);	//�����Բ����
		speed(0,0);
		Track_rear_clamp(50);  //�ͷű���

		while(1)  //ָ����������򷵻�
		{
			if((read_cmp() > 2000)&&(read_cmp() < 2100))
			{
				speed(-50,-50);
				break;
			}
			else if(read_cmp() < 2000)
			{
				speed(-0,-30);
			}
			else if(read_cmp() > 2100)
			{
				speed(-30,0);
			}
		} 
		
		speed(-50,-50);
		delay_ms(500);	

//		Track_rear_20cm();//�����ֱ�
		servo1(-120);
		servo4(-90);
		servo3(-20);			
	}
	else if(enn == 20)
	{
		speed(0,0);
		mid_stop(45);
		Track_wheel_right();

		back = 85;

		while(1)
		{
			Track_steep_line();
			if(distance(15) > 2250)
			{
				speed(0,0);
				break;
			}
		}
		Beep_ON;
		delay_ms(300);
		Beep_OFF;
		
		back = ~back;
	}
	else if(enn == 21)
	{
		speed(0,0);
		mid_stop(5);
		delay_ms(100);
		Track_wheel_right();
		back = 85;
	}
	else if(enn == 22)
	{
		speed(0,0);
		mid_stop(5);
		delay_ms(100);
		Track_wheel_right();
	}
	else if(enn == 23)
	{
		speed(0,0);
		mid_stop(4);
		delay_ms(100);
		Track_wheel_left();
	}
	else if(enn == 24)
	{
		delay_ms(200);
	}
	else if(enn == 25)
	{
		while((D12 != 0)&&(D9 != 0)&&(D15 != 0));
		delay_ms(800);
		speed(0,0);
		
		while(1);
	}
}

