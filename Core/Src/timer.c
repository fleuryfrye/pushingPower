#include "timer.h"
#include "stm32f3xx_hal.h"



volatile timerStatus_t g_timer;



// TIM2 is a 32-bit timer that is configured to count up until it reaches ARR.

void initTimer(void)
{

	RCC->APB1ENR |= (APB1_TIM2_EN);

	TIM2->CR1 |= (TIM2_CR1_URS);

	TIM2->DIER |= (TIM2_DIER_UIE);


	//TIM2->PSC = TIM2_PRESCALER;

	TIM2->ARR = 0; //ARR used for comparison. When count > ARR value, interrupt is triggered.

	NVIC_EnableIRQ(TIM2_IRQn);

	turnTimerOff();


}



//Turns timer off and resets count back to 0. Then sets timer status to off.
void turnTimerOff(void)
{

	TIM2->CR1 &= ~TIM2_CR1_CEN; //turn timer off
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




//Sets timer to wait until time requested in microseconds.

void setTimer(uint32_t us)
{
	TIM2->CNT = 0; //reset ticks to 0

	uint32_t waitTime = getTicks(us);

	TIM2->ARR = waitTime;

	//TIM2->EGR |= TIM2_EGR_UG;


	TIM2->CR1 |= TIM2_CR1_CEN; //start timer

	g_timer = TIMER_ACTIVE;



}


uint32_t getTicks(uint32_t us)
{

	return (    TIM2_CLK_FREQ *  ((long)(us) / 1000000.0)    );



}
