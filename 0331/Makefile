S=sdcc
PACK=packihx
FILE=LED
FILE2=display
# .hex 為 packihx 輸出結果
BlinkingLED: $(FILE).ihx 
	$(PACK) $(FILE).ihx > $(FILE).hex 

$(FILE).ihx: $(FILE).rel 
	sdld -iM $(FILE).rel 

$(FILE).rel: $(FILE).asm 
	sdas8051 -logs $(FILE).asm

.PHONY: clean
clean: 
	del $(FILE).hex $(FILE).rel  $(FILE).ihx $(FILE).lk $(FILE).lst $(FILE).map $(FILE).mem $(FILE).rst $(FILE).sym