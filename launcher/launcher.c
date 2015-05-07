/* Launcher program for FreeRTOS-86.
   This program loads FreeRTOS and an application using the following steps:
    - Find the application and copy it to 0xA000
    - Find the FreeRTOS module and copy it to 0x8100
    - Call 0xA000 to start the application.*/

#include "ti86_rom.h"

void main(void) __naked
{
    __asm
        .globl kernel
        ld hl, #kernel
        rst #0x20
        rst #0x10  ;// _FindSym done
        ret c ;// Carry reset if exists
        call #EX_AHL_BDE
        call #AHL_PLUS_TWO
        call #AHL_PLUS_TWO
        call #SET_ABS_SRC_ADDR
        ld a, #0x01
        ld hl, #0x0100
        call #SET_ABS_DEST_ADDR
        xor a
        ld hl, #0x1f00
        call #SET_MM_NUM_BYTES
        call #MM_LDIR
        ld hl, #demo
        rst #0x20
        rst #0x10  ;// _FindSym done
        ret c ;// Carry reset if exists
        call #EX_AHL_BDE
        call #AHL_PLUS_TWO
        call #AHL_PLUS_TWO
        call #SET_ABS_SRC_ADDR
        ld a, #0x01
        ld hl, #0x2000
        call #SET_ABS_DEST_ADDR
        xor a
        ld hl, #0x1f00
        call #SET_MM_NUM_BYTES
        call #MM_LDIR
        call 0x810b ; Initialize FreeRTOS and port
        jp 0xA002
    kernel:
        .db 0, 8
        .strz /freertos/
    demo:
        .db 0, 8
        .strz /demoprog/
    __endasm;
}
