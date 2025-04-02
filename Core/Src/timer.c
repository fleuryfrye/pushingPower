#include "timer.h"
#include "stm32f3xx_hal.h"



volatile timerStatus_t g_timer;

volatile timerStatus_t g_timer3;


extern volatile uint8_t messageReceived;


extern outputCharacteristics_t waveform;



// TIM2 is a 32-bit timer that is configured to count up until it reaches ARR.

void initTimer(void)
{

	RCC->APB1ENR |= (APB1_TIM2_EN);

	TIM2->CR1 |= (TIMx_CR1_URS);

	TIM2->DIER |= (TIMx_DIER_UIE);


	//TIM2->PSC = TIMx_PRESCALER;

	TIM2->ARR = 0; //ARR used for comparison. When count > ARR value, interrupt is triggered.

	//STM32F3 has a bug where interrupt flag is set after setting CNT and PSC. Forcing an interrupt and clearing it solves this issue.
	TIM2->EGR |= TIMx_EGR_UG;
	TIM2->SR &= ~(TIMx_SR_UIF);

	NVIC_EnableIRQ(TIM2_IRQn);

	turnTimerOff();


}


void initTimer3(void)
{

	RCC->APB1ENR |= APB1_TIM3_EN;

	TIM3->CR1 |= (TIMx_CR1_URS);

	TIM3->DIER |= (TIMx_DIER_UIE);

	TIM3->PSC = TIM3_PSC;


	TIM3->ARR = 0; //ARR used for comparison. When count > ARR value, interrupt is triggered.



	//STM32F3 has a bug where interrupt flag is set after setting CNT and PSC. Forcing an interrupt and clearing it solves this issue.
	TIM3->EGR |= TIMx_EGR_UG;
	TIM3->SR &= ~(TIMx_SR_UIF);

	NVIC_EnableIRQ(TIM3_IRQn);

	//turnTimerOff();

	g_timer3 = TIMER_OFF;




}



void turnTimer3Off(void)
{
	TIM3->CR1 &= ~TIMx_CR1_CEN; //turn timer off
	TIM3->CNT = 0; //reset count back to 0

	g_timer3 = TIMER_OFF;
}






//Turns timer off and resets count back to 0. Then sets timer status to off.
void turnTimerOff(void)
{

	TIM2->CR1 &= ~TIMx_CR1_CEN; //turn timer off
	TIM2->CNT = 0; //reset count back to 0

	g_timer = TIMER_OFF;
}


//waitForTimer() is a blocking function that waits for timer to expire
// If called and timer is turned off, returns -1
// Will wait until timer expires to exit.

int8_t waitForTimer(void)
{
	if(g_timer == TIMER_OFF) return ERROR;


	while(!(hasTimerExpired()));

	return 1;
}


//wait() is a blocking function that waits for the timer to expire OR exits upon a valid message request being received.
//Recommend to use this when waiting during signal generation.

// If timer expires, we return EXIT_SUCCESS. If a valid message is received, EXIT_NEWREQUEST is generated.

returnStatus_t wait(uint32_t us)
{

	setTimer(us);

	while(!hasTimerExpired())
	{

		if(messageReceived)
		{
			messageReceived = 0;
    		processMessage();
		}

		if(waveform.newRequest)
		{
			turnTimerOff();
			return EXIT_NEWREQUEST;
		}

	}

	return EXIT_SUCCESS;

}






//If timer has expired, returns 1.
//If timer still waiting, returns 0.
//If called and timer is off, returns -1.

int8_t hasTimerExpired(void)
{
	switch(g_timer)
	{
		case(TIMER_OFF): return ERROR;
		case(TIMER_ACTIVE): return FALSE;
		case(TIMER_EXPIRED):
		{
			turnTimerOff();
			return TRUE;
		}

		default: return ERROR;

	}
}

int8_t hasTimer3Expired(void)
{
	switch(g_timer3)
	{
		case(TIMER_OFF): return ERROR;
		case(TIMER_ACTIVE): return FALSE;
		case(TIMER_EXPIRED):
		{
			turnTimer3Off();
			return TRUE;
		}

		default: return ERROR;

	}
}





//Sets timer to wait until time requested in microseconds.

void setTimer(uint32_t us)
{

	if(g_timer == TIMER_ACTIVE)
	{
		turnTimerOff();
	}


	TIM2->CNT = 0; //reset ticks to 0

	uint32_t waitTime = getTicks(us);

	TIM2->ARR = waitTime;

	//TIM2->EGR |= TIMx_EGR_UG;


	TIM2->CR1 |= TIMx_CR1_CEN; //start timer

	g_timer = TIMER_ACTIVE;



}


void setTimer3(uint16_t ms)
{

	if(g_timer3 == TIMER_ACTIVE)
	{
		turnTimer3Off();
	}


	TIM3->CNT = 0; //reset ticks to 0

	uint16_t waitTime = getTimer3Ticks(ms);

	TIM3->ARR = waitTime;

	TIM3->CR1 |= TIMx_CR1_CEN; //start timer

	g_timer3 = TIMER_ACTIVE;

}



uint32_t getTicks(uint32_t us)
{

	return (    TIMx_CLK_FREQ *  ((double)(us) / 1000000.0)    );



}

uint16_t getTimer3Ticks(uint16_t ms)
{

	uint32_t ticks = TIM3_CLK_FREQ * ((double)(ms) / 1000);


	return (  (ticks > 0xFFFF) ? 0xFFFF  : (uint16_t)(ticks)  );


}
