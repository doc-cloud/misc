#include "InputNumber.h"
#include "InputChar.h"
#include "SMG1602.h"

//<<<<<<<<输入法标志位>>>>>>>>
unsigned char b_InputMode=0xff;	//0表示是数字输入法，1表示是字母输入法。
			        //默认是字母输入法。
//<<<<<<<<<显示介绍>>>>>>>>>>>>
extern unsigned char b_Introduce;

void vIntroduce(void);
//<<<<<<<<连续按键计数>>>>>>>>>
unsigned char uc_KeyTemp=0;	//按键键码暂存。

unsigned char uc_ClickCount=1;	//同一个按连续按下的次数。

extern unsigned char uc_CleanCount;//清除按键计数时间计数。

unsigned char b_CleanClick=0;	//为1时启用清除。


//<<<<<<<<大小写模式>>>>>>>>>
extern unsigned char b_CapStatus;//0--大写；1--小写。(默认为0:大写)


//<<<<<<<<<刷新字符显示>>>>>>>>>
unsigned char uca_CharBox[]={"                "};  //存储刷新字符。	 
							
unsigned char uc_CharPointer=0;	//刷新字符末位计数，指向字符光标位置。


/*******************************************
函数名称：vCleanAll
功    能：清除输入行的所有字符
参    数：无
返回值  ：无
********************************************/
void vCleanAll(void)
{
    unsigned char ucCount;

    for(ucCount=0;ucCount<uc_CharPointer;ucCount++)
        uca_CharBox[ucCount]=' ';

    uc_CharPointer=0;
    DispStr(0,1,"                ");
    LocateXY(0,1);
}
/*******************************************
函数名称：vCleanOne
功    能：向前清除输入行的一个字符
参    数：无
返回值  ：无
********************************************/
void vCleanOne(void)
{
    if(uc_CharPointer>0)
    {
        uc_CharPointer--;
        uca_CharBox[uc_CharPointer]=' ';
        LocateXY(uc_CharPointer,1);
        LcdWriteData(' ');
        LocateXY(uc_CharPointer,1);
    }
}
/*******************************************
函数名称：vCharAdd
功    能：向输入行的末尾追加显示一个字符
参    数：ucChar--要显示的字符的ASCII码
返回值  ：无
********************************************/
void vCharAdd(unsigned char ucChar)						   //接收的是ASC字符。
{
    unsigned char ucCount;
    
    if(uc_CharPointer<16)
    {
        LocateXY(uc_CharPointer,1);
        LcdWriteData(ucChar);
        
        uca_CharBox[uc_CharPointer]=ucChar; //将字符写入uca_CharBox。	
        uc_CharPointer++;	            //使ucCharPoint指向下一个位置。
        if(uc_CharPointer == 16)
        {
            LocateXY(0,1);    
        }
    }
    else
    {					    //如字符超出16个则全部清除，把光标移到最左边。
        
        DispStr(0,1,"                ");
        Disp1Char(0,1,ucChar);		    //写入输入字符。
    
        for(ucCount=1;ucCount<16;ucCount++)
                uca_CharBox[ucCount]=' ';   //同时清空uca_CharBox。
        uca_CharBox[0]=ucChar;
        uc_CharPointer=1;
    }

    b_CleanClick=1;
    uc_CleanCount=0;
}
/*******************************************
函数名称：ucGetChar
功    能：获取按键对应的数字或者字母
参    数：ucChar--键值
返回值  ：对应的ASCII码
********************************************/
unsigned char ucGetChar(unsigned char ucChar)
{
    if(b_InputMode==0)
        return ucGetNum(ucChar);	//获取数字字符
    else
        return ucGetLetter(ucChar);     //获取字母字符
}
/*******************************************
函数名称：vCharProcess
功    能：对字母状态下字母和符号进行处理的函数
参    数：ucKeyCode--键值
返回值  ：无
********************************************/
void vCharProcess(unsigned ucKeyCode)	       
{
    if(!b_InputMode)								 //如果是数字输入，就直接输出。
        vCharAdd(ucGetChar(ucKeyCode));
    else
    {
        if(ucKeyCode!=22)	//如果不是标点'!'
        {
            if(uc_ClickCount == 0)
            {
                vCharAdd(ucGetChar(ucKeyCode));	//如果是只连续按了1次就直接输出。
            }
            else
            {
                uc_CharPointer--;		//否则光标前移，然后再输出。
                vCharAdd(ucGetChar(ucKeyCode));
            }
        }
        else
        {
            vCharAdd('!');                      //追加显示!
        }
    }
    b_CleanClick=1;
    uc_CleanCount=0;
}
/*******************************************
函数名称：vKeyProcess
功    能：按键处理的主函数
参    数：ucKeyCode--键值
返回值  ：无
********************************************/
void vKeyProcess(unsigned char ucKeyCode)
{
    if(uc_KeyTemp==ucKeyCode)	//判断按键与上一次所按的键是否相同。
    {
        if(uc_ClickCount<255)	//同一个按连续按下的次数:1～255。
            uc_ClickCount++;
    }
    else
    {
        uc_KeyTemp=ucKeyCode;
        uc_ClickCount=0;
    }

    /*根据键值分别进行处理*/
    switch(ucKeyCode)
    {
    case 11:		//*****显示介绍****
            b_Introduce=1;
            vIntroduce();
            break;

    case 32:		//****输入空白****
            vCharAdd(' ');				
            break;

    case 31:	        //****大小写切换****
            if(b_InputMode)
            {
                b_CapStatus=~b_CapStatus;
                if(!b_CapStatus)    //大写
                {
                    
                    Disp1Char(14,0,'B');
                    LocateXY(uc_CharPointer,1);
                }
                else                //小写
                {
                    Disp1Char(14,0,'S');
                    LocateXY(uc_CharPointer,1);
                }
            }
            break;

    case 41:	    //****删除所有字符****
            vCleanAll();
            break;

    case 42:	    //****删除1个字符****
            vCleanOne();
            break;

    case 21:	    //****输入法切换****
            b_InputMode=~b_InputMode;
            if(b_InputMode)
            {
                if(b_CapStatus==0)	          //切换到字符输入法时在右上角显示“C”
                {
                    DispStr(14,0,"BC");		  //大写显示“BC”
                    LocateXY(uc_CharPointer,1);
                }
                else
                {
                    DispStr(14,0,"SC");		 //小写显示“SC”
                    LocateXY(uc_CharPointer,1);
                }
            }
            else
            {
                	  
                DispStr(14,0," N"); //切换到数字输入法时在右上角显示“N”
                LocateXY(uc_CharPointer,1);
            }	
            break;
    case 12:	 //获得键码
    case 13:
    case 14:
    case 22:	 
    case 23:
    case 24:
    case 33:	 
    case 34:
    case 43: 
    case 44:
            vCharProcess(ucKeyCode);
            break;
    default:
            break;
    }
}
