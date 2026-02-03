#ifndef CLOCK_H
#define CLOCK_H

#include <stdint.h>

#define MCLK ((MCLK_t *)0x40000C00)

typedef struct {
    uint32_t APBA:1;
    uint32_t APBB:1;
    uint32_t APBC:1;
    uint32_t DSU:1;
    uint32_t HMATRIXHS:1;
    uint32_t NVMCTRL:1;
    uint32_t HSRAM:1;
    uint32_t DMAC:1;
    uint32_t CAN0:1;
    uint32_t CAN1:1;
    uint32_t PAC:1;
    uint32_t RES1:1;
    uint32_t DIVAS:1;
    uint32_t APBD:1;
    uint32_t RES2:18;
} AHBMASK_t;

typedef struct {
    uint32_t PAC:1;
    uint32_t PM:1;
    uint32_t MCLKK:1;
    uint32_t RSTC:1;
    uint32_t OSCCTRL:1;
    uint32_t OSC32KCTRL:1;
    uint32_t SUPC:1;
    uint32_t GCLK:1;
    uint32_t WDT:1;
    uint32_t RTC:1;
    uint32_t EIC:1;
    uint32_t FREQM:1;
    uint32_t TSENS:1;
    uint32_t RES:19;
} APBAMASK_t;

typedef struct {
    uint32_t PORT:1;
    uint32_t DSU:1;
    uint32_t NVMCTRL:1;
    uint32_t RES1:2;
    uint32_t HMATRIXHS:1;
    uint32_t RES2:26;
} APBBMASK_t;

typedef struct {
    volatile uint8_t CTRLA;
    volatile uint8_t INTENCLR;
    volatile uint8_t INTENSET;
    volatile uint8_t INTFLAG;
    volatile uint8_t RES1;
    volatile uint8_t CPUDIV;
    volatile uint8_t RES2[10];
    volatile AHBMASK_t AHBMASK;
    volatile APBAMASK_t APBAMASK;
    volatile APBBMASK_t APBBMASK;
    volatile uint32_t APBCMASK;
    volatile uint32_t APBDMASK;
} MCLK_t;

#endif