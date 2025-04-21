#include "piezo.h"

// Abstracted Piezo Commands
// -------------

// The purpose of these functions is to extrapolate the logic for the piezo 
// commands so that programming the different types of waves (found in XXXXXX.c)
// will be easier and more readable for debugging.

// charges the piezo
// maybe have pictures here?
void chargePiezo(void)
{
	// Before activating, make sure that the discharge transistor is turned off!
	if(isDischargeCircuitActivated())
	{
		deactivateDischargeCircuit();
	}

	// Activate the transistor to begin charging the piezo.
	activateChargeCircuit();
}

// Discharges the piezo immediately 
// maybe have a picture here?
void dischargePiezo(void)
{
	// Before activating, make sure that the charge transistor is turned off!
	if(isChargeCircuitActivated())
	{
		deactivateChargeCircuit();
	}

	// Active the transistor to drain the piezo.
	activateDischargeCircuit();
}

// This will allow the piezo to maintain the level of charge declared.
// maybe have a picture of an example for that?
void holdPiezoVoltage(void)
{	
	deactivateChargeCircuit();
	deactivateDischargeCircuit();
}

void getPiezoVoltage(int16_t* voltage)
{
	//may have to make this a float but we will have to see.
	//is this still a pending change?
	double rawVoltage = (ADC_VREF * adcData[PIEZO_INDEX]) / ADC_LEVELS;

	// Scale raw voltage to be -20V to 5000V
	*voltage = (int16_t)(rawVoltage * ADC_PIEZO_SCALAR); 

}

// Utilizes an optocoupler and follows a HIGH-TRUE configuration.
// 3.3V on the piezo charge pin grounds the gate driver, which gives 0V to the IGBT to cutoff the IGBT
// still true even for the octocoupler design?
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

// No optocoupler. Pin is attached directly to the gate driver. Follows a HIGH-TRUE configuration.
// why this says no optocoupler? 
// 3.3V on the piezo discharge pin supplies 3.3V to the gate driver, which gives 15V to the IGBT to activate the IGBT.
void activateDischargeCircuit(void)
{
	writePin(GPIOA, PIEZO_DISCHARGE_PIN);
}


// 0V on the piezo discharge pin gives 0V to the gate driver, which in turn gives 0V to cutoff IGBT.
// is this still true for the octocoupler change?
void deactivateDischargeCircuit(void)
{
	clearPin(GPIOA, PIEZO_DISCHARGE_PIN);
}


// Low true configuration for the charging circuit.
// what does 'low true configuration' refer to 
uint8_t isChargeCircuitActivated(void)
{
	return(readPin(GPIOA, PIEZO_CHARGE_PIN));
}


// High true configuration for the discharging circuit.
// what does 'high true configuration' refer to 
uint8_t isDischargeCircuitActivated(void)
{
	return(readPin(GPIOA, PIEZO_DISCHARGE_PIN));
}

