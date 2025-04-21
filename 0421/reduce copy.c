#include<8052.h> 
#define NOTHING 0x00 //7段不會亮 

const char seg[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c, 0x58, 0x5e, 0x79, 0x71}; 
char table[8] = {0}; //0代表沒東西
const char activity[] = {0xff, 0, 1, 0xff, 2, 0xff, 0xff, 0xff, 3};
char now_pos = 0; //指向目前要填的table 
char seg_pos = 0; //七段目前顯示
char last = 0xff; 
char not_press = 1;

void int0(void) __interrupt(0) __using(1){
    not_press = 0;
}

char keypad(void){ 
    P0 = 0x0f; 
    if(not_press) return 0xff; 
    not_press = 0;
    for(char i = 0; i < 4; i++){         
        P0 = ~(1 << (7 - i)); //input
        //(button)
        //產生 output
        char return_act = activity[(~P0) & 0x0f];
        if(return_act != 0xff){ //-1會變成unsigned char -> 0x00
            //DEBOUNCE
            return seg[i * 4 + return_act]; 
        } 
    }  
    return 0xff;
} 

void timer(void) __interrupt(5) __using(1){
    TF2 = 0;
    seg_pos = ++seg_pos & 7;

    // __asm
    // clr _TF2

    // mov a, _seg_pos
    // inc a
    // anl a, #0x07
    // mov _seg_pos, a
    // __endasm;
}

void main(){ 
    EA = 1;
    EX0 = 1;
    IT0 = 1;
    //timer 2
    ET2 = 1;
    TR2 = 1;
    RCAP2L = (65536 - 5000) % 256;
    RCAP2H = (65536 - 5000) / 256;
    //P2 = NOTHING; 
    while(1){ 
        char keypad_return = keypad(); 
        if(keypad_return != 0xff && last != keypad_return){ 
            table[now_pos] = keypad_return; 
            now_pos = (++now_pos) & 7; 
        } 
        last = keypad_return; // always要更新
        //table對應seq_pos和now_pos 
        //7-(seq_pos - now_pos) % 8 == 要印哪個位數 
        P2 = table[(7 - (((7 - seg_pos) - now_pos + 8) & 7))]; 
        P1 = seg_pos; 
        // seg_pos = ++seg_pos & 7; 
    } 
}