#ifndef __GPIO_H
#define __GPIO_H

//Includes
#include "stm32f3xx_hal.h"


//Constants




//Piezo and ADC pins are on Port A
#define PIEZO_CHARGE_PIN 9U
#define PIEZO_DISCHARGE_PIN 10U
#define OUTPUT_MODE 1U
#define HIGH_SPEED_OUTPUT 0x03
#define PIEZO_CHARGE_PIN_HIGH (1U << PIEZO_CHARGE_PIN)
#define PIEZO_DISCHARGE_PIN_HIGH (1U << PIEZO_DISCHARGE_PIN)


#define AHBENR_GPIOAEN 17U
#define GPIOA_APB2_ENABLE (1 << AHBENR_GPIOAEN)





//Functions

void initGPIO(void);

void writePin(GPIO_TypeDef* GPIOX, uint32_t pinNum);

void clearPin(GPIO_TypeDef* GPIOX, uint32_t pinNum);

uint8_t readPin(GPIO_TypeDef* GPIOX, uint32_t pinNum);


#endif
