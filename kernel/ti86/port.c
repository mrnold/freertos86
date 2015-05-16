#include "FreeRTOS.h"
#include "task.h"

// Fill in the stack of a new task.
StackType_t *pxPortInitialiseStack(StackType_t *s, TaskFunction_t t, void *p)
{
    // Stack for the call to the task function
    *s-- = (StackType_t)p; // Parameters
    *s-- = (StackType_t)vTaskEndScheduler; // Return address
    *s-- = (StackType_t)t; // Task code start address
    // The 'ret' in the initial context restore will return to t.
    // The function t will expect the stack to have the return address of the
    // calling function, followed by parameters to the task function.
    // The return address does not necessarily need to be set, since tasks
    // aren't really supposed to return. This rule can be bent though.

    // Values for registers after initial context switch
    *s-- = (StackType_t)0x1111; // IX
    *s-- = (StackType_t)0xAFAF; // AF
    *s-- = (StackType_t)0xBCBC; // BC
    *s-- = (StackType_t)0xDEDE; // DE
    *s-- = (StackType_t)0xEFEF; // HL
    *s-- = (StackType_t)0xFAFA; // AF'
    *s-- = (StackType_t)0xCBCB; // BC'
    *s-- = (StackType_t)0xEDED; // DE'
    *s   = (StackType_t)0xFEFE; // HL'
    return s;
}

#define portSAVE_CONTEXT() \
    __asm__("di"); \
    __asm__("push ix"); \
    __asm__("push af"); \
    __asm__("push bc"); \
    __asm__("push de"); \
    __asm__("push hl"); \
    __asm__("ex af, af'"); \
    __asm__("exx"); \
    __asm__("push af"); \
    __asm__("push bc"); \
    __asm__("push de"); \
    __asm__("push hl"); \
    __asm__("ex af, af'"); \
    __asm__("exx"); \
    __asm__("ld hl, #0"); \
    __asm__("add hl, sp"); \
    __asm__("ex de, hl"); \
    __asm__("ld hl, (_pxCurrentTCB)"); \
    __asm__("ld (hl), e"); \
    __asm__("inc hl"); \
    __asm__("ld (hl), d")

#define portRESTORE_CONTEXT() \
    __asm__("di"); \
    __asm__("ld hl, (_pxCurrentTCB)"); \
    __asm__("ld e, (hl)"); \
    __asm__("inc hl"); \
    __asm__("ld d, (hl)"); \
    __asm__("ex de, hl"); \
    __asm__("ld sp, hl"); \
    __asm__("exx"); \
    __asm__("ex af, af'"); \
    __asm__("pop hl"); \
    __asm__("pop de"); \
    __asm__("pop bc"); \
    __asm__("pop af"); \
    __asm__("exx"); \
    __asm__("ex af, af'"); \
    __asm__("pop hl"); \
    __asm__("pop de"); \
    __asm__("pop bc"); \
    __asm__("pop af"); \
    __asm__("pop ix"); \
    __asm__("ei"); \
    __asm__("ret")

void vPortYieldFromTick(void)
{
    portSAVE_CONTEXT();
    xTaskIncrementTick();
    vTaskSwitchContext();
    portRESTORE_CONTEXT();
}

void vPortYield(void)
{
    portSAVE_CONTEXT();
    vTaskSwitchContext();
    portRESTORE_CONTEXT();
}

void timer_isr(void) __interrupt
{
    vPortYieldFromTick();
}

BaseType_t xPortStartScheduler(void)
{
    // Set up timer
    __asm
        di
        ld bc, #3
        ld hl, #jump_timer
        ld de, #0xF8F8
        ldir

        ld hl, #0xF900
        ld de, #0xF901
        ld (hl), #0xF8
        ld bc, #255
        ldir
        ld a, #0xF9
        ld i, a
        im 2
        ei
        jp timer_setup_done
    jump_timer::
        jp _timer_isr
    timer_setup_done:
    __endasm;

    portRESTORE_CONTEXT(); // Switch to first task

    return 0;
}

void vPortEndScheduler(void) __naked
{
    // Spin in circles
    __asm
        jp .
    __endasm;
}
