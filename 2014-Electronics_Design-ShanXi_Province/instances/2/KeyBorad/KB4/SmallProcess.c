
extern unsigned char uc_ClickCount;
/*******************************************
函数名称：ucSmallOne
功    能：找到单次按键对应的小写字母的ASCII码
参    数：键值
返回值  ：对应的小写字母的ASCII码
********************************************/
unsigned char ucSmallOne(unsigned char ucKeyCode)
{
    unsigned char tmp;
    
    switch(ucKeyCode)
    {
        case 14:tmp = 'a';break;
        case 24:tmp = 'd';break;
        case 34:tmp = 'g';break;
        case 44:tmp = 'j';break;
        case 13:tmp = 'm';break;
        case 23:tmp = 'p';break;
        case 33:tmp = 's';break;
        case 43:tmp = 'v';break;
        case 12:tmp = 'y';break;
        default:tmp = 0xFF;break;
    }
    return tmp;
}
/*******************************************
函数名称：ucSmallTwo
功    能：找到两次按键对应的小写字母的ASCII码
参    数：键值
返回值  ：对应的小写字母的ASCII码
********************************************/
unsigned char ucSmallTwo(unsigned char ucKeyCode)
{
    unsigned char tmp;
    
    switch(ucKeyCode)
    {
        case 14:tmp = 'b';break;
        case 24:tmp = 'e';break;
        case 34:tmp = 'h';break;
        case 44:tmp = 'k';break;
        case 13:tmp = 'n';break;
        case 23:tmp = 'q';break;
        case 33:tmp = 't';break;
        case 43:tmp = 'w';break;
        case 12:uc_ClickCount=2;tmp = 'z';break;
        default:tmp = 0xFF;break;
    }
    return tmp;
}
/*******************************************
函数名称：ucSmallThree
功    能：找到三次按键对应的小写字母的ASCII码
参    数：键值
返回值  ：对应的小写字母的ASCII码
********************************************/
unsigned char ucSmallThree(unsigned char ucKeyCode)
{
    unsigned char tmp;
    
    switch(ucKeyCode)
    {
        case 14:tmp = 'c';break;
        case 24:tmp = 'f';break;
        case 34:tmp = 'i';break;
        case 44:tmp = 'l';break;
        case 13:tmp = 'o';break;
        case 23:tmp = 'r';break;
        case 33:tmp = 'u';break;
        case 43:tmp = 'x';break;
        default:tmp = 0xFF;break;
    }
    return tmp;
}
