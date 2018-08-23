/*****************��д��ĸ������*****************/

extern unsigned char uc_ClickCount;

/*******************************************
�������ƣ�ucCapOne
��    �ܣ��ҵ����ΰ�����Ӧ�Ĵ�д��ĸ��ASCII��
��    ������ֵ
����ֵ  ����Ӧ�Ĵ�д��ĸ��ASCII��
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
�������ƣ�ucCapTwo
��    �ܣ��ҵ����ΰ�����Ӧ�Ĵ�д��ĸ��ASCII��
��    ������ֵ
����ֵ  ����Ӧ�Ĵ�д��ĸ��ASCII��
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
�������ƣ�ucCapThree
��    �ܣ��ҵ����ΰ�����Ӧ�Ĵ�д��ĸ��ASCII��
��    ������ֵ
����ֵ  ����Ӧ�Ĵ�д��ĸ��ASCII��
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

