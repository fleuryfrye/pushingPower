#include "signal.h"
#include "piezo.h"


extern outputCharacteristics_t waveform;

extern volatile uint8_t messageReceived;


returnStatus_t setVoltage(int16_t requestedVoltage)
{
	int16_t currentVolt;

	uint8_t confirmFlag = 0;


	returnStatus_t sts;

	while(!waveform.newRequest || (hasTimer3Expired() == FALSE)){

		//If we haven't received a valid message in over 10 seconds, reset SPI periph. in case we've gotten out of sync with master.
		if(uwTick >= SYS_TICKS_10_SEC)
		{
			resetSPI();
			uwTick = 0;
		}

		if(requestedVoltage == 0)
		{
			dischargePiezo();
			break;
		}

		getPiezoVoltage(&currentVolt);

		if (currentVolt <= (requestedVoltage * 0.95))
		{
			chargePiezo();

			confirmFlag = 0;
		}

		else if (currentVolt >= (requestedVoltage * 1.05))
		{
			dischargePiezo();

			confirmFlag = 0;
		}

		else
		{
			holdPiezoVoltage();

			confirmFlag++;
		}



		if(hasTimer3Expired() == TRUE) break;

		sts = wait(3);

		if(sts > 0)
		{
			holdPiezoVoltage();
			return sts;
		}

		if(confirmFlag > 2)
		{
			//getPiezoVoltage(&currentVolt);
			//holdPiezoVoltage();


			break;
		}


	}

    holdPiezoVoltage();

	if(messageReceived)
	{
		messageReceived = 0;
		processMessage();
	}

	if(waveform.newRequest)
	{
		return EXIT_NEWREQUEST;
	}

	return EXIT_SUCCESSFUL;
}





returnStatus_t pulse(void)
{

	returnStatus_t sts;


	sts = setVoltage(5000);

	if(sts > 0)
	{
		return sts;
	}


	dischargePiezo();

	return EXIT_SUCCESSFUL;



}







returnStatus_t rectangle(uint16_t amplitude, uint16_t frequency)
{

	float period = 1.0 / frequency;

	float holdTime = period / 2.0;

	returnStatus_t sts;


    setTimer3(holdTime * 1000);

	sts = setVoltage(amplitude);

	if(sts > 0)
	{
		return sts;
	}

	//sts = wait(getMicroseconds(holdTime));

    sts = waitForTimer3();
    if(sts > 0)
    {
        return sts;
    }

	// if(sts > 0)
	// {
	// 	return sts;
	// }


    setTimer3(holdTime * 1000);
	dischargePiezo();



	// sts = wait(getMicroseconds(holdTime));

	// if(sts > 0)
	// {
	// 	return sts;
	// }

    sts = waitForTimer3();
    if(sts > 0)
    {
        return sts;
    }


	return EXIT_SUCCESSFUL;

}


returnStatus_t sinusoid(uint16_t amplitude, uint16_t frequency)
{

	float sineValues[8] = {0, 0.5, 0.707, 0.866, 1, 0.866, 0.707, 0.5};


	float maxHoldTime = ((float) 1 / frequency) / (float)8;

	returnStatus_t sts;

		for(int i = 0; i < 8; i++)
		{
			uint16_t voltage = amplitude * sineValues[i];

            setTimer3(maxHoldTime * 1000);

			if(voltage == 0)
			{
				dischargePiezo();
			}
			else
			{
				sts = setVoltage(voltage);
				if (sts > 0)
				{
					return sts;
				}
			}

			//sts = wait(maxHoldTime * 1000000);
            sts = waitForTimer3();

            if(sts > 0)
            {
                return sts;
            }

		}


	
	return EXIT_SUCCESSFUL;

}
