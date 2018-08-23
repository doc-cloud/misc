//数码管7位段码：0--f
unsigned char scandata[16] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
                              0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
//记录显示位数的全局变量
unsigned char cnt = 0;
//显示缓存
unsigned char Dispbuf[2];

//引用外部变量的声明
extern unsigned char key_Pressed;      
extern unsigned char key_val;         
extern unsigned char key_Flag; 

