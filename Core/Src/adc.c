#include "adc.h"


volatile int16_t adcData[ADC_CHANNELS]; //signed 12 bit data.
volatile uint8_t ADCRDY;



void initADC(void)
{
	ADCRDY = 0;

	// ADC clock frequency is set to 32 MHz.
	//According to the reference manual, 12-bit resolution requires 14 clock cycles per sample.
	// This results in one ADC sample being generated every 388 nanoseconds.

	GPIOA->MODER |= (ADC_INPUT_MODE << (ADC1_IN_1 * 2));
	GPIOA->MODER |= (ADC_INPUT_MODE << (ADC1_IN_3 * 2));


	RCC->AHBENR |= (1 << ADC_CLK_EN); // enable ADC clock

	ADC12_COMMON->CCR |= (2 << ADC1_CCR_CKMODE); //Set ADC clock to 36 MHz. (prescaler = /2)


	//Voltage regular must start up before calibration.
	ADC1->CR &= ~(1 << ADC1_CR_VREG_MSB);
	ADC1->CR |= (1 << ADC1_CR_VREG_LSB); //startup vreg
	HAL_Delay(1); //must wait at least 10 us after starting up the vreg



	//Recommended to calibrate the ADC on startup.
	ADC1->CR |= (1 << ADC1_CR_CAL);
	while(ADC1->CR & (1 << ADC1_CR_CAL)); // hardware clears cal bit when finished.


	//Enable ADC ready and end of conversion interrupts
	ADC1->IER |= (1 << ADC_RDY);
	//ADC1->IER |= (1 << ADC_EOC);



	//12 bit is right aligned and (allegedly) sign extended to 16 bits. Need to verify with negative voltage.
	//(this looks good for positive values, but I need to check negative values!)

	//Enable the ADC code to be signed.
	ADC1->OFR4 |= (1 << ADC1_OFR4_OFFSET1_EN);
	ADC1->OFR4 |= (1 << ADC1_OFR4_OFFSET1_CH);


	ADC1->SQR1 |= (ADC1_CHANNEL_1 << ADC1_SQR1_SQ1); //activate channel 1 (piezo voltage).
	ADC1->SQR1 |= (ADC1_CHANNEL_3 << ADC1_SQR1_SQ2); // activate channel 3 (bank voltage)



	ADC1->SQR1 |= (ADC1_SEQUENCE_LEN << ADC1_SQR1_LEN); 

	ADC1->CFGR |= (1 << ADC1_CFGR_CONT); //continuously sample
	ADC1->CFGR |= (1 << ADC1_CFGR_OVRMOD); // if sample is missed, overwrite with newest

	//DMA Setup

	setupDMA();






	//8-bit set up for testing purposes

	//Make sure to edit ADC_RESOLUTION_BITs macro as well
//
	//ADC1->CFGR |= ADC_10_BIT_RES_BITMASK;
//

	//end of 8-bit setup

	ADC1->SMPR1 |= ADC_SAMPLING_RATE_BITMASK;



	ADC1->CR |= (1 << ADC1_CR_EN); //Enable the ADC and wait for it to be ready.

	NVIC_EnableIRQ(ADC1_2_IRQn); //Register the interrupt with NVIC

	while(!ADCRDY); //Interrupt will set ADCREADY.

	ADC1->CFGR |= (1 << 0) | (1 << 1); //circ mode and dma en


	ADC1->CR |= (1 << ADC1_CR_ADSTART); //Begin sampling!



}


void setupDMA(void)
{

	RCC->AHBENR |= RCC_DMA1_EN;


	DMA1_Channel1->CNDTR = ADC_CHANNELS;


	//DMA1_Channel1->CPAR = &(ADC1->DR);
	DMA1_Channel1->CPAR = ADC1_BASE + 0x40;
	DMA1_Channel1->CMAR = &adcData;

	DMA1_Channel1->CCR |= (DMA_CCR1);




}

