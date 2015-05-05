/* Launcher program for FreeRTOS-86.
   This program loads FreeRTOS and an application using the following steps:
    - Find the application and copy it to 0xA000
    - Find the FreeRTOS module and copy it to 0x8100
    - Call 0xA000 to start the application.*/

void main(void) __naked
{
    __asm
        ret
    __endasm;
}
