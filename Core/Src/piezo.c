#include "piezo.h"



void chargePiezo(void)
{
	//Before activating, make sure that the discharge transistor is turned off!
	if(GPIOA->ODR & PIEZO_DISCHARGE_PIN_HIGH)
	{
		GPIOA->BRR = PIEZO_DISCHARGE_PIN_HIGH; //clear discharge pin bit
	}

	//Activate the transistor to begin charging the piezo.
	GPIOA->BSRR = PIEZO_CHARGE_PIN_HIGH;
}

void dischargePiezo(void)
{
	//Before activating, make sure that the charge transistor is turned off!
	if(GPIOA->ODR & PIEZO_CHARGE_PIN_HIGH)
	{
		GPIOA->BRR = PIEZO_CHARGE_PIN_HIGH; // clear charge pin bit.
	}


	//Active the transistor to drain the piezo.
	GPIOA->BSRR = PIEZO_DISCHARGE_PIN_HIGH;
}


void holdPiezoVoltage(void)
{
	GPIOA->BRR = (PIEZO_CHARGE_PIN_HIGH | PIEZO_DISCHARGE_PIN_HIGH); //Turn off charge and discharge transistors.
}

void getPiezoVoltage(int16_t* voltage)
{

	//may have to make this a float but we will have to see.
	float rawVoltage = (ADC_VREF * adcData) / (pow(2, 12) - 1);


	*voltage = (int16_t)(rawVoltage * ADC_PIEZO_SCALAR); //Scale raw voltage to be -20V to 5000V

}
