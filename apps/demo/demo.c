#include "FreeRTOS.h"
#include "task.h"

portTASK_FUNCTION_PROTO(A, delay);
portTASK_FUNCTION_PROTO(B, delay);

void main(void)
{
    xTaskCreate(A, "A", configMINIMAL_STACK_SIZE, (void *)10, 3, NULL);
    xTaskCreate(B, "B", configMINIMAL_STACK_SIZE, (void *)3,  2, NULL);
    vTaskStartScheduler();
}

void putchar(char c)
{
    c;
    __asm
        di
        ld l, 4(ix)
        ld a, l
        call 0x4a2b
        ei
    __endasm;
}

__sfr __at 0x01 keyport;

portTASK_FUNCTION(A, delay)
{
    int ticks = (int)delay;
    char a = 'A';

    while (1) {
        putchar(a);
        vTaskDelay(ticks);	
        keyport = 0xfe;
        if (keyport != 0xff) {
            a++;
        }
    }
}

portTASK_FUNCTION(B, delay)
{
    int ticks = (int)delay;
    char b = 'B';

    while (1) {
        putchar(b);
        vTaskDelay(ticks);	
        keyport = 0xbf;
        if (keyport != 0xff) {
            b--;
        }
    }
}
