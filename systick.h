#ifndef SYSTICK_H
#define SYSTICK_H

#include <stdint.h>

typedef struct {
    volatile uint32_t ENABLE :1;
    volatile uint32_t TICKINT :1;
    volatile uint32_t CLKSOURCE :1;
    volatile uint32_t RES1 :13;
    volatile uint32_t COUNTFLAG :1;
    volatile uint32_t RES2 :15;
} SYST_CSR_t;

typedef struct {
    volatile uint32_t RELOAD :24;
    volatile uint32_t RES :8;
} SYST_RVR_t;

typedef struct {
    volatile uint32_t CURRENT :24;
    volatile uint32_t RES :8;
} SYST_CVR_t;

typedef struct {
    volatile uint32_t TENMS :24;
    volatile uint32_t RES :6;
    volatile uint32_t SKEW :1;
    volatile uint32_t NOREF :1;
} SYST_CALIB_t;

#define SYST_CSR    ((volatile SYST_CSR_t*)0xE000E010)
#define SYST_RVR    ((volatile SYST_RVR_t*)0xE000E014)
#define SYST_CVR    ((volatile SYST_CVR_t*)0xE000E018)
#define SYST_CALIB  ((volatile SYST_CALIB_t*)0xE000E01C)

#endif