#define two_DELAY(n) for(unsigned char l1 = 0; l1 < n; l1++) for(unsigned char l2 = 0; l2 < 255; l2++); 
#define DEBOUNCE(BUTTON) {two_DELAY(10) while(!BUTTON); two_DELAY(10)} //網路上很多都是用DELAY
#define DELAY(n) for (unsigned char l1 = 0; l1 < n; l1++); 
const char seg[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c, 0x58, 0x5e, 0x79, 0x71}; 
