#ifndef __RCC_H__
#define __RCC_H__

#include <stdint.h> // Include this header to use uint32_t
#include <stdlib.h>
#include <stdio.h>

#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif

#define SYSTEM_CORE_CLOCK 16000000
#define NULL 0

#define SYSCFGEN (1 << 14)
#define SPI1EN (1 << 12) // APB2ENR
#define SPI4EN (1 << 13) // APB2ENR

#define RCC_BASE ((uint32_t *)0x40023800)

typedef struct RCC
{
    volatile uint32_t CR;
    volatile uint32_t PLLCFGR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t AHB1RSTR;
    volatile uint32_t AHB2RSTR;
    volatile uint32_t AHB3RSTR;
    volatile uint32_t RESERVED0;
    volatile uint32_t APB1RSTR;
    volatile uint32_t APB2RSTR;
    volatile uint32_t RESERVED1[2];
    volatile uint32_t AHB1ENR;
    volatile uint32_t AHB2ENR;
    volatile uint32_t AHB3ENR;
    volatile uint32_t RESERVED2;
    volatile uint32_t APB1ENR;
    volatile uint32_t APB2ENR;
    volatile uint32_t RESERVED3[2];
    volatile uint32_t AHB1LPENR;
    volatile uint32_t AHB2LPENR;
    volatile uint32_t AHB3LPENR;
    volatile uint32_t RESERVED4;
    volatile uint32_t APB1LPENR;
    volatile uint32_t APB2LPENR;
    volatile uint32_t RESERVED5[2];
    volatile uint32_t BDCR;
    volatile uint32_t CSR;
    volatile uint32_t RESERVED6[2];
    volatile uint32_t SSCGR;
    volatile uint32_t PLLI2SCFGR;
    volatile uint32_t PLLSAICFGR;
    volatile uint32_t DCKCFGR;
} RCC_t;

#define RCC ((RCC_t *)RCC_BASE) // Corrected from "PCC_t" to "RCC_t"

#endif
