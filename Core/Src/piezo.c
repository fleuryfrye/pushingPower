#include "piezo.h"



void chargePiezo(void)
{
	//Before activating, make sure that the discharge transistor is turned off!
	if(isDischargeCircuitActivated())
	{
		deactivateDischargeCircuit();
	}

	//Activate the transistor to begin charging the piezo.
	activateChargeCircuit();
}

void dischargePiezo(void)
{
	//Before activating, make sure that the charge transistor is turned off!
	if(isChargeCircuitActivated())
	{
		deactivateChargeCircuit();
	}

	//Active the transistor to drain the piezo.
	activateDischargeCircuit();
}


void holdPiezoVoltage(void)
{	
	deactivateChargeCircuit();
	deactivateDischargeCircuit();
}

void getPiezoVoltage(int16_t* voltage)
{

	//may have to make this a float but we will have to see.
	double rawVoltage = (ADC_VREF * adcData[PIEZO_INDEX]) / ADC_LEVELS;


	*voltage = (int16_t)(rawVoltage * ADC_PIEZO_SCALAR); //Scale raw voltage to be -20V to 5000V

}



// Utilizes an optocoupler and follows a HIGH-TRUE configuration.
// 3.3V on the piezo charge pin grounds the gate driver, which gives 0V to the IGBT to cutoff the IGBT
void deactivateChargeCircuit(void)
{
	clearPin(GPIOA, PIEZO_CHARGE_PIN);
}


// Utilizes an optocoupler and follows a HIGH-TRUE configuration.
// 0V on the piezo charge pin gives 3.3V to the gate driver, which in turn gives 15V to activate IGBT to charge the piezo.
void activateChargeCircuit(void)
{
	writePin(GPIOA, PIEZO_CHARGE_PIN);
}

//No optocoupler. Pin is attached directly to the gate driver. Follows a HIGH-TRUE configuration.
// 3.3V on the piezo discharge pin supplies 3.3V to the gate driver, which gives 15V to the IGBT to activate the IGBT.
void activateDischargeCircuit(void)
{
	writePin(GPIOA, PIEZO_DISCHARGE_PIN);
}


// 0V on the piezo discharge pin gives 0V to the gate driver, which in turn gives 0V to cutoff IGBT.
void deactivateDischargeCircuit(void)
{
	clearPin(GPIOA, PIEZO_DISCHARGE_PIN);
}


//Low true configuration for the charging circuit.
uint8_t isChargeCircuitActivated(void)
{
	return(readPin(GPIOA, PIEZO_CHARGE_PIN));
}


//High true configuration for the discharging circuit.
uint8_t isDischargeCircuitActivated(void)
{
	return(readPin(GPIOA, PIEZO_DISCHARGE_PIN));
}

