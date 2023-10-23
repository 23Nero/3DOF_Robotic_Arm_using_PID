#ifndef __DMA_H__
#define __DMA_H__

#include <stdint.h>

#define DMA1_BASE ((uint32_t *)0x40026000)
#define DMA2_BASE ((uint32_t *)0x40024000)

typedef struct DMA_Stream
{
    volatile uint32_t CR;    // Control register
    volatile uint32_t NDTR;  // Number of data items to transfer
    volatile uint32_t PAR;   // Peripheral address register
    volatile uint32_t M0AR;  // Memory 0 address register
    volatile uint32_t M1AR;  // Memory 1 address register
    volatile uint32_t FCR;   // FIFO control register
} DMA_Stream_t;

typedef struct DMA
{
    volatile uint32_t LISR;   // Low interrupt status register
    volatile uint32_t HISR;   // High interrupt status register
    volatile uint32_t LIFCR;  // Low interrupt flag clear register
    volatile uint32_t HIFCR;  // High interrupt flag clear register
    DMA_Stream_t stream[8];   // DMA stream registers
} DMA_t;

extern DMA_t *DMA1;
extern DMA_t *DMA2;

#endif
