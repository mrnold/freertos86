#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "ti86.h"

portTASK_FUNCTION_PROTO(keys, params);
portTASK_FUNCTION_PROTO(link, params);
portTASK_FUNCTION_PROTO(menu, params);
QueueHandle_t keyqueue;

void main(void)
{
    keyqueue = xQueueCreate(10, 1);
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
    unsigned char key;
    while (1) {
        keyport = 0xfe;
        key = keyport;
        if (key != 0xff) {
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
    unsigned char key;
    setxy(0, 0);
    puts("Power Control");
    while (1) {
        xQueueReceive(keyqueue, &key, portMAX_DELAY);
        if (key != 0xff) {
            setxy(0, 8);
            puts("Key pressed, quitting!");
            vPortEndScheduler();
        }
    }
}
