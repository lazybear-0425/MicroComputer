#include <8052.h>
#define C_h 0
#define C_hash_h 1
#define D_h 2
#define D_hash_h 3
#define E_h 4
#define F_h 5
#define F_hash_h 6
#define G_h 7
#define G_hash_h 8
#define A_h 9
#define A_hash_h 10
#define B_h 11
#define hC_h 12
#define hF_h 13
#define hE_h 14
#define hG_h 15
#define hA_h 16

// 公式 T = 65536-10^6/(2*(12/11.0592)*262)=63777=0xF921
//經過算式算出來的
__code int frq[] = {
    0xf921,
    0xf980,
    0xf9e0,
    0xfa36,
    0xfa8b,
    0xfad7,
    0xfb22,
    0xfb68,
    0xfba9,
    0xfbe8,
    0xfc23,
    0xfc5b,
    0xfc90,
    0xfd91,
    0xfd45,
    0xfdd5,
    0xfdf4
};

//樂譜
__code unsigned char high[] = {
    E_h, B_h, G_hash_h,G_hash_h, E_h, B_h, G_hash_h,G_hash_h, E_h, B_h, A_h, A_h,E_h, B_h, A_h, A_h,E_h, B_h, G_hash_h,G_hash_h, E_h, B_h, G_hash_h, G_hash_h, E_h, B_h, A_h,A_h, E_h, B_h, 0xff, E_h, F_hash_h, F_hash_h, F_hash_h, E_h, F_hash_h, B_h, B_h, G_hash_h,
    G_hash_h,G_hash_h,G_hash_h, G_hash_h, 0xff, 0xff,0xff, E_h, F_hash_h, F_hash_h, F_hash_h, E_h, F_hash_h, B_h,B_h, E_h, E_h, E_h,E_h, E_h, 0xff, B_h, G_hash_h, G_hash_h, G_hash_h,G_hash_h, G_hash_h, 0xff, C_hash_h,C_hash_h, F_hash_h, F_hash_h, G_hash_h,G_hash_h, E_h, E_h, G_hash_h,G_hash_h, C_hash_h, C_hash_h, C_hash_h,C_hash_h, C_hash_h, 0xff, G_hash_h,G_hash_h, F_hash_h,
    F_hash_h, F_hash_h,F_hash_h, F_hash_h, 0xff, 0xff,0xff, E_h, F_hash_h, F_hash_h, F_hash_h, E_h, F_hash_h, B_h,B_h, G_hash_h, G_hash_h, G_hash_h,G_hash_h, G_hash_h, 0xff, 0xff,0xff, E_h, F_hash_h, F_hash_h, F_hash_h, E_h,F_hash_h,B_h,B_h,E_h,E_h,E_h,E_h,E_h,0xff,B_h,B_h,G_hash_h,G_hash_h,G_hash_h,G_hash_h,G_hash_h,0xff,C_hash_h,C_hash_h,F_hash_h,
    F_hash_h, G_hash_h,G_hash_h, E_h, E_h, G_hash_h, G_hash_h, C_hash_h, C_hash_h, C_hash_h,C_hash_h, C_hash_h, 0xff,0xff, E_h, E_h, B_h, G_hash_h, F_hash_h, E_h, B_h, D_hash_h, D_hash_h,E_h, E_h,E_h, 0xff, G_hash_h, A_h,A_h, G_hash_h,  D_hash_h,D_hash_h,D_hash_h, 0xff, G_hash_h, A_h,A_h, G_hash_h,  D_hash_h,
    D_hash_h,D_hash_h, 0xff, C_hash_h, D_hash_h, hE_h,hE_h, F_hash_h,G_hash_h,F_hash_h,F_hash_h, 0xff, 0xff, C_hash_h, D_hash_h, hE_h, C_hash_h, G_hash_h, G_hash_h, A_h, hE_h, hE_h,hE_h, hE_h,hE_h, B_h, G_hash_h, B_h, hE_h,hE_h, hE_h, hE_h,hE_h, hE_h, C_hash_h, hE_h, hG_h, hG_h,hG_h, hG_h, hF_h, hF_h, hF_h, hF_h,hF_h, hF_h, hF_h,
    0xff,0xff, 0xff, hF_h, hF_h, hE_h, D_hash_h, hE_h, hE_h, G_hash_h, G_hash_h, B_h,B_h, hF_h, hF_h, hF_h, hF_h, hF_h, 0xff, hF_h, hF_h, hE_h, D_hash_h, hE_h, hE_h, G_hash_h, G_hash_h, B_h,B_h, hF_h, hF_h, hF_h, hF_h,hF_h, 0xff, hE_h, hE_h, hF_h, hE_h, hG_h,
    G_h, hG_h,hG_h, hG_h, 0xff, hA_h, hG_h, D_hash_h, D_hash_h,D_hash_h, 0xff, hE_h, hE_h, hF_h, hE_h, hG_h, hG_h, hG_h,hG_h, hG_h, 0xff, C_hash_h, hG_h, hG_h, hF_h,hF_h, 0xff, hF_h, hF_h, hE_h, D_hash_h, hE_h, hE_h, G_hash_h, G_hash_h, B_h,B_h, hF_h, hF_h, hF_h,
    hF_h, hE_h, 0xff, hF_h, hF_h, hE_h, C_hash_h, hE_h, hE_h, G_hash_h, G_hash_h, B_h,B_h, hF_h, hF_h, hF_h, hF_h,hF_h, 0xff, hE_h, hE_h, hF_h, hE_h, hG_h, hG_h, hG_h,hG_h, hG_h, 0xff, hA_h, hG_h, hE_h, hE_h,hE_h, 0xff, hE_h, hE_h, hF_h, hE_h, hG_h,
    hG_h, hG_h,hG_h, hG_h, 0xff, C_hash_h, hG_h, hG_h, hF_h,hF_h, D_hash_h, D_hash_h,D_hash_h, D_hash_h, hE_h,hE_h, hE_h, hE_h
};
int j = 0; // 注意DataType
unsigned char count = 0; //拍子用

void timer2(void) __interrupt(5) __using(1) {
    TF2 = 0;
    count++;
}

void timer0(void) __interrupt(1) __using(1) {
    //unsigned char note_idx = high[j];
    if (high[j] != 0xff) {
        TH0 = (unsigned char)(frq[high[j]] >> 8);
        TL0 = (unsigned char)(frq[high[j]] & 0xff);
        P3_4 = !P3_4;  // 只有在播放音符時切換輸出
    }
}

void main(void) {
    EA = 1;
    ET0 = 1;
    ET2 = 1;
    TMOD = 0x01;
    // 0.625s = 625000us // 所以要做十次
    // (65536 - 62500)us
    RCAP2H = 0x0b;
    RCAP2L = 0xdc;
    TR2 = 1;

    // 一行 j < 25
    // 兩行 j < 54
    for (j = 0; j < 360; j++) {
        if (high[j] != 0xff)
            TR0 = 1; // 啟動
        // 這邊是high == low == 0xff 就不動作
        // 因為音符沒有一個是low和high相同的，所以直接用==應該還好

        // TR2 = 0;
        while (count < 5); // 10 -> 一拍
        // TR2 = 1;
        TR0 = 0;
        count = 0;
    }
}