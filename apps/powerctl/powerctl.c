#include "FreeRTOS.h"
#include "task.h"
#include "ti86.h"

portTASK_FUNCTION_PROTO(keys, params);
portTASK_FUNCTION_PROTO(link, params);
portTASK_FUNCTION_PROTO(menu, params);

void main(void)
{
    xTaskCreate(keys, "keys", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(link, "link", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(menu, "menu", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

    vTaskStartScheduler();
}

portTASK_FUNCTION(keys, params)
{
    while (1) {
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
    setxy(0, 0);
    puts("Power Control");
    while (1) {
        vPortYield();
    }
}
