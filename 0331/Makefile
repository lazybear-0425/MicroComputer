S=sdcc
PACK=packihx
FILE=sub
FILE2=display
# .hex 為 packihx 輸出結果
BlinkingLED: $(FILE).ihx 
	$(PACK) LED.ihx > LED.hex 

$(FILE).ihx: $(FILE).rel LED.c
	sdcc LED.c $(FILE).rel 

$(FILE).rel: $(FILE).asm 
	sdas8051 -logs $(FILE).asm

.PHONY: clean
clean: 
	del $(FILE).hex $(FILE).rel  $(FILE).ihx $(FILE).lk $(FILE).lst $(FILE).map $(FILE).mem $(FILE).rst $(FILE).sym LED.lk LED.ihx LED.lst LED.map LED.rel LED.rst LED.sym LED.mem LED.asm LED.hex