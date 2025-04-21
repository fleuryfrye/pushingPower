// Reset and Clock Controller
// -----------

// why is this here
// for what does it do
// generally not really sure what all of this does lol




#include "rcc.h"



void initRCC(void)
{

	RCC->CR |= RCC1_CR_HSION;

	while(!(RCC->CR & RCC1_CR_HSIRDY)); //Hardware will set HSIRDY when clock is ready


	RCC->CFGR |= (RCC1_CFGR_PLLMUL | RCC1_CFGR_PPRE1);

	RCC->CR |= RCC1_CR_PLLON;

	FLASH->ACR |= FLASH_2_CYCLE_LATENCY; //for SYCLK over 48 MHz, need to wait 2 cycles to properly read from flash memory

	while(!(RCC->CR & RCC1_CR_PLLRDY)); //Hardware will set PLLRDY when PLL Is locked and ready.


	RCC->CFGR |= RCC1_CFGR_SW; //Select PLL as system clock


	while(!(RCC->CFGR & RCC1_CFGR_SWS));


	return;





}
