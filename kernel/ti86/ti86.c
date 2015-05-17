#include "ti86_rom.h"

__at (TEXTCOL_ADDRESS) static unsigned char textcol;
__at (TEXTROW_ADDRESS) static unsigned char textrow;

void setxy(const unsigned char x, const unsigned char y)
{
    textcol = x;
    textrow = y;
}

void puts(const char *const string)
{
    string;
    __asm
        ld l, 4(ix)
        ld h, 5(ix)
        call #VPUTS
    __endasm;
}

static void printdigits(unsigned int number)
{
    number;
    __asm
        ld l, 4(ix)
        ld h, 5(ix)
        ld b, #5
    printnumxygetdigits:
        call #DIVHLBY10 ;// _divHLby10, remainder in A
        push af
        djnz printnumxygetdigits
        ld b, #5
    printnumxystripzero:
        pop af
        cp #0
        jp nz, printnumxyprintdigitsskip
        djnz printnumxystripzero
    printnumxyprintdigits:
        pop af
    printnumxyprintdigitsskip:
        add #0x30    ;// Add ASCII numbers offset
        call #VPUTMAP
        djnz printnumxyprintdigits
    __endasm;
}

void printnum(unsigned int number)
{
    if (number == 0) {
        puts("0");
    } else {
        printdigits(number);
    }
}

