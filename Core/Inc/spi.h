#ifndef __SPI_H
#define __SPI_H


//Includes
#include "stm32f3xx_hal.h"

//Variables



//Macros




//Constants
#define RX_BUFFER_LENGTH 100

#define NSS_PIN 11U //Port A
#define NSS_ASSERTED (1 << NSS_PIN)



#define RCC_APB2_ENR_SPIEN 12U
#define SPI1_CR1_CPHA 0U
#define SPI1_CR1_CPOL 1U
#define SPI1_CR1_MSTR 2U
#define SPI1_CR1_SPE 6U
#define SPI1_CR1_LSBFIRST 7U
#define SPI1_CR1_RXONLY 10U


#define SPI1_CR2_DS_LSB 8U
#define SPI1_CR2_RXNEIE 6U
#define SPI1_CR2_FRXTH 12U

#define SPI1_SR_RXNE 0U



#define SPI_DATA_SIZE 0x07 //8 bit data length


#define SPI1_APB2_ENABLE (1 << RCC_APB2_ENR_SPIEN)
#define SPI_ENABLE (1 << SPI1_CR1_SPE)
#define SPI_RX_ONLY (1 << SPI1_CR1_RXONLY)
#define SPI_SET_DATA_SIZE (SPI_DATA_SIZE << SPI1_CR2_DS_LSB)
#define SPI_ENABLE_RX_INT (1 << SPI1_CR2_RXNEIE)
#define SPI_RX_FIFO_8_BIT_THRESHOLD (1 << SPI1_CR2_FRXTH)

#define SPI1_RXNE_SET (1 << SPI1_SR_RXNE)





//Functions
void initSPI(void);

uint8_t NSSAsserted(void);








#endif
