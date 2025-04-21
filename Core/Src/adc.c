// Analog to Digital Converter
// ---------------------------

// The analog to digital converter (ADC) will be used to measure the voltage
// across the piezo motor.

// DMA set up so we can use both channels but rn we are only use the one channel
// for the piezo motor and other channel not connected to anything yet.

// ADC documentation on the STM32 is in the STM32 manual on page 310 In the
// README there is also an STM32 ADC document as well for more context.

// INSERT PICTURE OF THE ADC IN THE MANUAL? WHAT ARE OTHER PICTURES YOU CAN
// THINK OF?


#include "adc.h"

volatile int16_t adcData[ADC_CHANNELS]; // signed 12 bit data.
volatile uint8_t ADCRDY;

// This will set up the ADC when the STM32 first is started up.
void initADC(void)
{
	ADCRDY = 0;

	// ADC clock frequency is set to 32 MHz. According to the reference manual,
	// 12-bit resolution requires 14 clock cycles per sample. This results in one
	// ADC sample being generated every 388 nanoseconds.
	//
	// See Page 312 of the STM32 manual See STM32 ADC document
	GPIOA->MODER |= (ADC_INPUT_MODE << (ADC1_IN_1 * 2));
	GPIOA->MODER |= (ADC_INPUT_MODE << (ADC1_IN_3 * 2));

	// Enable ADC clock
	RCC->AHBENR |= (1 << ADC_CLK_EN); 

	// Set ADC clock to 36 MHz. (prescaler = /2) , page 414 of manual to use
	// CK\_MODE
	ADC12_COMMON->CCR |= (2 << ADC1_CCR_CKMODE); 

	// Voltage regular must start up before calibration.
	ADC1->CR &= ~(1 << ADC1_CR_VREG_MSB);
	// Startup vreg WHAT DOES VREG DO?
	ADC1->CR |= (1 << ADC1_CR_VREG_LSB); 
	
	// Must wait at least 10 us after starting up the vreg
	HAL_Delay(1); 

	// Recommended to calibrate the ADC on startup.
	ADC1->CR |= (1 << ADC1_CR_CAL);
	while(ADC1->CR & (1 << ADC1_CR_CAL)); // hardware clears cal bit when finished.

	// Enable ADC ready and end of conversion interrupts
	ADC1->IER |= (1 << ADC_RDY);
	// WHAT IS THE PURPOSE OF THIS? -> ADC1->IER |= (1 << ADC\_EOC);

	// 12 bit is right aligned and (allegedly) sign extended to 16 bits. Need to
	// verify with negative voltage. (this looks good for positive values, but I
	// need to check negative values!) Enable the ADC code to be signed.
	ADC1->OFR4 |= (1 << ADC1_OFR4_OFFSET1_EN);
	ADC1->OFR4 |= (1 << ADC1_OFR4_OFFSET1_CH);

	ADC1->SQR1 |= (ADC1_CHANNEL_1 << ADC1_SQR1_SQ1); // activate channel 1 (piezo voltage).
	ADC1->SQR1 |= (ADC1_CHANNEL_3 << ADC1_SQR1_SQ2); // activate channel 3 (bank voltage)

	ADC1->SQR1 |= (ADC1_SEQUENCE_LEN << ADC1_SQR1_LEN); 

	// Continuously sample *WHAT*
	ADC1->CFGR |= (1 << ADC1_CFGR_CONT); 

	// If a sample is missed, overwrite with newest sample read
	ADC1->CFGR |= (1 << ADC1_CFGR_OVRMOD); 

	// DMA Setup
	setupDMAChannel1();

	// 8-bit set up for testing purposes Make sure to edit ADC\_RESOLUTION\_BITs
	// macro as well WHY DO WE NEED TO EDIT THIS MACRO? WHAT IS THIS FOR???? ->
	// ADC1->CFGR |= ADC\_10\_BIT\_RES\_BITMASK; End of 8-bit setup
	ADC1->SMPR1 |= ADC_SAMPLING_RATE_BITMASK;


	// Enable the ADC and wait for it to be ready.
	ADC1->CR |= (1 << ADC1_CR_EN); 

	// Register the interrupt with NVIC
	NVIC_EnableIRQ(ADC1_2_IRQn); 

	// Interrupt will set ADCREADY.
	while(!ADCRDY); 
	
	// circ mode and dma en WHAT DOES CIRC MODE MEAN
	ADC1->CFGR |= (1 << 0) | (1 << 1); 

	// Begin sampling!
	ADC1->CR |= (1 << ADC1_CR_ADSTART); 
}

// DMA set up functions
void setupDMAChannel1(void)
{
	RCC->AHBENR |= RCC_DMA1_EN;


	DMA1_Channel1->CNDTR = ADC_CHANNELS;

	DMA1_Channel1->CPAR = ADC1_BASE + ADC_DATA_REG_OFFSET;
	DMA1_Channel1->CMAR = &adcData;

	DMA1_Channel1->CCR |= (DMA_CCR1);
}

// what does this one do?????
void getBankVoltage(int16_t* voltage)
{
	double rawvoltage =  ((adcData[BANK_INDEX] * ADC_VREF) / ADC_LEVELS);

	*voltage = (int16_t)(rawvoltage * ADC_PIEZO_SCALAR);
}


