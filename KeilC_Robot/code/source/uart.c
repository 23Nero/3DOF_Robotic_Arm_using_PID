#include "./../include/uart.h"
#include "./../include/RCC.h"

uint32_t compute_uart(uint32_t PeriphClk, uint32_t BaudRate)
{
    return ((PeriphClk + (BaudRate / 2u)) / BaudRate);
}

void uart_set_baudrate(USART_t *USARTx, uint32_t PeriphClk, uint32_t BaudRate)
{
    USARTx->BRR = compute_uart(PeriphClk, BaudRate);
}

void UART_configureTX(USART_t *USARTx)
{
    USARTx->CR1 |= USART_CR1_TE;
}

void UART_configureRX(USART_t *USARTx)
{
    USARTx->CR1 |= USART_CR1_RE;
}

void USART_sendChar(USART_t *usart, char ch)
{
    while (!(usart->SR & USART_SR_TXE));
    usart->DR = (ch & 0xFF);
}

void USART_sendString(USART_t *usart, const char *str)
{
    while (*str != '\0')
    {
        USART_sendChar(usart, *str);
        str++;
    }
}

uint8_t USART_read(USART_t *usart)
{
    while(!(usart->SR & (1 << 5)))
        ;
    return (uint8_t)(usart->DR);
}

void USART_receiveString(USART_t *usart, char *buffer, uint32_t bufferSize)
{
    char receivedChar;
    uint32_t charCount = 0;
    uint32_t timeout = 100000; // Timeout value

    do
    {
        if (usart->SR & (1 << 5)) // check data for ready to read 
        {
            receivedChar = (char)(usart->DR & 0xFF); // read data

            if (receivedChar == '\r' || receivedChar == '\n')
            {
                break; // End string 
            }

            buffer[charCount] = receivedChar;
            charCount++;
        }
        else
        {
            timeout--;
        }
    } while (timeout > 0 && charCount < bufferSize - 1);

    buffer[charCount] = '\0'; // End string 
}
