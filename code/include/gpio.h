#ifndef __GPIO_H__
#define __GPIO_H__

#include <stdint.h>

// GPIO Modes
#define INPUT 0x00
#define OUTPUT 0x01
#define ALTERNATE 0x02
#define ANALOG 0x03

// GPIO Output Types
#define TYPE_PUSHPULL 0x00
#define TYPE_OPENDRAIN 0x01

// GPIO Output Speeds
#define SPEED_LOW 0x00
#define SPEED_MEDIUM 0x01
#define SPEED_HIGH 0x02
#define SPEED_VERY_HIGH 0x03

// GPIO Pull-Up/Pull-Down
#define PULL_NONE 0x00
#define PULL_UP 0x01
#define PULL_DOWN 0x02

// GPIO Alternate Functions
#define AF0 0x00
#define AF1 0x01
#define AF2 0x02
#define AF3 0x03
#define AF4 0x04
#define AF5 0x05
#define AF6 0x06
#define AF7 0x07
#define AF8 0x08
#define AF9 0x09
#define AF10 0x0A
#define AF11 0x0B
#define AF12 0x0C
#define AF13 0x0D
#define AF14 0x0E
#define AF15 0x0F

#define GPIOH_BASE ((uint32_t *)0x40021C00)
#define GPIOG_BASE ((uint32_t *)0x40021800)
#define GPIOF_BASE ((uint32_t *)0x40021400)
#define GPIOE_BASE ((uint32_t *)0x40021000)
#define GPIOD_BASE ((uint32_t *)0x40020C00)
#define GPIOC_BASE ((uint32_t *)0x40020800)
#define GPIOB_BASE ((uint32_t *)0x40020400)
#define GPIOA_BASE ((uint32_t *)0x40020000)

typedef struct GPIO
{
    volatile uint32_t MODER;   // Mode register
    volatile uint32_t OTYPER;  // Output type register
    volatile uint32_t OSPEEDR; // Output speed register
    volatile uint32_t PUPDR;   // Pull-up/pull-down register
    volatile uint32_t IDR;     // Input data register
    volatile uint32_t ODR;     // Output data register
    volatile uint32_t BSRR;    // Bit set/reset register
    volatile uint32_t LCKR;    // Configuration lock register
    volatile uint32_t AFRL;    // Alternate function registers (AFRL and AFRH)
    volatile uint32_t AFRH;
} GPIO_t;

#define GPIO_A ((GPIO_t *)GPIOA_BASE)
#define GPIO_B ((GPIO_t *)GPIOB_BASE)
#define GPIO_C ((GPIO_t *)GPIOC_BASE)
#define GPIO_D ((GPIO_t *)GPIOD_BASE)
#define GPIO_E ((GPIO_t *)GPIOE_BASE)
#define GPIO_F ((GPIO_t *)GPIOF_BASE)
#define GPIO_G ((GPIO_t *)GPIOG_BASE)
#define GPIO_H ((GPIO_t *)GPIOH_BASE)

void GPIO_setMode(GPIO_t *gpio, uint32_t pin, uint32_t mode);
void GPIO_setOutputType(GPIO_t *gpio, uint32_t pin, uint32_t type);
void GPIO_setOutputSpeed(GPIO_t *gpio, uint32_t pin, uint32_t speed);
void GPIO_setPullUpDown(GPIO_t *gpio, uint32_t pin, uint32_t pupd);
void GPIO_setPin(GPIO_t *gpio, uint32_t pin);
void GPIO_resetPin(GPIO_t *gpio, uint32_t pin);
void GPIO_togglePin(GPIO_t *gpio, uint32_t pin);
uint32_t GPIO_readPin(GPIO_t *gpio, uint32_t pin);
void GPIO_setAlternateFunction(GPIO_t *gpio, uint32_t pin, uint32_t alternateFunction);

#endif
