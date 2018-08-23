/*****************大写字母处理函数*****************/

extern unsigned char uc_ClickCount;

/*******************************************
函数名称：ucCapOne
功    能：找到单次按键对应的大写字母的ASCII码
参    数：键值
返回值  ：对应的大写字母的ASCII码
********************************************/
unsigned char ucCapOne(unsigned char ucKeyCode)
{
    unsigned char tmp;
    
    switch(ucKeyCode)
    {
        case 14:tmp =  'A';break;
        case 24:tmp =  'D';break;
        case 34:tmp =  'G';break;
        case 44:tmp =  'J';break;
        case 13:tmp =  'M';break;
        case 23:tmp =  'P';break;
        case 33:tmp =  'S';break;
        case 43:tmp =  'V';break;
        case 12:tmp =  'Y';break;
        default:tmp =  0xFF;break;
    }
    return tmp;
}

/*******************************************
函数名称：ucCapTwo
功    能：找到两次按键对应的大写字母的ASCII码
参    数：键值
返回值  ：对应的大写字母的ASCII码
********************************************/
unsigned char ucCapTwo(unsigned char ucKeyCode)
{
    unsigned char tmp;
    
    switch(ucKeyCode)
    {
        case 14:tmp =  'B';break;
        case 24:tmp =  'E';break;
        case 34:tmp =  'H';break;
        case 44:tmp =  'K';break;
        case 13:tmp =  'N';break;
        case 23:tmp =  'Q';break;
        case 33:tmp =  'T';break;
        case 43:tmp =  'W';break;
        case 12:uc_ClickCount=2;tmp =  'Z';break;
        default:tmp =  0xff;break;
    }
    return tmp;
}

/*******************************************
函数名称：ucCapThree
功    能：找到三次按键对应的大写字母的ASCII码
参    数：键值
返回值  ：对应的大写字母的ASCII码
********************************************/
unsigned char ucCapThree(unsigned char ucKeyCode)
{
    unsigned char tmp;
    
    switch(ucKeyCode)
    {
        case 14:tmp = 'C';break;
        case 24:tmp = 'F';break;
        case 34:tmp = 'I';break;
        case 44:tmp = 'L';break;
        case 13:tmp = 'O';break;
        case 23:tmp = 'R';break;
        case 33:tmp = 'U';break;
        case 12:tmp = 'X';break;
        default:tmp = 0xff;break;
    }
    return tmp;
}

