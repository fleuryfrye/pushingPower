#ifndef __GPIO_H
#define __GPIO_H

//Includes
#include "stm32f3xx_hal.h"


//Constants




//Piezo, ADC, and SPI NSS pins are on Port A
#define PIEZO_CHARGE_PIN 9U
#define PIEZO_DISCHARGE_PIN 10U
#define SPI_NSS_PIN 11U
#define OUTPUT_MODE 1U
#define ALT_FUNCT_MODE 2U
#define HIGH_SPEED_OUTPUT 0x03
#define PIEZO_CHARGE_PIN_HIGH (1U << PIEZO_CHARGE_PIN)
#define PIEZO_DISCHARGE_PIN_HIGH (1U << PIEZO_DISCHARGE_PIN)

//SPI Pins are on Port B
#define SPI_CLK_PIN 3U
#define SPI_MOSI_PIN 5U

#define AF5 5U
#define SPI_MOSI_AF (AF5 << (SPI_MOSI_PIN * 4))
#define SPI_CLK_AF  (AF5 << (SPI_CLK_PIN * 4))
#define SPI_NSS_AF  (AF5 << ((SPI_NSS_PIN - 8 ) * 4)) //hacky




#define AHBENR_GPIOAEN 17U
#define AHBENR_GPIOBEN 18U
#define GPIOA_AHB_ENABLE (1 << AHBENR_GPIOAEN)
#define GPIOB_AHB_ENABLE (1 << AHBENR_GPIOBEN)





//Functions

void initGPIO(void);

void writePin(GPIO_TypeDef* GPIOX, uint32_t pinNum);

void clearPin(GPIO_TypeDef* GPIOX, uint32_t pinNum);

uint8_t readPin(GPIO_TypeDef* GPIOX, uint32_t pinNum);


#endif
