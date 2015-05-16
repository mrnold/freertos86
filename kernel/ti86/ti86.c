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
