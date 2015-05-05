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

portTASK_FUNCTION(A, delay)
{
    int ticks = (int)delay;

    while (1) {
        vTaskDelay(ticks);	
    }
}

portTASK_FUNCTION(B, delay)
{
    int ticks = (int)delay;

    while (1) {
        vTaskDelay(ticks);	
    }
}
