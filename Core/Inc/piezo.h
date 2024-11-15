#ifndef __PIEZO_H
#define __PIEZO_H

//Includes
#include "stm32f3xx_hal.h"
#include "adc.h"
#include"gpio.h"

//Functions
void chargePiezo(void);
void dischargePiezo(void);
void holdPiezoVoltage(void);
void getPiezoVoltage(int16_t* voltage);




#endif
