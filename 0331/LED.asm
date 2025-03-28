    .area HOME 
    .area DSEG 

	ar7 = 0x07
	ar6 = 0x06
	ar5 = 0x05
	ar4 = 0x04
	ar3 = 0x03
	ar2 = 0x02
	ar1 = 0x01
	ar0 = 0x00

seg:
.db 0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07
    ljmp main

;=====================================================
.area CSEG
main:

    mov r0, #0x00
;=====================================================
CONTINUE:
    mov dptr, #seg; 把存七段表的位址給a
    mov a, r0; a 加上offset
    movc a, @a + dptr; 要顯示的七段(0-7)
    mov r1, a; 要顯示什麼
;    mov P2, a
;    mov P1, r0; 第幾個七段要顯示

    mov a, r0
    anl a, #0x01; 判斷是否為偶數
; 偶數位數使用 non-reentrant subroutine 來顯示
    jnz to_REENT
; non_reent(y, digit)
    mov _NON_REENT_PARM_2, r1; 第二個參數
    mov dpl, r0; 第一個參數
    lcall _NON_REENT
    sjmp back
to_REENT:
    push ar0; 用stack
    push ar1
    lcall _REENT
    pop ar1
    pop ar0
back:
;=====================================================
; r0 + 1
    mov a, r0
    inc a
    anl a, #0x07
    mov r0, a
;=====================================================
; delay 不加有殘影
    mov a, #0xff
DELAY_LOOP:
    dec a
    jnz DELAY_LOOP
;=====================================================

    sjmp CONTINUE

;=====================================================
.globl _NON_REENT
.globl _NON_REENT_PARM_2
.globl _REENT

.area OSEG
_NON_REENT_PARM_2:
    .ds 1
.area CSEG; 不能用CODE不然結果很怪
_NON_REENT:
    mov P2, _NON_REENT_PARM_2
    mov P1, dpl; 第幾個七段要顯示
    ret

_REENT:
    mov P2, r1
    mov P1, r0; 第幾個七段要顯示
    ret
