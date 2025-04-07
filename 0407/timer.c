#include <8051.h>

void timer() __interrupt(1) __using(1) {
    P2 = ~P2;  // 翻轉 P2
}

void main() {
    EA = 1;    // 啟用全域中斷
    ET0 = 1;   // 啟用 Timer0 中斷
    TMOD = 0x01; // 設定 Timer0 為 16-bit 計時模式 (Mode 1)
    
    // 設定 Timer0 的初始值
    TH0 = 0x3C; // 高位 (預設讓 Timer0 以 50ms 產生中斷)
    TL0 = 0xB0; // 低位

    TR0 = 1;    // 啟動 Timer0 計數

    P2 = 0xFF;  // 預設 P2 高電位
    
    while (1) {
        // 無限迴圈，等待 Timer0 觸發中斷
    }
}
