#include<8051.h>
#include"Keypad4x4.h"

char keypad_check(char r){ 
    P0 = ~(1 << (7 - r)); 
    DELAY(10) 
    char return_act = activity[(~P0) & 0x0f];
    if(return_act != 0xff){
        DEBOUNCE
    }
    return return_act;
} 
char keypad(){ 
    for(char i = 0; i < 4; i++){ 
        char key = keypad_check(i); 
        if(key != 0xff){ //-1會變成unsigned char -> 0x00
            return seg[i * 4 + key]; 
        } 
    } 
    return 0xff; 
} 