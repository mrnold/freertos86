.module syscall_internal
.macro define_syscall name address
    .globl _'name
    .org address
    jp _'name
.endm
.area HEADER(ABS)
.org 0x8100
.include /syscall.inc/
