#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#include <stdint.h> // Include this header to use uint32_t

#define EXTI_BASE ((uint32_t *)0x40013C00)
#define SYSCFG_BASE ((uint32_t *)0x40013800)

typedef struct EXTI
{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;

} EXTI_t;

typedef struct NVIC
{
	volatile uint32_t ISER[8]; // set interrupt
	volatile uint32_t ICER[8]; // NVIC_ICER0- NVIC_ICER7 RW Privileged 0x00000000 Interrupt Clear-enable Registers on page 4-5
	volatile uint32_t ISPR[8]; // NVIC_ISPR0- NVIC_ISPR7 RW Privileged 0x00000000 Interrupt Set-pending Registers on page 4-5
	volatile uint32_t ICPR[8]; // NVIC_ICPR0- NVIC_ICPR7 RW Privileged 0x00000000 Interrupt Clear-pending Registers on page 4-6
	volatile uint32_t IABR[8]; // NVIC_IABR0- NVIC_IABR7 RW Privileged 0x00000000 Interrupt Active Bit Registers on page 4-7
	volatile uint32_t IPR[8];  // NVIC_IPR0-NVIC_IPR59 RW Privileged 0x00000000 Interrupt Priority Registers on page 4-7
	volatile uint32_t STIR[8]; // STIR WO Configurablea 0x00000000 Software Trigger Interrupt Register on page 4-8
} NVIC_t;

typedef struct SYSCFG
{
	volatile uint32_t MEMRMP;
	volatile uint32_t PMC;
	volatile uint32_t EXTICR1;
	volatile uint32_t EXTICR2;
	volatile uint32_t EXTICR3;
	volatile uint32_t EXTICR4;
	volatile uint32_t CMPCR;
	volatile uint32_t CFGR;

} SYSCFG_t;

#define NVIC ((NVIC_t *)((uint32_t *)0xE000E100))

#define EXTI ((EXTI_t *)EXTI_BASE)
#define SYSCFG ((SYSCFG_t *)SYSCFG_BASE)

void EXTI15_10_IRQHandler(void);
void USART2_IRQHandler(void);
void EXTI9_5_IRQHandler(void);
void TIM4_IRQHandler(void);

#endif
