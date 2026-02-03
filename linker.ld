MEMORY {
    FLASH (rx)  : ORIGIN = 0x00000000 , LENGTH = 256k
    RAM   (rwx) : ORIGIN = 0x20000000 , LENGTH = 32k
}

SECTIONS {
    .vectors ORIGIN(FLASH) :
    {
        *(.vectors*)
    } > FLASH

    .text : 
    {
        *(.text*)
        *(.rodata*)
    } > FLASH

    .data : ALIGN(4) 
    {
        __sdata = .;
        *(.data*)
        *(.rodata*)
        . = ALIGN(4);
        __edata = .;
    } > RAM AT > FLASH

    __sidata = LOADADDR(.data);

    .bss (NOLOAD) : ALIGN(4) 
    {
        __sbss = .;
        *(.bss*)
        . = ALIGN(4);
        __ebss = .;
    } > RAM

    __stackTop = ORIGIN(RAM) + LENGTH(RAM);
    __stack = __stackTop & ~0x07;
}