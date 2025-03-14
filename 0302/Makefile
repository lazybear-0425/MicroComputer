S=sdcc
PACK=packihx
FILE=BlinkingLEDs
# .hex 為 packihx 輸出結果
BlinkingLED: $(FILE).ihx 
	$(PACK) $(FILE).ihx > $(FILE).hex 

$(FILE).ihx: $(FILE).c
	$(S) $(FILE).c
	
.PHONY: clean
clean: 
	del $(FILE).hex  $(FILE).ihx  $(FILE).lk  $(FILE).lst  $(FILE).map  $(FILE).mem  $(FILE).rst  $(FILE).sym 
# sdcc BlinkingLED.c
# packihx BlinkingLED.ihx > BlinkingLED.hex