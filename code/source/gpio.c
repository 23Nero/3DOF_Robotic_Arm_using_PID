#include "./../include/gpio.h"
#include "./../include/RCC.h"

// Function to configure the mode of a GPIO pin
void GPIO_setMode(GPIO_t *gpio, uint32_t pin, uint32_t mode)
{
    uint32_t temp = gpio->MODER;
    temp &= ~(3u << (pin * 2));         // Clear mode bits for the specific pin
    temp |= (mode & 0x03) << (pin * 2); // Set the new mode
    gpio->MODER = temp;
}

// Function to configure the output type of a GPIO pin
void GPIO_setOutputType(GPIO_t *gpio, uint32_t pin, uint32_t type)
{
    uint32_t temp = gpio->OTYPER;
    temp &= ~(1 << pin);   // Clear the type bit for the specific pin
    temp |= (type << pin); // Set the new type
    gpio->OTYPER = temp;
}

// Function to configure the output speed of a GPIO pin
void GPIO_setOutputSpeed(GPIO_t *gpio, uint32_t pin, uint32_t speed)
{
    uint32_t temp = gpio->OSPEEDR;
    temp &= ~(3u << (pin * 2));   // Clear speed bits for the specific pin
    temp |= (speed << (pin * 2)); // Set the new speed
    gpio->OSPEEDR = temp;
}

// Function to configure the pull-up/pull-down of a GPIO pin
void GPIO_setPullUpDown(GPIO_t *gpio, uint32_t pin, uint32_t pupd)
{
    uint32_t temp = gpio->PUPDR;
    temp &= ~(3u << (pin * 2));  // Clear pupd bits for the specific pin
    temp |= (pupd << (pin * 2)); // Set the new pupd
    gpio->PUPDR = temp;
}

// Function to set the state of a GPIO pin
void GPIO_setPin(GPIO_t *gpio, uint32_t pin)
{
    gpio->BSRR |= (1 << pin);
}

// Function to reset the state of a GPIO pin
void GPIO_resetPin(GPIO_t *gpio, uint32_t pin)
{
    gpio->BSRR |= (1u << (pin + 16));
}
void GPIO_togglePin(GPIO_t *gpio, uint32_t pin)
{
    gpio->ODR ^= (1 << pin);
}

// Function to read the state of a GPIO pin
uint32_t GPIO_readPin(GPIO_t *gpio, uint32_t pin)
{
    return gpio->IDR & (1 << pin);
}

void GPIO_setAlternateFunction(GPIO_t *gpio, uint32_t pin, uint32_t alternateFunction)
{
    if (pin < 8)
    {
        uint32_t temp = gpio->AFRL;
        temp &= ~(0xFu << (pin * 4));              // Clear AF bits for the specific pin
        temp |= (alternateFunction << (pin * 4)); // Set the new AF
        gpio->AFRL = temp;
    }
    else
    {
        pin -= 8; // Adjust pin index for AFRH
        uint32_t temp = gpio->AFRH;
        temp &= ~(0xFu << (pin * 4));              // Clear AF bits for the specific pin
        temp |= (alternateFunction << (pin * 4)); // Set the new AF
        gpio->AFRH = temp;
    }
}
