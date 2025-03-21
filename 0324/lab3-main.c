#include<8051.h> 
#define NOTHING 0x00 //7段不會亮 

void main(){ 
    P2 = NOTHING; 
    while(1){ 
        display();
    } 
}

/*
至今為止採到的坑
1. mod
2. -1
*/