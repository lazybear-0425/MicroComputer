#include<8051.h>
#define DELAY for(unsigned char i = 0; i < 255; i++);

unsigned char seg[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07};
unsigned char idx = 0;

extern void NON_REENT(unsigned char idx, unsigned char seg);
extern void REENT(unsigned char idx, unsigned char seg)  __reentrant; 

void main(){
    while (1) {
        if(idx & 1) REENT(idx, seg[idx]);
        else NON_REENT(idx, seg[idx]);

        idx = ++idx & 0x07;
        DELAY
    }
}