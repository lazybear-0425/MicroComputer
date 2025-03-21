#include"LED_Display.h"
#include<8051.h>

void display(){
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