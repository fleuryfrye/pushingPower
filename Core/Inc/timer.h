#ifndef TIMER_H
#define TIMER_H

#include "main.h"



#define APB1_TIM2_EN (1 << 0)
#define APB1_TIM3_EN (1 << 1)


#define TIMx_CR1_CEN (1 << 0)
#define TIMx_CR1_URS (1 << 2)

#define TIMx_DIER_UIE (1 << 0)

#define TIMx_EGR_UG (1 << 0)

#define TIMx_SR_UIF (1 << 0)


#define TIMx_CLK_INT_FREQ 64000000
//#define TIMx_PRESCALER 0

#define TIMx_CLK_FREQ (TIMx_CLK_INT_FREQ / 1)

#define TIM3_PSC 9999

#define TIM3_CLK_FREQ (TIMx_CLK_INT_FREQ / (TIM3_PSC + 1))




typedef enum timerStatus {TIMER_OFF, TIMER_ACTIVE, TIMER_EXPIRED} timerStatus_t;

typedef enum returnStatus {EXIT_SUCCESS, EXIT_NEWREQUEST, EXIT_TIMEOUT} returnStatus_t;



void initTimer(void);
void initTimer3(void);


void setTimer(uint32_t us);
void setTimer3(uint16_t ms);


int8_t waitForTimer(void);

returnStatus_t wait(uint32_t us);


int8_t hasTimerExpired(void);
int8_t hasTimer3Expired(void);

void turnTimerOff(void);
void turnTimer3Off(void);


uint32_t getTicks(uint32_t us);

uint16_t getTimer3Ticks(uint16_t ms);


static inline uint32_t getMicroseconds(double seconds)
{

	return (seconds * 1000000);
}







int8_t timeout(void);














#endif
