#include "FreeRTOS.h"

// Fill in the stack of a new task.
StackType_t *pxPortInitialiseStack(StackType_t *s, TaskFunction_t t, void *p)
{
    *s-- = (StackType_t)p; // Parameters
    *s-- = (StackType_t)0x0000; // Return address
    *s-- = (StackType_t)t; // Task code start address
    *s-- = (StackType_t)0x11111111; // IX
    *s-- = (StackType_t)0xAFAFAFAF; // AF
    *s-- = (StackType_t)0xBCBCBCBC; // BC
    *s-- = (StackType_t)0xDEDEDEDE; // DE
    *s-- = (StackType_t)0xEFEFEFEF; // HL
    *s-- = (StackType_t)0xFAFAFAFA; // AF'
    *s-- = (StackType_t)0xCBCBCBCB; // BC'
    *s-- = (StackType_t)0xEDEDEDED; // DE'
    *s   = (StackType_t)0xFEFEFEFE; // HL'
    return s;
}

BaseType_t xPortStartScheduler(void) { return 0; }

void vPortEndScheduler(void) { }

void vPortYield(void) { }
