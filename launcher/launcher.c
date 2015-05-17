/* Launcher program for FreeRTOS-86.
   This program loads FreeRTOS and an application using the following steps:
    - Find the application and copy it to 0xA000
    - Find the FreeRTOS module and copy it to 0x8100
    - Call 0xA000 to start the application.*/

#include "ti86_rom.h"

void main(void) __naked
{
    __asm
        appaddr .equ 0xA500
        krnaddr .equ 0x8100
        rambase .equ 0x8000
        .globl kernel
        ld hl, #kernel
        rst #0x20
        rst #0x10  ;// _FindSym done
        ret c ;// Carry reset if exists
        call #EX_AHL_BDE
        call #GET_WORD_AHL
        call #AHL_PLUS_TWO
        call #SET_ABS_SRC_ADDR
        ld a, #0x01
        ld hl, #krnaddr-rambase ;// 0x0100, real address 0x8100
        call #SET_ABS_DEST_ADDR
        xor a
        ex de, hl ;// DE should have size from GET_WORD_AHL
        call #SET_MM_NUM_BYTES
        call #MM_LDIR
        ld hl, #demo
        rst #0x20
        rst #0x10  ;// _FindSym done
        ret c ;// Carry reset if exists
        call #EX_AHL_BDE
        call #GET_WORD_AHL
        call #AHL_PLUS_TWO
        call #SET_ABS_SRC_ADDR
        ld a, #0x01
        ld hl, #appaddr-rambase
        call #SET_ABS_DEST_ADDR
        xor a
        ex de, hl
        call #SET_MM_NUM_BYTES
        call #MM_LDIR
        call 0x810b ; Initialize FreeRTOS and port
        jp appaddr+2
    kernel:
        .db 0, 8
        .strz /freertos/
    demo:
        .db 0, 8
        .strz /powerctl/
    __endasm;
}
