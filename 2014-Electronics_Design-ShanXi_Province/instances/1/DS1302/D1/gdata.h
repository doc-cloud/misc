unsigned char shuzi[]={"0123456789"};
unsigned char tishi[]={"The time is : "};

//秒，分，时，日，月，星期，年
unsigned char wdata[7]={0x30,0x46,0x20,0x14,0x08,0x02,0x07};
unsigned char rdata[7];
//秒，分，时，日，月，星期，年，控制
unsigned char bwdata[8]={0x30,0x34,0x20,0x24,0x11,0x02,0x10,0x00};
unsigned char brdata[8];
//读写RAM中的数据
unsigned char rwdata[31]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,
                          18,19,20,21,22,23,24,25,26,27,28,29,30,31};
unsigned char rrdata[31];
