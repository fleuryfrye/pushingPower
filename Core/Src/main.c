
#include "main.h"

#include <math.h>


/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

static void initGPIO(void);
static void initADC(void);


static void chargePiezo(void);
static void dischargePiezo(void);
static void getPiezoVoltage(int16_t* voltage);



extern volatile int16_t adcData; //raw signed 12 bit data.
extern volatile uint8_t ADCRDY;


int main(void)
{

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();


  /* Configure the system clock */
  SystemClock_Config();

  __enable_irq();


  initGPIO();
  initADC();

  int16_t piezoVoltage = 0;

  while (1) //while loop being used for testing right now.
  {
    chargePiezo();

    getPiezoVoltage(&piezoVoltage); //testing.

    HAL_Delay(1000);
    dischargePiezo();
    HAL_Delay(1000);

  }
}

static void initADC(void)
{
	// ADC clock frequency is set to 36 MHz.
	//According to the reference manual, 12-bit resolution requires 14 clock cycles per sample.
	// This results in one ADC sample being generated every 388 nanoseconds.

	GPIOA->MODER |= (ADC_INPUT_MODE << (ADC_PIN * 2));
	RCC->AHBENR |= (1 << ADC_CLK_EN); // enable ADC clock

	ADC12_COMMON->CCR |= (2 << ADC1_CCR_CKMODE); //Set ADC clock to 36 MHz. (prescaler = /2)


	//Voltage regular must start up before calibration.
	ADC1->CR &= ~(1 << ADC1_CR_VREG_MSB);
	ADC1->CR |= (1 << ADC1_CR_VREG_LSB); //startup vreg
	HAL_Delay(1); //must wait at least 10 us after starting up the vreg



	//Recommended to calibrate the ADC on startup.
	ADC1->CR |= (1 << ADC1_CR_CAL);
	while(ADC1->CR & (1 << ADC1_CR_CAL)); // hardware clears cal bit when finished.


	//Enable ADC ready and end of conversion interrupts
	ADC1->IER |= (1 << ADC_RDY);
	ADC1->IER |= (1 << ADC_EOC);



	//12 bit is right aligned and (allegedly) sign extended to 16 bits. Need to verify with negative voltage.
	//(this looks good for positive values, but I need to check negative values!)

	//Enable the ADC code to be signed.
	ADC1->OFR4 |= (1 << ADC1_OFR4_OFFSET1_EN);
	ADC1->OFR4 |= (1 << ADC1_OFR4_OFFSET1_CH);


	ADC1->SQR1 |= (ADC1_CHANNEL_1 << ADC1_SQR1_SQ1); //activate channel 1.
	//note: length bit field is left as 0 because we are only doing 1 conversion.



	ADC1->CFGR |= (1 << ADC1_CFGR_CONT); //continuously sample
	ADC1->CFGR |= (1 << ADC1_CFGR_OVRMOD); // if sample is missed, overwrite with newest


	ADC1->CR |= (1 << ADC1_CR_EN); //Enable the ADC and wait for it to be ready.

	NVIC_EnableIRQ(ADC1_2_IRQn); //Register the interrupt with NVIC

	while(!ADCRDY); //Interrupt will set ADCREADY.


	ADC1->CR |= (1 << ADC1_CR_ADSTART); //Begin sampling!


}

static void initGPIO(void)
{
	//Peripheral clocks turned off by default, each GPIO port has a clock that must be activated first.
	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIOA->MODER |= (OUTPUT_MODE << (PIEZO_CHARGE_PIN * 2));
	GPIOA->MODER |= (OUTPUT_MODE << (PIEZO_DISCHARGE_PIN * 2));


	GPIOA->OSPEEDR |= (HIGH_SPEED_OUTPUT << (PIEZO_CHARGE_PIN * 2));
	GPIOA->OSPEEDR |= (HIGH_SPEED_OUTPUT << (PIEZO_DISCHARGE_PIN * 2));

	return;
}

static void chargePiezo(void)
{
	//Before activating, make sure that the discharge transistor is turned off!
	if(GPIOA->ODR & PIEZO_DISCHARGE_PIN_HIGH)
	{
		GPIOA->BRR = PIEZO_DISCHARGE_PIN_HIGH; //clear discharge pin bit
	}

	//Activate the transistor to begin charging the piezo.
	GPIOA->BSRR = PIEZO_CHARGE_PIN_HIGH;
}

static void dischargePiezo(void)
{
	//Before activating, make sure that the charge transistor is turned off!
	if(GPIOA->ODR & PIEZO_CHARGE_PIN_HIGH)
	{
		GPIOA->BRR = PIEZO_CHARGE_PIN_HIGH; // clear charge pin bit.
	}


	//Active the transistor to drain the piezo.
	GPIOA->BSRR = PIEZO_DISCHARGE_PIN_HIGH;
}




static void getPiezoVoltage(int16_t* voltage)
{

	//may have to make this a float but we will have to see.
	float rawVoltage = (ADC_VREF * adcData) / (pow(2, 12) - 1);


	*voltage = (int16_t)(rawVoltage * ADC_PIEZO_SCALAR); //Scale raw voltage to be -20V to 5000V

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
