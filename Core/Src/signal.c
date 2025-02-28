#include "signal.h"

void setVoltage(int16_t requestedVoltage){
	int16_t currentVolt;

	uint8_t confirmFlag = 0;


	while(1){
		getPiezoVoltage(&currentVolt);

		//HAL_Delay(25);

		if (currentVolt <= (requestedVoltage * 0.9))
		{
			chargePiezo();
			HAL_Delay(10);

			confirmFlag = 0;
		}

		else if (currentVolt >= (requestedVoltage * 1.1))
		{
			dischargePiezo();
			HAL_Delay(25);
			confirmFlag = 0;
		}

		else
		{
			holdPiezoVoltage();
			HAL_Delay(100);
			confirmFlag++;
		}

		if(confirmFlag > 3)
		{
			break;
		}


	}
}
