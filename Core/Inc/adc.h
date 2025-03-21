#ifndef __ADC_H
#define __ADC_H

//Includes
#include "stm32f3xx_hal.h"


//Constants

//ADC Input 1 is on A0 on the nucleo board (PA0)
//ADC Input 3 is on A7 on the nucleo board (PA7)


#define ADC_CHANNELS 2U

#define PIEZO_INDEX 0U
#define BANK_INDEX 1U


#define ADC1_IN_1 0U
#define ADC1_IN_3 2U


#define ADC_INPUT_MODE 3U
#define ADC_CLK_EN 28U

#define ADC_RDY 0U
#define ADC_EOC 2U

#define ADC1_SQR1_SQ1 6U // [4:0]
#define ADC1_SQR1_SQ2 12U
#define ADC1_SQR1_LEN 0U

#define ADC1_CHANNEL_1 1U
#define ADC1_CHANNEL_3 3U
#define ADC1_SEQUENCE_LEN (ADC_CHANNELS - 1)



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
#define ADC1_SMP3 9U

#define ADC_VREF 3.3
#define ADC_PIEZO_SCALAR 1515.15 //3.3 volts should represent 5000V
#define ADC_RESOLUTION_BITS 12
#define ADC_LEVELS ((1 << ADC_RESOLUTION_BITS) - 1)




#define ADC_READY_BITMASK (1 << ADC_RDY)
#define ADC_EOC_BITMASK (1 << ADC_EOC)

#define ADC_8_BIT_RES_BITMASK (2 << ADC1_CFGR_RES)
#define ADC_10_BIT_RES_BITMASK (1 << ADC1_CFGR_RES)



#define SAMPLING_RATE_1_CYCLE 0U
#define SAMPLING_RATE_7_CYCLES 3U
#define SAMPLING_RATE_20_CYCLES 4U
#define SAMPLING_RATE_60_CYCLES 5U
#define SAMPLING_RATE_180_CYCLES 6U



#define ADC_SAMPLING_RATE_BITMASK (SAMPLING_RATE_60_CYCLES << ADC1_SMP3 | SAMPLING_RATE_60_CYCLES << ADC1_SMP1)

#define ADC_DATA_REG_OFFSET 0x40


//DMA Setup

#define DMA_16_BIT_SIZE 1U
#define DMA_32_BIT_SIZE 2U

#define DMA_CIRCULAR_MODE_ON 1U

#define DMA_READ_PERIPH 0U

#define DMA_XFR_COMPLETE_INT_EN 0U // TURNING off for testing

#define DMA_CHANNEL_ENABLE 1U

#define DMA_MEMORY_INCREMENT 1U


#define RCC_DMA1_EN (1 << 0)

#define DMA_CCR1_MSIZE (DMA_16_BIT_SIZE << 10)

#define DMA_CCR1_PSIZE (DMA_32_BIT_SIZE << 8)

#define DMA_CCR1_MINC (DMA_MEMORY_INCREMENT << 7)

#define DMA_CIRC (DMA_CIRCULAR_MODE_ON << 5)

#define DMA_DIR (DMA_READ_PERIPH << 4)

#define DMA_TCIE (DMA_XFR_COMPLETE_INT_EN << 1)

#define DMA_EN (DMA_CHANNEL_ENABLE << 0)


#define DMA_CCR1 (DMA_CCR1_MSIZE | DMA_CCR1_PSIZE | DMA_CCR1_MINC | DMA_CIRC | DMA_DIR | DMA_TCIE | DMA_EN)






//Variables
extern volatile int16_t adcData[ADC_CHANNELS]; //signed 12 bit data.
extern volatile uint8_t ADCRDY;



//Functions

void initADC(void);

void setupDMAChannel1(void);



#endif
