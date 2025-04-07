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
    push _bp
    mov _bp, sp

    mov P1, dpl

    mov a, _bp ;sp
    add a, #0xfd
    mov r0, a
    mov P2, @r0
    
    pop _bp
    ret