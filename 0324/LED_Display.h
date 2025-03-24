#include<8051.h> 
#define DELAY(n) for (unsigned char l1 = 0; l1 < n; l1++); 

char table[8] = {0}; //0代表沒東西
char now_pos = 0; //指向目前要填的table 
char seg_pos = 0; //七段目前顯示
char last = 0xff; 