#include "gpio.h"

// what is the goal /purpsoe of this
// what is important information for this
// the GPIO part of the manual starts on page 230
// 

// Set up all GPIO pins to prepare to do whatever function it is assigned to (ex: SPI, ADC etc)

void initGPIO(void)
{
	//Peripheral clocks turned off by default, each GPIO port has a clock that must be activated first.
	RCC->AHBENR |= (GPIOA_AHB_ENABLE | GPIOB_AHB_ENABLE);

	//To Do: make a function that abstracts the process of setting a pin and it's mode.
	// is this still true?
	GPIOA->MODER |= (OUTPUT_MODE << (PIEZO_CHARGE_PIN * 2));
	GPIOA->MODER |= (OUTPUT_MODE << (PIEZO_DISCHARGE_PIN * 2));
	GPIOA->MODER |= (ALT_FUNCT_MODE << (SPI_NSS_PIN * 2));

	GPIOA->AFR[1] |= (SPI_NSS_AF);
	GPIOA->PUPDR |= (1 << SPI_NSS_PIN * 2);


	GPIOA->OSPEEDR |= (HIGH_SPEED_OUTPUT << (PIEZO_CHARGE_PIN * 2));
	GPIOA->OSPEEDR |= (HIGH_SPEED_OUTPUT << (PIEZO_DISCHARGE_PIN * 2));

	GPIOB->MODER |= (ALT_FUNCT_MODE << (SPI_CLK_PIN * 2));
	GPIOB->MODER |= (ALT_FUNCT_MODE << (SPI_MOSI_PIN * 2));

	GPIOB->AFR[0] |= (SPI_MOSI_AF | SPI_CLK_AF);

	return;
}

// Allow the GPIO pin to write data
// where would this be used at
void writePin(GPIO_TypeDef* GPIOX, uint32_t pinNum)
{
	GPIOX->BSRR = (1 << pinNum);
}

// Clear the pin for reset
// why/where would this be useful at?
void clearPin(GPIO_TypeDef* GPIOX, uint32_t pinNum)
{
	GPIOX->BRR = (1 << pinNum);
}

// Allow the GPIO pin to read data
// where would this be used at
uint8_t readPin(GPIO_TypeDef* GPIOX, uint32_t pinNum)
{
	return ((GPIOX->IDR >> pinNum) & 0x1);
}
