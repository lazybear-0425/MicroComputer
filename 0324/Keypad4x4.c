#include<8051.h>
#include"Keypad4x4.h"

char keypad(){ 
    P0 = 0xf0;
    if((~(P0) & 0xf0) == 0) return 0xff;
    for(char i = 0; i < 4; i++){         
        P0 = ~(1 << (7 - i)); 
        DELAY(10) 
        char return_act = activity[(~P0) & 0x0f];
        if(return_act != 0xff){ //-1會變成unsigned char -> 0x00
            //DEBOUNCE
            return seg[i * 4 + return_act]; 
        } 
    }  
    //return 0xff;
} 