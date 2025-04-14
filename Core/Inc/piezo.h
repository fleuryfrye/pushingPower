#ifndef __PIEZO_H
#define __PIEZO_H

//Includes
#include "stm32f3xx_hal.h"
#include "adc.h"
#include "gpio.h"
#include "timer.h"


//Types

typedef enum {VOLT, SINE, RECTANGLE, PULSE} waveform_t;


typedef struct outputCharacteristics
{
	waveform_t wave;
	uint16_t amplitude;
	uint16_t frequency;
	uint8_t newRequest;

} outputCharacteristics_t;





//Functions
void chargePiezo(void);
void dischargePiezo(void);
void holdPiezoVoltage(void);
void getPiezoVoltage(int16_t* voltage);
void activateChargeCircuit(void);
void deactivateChargeCircuit(void);
void activateDischargeCircuit(void);
void deactivateDischargeCircuit(void);
uint8_t isChargeCircuitActivated(void);
uint8_t isDischargeCircuitActivated(void);





#endif
