#include "./../include/i2c.h"

//void EXTI_Config(uint32_t exti, uint32_t mode, uint32_t trigger)
//{
//    EXTI->IMR |= (1 << exti); // Enable interrupt on the exti
//    EXTI->RTSR &= ~(1 << exti); // Clear rising trigger bit
//    EXTI->FTSR &= ~(1 << exti); // Clear falling trigger bit

//    if (trigger & EXTI_TRIGGER_RISING)
//        EXTI->RTSR |= (1 << exti); // Set rising trigger bit

//    if (trigger & EXTI_TRIGGER_FALLING)
//        EXTI->FTSR |= (1 << exti); // Set falling trigger bit

//    // Configure EXTI pin in SYSCFG
//    uint32_t port = exti / 4;
//    uint32_t pin = exti % 4;
//    SYSCFG->EXTICR[port] |= (pin << (4 * pin));
//}
