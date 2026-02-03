.syntax unified
.cpu cortex-m0plus
.thumb

.section .vectors, "a"

vector_table:
    .word __stack
    .word reset_handler
    .word NMI_handler
    .word hardFault_handler
    .zero 28
    .word SVCall_handler
    .zero 8
    .word pendSV_handler
    .word sysTick_handler

.section .text
.thumb
.thumb_func

reset_handler:
    b main
    b .
    