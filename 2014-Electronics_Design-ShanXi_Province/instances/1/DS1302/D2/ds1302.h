void delay(unsigned int time);
void Reset_DS1302(void);
void Write1Byte(unsigned char wdata);
unsigned char Read1Byte(void);
void W_Data(unsigned char addr, unsigned char wdata);
unsigned char R_Data(unsigned char addr);
void BurstWrite1302(unsigned char *ptr);
void BurstRead1302(unsigned char *ptr);
void BurstWriteRAM(unsigned char *ptr);
void BurstReadRAM(unsigned char *ptr);
void Set_DS1302(unsigned char *ptr);
void Get_DS1302(unsigned char *ptr);

