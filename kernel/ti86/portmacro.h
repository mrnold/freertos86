#define portMAX_DELAY 0xffff
#define portSTACK_GROWTH (-1)
#define portBYTE_ALIGNMENT (1)

typedef unsigned short StackType_t;
typedef unsigned short TickType_t;
typedef unsigned char UBaseType_t;
typedef char BaseType_t;
void vPortYield(void);

#define portTASK_FUNCTION_PROTO(func, params) void func(void *params)
#define portTASK_FUNCTION(func, params) void func(void *params)
#define portDISABLE_INTERRUPTS() __asm__("di")
#define portENABLE_INTERRUPTS() __asm__("ei")
#define portENTER_CRITICAL() __asm__("di")
#define portEXIT_CRITICAL() __asm__("ei")
#define portYIELD() vPortYield()
