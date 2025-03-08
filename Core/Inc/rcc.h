

#ifndef __RCC_H_
#define __RCC_H_

#include "stm32f3xx_hal.h"

/*
	Notes


	SYSCLK/AHB set to 64 MHz

	APB2 set to 64 MHz

	APB1 set to 32 MHz


*/


#define PLL_SCALE_4X 2U
#define PLL_SCALE_9X 7U
#define PLL_SCALE_12X 10U
#define PLL_SCALE_14X 12U
#define PLL_SCALE_16X 14U




#define PLL_SCALAR PLL_SCALE_16X  //multiply HSI (8 MHz) 16x to 64 MHz (this is the  max frequency achievable with the HSI)



#define FLASH_ACCESS_LATENCY 2U
#define FLASH_ACR 0U


#define FLASH_2_CYCLE_LATENCY (FLASH_ACCESS_LATENCY << FLASH_ACR)



#define PLL_USED 2U

#define APB1_PRESCALER 4U //APB1 limited to 36 MHz. Divide SYSCLK (64 MHz) by 2 to limit APB1 to 32 MHz.


#define RCC1_CR_PLLON (1 << 24)
#define RCC1_CR_PLLRDY (1 << 25)

#define RCC1_CR_HSION (1 << 0)
#define RCC1_CR_HSIRDY (1 << 0)



#define RCC1_CFGR_PLLMUL (PLL_SCALAR << 18)
#define RCC1_CFGR_SW (2 << 0) //Use PLL as system clock
#define RCC1_CFGR_SWS (PLL_USED << 2)

#define RCC1_CFGR_PPRE1 (APB1_PRESCALER << 8)


void initRCC(void);







#endif
