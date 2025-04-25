#include<8052.h>
#define C_l 0x21 //1
#define C_h 0xf9
#define C_hash_l 0x80
#define C_hash_h 0xf9
#define D_l 0xe0 //2
#define D_h 0xf9
#define D_hash_l 0x36
#define D_hash_h 0xfa
#define E_l 0x8b
#define E_h 0xfa
#define F_l 0xd7
#define F_h 0xfa
#define F_hash_l 0x22
#define F_hash_h 0xfb
#define G_l 0x68
#define G_h 0xfb
#define G_hash_l 0xa9
#define G_hash_h 0xfb
#define A_l 0xe8
#define A_h 0xfb
#define A_hash_l 0x23
#define A_hash_h 0xfc
#define B_l 0x5b
#define B_h 0xfc
#define hC_l 0x90
#define hC_h 0xfc

//公式 T = 65536-10^6/(2*(12/11.0592)*262)=63777=0xF921
__code unsigned char high[]={
        A_h, E_h, C_h, G_h, F_hash_h, F_hash_h, A_h, E_h, C_h, G_h, F_hash_h, F_hash_h, A_h, E_h, C_h, G_h, F_hash_h, 0xff, C_h, D_h, D_h, 0xff, E_h, E_h, G_h,
        A_h, G_h, A_h, C_h, B_h, A_h, G_h, A_h, G_h, E_h, 0xff, E_h, E_h, G_h, A_h, G_h, A_h, C_h, B_h, A_h, A_h, E_h, E_h, D_h, D_h, 0xff, A_h, D_h,
        // A_h, D_h, 0xff, A_h, D_h, A_h, B_h, E_h, 0xff, D_h, E_h, D_h, G_h, 0xff, D_h, E_h, G_h, B_h, C_h, B_h, A_h, B_h, 0xff, E_h, E_h, G_h,
        // A_h, G_h, A_h, C_h, B_h, A_h, G_h, A_h, A_h, E_h, 0xff, E_h, E_h, G_h, A_h, G_h, A_h, C_h, B_h, A_h, A_h, G_h, G_h, E_h, 0xff, A_h, D_h, A_h,
        // D_h, D_h, 0xff, E_h, B_h, A_h, B_h, C_h, B_h, B_h, B_h, A_h, D_h, B_h, E_h, G_h, D_h, B_h, E_h, A_h, G_h, A_h, A_h, A_h, G_h, E_h,
        // D_h, D_h, 0xff, E_h, B_h, A_h, B_h, C_h, B_h, B_h, B_h, A_h, D_h, B_h, E_h, A_h, B_h, E_h, A_h, G_h, A_h, A_h, A_h, G_h, E_h,
        };
__code unsigned char low[]={
    A_l, E_l, C_l, G_l, F_hash_l, F_hash_l, A_l, E_l, C_l, G_l, F_hash_l, F_hash_l, A_l, E_l, C_l, G_l, F_hash_l, 0xff, C_l, D_l, D_l, 0xff, E_l, E_l, G_l,
    A_l, G_l, A_l, C_l, B_l, A_l, G_l, A_l, G_l, E_l, 0xff, E_l, E_l, G_l, A_l, G_l, A_l, C_l, B_l, A_l, A_l, E_l, E_l, D_l, D_l, 0xff, A_l, D_l,
    // A_l, D_l, 0xff, A_l, D_l, A_l, B_l, E_l, 0xff, D_l, E_l, D_l, G_l, 0xff, D_l, E_l, G_l, B_l, C_l, B_l, A_l, B_l, 0xff, E_l, E_l, G_l,
    // A_l, G_l, A_l, C_l, B_l, A_l, G_l, A_l, A_l, E_l, 0xff, E_l, E_l, G_l, A_l, G_l, A_l, C_l, B_l, A_l, A_l, G_l, G_l, E_l, 0xff, A_l, D_l, A_l,
    // D_l, D_l, 0xff, E_l, B_l, A_l, B_l, C_l, B_l, B_l, B_l, A_l, D_l, B_l, E_l, G_l, D_l, B_l, E_l, A_l, G_l, A_l, A_l, A_l, G_l, E_l,
    // D_l, D_l, 0xff, E_l, B_l, A_l, B_l, C_l, B_l, B_l, B_l, A_l, D_l, B_l, E_l, A_l, B_l, E_l, A_l, G_l, A_l, A_l, A_l, G_l, E_l,
    };
unsigned char j = 0; //注意DataType
unsigned char count = 0;

void timer2(void) __interrupt(5) __using(1){
    TF2 = 0;
    count++;
}

void timer0(void) __interrupt(1) __using(1){
    TH0 = high[j];
    TL0 = low[j];
    P3_4 = !P3_4;
}

void main(void){
    EA = 1;
    ET0 = 1;
    ET2 = 1;
    TMOD = 0x01;
    // 0.625s = 625000us // 所以要做十次
    // (65536 - 62500)us
    RCAP2H = 0x0b;
    RCAP2L = 0xdc;
    TR2 = 1;    

    while(1){
        //一行 j < 25
        //兩行 j < 54
        for(j = 0; j < 54; j++){
            if (high[j] != low[j]) TR0 = 1; //啟動
            //這邊是high == low == 0xff 就不動作
            //因為音符沒有一個是low和high相同的，所以直接用==應該還好 
                     
            // TR2 = 0;   
            while(count < 10); // 10 -> 一拍
            // TR2 = 1;   
            TR0 = 0;
            count = 0;
        }
    }
}