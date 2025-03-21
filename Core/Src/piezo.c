#include "piezo.h"



void chargePiezo(void)
{
	//Before activating, make sure that the discharge transistor is turned off!
	if(readPin(GPIOA, PIEZO_DISCHARGE_PIN))
	{
		clearPin(GPIOA, PIEZO_DISCHARGE_PIN);
	}

	//Activate the transistor to begin charging the piezo.
	writePin(GPIOA, PIEZO_CHARGE_PIN);
}

void dischargePiezo(void)
{
	//Before activating, make sure that the charge transistor is turned off!
	if(readPin(GPIOA, PIEZO_CHARGE_PIN))
	{
		clearPin(GPIOA, PIEZO_CHARGE_PIN);
	}

	//Active the transistor to drain the piezo.
	writePin(GPIOA, PIEZO_DISCHARGE_PIN);
}


void holdPiezoVoltage(void)
{	
	clearPin(GPIOA, PIEZO_CHARGE_PIN);
	clearPin(GPIOA, PIEZO_DISCHARGE_PIN);
}

void getPiezoVoltage(int16_t* voltage)
{

	//may have to make this a float but we will have to see.
	double rawVoltage = (ADC_VREF * adcData[PIEZO_INDEX]) / ADC_LEVELS;


	*voltage = (int16_t)(rawVoltage * ADC_PIEZO_SCALAR); //Scale raw voltage to be -20V to 5000V

}
