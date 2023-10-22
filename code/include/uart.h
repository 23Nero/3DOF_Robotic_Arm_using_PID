#ifndef __USART_H__
#define __USART_H__

#include <stdint.h> // Include this header to use uint32_t
#include <string.h>

#define USART_SR_TXE (1 << 7)
#define USART_CR1_TE (1 << 3)
#define USART_CR1_RE (1 << 2)
#define USART_SR_TC (1 << 6)

#define USART_CR1_UE (1 << 13)
#define USART_CR1_TXEIE (1 << 7)
#define USART_CR1_RXNEIE (1 << 5)
#define USART_SR_TXE (1 << 7)
#define USART_SR_RXNE (1u << 5)

#define BUFFER 256

/* Define USART */
#define USART6_BASE ((uint32_t *)0x40011400)
#define USART1_BASE ((uint32_t *)0x40011000)
#define USART3_BASE ((uint32_t *)0x40004800)
#define USART2_BASE ((uint32_t *)0x40004400)

/* Define UART */
#define UART5_BASE ((uint32_t *)0x40005000)
#define UART4_BASE ((uint32_t *)0x40004C00)

typedef struct USART
{
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t BRR;
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t CR3;
    volatile uint32_t GTPR;
} USART_t;

#define USART6 ((USART_t *)USART6_BASE)
#define USART1 ((USART_t *)USART1_BASE)
#define USART3 ((USART_t *)USART3_BASE)
#define USART2 ((USART_t *)USART2_BASE)
#define UART5 ((USART_t *)UART5_BASE)
#define UART4 ((USART_t *)UART4_BASE)

uint32_t compute_uart(uint32_t PeriphClk, uint32_t BaudRate);
void uart_set_baudrate(USART_t *USARTx, uint32_t PeriphClk, uint32_t BaudRate);
void UART_configureTX(USART_t *USARTx);
void UART_configureRX(USART_t *USARTx);
void USART_sendChar(USART_t *usart, char ch);
void USART_sendString(USART_t *usart, const char *str);
uint8_t USART_read(USART_t *usart);
void USART_receiveString(USART_t *usart, char *buffer, uint32_t bufferSize);

#endif
