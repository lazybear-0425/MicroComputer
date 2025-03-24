#include<8051.h> 
#define NOTHING 0x00 //7段不會亮 
#define DELAY(n) for (unsigned char l1 = 0; l1 < n; l1++); 
#define two_DELAY(n) for(unsigned char l1 = 0; l1 < n; l1++) for(unsigned char l2 = 0; l2 < 255; l2++); 
#define DEBOUNCE { two_DELAY(90) } //網路上很多都是用DELAY

const char seg[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c, 0x58, 0x5e, 0x79, 0x71}; 
char table[8] = {0}; //-1代表沒東西
const char activity[] = {0xff, 0, 1, 0xff, 2, 0xff, 0xff, 0xff, 3};
char now_pos = 0; //指向目前要填的table 
char seg_pos = 0; //七段目前顯示
 
char keypad(){ 
    for(char i = 0; i < 4; i++){         
        P0 = ~(1 << (7 - i)); 
        DELAY(10) 
        char return_act = activity[(~P0) & 0x0f];
        if(return_act != 0xff){ //-1會變成unsigned char -> 0x00
            DEBOUNCE
            return seg[i * 4 + return_act]; 
        } 
    } 
    return 0xff; 
} 

void main(){ 
    P2 = NOTHING; 
    while(1){ 
        char keypad_return = keypad(); 
        if(keypad_return != 0xff){ 
            table[now_pos] = keypad_return; 
            now_pos = (++now_pos) % 8; 
        } 
        //table對應seq_pos和now_pos 
        //7-(seq_pos - now_pos) % 8 == 要印哪個位數 
        P2 = table[7 - (((7 - seg_pos) - now_pos + 8) % 8)]; 
        P1 = seg_pos; 
        seg_pos = ++seg_pos % 8; 
        DELAY(255) 
    } 
}

/*
至今為止採到的坑
1. mod
2. -1
*/