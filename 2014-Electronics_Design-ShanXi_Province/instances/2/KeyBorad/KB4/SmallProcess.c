
extern unsigned char uc_ClickCount;
/*******************************************
�������ƣ�ucSmallOne
��    �ܣ��ҵ����ΰ�����Ӧ��Сд��ĸ��ASCII��
��    ������ֵ
����ֵ  ����Ӧ��Сд��ĸ��ASCII��
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
�������ƣ�ucSmallTwo
��    �ܣ��ҵ����ΰ�����Ӧ��Сд��ĸ��ASCII��
��    ������ֵ
����ֵ  ����Ӧ��Сд��ĸ��ASCII��
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
�������ƣ�ucSmallThree
��    �ܣ��ҵ����ΰ�����Ӧ��Сд��ĸ��ASCII��
��    ������ֵ
����ֵ  ����Ӧ��Сд��ĸ��ASCII��
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
