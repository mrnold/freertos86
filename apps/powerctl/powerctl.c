#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "ti86.h"

portTASK_FUNCTION_PROTO(keys, params);
portTASK_FUNCTION_PROTO(link, params);
portTASK_FUNCTION_PROTO(menu, params);
QueueHandle_t keyqueue;
struct keymsg {
    unsigned char mask;
    unsigned char bits;
};

void main(void)
{
    setxy(32, 32);
    puts("FreeRTOS startup");
    keyqueue = xQueueCreate(10, sizeof(struct keymsg));
    xTaskCreate(keys, "keys", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(link, "link", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(menu, "menu", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

    vTaskStartScheduler();
    setxy(0, 16);
    puts("FreeRTOS done.");
}

__sfr __at 0x01 keyport;
portTASK_FUNCTION(keys, params)
{
    struct keymsg key;
    while (1) {
        key.mask = 0xfe;
        keyport = key.mask;
        key.bits = keyport;
        if (key.bits != 0xff) {
            xQueueSend(keyqueue, &key, 0);
        }
        key.mask = 0xbf;
        keyport = key.mask;
        key.bits = keyport;
        if (key.bits != 0xff) {
            xQueueSend(keyqueue, &key, 0);
        }
        vPortYield();
    }
}

portTASK_FUNCTION(link, params)
{
    while (1) {
        vPortYield();
    }
}

portTASK_FUNCTION(menu, params)
{
    struct keymsg key;
    setxy(0, 0);
    puts("Power Control");
    while (1) {
        xQueueReceive(keyqueue, &key, portMAX_DELAY);
        setxy(0, 16);
        printnum(key.mask);
        setxy(0, 24);
        printnum(key.bits);
        if (key.mask == 0xfe) {
            setxy(0, 8);
            if ((key.bits & 0x08) == 0) {
                puts("up ");
            }
            if ((key.bits & 0x04) == 0) {
                puts("right ");
            }
            if ((key.bits & 0x02) == 0) {
                puts("left ");
            }
            if ((key.bits & 0x01) == 0) {
                puts("down ");
            }
        } else if (key.mask == 0xbf) {
            if ((key.bits & 0x40) == 0) {
                setxy(0, 8);
                puts("Exit key pressed, quitting!");
                vPortEndScheduler();
            }
        }
    }
}
