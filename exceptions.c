#include<stdint.h>
#include "TCB.h"

#define ICSR (*(volatile uint32_t*)0xE000ED04)

extern void NMI_handler();
extern void hardFault_handler();
extern void SVCall_handler();
extern void pendSV_handler();
extern void sysTick_handler();

void NMI_handler() {}
void hardFault_handler() {}
void SVCall_handler() {}

extern uint8_t schedularStarted;

// Exception systick handler
void sysTick_handler() {
    // Trigger pendSV Exception
    ICSR = (1 << 28);
}

// Exception pendSV handler - Using MSP only for context switching
__attribute__((naked)) 
void pendSV_handler() {
    __asm volatile
    (
        ".syntax unified \n"
        ".thumb \n"
        /*push current task r4-r11 to stack*/
        "push {r4-r7} \n"
        "mov r0, r8 \n"
        "mov r1, r9 \n"
        "mov r2, r10 \n"
        "mov r3, r11 \n"
        "push {r0-r3} \n"

        // If scheduler already started, save sp
        "ldr r0, =schedularStarted \n"
        "ldr r0, [r0] \n"
        "cmp r0, #0 \n"
        "beq skip_save \n"

        // Storing current task sp
        "mrs r0, msp \n"
        "ldr r1, =head \n"
        "ldr r1, [r1] \n"
        "str r0, [r1] \n" 
        
        "skip_save: \n"
        "movs r0, #1 \n"
        "ldr r1, =schedularStarted \n"
        "str r0, [r1] \n"

        // Save next as current
        "ldr r0, =head \n"
        "ldr r1, [r0] \n"
        "ldr r1, [r1, #4] \n"
        "str r1, [r0] \n"
        "ldr r0, [r0] \n"
        "ldr r0, [r0] \n"
        "msr msp, r0 \n"
        "pop {r4-r7} \n"
        "mov r8, r4 \n"
        "mov r9, r5 \n"
        "mov r10, r6 \n"
        "mov r11, r7 \n"
        "pop {r4-r7} \n"
        "bx lr \n"
    );
}

// Exception pendSV handler - Using PSP for context switching
__attribute__((naked))
void pendSV_handler() {
    __asm volatile 
    (
        ".syntax unified \n"
        ".thumb \n"

        "mrs r0, psp \n"
        "cmp r0, #0 \n"
        "beq skip_save \n"

        "subs r0,r0,#32 \n"
        "stmia r0!,{r4-r7} \n"
        "mov r4, r8 \n"
        "mov r5, r9 \n"
        "mov r6, r10 \n"
        "mov r7, r11 \n"
        "stmia r0!, {r4-r7} \n"
        "subs r0, r0, #32 \n"
  
        "ldr r1, =head \n"
        "ldr r1, [r1] \n"
        "str r0, [r1] \n"

        "skip_save: \n"
        // Move head to point next task
        "ldr r1, =head \n"
        "ldr r2, [r1] \n"
        "ldr r2, [r2, #4] \n" // load next task sp
        "str r2, [r1] \n" // move head to next tcb

        "ldr r0, [r2] \n"
        "adds r0, r0, #16 \n"
        "ldmia r0!, {r4-r7} \n"
        "mov r8, r4 \n"
        "mov r9, r5 \n"
        "mov r10, r6 \n"
        "mov r11, r7 \n"
        "subs r0,r0,#32 \n"
        "ldmia r0!, {r4-r7} \n"
        "adds r0, r0, #16 \n"
        "msr psp, r0 \n"

        // Shift from msp to psp
        "movs r3, #2 \n"
        "msr control, r3 \n"
        "isb \n"
        
        "ldr r0, =0xFFFFFFFD \n"
        "mov lr, r0 \n"
        "bx lr \n"
    );
}