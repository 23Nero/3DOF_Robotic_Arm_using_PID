#ifndef __TIMER_H__
#define __TIMER_H__

#include <stdint.h> // Include this header to use uint32_t

#define CHANEL1 1
#define CHANEL2 2
#define CHANEL3 3
#define CHANEL4 4

// Định nghĩa các bit cho thanh ghi CR1
#define TIM_CR1_CEN (1U << 0)  // Bật bộ đếm (Counter Enable)
#define TIM_CR1_UDIS (1U << 1) // Vô hiệu hóa cờ update
#define TIM_CR1_URS (1U << 2)  // Bật chế độ ngắt chỉ sau lần update
#define TIM_CR1_OPM (1U << 3)  // Chế độ one-pulse
#define TIM_CR1_DIR (1U << 4)  // Chế độ tính toán xuôi (upcounting) hoặc ngược (downcounting)
#define TIM_CR1_CMS (3U << 5)  // Chế độ bảng so sánh (Center-aligned mode selection)
#define TIM_CR1_ARPE (1U << 7) // Bật auto-reload preload enable

// Định nghĩa các bit cho thanh ghi SR (Status Register)
#define TIM_SR_UIF (1U << 0) // Cờ update (Update interrupt flag)

// Định nghĩa giá trị cho chế độ chạy cơ bản
#define TIM_MODE_BASIC (TIM_CR1_CEN | TIM_CR1_ARPE)
#define TIM_CCER_CC1P (1u << 0) // 0: OC1 active high
                               // 1: OC1 active low
#define TIM_CCER_CC2P (1u << 5)
#define TIM_CCER_CC3P (1u << 9)
#define TIM_CCER_CC4P (1u << 13)

// Định nghĩa các bit cho thanh ghi CCER
#define TIM_CCER_CC1E (1U << 0) // Bật chức năng Capture/Compare cho kênh 1
#define TIM_CCER_CC2E (1U << 4) // Bật chức năng Capture/Compare cho kênh 2
#define TIM_CCER_CC3E (1U << 8) // Bật chức năng Capture/Compare cho kênh 3
#define TIM_CCER_CC4E (1U << 12) // Bật chức năng Capture/Compare cho kênh 4

#define TIM_CCMR1_CC1S_INPUT_TI1 (1 << 0)

#define TIM_SR_CC1IF (1u << 1)
#define TIM_SR_CC2IF (1u << 2)
#define TIM_SR_CC3IF (1u << 3)
#define TIM_SR_CC4IF (1u << 4)

#define TIM_OCMODE1_PWM1 (6 << 4)
#define TIM_OCMODE2_PWM1 (6 << 12)
#define TIM_OCMODE_TOGGLE (3 << 4)

#define PWM_PRESCALER   62
#define PWM_PERIOD      255
#define ACTIVE_LOW      1
#define ACTIVE_HIGH     0

#define TIM11_BASE ((uint32_t *)0x40014800)
#define TIM10_BASE ((uint32_t *)0x40014400)
#define TIM9_BASE ((uint32_t *)0x40014000)
#define TIM8_BASE ((uint32_t *)0x40010400)
#define TIM1_BASE ((uint32_t *)0x40010000)
#define TIM14_BASE ((uint32_t *)0x40002000)
#define TIM13_BASE ((uint32_t *)0x40001C00)
#define TIM12_BASE ((uint32_t *)0x40001800)
#define TIM7_BASE ((uint32_t *)0x40001400)
#define TIM6_BASE ((uint32_t *)0x40001000)
#define TIM5_BASE ((uint32_t *)0x40000C00)
#define TIM4_BASE ((uint32_t *)0x40000800)
#define TIM3_BASE ((uint32_t *)0x40000400)
#define TIM2_BASE ((uint32_t *)0x40000000)

/*TIM2 - TIM 5*/
typedef struct timer
{
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t SMCR;
    volatile uint32_t DIER;
    volatile uint32_t SR;
    volatile uint32_t EGR;
    volatile uint32_t CCMR1;
    volatile uint32_t CCMR2;
    volatile uint32_t CCER;
    volatile uint32_t CNT;
    volatile uint32_t PSC;
    volatile uint32_t ARR;
    volatile uint32_t RCR;
    volatile uint32_t CCR1;
    volatile uint32_t CCR2;
    volatile uint32_t CCR3;
    volatile uint32_t CCR4;
    volatile uint32_t BDTR;
    volatile uint32_t DCR;
    volatile uint32_t DMAR;
    volatile uint32_t OR;

} timer_t;

#define TIM1 ((timer_t *)TIM1_BASE)
#define TIM2 ((timer_t *)TIM2_BASE)
#define TIM3 ((timer_t *)TIM3_BASE)
#define TIM4 ((timer_t *)TIM4_BASE)
#define TIM5 ((timer_t *)TIM5_BASE)
#define TIM6 ((timer_t *)TIM6_BASE)
#define TIM7 ((timer_t *)TIM7_BASE)
#define TIM8 ((timer_t *)TIM8_BASE)
#define TIM9 ((timer_t *)TIM9_BASE)
#define TIM10 ((timer_t *)TIM10_BASE)
#define TIM11 ((timer_t *)TIM11_BASE)
#define TIM12 ((timer_t *)TIM12_BASE)
#define TIM13 ((timer_t *)TIM13_BASE)
#define TIM14 ((timer_t *)TIM14_BASE)

void TIM_Config(timer_t *tim, uint32_t prescaler, uint32_t period, uint32_t mode);
void TIM_Start(timer_t *tim);
void TIM_Stop(timer_t *tim);
uint32_t TIM_GetUpdateInterruptStatus(timer_t *tim);
void TIM_ClearUpdateInterruptFlag(timer_t *tim);

void TIM_ConfigOutputCompare(timer_t *tim, uint8_t channel, uint32_t mode);
void TIM_SetDutyCycle(timer_t *tim, uint8_t channel, uint16_t dutyCycle);
void TIM_EnableOutputCompare(timer_t *tim, uint8_t channel, int polarity);
void TIM_DisableOutputCompare(timer_t *tim, uint8_t channel);

void TIM_ConfigInputCapture(timer_t *tim, uint8_t channel, uint32_t mode);
uint32_t TIM_ReadCapturedValue(timer_t *tim, uint8_t channel);
void TIM_ClearCaptureFlag(timer_t *tim, uint8_t channel);

#endif
