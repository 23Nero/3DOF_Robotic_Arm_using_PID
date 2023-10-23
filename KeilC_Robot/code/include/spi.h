// #ifndef __SPI_H__
// #define __SPI_H__

// #include <stdint.h>

// #define SR_TXE (1 << 1)
// #define SR_RXNE (1 << 0)
// #define SR_BSY (1 << 7)

// #define SPI1_BASE ((uint32_t *)0x40013000)
// #define SPI2_BASE ((uint32_t *)0x40003800) // I2S2
// #define SPI3_BASE ((uint32_t *)0x40003C00) // I2S3
// #define SPI4_BASE ((uint32_t *)0x40013400)

// typedef struct SPI
// {
//     volatile uint32_t CR1;
//     volatile uint32_t CR2;
//     volatile uint32_t SR;
//     volatile uint32_t DR;
//     volatile uint32_t CRCPR;
//     volatile uint32_t RXCRCR;
//     volatile uint32_t TXCRCR;
//     volatile uint32_t I2SCFGR;
//     volatile uint32_t I2SPR;
// }SPI_t;

// #define SPI1 ((SPI_t *)SPI1_BASE)
// #define SPI2 ((SPI_t *)SPI2_BASE)
// #define SPI3 ((SPI_t *)SPI3_BASE)
// #define SPI4 ((SPI_t *)SPI4_BASE)

// void sp1_config(void);
// void spi_transmit(SPI_t *spi, uint8_t *data, uint32_t size);
// void spi_receive(SPI_t *spi, uint8_t *data, uint32_t size);
// void cs_enable(GPIO_t *gpio, uint32_t pin);
// void initMAX7219(void);


// #endif
