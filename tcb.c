#include "tcb.h"

TCB task1_TCB;
TCB task2_TCB;
TCB task3_TCB;
TCB* head;

// Stacks for tasks
uint32_t task1Stack[64];
uint32_t task2Stack[64];
uint32_t task3Stack[64];