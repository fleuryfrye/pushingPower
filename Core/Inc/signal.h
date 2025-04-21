#ifndef __SIGNAL_H
#define __SIGNAL_H

#include "timer.h"


returnStatus_t setVoltage(int16_t requestedVoltage);

returnStatus_t pulse(void);

returnStatus_t rectangle(uint16_t amplitude, uint16_t frequency);

returnStatus_t sinusoid(uint16_t amplitude, uint16_t frequency);





#endif