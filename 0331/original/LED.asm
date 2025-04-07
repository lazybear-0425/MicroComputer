.area HOME
ar0=0x00
ar1=0x01
seg: .db 0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07
    ljmp m

.area CSEG
m:  mov r0,#0
c:  mov dptr,#seg
    mov a,r0
    movc a,@a+dptr
    mov r1,a
    mov a,r0
    anl a,#1
    jnz o
    mov _NR2,r1
    mov dpl,r0
    lcall _NR
    sjmp n
o:  push ar0
    push ar1
    lcall _R
    pop ar1
    pop ar0
n:  inc r0
    mov a,r0
    anl a,#7
    mov r0,a
    mov a,#0xff
d:  dec a
    jnz d
    sjmp c

.globl _NR
.globl _NR2
.globl _R

.area OSEG
_NR2: .ds 1
    
.area CSEG
_NR:mov P2,_NR2
    mov P1,dpl
    ret

_R: mov P2,r1
    mov P1,r0
    ret