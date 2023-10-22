#ifndef __ADC_H__
#define __ADC_H__

#include <stdint.h> // Include this header to use uint32_t

#define ADC1_BASE ((uint32_t *)0x40012000)
#define ADC2_BASE ((uint32_t *)0x40012100)
#define ADC3_BASE ((uint32_t *)0x40012200)
#define COMMONADC_BASE ((uint32_t *)0x40012300)

typedef struct ADC
{
    volatile uint32_t SR;    // Status Register
    volatile uint32_t CR1;   // Control Register 1
    volatile uint32_t CR2;   // Control Register 2
    volatile uint32_t SMPR1; // Sample Time Register 1
    volatile uint32_t SMPR2; // Sample Time Register 2
    volatile uint32_t JOFR1; // Injected Channel Offset Register 1
    volatile uint32_t JOFR2; // Injected Channel Offset Register 2
    volatile uint32_t JOFR3; // Injected Channel Offset Register 3
    volatile uint32_t JOFR4; // Injected Channel Offset Register 4
    volatile uint32_t HTR;   // Watchdog Higher Threshold Register
    volatile uint32_t LTR;   // Watchdog Lower Threshold Register
    volatile uint32_t SQR1;  // Regular Sequence Register 1
    volatile uint32_t SQR2;  // Regular Sequence Register 2
    volatile uint32_t SQR3;  // Regular Sequence Register 3
    volatile uint32_t JSQR;  // Injected Sequence Register
    volatile uint32_t JDR1;  // Injected Data Register 1
    volatile uint32_t JDR2;  // Injected Data Register 2
    volatile uint32_t JDR3;  // Injected Data Register 3
    volatile uint32_t JDR4;  // Injected Data Register 4
    volatile uint32_t DR;    // Regular Data Register

} ADC_t;

typedef struct commonADC
{
    volatile uint32_t CSR;
    volatile uint32_t CCR;
    volatile uint32_t CDR;

} commonADC_t;

#define ADC1 ((ADC_t *)ADC1_BASE)
#define ADC2 ((ADC_t *)ADC2_BASE)
#define ADC3 ((ADC_t *)ADC3_BASE)
#define COMMONADC ((commonADC_t *)COMMONADC_BASE)

#endif
