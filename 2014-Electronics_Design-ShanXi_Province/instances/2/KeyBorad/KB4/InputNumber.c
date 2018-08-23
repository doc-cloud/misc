
/*******************************************
函数名称：ucGetNum
功    能：找到数字输入方式下按键对应数据的
          ASCII码值
参    数：键值
返回值  ：对应数字的ASCII码
********************************************/
unsigned char ucGetNum(unsigned char ucKeyCode)
{
    unsigned char tmp;
    
    switch(ucKeyCode)
    {        
        case 14:tmp = '1';break;
        case 24:tmp = '2';break;
        case 34:tmp = '3';break;
        case 44:tmp = '4';break;
        case 13:tmp = '5';break;
        case 23:tmp = '6';break;
        case 33:tmp = '7';break;
        case 43:tmp = '8';break;
        case 12:tmp = '9';break;
        case 22:tmp = '0';break;
        default:tmp = 0xFF;break;
    }
    
    return tmp;  
}
