# 定義變數
S = sdcc
PACK = packihx
FILE = lab3-main
LIBRARY = myIO.lib
CFLAGS = -mmcs51

# 所有物件檔
OBJS = LED_Display.o Keypad4x4.o

# 目標：最終產生 .hex 檔案
all: $(FILE).hex 

# 轉換 ihx 到 hex
$(FILE).hex: $(FILE).ihx 
	$(PACK) $(FILE).ihx > $(FILE).hex 

# 編譯 lab3-main.c，並連結 myIO.lib
$(FILE).ihx: $(FILE).c $(LIBRARY)
	$(S) $(CFLAGS) $(FILE).c $(LIBRARY) -o $(FILE).ihx

# 建立靜態函式庫 myIO.lib
$(LIBRARY): $(OBJS)
	sdar rcs $(LIBRARY) $(OBJS)
	sdranlib $(LIBRARY)

# 個別編譯 .c 檔案
LED_Display.o: LED_Display.c LED_Display.h
	$(S) $(CFLAGS) -c LED_Display.c -o LED_Display.o

Keypad4x4.o: Keypad4x4.c Keypad4x4.h
	$(S) $(CFLAGS) -c Keypad4x4.c -o Keypad4x4.o

# 清理編譯產物
.PHONY: clean
clean: 
	del $(FILE).hex $(FILE).rel $(FILE).asm $(FILE).ihx $(FILE).lk $(FILE).lst $(FILE).map $(FILE).mem $(FILE).rst $(FILE).sym $(OBJS) $(LIBRARY)
	del LED_Display.asm LED_Display.lst LED_Display.sym Keypad4x4.asm Keypad4x4.lst Keypad4x4.sym 
