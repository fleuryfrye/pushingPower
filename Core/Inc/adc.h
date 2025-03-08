#ifndef __ADC_H
#define __ADC_H

//Includes
#include "stm32f3xx_hal.h"


//Variables
extern volatile int16_t adcData; //signed 12 bit data.
extern volatile uint8_t ADCRDY;



//Constants

//ADC is on A0 on the nucleo board (PA0)


#define ADC_PIN 0U
#define ADC_INPUT_MODE 3U
#define ADC_CLK_EN 28U

#define ADC_RDY 0U
#define ADC_EOC 2U

#define ADC1_SQR1_SQ1 6U // [4:0]
#define ADC1_CHANNEL_1 1U


#define ADC1_CFGR_CONT 13U
#define ADC1_CFGR_OVRMOD 12U
#define ADC1_CFGR_RES 3U

#define ADC1_CR_ADSTART 2U
#define ADC1_CR_EN 0U
#define ADC1_CR_CAL 31U
#define ADC1_CR_VREG_MSB 29U
#define ADC1_CR_VREG_LSB 28U

#define ADC1_CCR_CKMODE 16U

#define ADC1_OFR4_OFFSET1_EN 31U
#define ADC1_OFR4_OFFSET1_CH 1U //[4:0]


#define ADC1_SMP1 3U


#define ADC_VREF 3.3
#define ADC_PIEZO_SCALAR 1515.15 //3.3 volts should represent 5000V
#define ADC_RESOLUTION_BITS 12
#define ADC_LEVELS ((1 << ADC_RESOLUTION_BITS) - 1)




#define ADC_READY_BITMASK (1 << ADC_RDY)
#define ADC_EOC_BITMASK (1 << ADC_EOC)

#define ADC_8_BIT_RES_BITMASK (2 << ADC1_CFGR_RES)


#define SAMPLING_RATE_1_CYCLE 0U
#define SAMPLING_RATE_7_CYCLES 3U
#define SAMPLING_RATE_20_CYCLES 4U
#define SAMPLING_RATE_60_CYCLES 5U
#define SAMPLING_RATE_180_CYCLES 6U



#define ADC_SAMPLING_RATE_BITMASK (SAMPLING_RATE_60_CYCLES << ADC1_SMP1) //sample 7.5 adc clock cyles


//Functions

void initADC(void);



#endif
