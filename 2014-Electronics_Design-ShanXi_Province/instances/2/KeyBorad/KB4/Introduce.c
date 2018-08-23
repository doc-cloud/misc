#include "SMG1602.h"
#include "msp430.h"

unsigned char b_Introduce=1;	//用于关闭介绍。1--滚动介绍；0--退出介绍。

extern unsigned char uca_CharBox[];
extern unsigned char uc_CharPointer;
extern unsigned char b_CapStatus;
extern unsigned char b_InputMode;

unsigned char  d0[]={"                "};
unsigned char d1[]={"Hello. Sir! I am"};
unsigned char d2[]={"clear!I can show"};
unsigned char d3[]={"what you press !"};
unsigned char d4[]={"       ^-^      "};

/*******************************************
函数名称：vIntroduce
功    能：滚动显示介绍文字
参    数：无
返回值  ：无
********************************************/
void vIntroduce(void)
{
    unsigned int uiCount;	//循环滚动显示:
    unsigned char ucCount;
    
    unsigned char *ucaIntroduce[5];
    
    ucaIntroduce[0] = d0;
    ucaIntroduce[1] = d1;
    ucaIntroduce[2] = d2;
    ucaIntroduce[3] = d3;
    ucaIntroduce[4] = d4;
      
    LcdWriteCommand(0x0c,1);	//关闭光标显示

    //循环显示，等待退出
    for(ucCount=0;b_Introduce==1;ucCount++)
    {
        DispStr(0,0,ucaIntroduce[ucCount]);     //刷新第一行     	
        if(ucCount==4)
        {
            ucCount=0;
        }
        DispStr(0,1,ucaIntroduce[ucCount+1]);   //刷新第二行
    
        for(uiCount=0;uiCount<65000;uiCount++)
        {
            _NOP();
            _NOP();
            _NOP();
            _NOP();
            _NOP();
        }
        
    }
/*<<<<<<<<<<<<<<<结束介绍，恢复屏幕>>>>>>>>>>>>>>>>*/
    LcdWriteCommand(0x01, 1);	        //显示清屏					 
    DispStr(0,0,"Please Input: ");	//恢复提示信息。

    if(!b_InputMode)
    {									//恢复状态标志。
        DispStr(14,0," N");
    }
    else
    {
        if(!b_CapStatus)
            DispStr(14,0,"BC");
        else
            DispStr(14,0,"SC");
    }

    DispStr(0,1,uca_CharBox);	//恢复介绍前数据。

    LocateXY(uc_CharPointer,1);	//恢复介绍前光标位置。

    LcdWriteCommand(0x0F,1);	//恢复显示模式：显示器开、光标开、闪烁开。
}
