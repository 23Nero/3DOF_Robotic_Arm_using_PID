#ifndef __sysTick_H__
#define __sysTick_H__

#include <stdint.h>

// sysTick timer
#define INTTERUPT 1
extern uint32_t FLAG_SYST_INT;

typedef struct sysTick
{
	volatile uint32_t CSR;	  // 0xE000E010 SYST_CSR RW Privileged a sysTick Control and Status Register
	volatile uint32_t RVR;	  // 0xE000E014 SYST_RVR RW Privileged Unknown sysTick Reload Value Register on page 4-34
	volatile uint32_t CVR;	  // 0xE000E018 SYST_CVR RW Privileged Unknown sysTick Current Value Register on page 4-35
	volatile uint32_t CALIB; // 0xE000E01C SYST_CALIB RO Privileged -a sysTick Calibration Value Register on page 4-35
} sysTick_t;

#define sysTick ((sysTick_t *)((uint32_t *)0xE000E010))

void configSysTickInt(uint8_t interrupt);
void delay(uint32_t milliseconds);

#endif
