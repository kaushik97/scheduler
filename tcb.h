#ifndef TCB_H
#define TCB_H

#include<stdint.h>

typedef struct TCB_t {
    uint32_t* sp;
    struct TCB_t* next;
} TCB;

extern TCB task1_TCB;
extern TCB task2_TCB;
extern TCB task3_TCB;
extern TCB* head;

// Stacks for tasks
extern uint32_t task1Stack[64];
extern uint32_t task2Stack[64];
extern uint32_t task3Stack[64];

#endif