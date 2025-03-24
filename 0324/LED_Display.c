#include<8051.h> 
#include"LED_Display.h"

void display(){
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
    seg_pos = ++seg_pos & 7; 
    DELAY(255)
}