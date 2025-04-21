#include<8052.h>

const char seg[] = {0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f}; 
char idx = 0;

// __interrupt(5) -> 因為 timer2的中斷編號是5 -> 不寫的話會跳去怪怪的位置
// __using(1) -> register bank 1
void display(void) __interrupt(5) __using(1) {
    idx = ++idx & 7;
    TF2 = 0;
}

void main(void){ 
    P2 = 0x00;
    //總開關
    EA = 1;
    ET2 = 1; // timer 0 overflow interrupt
    //TH0 = (65536 - 15536) / 256; // 50000us = 1/20s // /256 -> high
    //TL0 = (65536 - 15536) % 256; // %256 -> low
    //因為題目說要1/20s完成八個數字，所以總共需要1/20/8*(10^6)us = 6250us
    //us = 10^-6s
    TH2 = (65536 - 6250) / 256;
    RCAP2H = TH2; //(65536 - 59286) / 256;
    //
    TL2 = (65536 - 59286) % 256;
    RCAP2L = TL2; //(65536 - 59286) % 256;
    //T2CON = 0x04; //TR2 = 1
    TR2 = 1;

    while(1){ 
        P2 = seg[idx];
        P1 = idx;
    } 
}

// https://reurl.cc/8DpY2b
/*
中斷函式有幾點需要注意：

中斷函式不可傳入引數，也不會回傳任何值。
8051 只有兩種中斷優先順序分別是高與低，預設都是低順序。
中斷函式要盡快退出不要占用太久，因此避免在中斷內部使用延遲。
*/