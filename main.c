#include <stdint.h>
#include <systick.h>
#include <clock.h>
#include "TCB.h"

// Initialise RAM
extern uint32_t __sdata;
extern uint32_t __edata;
extern uint32_t __sidata;
extern uint32_t __sbss;
extern uint32_t __ebss;

// Global initialized
uint8_t schedularStarted = 0;
uint32_t task1Data = 0;
uint32_t task2Data = 0;
uint32_t task3Data = 0;

// Task 1
void task1() {
    while(1) {
        task1Data += 1;
    }
}

// Task 2
void task2() {
    while(1) {
        task2Data += 1;
    }
}

// Task 3
void task3() {
    while(1) {
        task3Data += 1;
    }
}

// Initialize stack for tasks
uint32_t* initTask(uint32_t* stack, void (*task)(void)) {
    *(--stack) = 0x01000000; // xPSR ->Thumb mode bit set
    *(--stack) = (uint32_t)task; // PC
    *(--stack) = 0xFFFFFFFD; // LR -> Use MSP on exit
    *(--stack) = 0x12; // R12
    *(--stack) = 0x00; // R0
    *(--stack) = 0x01; // R1
    *(--stack) = 0x02; // R2
    *(--stack) = 0x03; // R3
    *(--stack) = 0x08; // R8
    *(--stack) = 0x09; // R9
    *(--stack) = 0x10; // R10
    *(--stack) = 0x11; // R11
    *(--stack) = 0x04; // R4
    *(--stack) = 0x05; // R5
    *(--stack) = 0x06; // R6
    *(--stack) = 0x07; // R7
    return stack;
}

// Initialise clocks and settings for SysTick
void initSysTick() {
    SYST_RVR->RELOAD = 0xFFFFFF;
    SYST_CSR->ENABLE = 1; 
    SYST_CSR->TICKINT = 1;
    SYST_CSR->CLKSOURCE = 1;
}

void main() {
    // Prepare RAM
    uint32_t *src = &__sidata;
    uint32_t *dst = &__sdata;

    uint32_t srcs = __sidata;
    
    while(dst < &__edata) {
        *dst++ = *src++;
    }

    dst = &__sbss;
    while(dst < &__ebss) {
        *dst++ = 0;
    }

    // Prepare Tasks

    task1_TCB.sp = initTask(&task1Stack[64], task1);
    task1_TCB.next = &task2_TCB;
    task2_TCB.sp = initTask(&task2Stack[64], task2);
    task2_TCB.next = &task3_TCB;
    task3_TCB.sp = initTask(&task3Stack[64], task3);
    task3_TCB.next = &task1_TCB;

    head = &task3_TCB;

    initSysTick();
    while(1);
}
