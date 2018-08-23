#include "CapProcess.h"
#include "SmallProcess.h"

/**************全局变量*****************/
extern unsigned char uc_ClickCount;

unsigned char b_CapStatus=0;//大小写模式：0--大写；1--小写。

/*******************************************
函数名称：ucCapProc
功    能：根据按键的次数找到对应的大写字母的
          ASCII码值
参    数：键值
返回值  ：对应的大写字母的ASCII码
********************************************/
unsigned char ucCapProc(unsigned char ucKeyCode)
{
    switch(uc_ClickCount%3)
    {
        case 0:return ucCapOne(ucKeyCode);
        case 1:return ucCapTwo(ucKeyCode);
        case 2:return ucCapThree(ucKeyCode);
        default:break;
    }
    return ' ';
}
/*******************************************
函数名称：ucSmallProc
功    能：根据按键的次数找到对应的小写字母的
          ASCII码值
参    数：键值
返回值  ：对应的大写字母的ASCII码
********************************************/
unsigned char ucSmallProc(unsigned char ucKeyCode)
{
    switch(uc_ClickCount%3)
    {
        case 0:return ucSmallOne(ucKeyCode);
        case 1:return ucSmallTwo(ucKeyCode);
        case 2:return ucSmallThree(ucKeyCode);
        default:break;
    }
    return ' ';
}
/*******************************************
函数名称：ucGetLetter
功    能：获取按键对应字母的ASCII码值
参    数：键值
返回值  ：对应的大写字母的ASCII码
********************************************/
unsigned char ucGetLetter(unsigned char ucKeyCode)
{
    if(b_CapStatus==0)		//大写输入方式
    {
        return ucCapProc(ucKeyCode);
    }
    else                        //小写输入方式
    {
        return ucSmallProc(ucKeyCode);	
    }
        
}
