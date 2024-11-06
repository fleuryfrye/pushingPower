#include "gpio.h"



void initGPIO(void)
{
	//Peripheral clocks turned off by default, each GPIO port has a clock that must be activated first.
	RCC->AHBENR |= (GPIOA_APB2_ENABLE);

	GPIOA->MODER |= (OUTPUT_MODE << (PIEZO_CHARGE_PIN * 2));
	GPIOA->MODER |= (OUTPUT_MODE << (PIEZO_DISCHARGE_PIN * 2));


	GPIOA->OSPEEDR |= (HIGH_SPEED_OUTPUT << (PIEZO_CHARGE_PIN * 2));
	GPIOA->OSPEEDR |= (HIGH_SPEED_OUTPUT << (PIEZO_DISCHARGE_PIN * 2));

	return;
}
