#ifndef TIMER_H
#define TIMER_H

#include "main.h"



#define APB1_TIM2_EN (1 << 0)


#define TIM2_CR1_CEN (1 << 0)
#define TIM2_CR1_URS (1 << 2)

#define TIM2_DIER_UIE (1 << 0)

#define TIM2_EGR_UG (1 << 0)

#define TIM2_SR_UIF (1 << 0)

#define TIM2_CLK_INT_FREQ 64000000
//#define TIM2_PRESCALER 0

#define TIM2_CLK_FREQ (TIM2_CLK_INT_FREQ / 1)




typedef enum timerStatus {TIMER_OFF, TIMER_ACTIVE, TIMER_EXPIRED} timerStatus_t;

void initTimer(void);

void setTimer(uint32_t us);

int8_t waitForTimer(void);

int8_t hasTimerExpired(void);

void turnTimerOff(void);

uint32_t getTicks(uint32_t us);

static inline uint32_t getMicroseconds(double seconds)
{

	return (seconds * 1000000);
}








#endif
