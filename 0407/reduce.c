#include<8051.h> 
#define NOTHING 0x00 

const char seg[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c, 0x58, 0x5e, 0x79, 0x71}; 
char table[8] = {0}; //0代表沒東西
const char activity[] = {0xff, 0, 1, 0xff, 2, 0xff, 0xff, 0xff, 3};
char now_pos = 0; //指向目前要填的table 
char seg_pos = 0; //七段目前顯示
char last = 0xff; 

// 要加上void，避免 "function declarator with no prototype" Warning
char keypad(void){ 
    P0 = 0xf0;
    if((~(P0) & 0xf0) == 0) return 0xff;
    for(char i = 0; i < 4; i++){         
        P0 = ~(1 << (7 - i)); 
        char return_act = activity[(~P0) & 0x0f];
        if(return_act != 0xff){
            return seg[i * 4 + return_act]; 
        } 
    }  
    return 0xff;
} 

// __interrupt(1) -> 因為 timer0的中斷編號是1 -> 不寫的話會跳去怪怪的位置
// __using(1) -> register bank 1
void display(void) __interrupt(1) __using(1) {
    char keypad_return = keypad(); 
    if(keypad_return != 0xff && last != keypad_return){ 
        table[now_pos] = keypad_return; 
        now_pos = (++now_pos) & 7; 
    } 
    last = keypad_return; // always要更新
    //table對應seq_pos和now_pos 
    //7-(seq_pos - now_pos) % 8 == 要印哪個位數 
    //P2 = table[(7 - (((7 - seg_pos) - now_pos + 8) & 7))]; 
    P2 = table[(7 - ((15 - seg_pos - now_pos) & 7))];  
    P1 = seg_pos; 
    seg_pos = ++seg_pos & 7; 
    //init // 因為發生中斷後會停掉
    TH0 = (65536 - 59286) / 256;
    TH1 = (65536 - 59286) % 256;
    TF0 = 1; 
}

void main(void){ 
    P2 = NOTHING; 
    EA = 1;
    //TH0 = (65536 - 15536) / 256; // 50000us = 1/20s // /256 -> high
    //TL0 = (65536 - 15536) % 256; // %256 -> low
    //因為題目說要1/20s完成八個數字，所以總共需要1/20/8*(10^6)us = 6250us
    //us = 10^-6s
    TH0 = (65536 - 59286) / 256;
    TH1 = (65536 - 59286) % 256;
    TMOD = 0x01;
    TR0 = 1; // 啟動timer 0
    TF0 = 1; // timer 0 interrupt flag
    while(1){ 
        display();
        // for(unsigned char i = 0; i < 100; i++)
        //     for(unsigned char j = 0; j < 255; j++);
    } 
}

// https://reurl.cc/8DpY2b
/*
中斷函式有幾點需要注意：

中斷函式不可傳入引數，也不會回傳任何值。
8051 只有兩種中斷優先順序分別是高與低，預設都是低順序。
中斷函式要盡快退出不要占用太久，因此避免在中斷內部使用延遲。
*/