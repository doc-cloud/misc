//SuperShark Ver1.0
/**************************
名称：预编译开关  “//”注释即不运行相关程序
**************************/
//选择开机是否有菜单画面 
#define MENU

//选择开机是否有LOGO画面
#define LOGO
/**************************
名称：变量类型缩写定义
**************************/
typedef signed long  s32;
typedef signed short s16;
typedef signed char  s8;

typedef unsigned long  u32;
typedef unsigned short u16;
typedef unsigned char  u8;

/**************************
名称：系统函数API
**************************/
void SuperShark_Init(void); 
//系统初始化
 
u16 BatteryVoltage(u8 num);	  //电池电压检测
//参数num:0表示控制器电池（占用AD14资源） 1表示驱动板电池（占用AD15资源）  

void delay_ms(u16 nms);     //对72M条件下,nms<=1864 
//等待时间 单位毫秒

void delay_us(u32 nus);
//等待时间 单位微秒

/**************************
名称：LED、蜂鸣器、按键API
**************************/
void LED_ON(void);
void LED_OFF(void);
//LED控制函数

void BEEP_ON(void);
void BEEP_OFF(void);
//BEEP控制函数

u8 Key_Start(void);
//驱动按键状态获取函数  返回1：按键按下  返回0：按键弹起

/**************************
名称：LCD显示API
**************************/
void ShowVar(u8 x,u8 y,u16 a);
//在指定位置显示变量(占用5个字符) 参数x:横坐标  y:纵坐标  Show_D:变量名

void SetBackLight(u8 Deg); 
// 描述: 设置背光亮度等级 参数: Grade  0~127的等级

void FontSet(u8 Font_NUM,u8 Color);		
//字符字体大小设置 参数1：0是6*10  1是8*16  参数2 写1即可

void FontSet_cn(u8 Font_NUM,u8 Color);	
//中文字体大小设置 参数1 0是12*12 1是16*16 参数2 写1即可

void PutString(u8 x,u8 y,u8 *p); 
//在指定位置显示ASCII字符串 参数x:横坐标  y:纵坐标  *p:字符串首地址 使用前先设置字体大小，否则为默认6*10

void PutString_cn(u8 x,u8 y,u8 *p);
//在指定位置显示中文字符串  示例：PutString_cn(0,0,“我爱机器人”) 使用前先设置字体大小，否则为默认12*12

void ClrScreen(void); 
//清屏

/**************************
名称：数字口、模拟口API
**************************/
u8 DigitalIn(u8 channel); 
//返回数字端口输入值0或1 参数channel:0至0-49
//其中34-49是模拟口0-15的数字复用,只能在模拟口未用的情况下使用

u16 AnalogIn(u8 channel); 
//返回模拟端口输入值 参数channel:0至15 
//短路帽短接14检测控制板电压，此时不能再用模拟14口 
//短路帽短接15检测驱动板电压，此时不能再用模拟15口

/**************************
名称：红外遥控API
遥控对应键值：
162 098 226	  
034 002 194
224 168 144
104 152 176
048 024 122
016 056 090
066 074 082
**************************/
//用户可以在stm32f10x_it.c中自定义动作函数

/**************************
名称：电机、舵机 API
**************************/
void DMotor( u8 port, s8 speed ); 
//直流电机调速 参数port:1至4  speed:-100至100

void SMotor( u8 port, s8 degree ); 
//舵机控制 参数port:1至4  degree:-90至90

/**************************
名称：倾角传感器adxl345 API
**************************/
u16 ADXL345(u8 num);  
//倾角 参数num1-3  1:与X轴的角度   2:与Y轴的角度   3:与Z轴的角度
//返回：角度值

/**************************
名称：指南针传感器GY26 API 
**************************/
u16 read_cmp(void);	 //获取角度值

/**************************
名称：EEPROM存储器 API
**************************/
u16 EEPROM_Read(u8 ReadAddr);
//返回EEPROM储存的16位数据 参数ReadAddr(存储序号):0~127

void EEPROM_Write(u8 WriteAddr,u16 DataToWrite);
//储存16位数据至EEPROM 参数WriteAddr(存储序号):0~127  DataToWrite:保存的数据

/**************************
名称：定时器 API   占用定时器2 10ms中断一次 用户可以在stm32f10x_it.c中自定义动作函数
**************************/
void StartTimer(void);
//开始计时

u32 GetTimer(void);			//使用前必须调用 StartTimer(void);
//返回计时数值 单位0.01秒 即100就是1秒 

/**************************
名称：编码器 API
功能：使用前，需调用StartTimer()函数，开启定时器。
**************************/
extern unsigned long   lEncoderTotal;          /* 计数累计值（距离）*/
extern unsigned int    iEncoderMax;            /* 10ms内计数最大值（速度）*/
extern unsigned int    iEncoder;               /* 目前10ms计数值（速度）*/

/**************************
名称：外部中断 API
**************************/
/*
	用户可以在stm32f10x_it.c中自定义动作函数：
	外部中断1：void EXTI2_IRQHandler(void)
	外部中断2：void EXTI3_IRQHandler(void)
*/

/**************************
名称：摄像头 API
**************************/
/*
	待开发
*/


