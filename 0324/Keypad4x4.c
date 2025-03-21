#include"Keypad4x4.h"
#include<8051.h>

char keypad_check(char r){ 
    P0 = ~(1 << (7 - r)); 
    DELAY(10) 
    if(!(P0 & 0x01)) { 
        DEBOUNCE(P0_0) 
        return 0; 
    } 
    if(!(P0 & 0x02)) {
        DEBOUNCE(P0_1) 
        return 1; 
    } 
    if(!(P0 & 0x04)) { 
        DEBOUNCE(P0_2) 
        return 2; 
    }
    if(!(P0 & 0x08)) { 
        DEBOUNCE(P0_3) 
        return 3; 
    } 
    return 0xff; 
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