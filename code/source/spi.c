// #include "./../include/spi.h"
#include "./../include/RCC.h"
#include "./../include/gpio.h"

// // PA5 - CLK
// // PA6 - MISO
// // PA7 - MOSI

// // PA9 - Slave Select

// void sp1_config(void)
// {
//     /*Enable clock acess to SPI1 module*/
//     RCC->APB2ENR |= SPI1EN;

//     /*Set clock to fPCLK/4*/
//     SPI1->CR1 |= (1 << 3);

//     /*Set CPOL to 1 and CPHA to 1*/
//     SPI1->CR1 |= (1 << 0);
//     SPI1->CR1 |= (1 << 1);

//     /*Enable full duplex*/
//     SPI1->CR1 &= ~(1u << 10);

//     /*Set mode to master*/
//     SPI1->CR1 |= (1 << 2);

//     /*Set 8 bit data mode*/
//     SPI1->CR1 &= ~(1u << 11);

//     /*Select sorfware slave management by
//         setting SSM=1 and SSI=1 */
//     SPI1->CR1 |= (1 << 8);
//     SPI1->CR1 |= (1 << 9);

//     /*Enable SPI module*/
//     SPI1->CR1 |= (1 << 6);
// }

// void spi_transmit(SPI_t *spi, uint8_t *data, uint32_t size)
// {
//     uint32_t i = 0;
//     uint8_t temp;

//     while (i < size)
//     {
//         /* Wait until TXE set */
//         while (!(spi->SR & SR_TXE))
//             ;

//         /* Write the data to the data register */
//         spi->DR = data[i];
//         i++;
//     }

//     /* Wait until TXE is set */
//     while (!(spi->SR & SR_TXE))
//         ;

//     /* Wait for BUSY flag to reset */
//     while (spi->SR & SR_BSY)
//         ;

//     /* Clear overrun flag */
//     temp = spi->DR;
//     temp = spi->SR;
// }

// void spi_receive(SPI_t *spi, uint8_t *data, uint32_t size)
// {
//     while (size)
//     {
//         /* Send dummy data */
//         spi->DR = 0;

//         /* Wait for RXNE flag to set */
//         while (!(spi->SR & SR_RXNE))
//             ;

//         /* Read data from data register */
//         *data++ = (spi->DR);
//         size--;
//     }
// }

// void cs_enable(GPIO_t *gpio, uint32_t pin)
// {
//     gpio->ODR &= ~(1u << pin);
// }

// volatile uint32_t LED[] = {
//     0x0000, // reverd
//     0x0100, // Led 1
//     0x0200, // Led 2
//     0x0300, // Led 3
//     0x0400, // Led 4
//     0x0500, // Led 5
//     0x0600, // Led 6
//     0x0700, // Led 7
//     0x0800, // Led 8
// };

// void initMAX7219(void)
// {
//     uint32_t giay = 10;
//     uint8_t tmp;
//     uint32_t size = sizeof(tmp);

//     tmp = 0x0C01;
//     spi_transmit(SPI1, tmp, size); // Shutdown mode

//     tmp = 0x0B07;
//     spi_transmit(SPI1, tmp, size);

//     tmp = 0x0A05;
//     spi_transmit(SPI1, tmp, size);

//     tmp = 0x09FF;
//     spi_transmit(SPI1, tmp, size);

//     tmp = LED[1] | giay % 10;
//     spi_transmit(SPI1, tmp, size);

//     tmp = LED[2] | giay / 10;
//     spi_transmit(SPI1, tmp, size);
// }

