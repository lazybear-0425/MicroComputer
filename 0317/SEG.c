#include<8051.h>
#define DELAY(n) for(unsigned char cou = 0; cou < n; cou++);
#define two_DELAY(n) for(unsigned char k = 0; k < n; k++) for(unsigned char cou = 0; cou < 255; cou++);
#define DEBOUNCE two_DELAY(10) while(!P3_2); two_DELAY(10) //網路上很多都是用DELAY

const unsigned char table[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f}; // 0~9
unsigned int counter = 0; //0 ~ 9999
unsigned char idx = 0;

//中斷 -> 做事情(中斷是一種硬體機制，用來通知CPU有個非同步事件發生了)
//定義了一個中斷服務子程式(ISR)
void int0_isr(void) __interrupt(0) { 
    unsigned char time = 0;
    while(!P3_2){ //看當前狀況是否有持續按壓
        two_DELAY(10) // 延遲 -> 避免一下子跳太多
        time++;
        if(time == 20) { //兩秒後歸零
            counter = 0; 
            DEBOUNCE
            return;
        }
    }
    counter++;
    if(counter == 10000) counter = 0;
    DEBOUNCE
}

void main(){
    EA=1;			//首先開啟總中斷
	EX0=1;  		//開啟外部中斷 0
	IT0=0;          //下降沿觸發模式 (1)
    unsigned char Y6, Y5, Y4;
    while(1){
        //該數字位置
        Y6 = (unsigned char)(counter % 100 / 10); 
        Y5 = (unsigned char)(counter % 1000 / 100);
        Y4 = (unsigned char)(counter / 1000);
        switch(idx){ //Rules
            case 0: //Y7
                P2 = table[counter % 10];
                P1 = 0b00000111; // P1 = idx - 7
                break;
            case 1: //Y6
                if(Y4 || Y5 || Y6){
                    P2 = table[Y6];
                    P1 = 0b00000110;
                }
                break;
            case 2: //Y5
                if(Y4 || Y5){
                    P2 = table[Y5];
                    P1 = 0b00000101;
                }
                break;
            case 3: //Y4
                if(Y4){
                    P2 = table[Y4];
                    P1 = 0b00000100;
                }
                break;
        }
        if(++idx == 4) idx = 0;
        DELAY(255)
    }
}