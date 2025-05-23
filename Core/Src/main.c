
#include "main.h"


/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);


extern volatile uint8_t messageReceived;

outputCharacteristics_t waveform = {VOLT, 0, 0, FALSE};

extern __IO uint32_t uwTick;


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
  initTimer3();

//  int16_t piezoVoltage = 0;


  while (1) //while loop being used for testing right now.
  {

	//If we haven't received a valid message in over 10 seconds, reset SPI periph. in case we've gotten out of sync with master.
	if(uwTick >= SYS_TICKS_3_SEC && SPI_Idle())
	{
		resetSPI();
		uwTick = 0;
	}

//	  int count = 0;
//	  int totalCount = 0;
//	  uint16_t totalTime_ms;
//
//	  while(1)
//	  {
//
//		  if(messageReceived)
//		  {
//			  messageReceived = 0;
//			  processMessage();
//			  //waveform.newRequest = 1;
//			  ++totalCount;
//		  }
//
//		  if(waveform.newRequest)
//		  {
//			  waveform.newRequest = 0;
//			  ++count;
//			  if(count == 1)
//			  {
//				  setTimer3(10000);
//				  continue;
//			  }
//
//
//			  if(count == 20000)
//			  {
//				  totalTime_ms = TIM3->CNT;
//				  __asm__("nop");
//			  }
//
//		  }
//		  else if(uwTick >= SYS_TICKS_10_SEC)
//			{
//				resetSPI();
//				initTimer3();
//				totalTime_ms = 0;
//				count = 0;
//				totalCount = 0;
//				uwTick = 0;
//
//			}
//	  }



    if(messageReceived)
    {
    	messageReceived = 0;
    	processMessage();
    }

    if(waveform.newRequest)
    {
		waveform.newRequest = 0;

    	//generate signal here.
		if(waveform.wave == SINE)
		{
			while(sinusoid(waveform.amplitude, waveform.frequency) == EXIT_SUCCESSFUL);
		}
		else if (waveform.wave == RECTANGLE)
		{
			while(rectangle(waveform.amplitude, waveform.frequency) == EXIT_SUCCESSFUL);
		}
		else if (waveform.wave == VOLT)
		{
			while(setVoltage(waveform.amplitude) == EXIT_SUCCESSFUL);
		}
		else
		{
			holdPiezoVoltage();
		}


		
    }

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
