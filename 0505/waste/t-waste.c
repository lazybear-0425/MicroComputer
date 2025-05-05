// 參考自 https://reurl.cc/GnGA7Z
// 好難啊QAQ
#include<8052.h>
#define DELAY(n) for(char i = 0; i < n; i++);
#define DQ P3_3 // Data Input/Output pin

const unsigned char seg[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f}; // 0~9
char record[8] = {0};
char idx = 0;

unsigned char info[] = {0, 0x1F, 0x3F, 0, 0x5F, 0, 0, 0, 0x7F};
unsigned char resolution[] = {0, 2, 4, 0, 8, 0, 0, 0, 16};
char mode = 8;

void check(void);
void DS18B20_Init(void);
int DS18B20_ReadTemperature(void);
unsigned char DS18B20_ReadByte(void);
void Delay_ms(unsigned char i);
void ConvertToTemperature(int rawTemp);
void DS18B20_WriteByte(unsigned char byte);

void main(void){
    while(1){
        check();
        int temp_raw;
        temp_raw = DS18B20_ReadTemperature(); // 读取温度
        ConvertToTemperature(temp_raw); // 转换温度
        P1 = idx;
        P2 = record[idx];
        if(++idx == 8) idx = 0;
    }
}

void check(void){
    P0 = 0x0f;
    if((~P0) & 0x0f == 0) return;
    mode = (~P0) & 0x0f;
}

void Delay_ms(unsigned char i) {
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
        testb=dat&0x01;
        dat=dat>>1;
        if(testb){     // 寫1部分 
            DQ=0;
            i++;i++;
            DQ=1;
            i=8;while(i>0)i--;
        } else {
            DQ=0;       //寫0部分
            i=8;while(i>0)i--;
            DQ=1;
            i++;i++;
        }   
    }
}


int DS18B20_ReadTemperature(void) {
    unsigned char temp_low, temp_high;
    int temp;
    DS18B20_Init();
    // 发送温度转换命令
    DQ = 0; // 拉低DQ线
    DS18B20_WriteByte(0xCC); // 跳过ROM命令
    DS18B20_WriteByte(0x44); // 启动温度转换命令
    DS18B20_Init();
    DQ = 0;
    DS18B20_WriteByte(0xCC); // 跳过ROM命令
    DS18B20_WriteByte(0xBE); // 读取温度寄存器命令
    
    // DS18B20_WriteByte(0x00); // TH register (default 0x00)
    // DS18B20_WriteByte(0x00); // TL register (default 0x00)
    //DS18B20_WriteByte(info[mode]);  // Configuration register
 
    temp_low = DS18B20_ReadByte(); // 读取温度低字节
    temp_high = DS18B20_ReadByte(); // 读取温度高字节
    // 第九個是CRC

    temp = (int)(temp_high << 8) | temp_low; // 合成温度值
    return temp;
}

void ConvertToTemperature(int rawTemp) {
    unsigned char temp_int = rawTemp >> 4;
    float temp_frac = (rawTemp & 0x0F) / (float)resolution[mode];

    record[4] = seg[(temp_int / 10) % 10];
    record[5] = seg[temp_int % 10] | 0x80; 

    record[6] = seg[(unsigned char)(temp_frac * 10) % 10];
    record[7] = seg[(unsigned char)(temp_frac * 100) % 10];
}
