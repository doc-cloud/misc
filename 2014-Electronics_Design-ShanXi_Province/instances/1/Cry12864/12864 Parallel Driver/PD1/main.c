/*************************************************************
程序功能：在12864液晶上显示ASCII常用字符
-------------------------------------------------------------
测试说明：观察液晶显示
**************************************************************/
#include  "msp430.h"
#include  "BoardConfig.h"
#include  "cry12864.h"

/***************************主函数***************************/
void main( void )
{
    uint i;
    uchar laba[]=
    { 0x00,0x00,0x00,0xC0,0x01,0x48,0x02,0x44,0x04,0x52,0xF8,0x49,0x88,0x49,0x88,0x49,
      0x88,0x49,0x88,0x49,0xF8,0x49,0x04,0x52,0x02,0x44,0x01,0x48,0x00,0xC0,0x00,0x00};
    
    WDTCTL = WDTPW + WDTHOLD;    //关狗
    BoardConfig(0xbe);

    Ini_Lcd();                  //初始化液晶
    
    Write_Cmd(0x80);            //写第一行的显示地址
    for(i = 0; i < 16; i++)
      Write_Data(0x00 + i);     //显示0x30~0x3f对应的字符
    Write_Cmd(0x90);            //写第二行的显示地址
    for(i = 0; i < 16; i++)
      Write_Data(0x10 + i);     //显示0x40~0x4f对应的字符
    Write_Cmd(0x88);            //写第三行的显示地址
    for(i = 0; i < 16; i++)
      Write_Data(0x20 + i);     //显示0x50~0x5f对应的字符
    Write_Cmd(0x98);            //写第四行的显示地址
    for(i = 0; i < 16; i++)
      Write_Data(0x30 + i);     //显示0x60~0x6f对应的字符
    
 /*   for(i = 1000; i > 0; i--)        //延时一会
    {
        for(j = 1000; j > 0; j--)
          _NOP();    
    }*/
 
    
    //在显示时DDAM和GDRAM是同时显示的，也就是它们的显示结果是叠加在一起的
    /*SM12864液晶基本指令集控制命令测试*/
    //1.设定DDRAM地址命令
    Write_Cmd(0x90);            //设定DDRAM地址，因为此时DDRAM地址已经溢出
    //2.显示状态命令
    Write_Cmd(0x08);            //整体显示关，游标关，游标位置关
    Write_Cmd(0x0c);            //整体显示开，游标关，游标位置关
    Write_Cmd(0x0e);            //整体显示开，游标开，游标位置关
    Write_Cmd(0x0f);            //整体显示开，游标开，游标位置开
    //3.位址归位
    Write_Cmd(0x02);            //位址归位，游标回到原点
    
    Write_Cmd(0x84);            //将DDRAM地址设为0x88，游标在此闪烁
    //4.点设定指令
    //（以下四个命令是控制写入字符以后光标及整屏显示的移动）   
    Write_Cmd(0x07);            //光标右移整体显示左移
    Write_Data(0x20);           //写入两个空格
    Write_Data(0x20);  
    
    Write_Cmd(0x05);            //光标左移整体显示右移
    Write_Data(0x20);           //写入两个空格
    Write_Data(0x20); 
    
    Write_Cmd(0x06);            //光标右移整体显示不移动
    Write_Data(0x20);           //写入两个空格
    Write_Data(0x20); 
    
    Write_Cmd(0x04);            //光标左移整体显示不移动
    Write_Data(0x20);           //写入两个空格
    Write_Data(0x20);   
    //5.游标和显示移位控制
    //（以下四个命令无需写入显示数据，直接控制光标和整屏显示的移动）  
    Write_Cmd(0x10);            //光标左移
    Write_Cmd(0x14);            //光标右移
    Write_Cmd(0x18);            //整体显示左移，光标跟随  
    Write_Cmd(0x1c);            //整体显示右移，光标跟随 
    
    Write_Cmd(0x0c);            //关闭光标
    
    //6.进入扩展功能模式命令
    Write_Cmd(0x34);            //打开扩展功能模式，绘图显示关闭
    //7.反白命令
    Write_Cmd(0x04);            //同时反白1、3行
    Write_Cmd(0x04);            //再次反白1、3行，相当于关闭1、3行反白
    Write_Cmd(0x05);            //同时反白2、4行
    Write_Cmd(0x05);            //再次反白2、4行，相当于关闭2、4行反白
    //8.睡眠模式命令  
    Write_Cmd(0x08);            //进入睡眠模式
    Write_Cmd(0x0c);            //退出睡眠模式
    //9.待命模式命令
    Write_Cmd(0x01);            //进入待命模式
    //10.打开GDRAM显示
    Write_Cmd(0x36);            //打开扩展功能模式，打开绘图显示
    Draw_TX(0x80,0x84,laba);    //设置16*16大小图形
    Clear_GDRAM();              //清除上电复位后RAM中的随机数值
    Draw_TX(0x80,0x84,laba);    //重新显示设置16*16大小图形
   //11.关闭GDRAM显示
    Write_Cmd(0x34);            //打开扩展功能模式，关闭绘图显示
    //12.设定基本指令集
    Write_Cmd(0x30);              //回到基本指令集
    //13.清除显示命令
    Write_Cmd(0x01);            //清屏
    
    Write_Cmd(0x80);            //写第一行的显示地址
    for(i = 0; i < 16; i++)
      Write_Data(0x40 + i);     //显示0x40~0x4f对应的字符
    
    Write_Cmd(0x90);            //写第二行的显示地址
    for(i = 0; i < 16; i++)
      Write_Data(0x50 + i);     //显示0x50~0x5f对应的字符
    
    Write_Cmd(0x88);            //写第三行的显示地址
    for(i = 0; i < 16; i++)
      Write_Data(0x60 + i);     //显示0x60~0x6f对应的字符
    
    Write_Cmd(0x98);            //写第二行的显示地址
    for(i = 0; i < 16; i++)
      Write_Data(0x70 + i);     //显示0x70~0x7f对应的字符
    
    LPM4;
}
