// 參考自 https://reurl.cc/GnGA7Z
// 好難啊QAQ
#include<8052.h>
#define DELAY(n) for(char i = 0; i < n; i++);
#define DQ P3_3 // Data Input/Output pin

const unsigned char seg[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f}; // 0~9
unsigned char record[8] = {0};
const float resolution[4] = {0.5, 0.25, 0.125, 0.0625};
const unsigned mode_table[4] = {0x1f, 0x3f, 0x5f, 0x7f};
const int wait_time[4] = {285, 569, 1137, 2273};
unsigned char idx = 0;
unsigned char data[9];
unsigned char mode = 3;

void timer2(void) __interrupt(5) __using(1){
    TF2 = 0;
    P1 = idx;
    P2 = record[idx];
    if(++idx == 8) idx = 0;
}
void DS18B20_Init(void);
int DS18B20_ReadTemperature(void);
unsigned char DS18B20_ReadByte(void);
void Delay_ms(int i);
void ConvertToTemperature(int rawTemp);
void DS18B20_WriteByte(unsigned char byte);
unsigned char DS18B20_ReadWithCRCValidation(unsigned char *scratchpad);
unsigned char DS18B20_CalculateCRC(unsigned char *data, unsigned char length);

unsigned char keypad(void){
    P0 = 0x0f;
    if((~(P0) & 0x0f) == 0) return 0xff; 
    if((~(P0) & 0x0f) == 0x01) return 0; 
    if((~(P0) & 0x0f) == 0x02) return 1; 
    if((~(P0) & 0x0f) == 0x04) return 2; 
    if((~(P0) & 0x0f) == 0x08) return 3; 
    return 0xff;
}

void main(void){
    EA = 1;
    ET2 = 1;
    RCAP2H = 0xF9; //(65536 - 59286) / 256;
    RCAP2L = 0x60; //(65536 - 59286) % 256;
    TR2 = 1;
    while(1){
        unsigned char keypad_return = keypad();
        if (keypad_return != 0xff) mode = keypad_return;
        int temp_raw;
        temp_raw = DS18B20_ReadTemperature(); // 读取温度
        ConvertToTemperature(temp_raw); // 转换温度
    }
}

void Delay_ms(int i) {
    for(; i > 0; i--)
        for(unsigned char k = 110; k > 0; k--);
}

void DS18B20_Init(void){
    DQ = 1; // 线路拉高
    Delay_ms(1);
    DQ = 0; // 拉低DQ线，DS18B20复位
    Delay_ms(15); // 延时大于480us
    DQ = 1; // 拉高DQ线
    Delay_ms(1);
}

unsigned char DS18B20_ReadByte(void) {
    unsigned char i, byte = 0;
    for (i = 0; i < 8; i++) {
        byte >>= 1;
        DQ = 0; // 拉低DQ线，启动时隙
        DQ = 1; // 释放总线，DS18B20发送数据位
        if(DQ) byte |= 0x80; // 读取数据位
        Delay_ms(1); // 等待数据稳定
    }
    return byte;
}

void DS18B20_WriteByte(unsigned char dat) {
    unsigned int i;
    unsigned char testb;
    for(unsigned char j=1; j<=8; j++) {
        testb = dat & 0x01;
        dat = dat >> 1;
        if(testb){     // 寫1部分 
            DQ=0;
            i++;i++;
            DQ=1;
            i=8;while(i)i--;
        } else {
            DQ=0;       //寫0部分
            i=8;while(i)i--;
            DQ=1;
            i++;i++;
        }   
    }
}


int DS18B20_ReadTemperature(void) {
    unsigned char temp_low = 0, temp_high = 0;
    int temp;
    //==============================
    DS18B20_Init();
    // 发送温度转换命令
    DQ = 0; // 拉低DQ线
    DS18B20_WriteByte(0xCC); // 跳过ROM命令
    DS18B20_WriteByte(0x4E); // Write Scratchpad
    DS18B20_WriteByte(0x00); // 
    DS18B20_WriteByte(0x00); // 
    DS18B20_WriteByte(mode_table[mode]); // mode change 
    //==============================
    DS18B20_Init();
    // 发送温度转换命令
    DQ = 0; // 拉低DQ线
    DS18B20_WriteByte(0xCC); // 跳过ROM命令
    DS18B20_WriteByte(0x44); // 启动温度转换命令
    //==============================
    Delay_ms(wait_time[mode]);
    //==============================
    DS18B20_Init();
    DQ = 0;
    DS18B20_WriteByte(0xCC); // 跳过ROM命令
    DS18B20_WriteByte(0xBE); // 读取温度寄存器命令
 
    for(unsigned char i = 0; i < 9; i++)
        data[i] = DS18B20_ReadByte();

    temp_low = data[0]; // 读取温度低字节 // 1
    temp_high = data[1]; // 读取温度高字节 // 2
    // 第九個是CRC

    temp = (int)(temp_high << 8) | temp_low; // 合成温度值
    return temp;
}

// DS18B20 內建的 CRC 多項式: X^8 + X^5 + X^4 + 1
unsigned char DS18B20_CalculateCRC(unsigned char *data, unsigned char length) {
    unsigned char crc = 0;
    for (unsigned char i = 0; i < length; i++) {
        crc ^= data[i];
        for (unsigned char j = 0; j < 8; j++) {
            if (crc & 0x01) {
                crc = (crc >> 1) ^ 0x8C; // 0x8C = 10001100 (CRC8 Polynomial)
            } else {
                crc >>= 1;
            }
        }
    }
    return crc;
}

// 讀取 Scratchpad 並驗證 CRC
unsigned char DS18B20_ReadWithCRCValidation(unsigned char *scratchpad) {
    unsigned char calculatedCRC = DS18B20_CalculateCRC(scratchpad, 8); // 計算前 8 個字節的 CRC
    return (calculatedCRC != scratchpad[8]); // 比較與 DS18B20 提供的 CRC
}

void ConvertToTemperature(int rawTemp) {
    unsigned char temp_int = rawTemp >> 4;
    float temp_frac = (rawTemp & 0x0F) * resolution[mode];

    record[0] = seg[DS18B20_ReadWithCRCValidation(data)];

    record[4] = seg[((temp_int / 10) % 10)];
    record[5] = seg[temp_int % 10] | 0x80; 

    record[6] = seg[(unsigned char)(temp_frac * 10) % 10];
    record[7] = seg[(unsigned char)(temp_frac * 100) % 10];
}