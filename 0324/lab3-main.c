#include<8051.h> 
#define NOTHING 0x00 //7段不會亮 

void main(){ 
    P2 = NOTHING; 
    while(1){ 
        display();
    } 
}