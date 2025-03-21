
#include "main.h"


/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);


extern volatile uint8_t messageReceived;

outputCharacteristics_t waveform = {OFF, 0, 0, FALSE};

uint8_t isSpiOn;






void setVoltage(int16_t requestedVoltage){
	int16_t currentVolt;

	uint8_t confirmFlag = 0;


	while(1){
		getPiezoVoltage(&currentVolt);

		//HAL_Delay(25);

		if (currentVolt <= (requestedVoltage * 0.9))
		{
			chargePiezo();
			//HAL_Delay(1);

			setTimer(50);

			waitForTimer();

			confirmFlag = 0;
		}

		else if (currentVolt >= (requestedVoltage * 1.1))
		{
			dischargePiezo();
			//HAL_Delay(1);

			setTimer(50);

			waitForTimer();


			confirmFlag = 0;
		}

		else
		{
			holdPiezoVoltage();
			//HAL_Delay(1);

			setTimer(50);

			waitForTimer();
			confirmFlag++;
		}

		if(confirmFlag > 1)
		{
			getPiezoVoltage(&currentVolt);

			break;
		}


	}
}





void pulse(void)
{


	setVoltage(5000);
	dischargePiezo();



}







void rectangle(uint16_t amplitude, uint16_t frequency)
{

	double period = 1.0 / frequency;

	double holdTime = period / 2.0;

	while(!(waveform.newRequest))
	{

		//chargePiezo();
		setVoltage(amplitude);



		setTimer(getMicroseconds(holdTime));

		waitForTimer();

		dischargePiezo();

		setTimer(getMicroseconds(holdTime));

		waitForTimer();


	}



}



void sinusoid(void)
{
	  //Sine wave???

	  int volt = 100;
	  int up = 1;

	  while(!(waveform.newRequest))
	  {

		setVoltage(volt);

		setTimer(10);
		waitForTimer();

		if(volt < 5000 && up)
		{
			volt += 200;

			if(volt >= 5000)
			{
				up = 0;
				volt = 5000;
			}

		}



		if(volt > 0 && !up)
		{
			volt -= 200;

			if(volt <= 0)
			{
				up = 1;
				volt = 100;
			}
		}

	  }

}






int main(void)
{

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();


  /* Configure the system clock */
  //SystemClock_Config();

  initRCC();

  __enable_irq();


  initGPIO();
  initADC();
  initSPI();
  initTimer();
  isSpiOn = 1;

  int16_t piezoVoltage = 0;
//  volatile uint32_t timeout = 0;


  while (1) //while loop being used for testing right now.
  {

    getPiezoVoltage(&piezoVoltage); //testing.


    if(messageReceived)
    {
    	messageReceived = 0;
    	processMessage();
    }

    if(waveform.newRequest)
    {
    	//generate signal here.
    }


    //Need to be able to detect if controller disconnected.
    //This works, but we need to make this more robust
    //Detect if NSS is high for 5 seconds, if so turn off SPI
    // Detect if controller connected, re-enable SPI
    //EXT Interrupt of NSS pin and a timer preferred.
    //EXT Higher Interrupt Priority than SPI
//	if(isSpiOn && NSSUnasserted())
//	{
//		while(NSSUnasserted())
//		{db   1a
//			if(timeout++ > 60000)
//			{
//				SPI1->CR1 &= ~(SPI_ENABLE);
//				isSpiOn = 0;
//				break;
//			}
//		}
//
//		timeout = 0;
//
//
//
//	}
//
//	if(!isSpiOn && !NSSUnasserted())
//	{
//		SPI1->CR1 |= SPI_ENABLE;
//		isSpiOn = 1;
//	}

  }
}



/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}




/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
