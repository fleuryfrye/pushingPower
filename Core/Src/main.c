/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

#define PIEZO_CHARGE_PIN 9U
#define PIEZO_DISCHARGE_PIN 10U
#define OUTPUT_MODE 1U
#define HIGH_SPEED_OUTPUT 0x03
#define PIEZO_CHARGE_PIN_HIGH (1U << PIEZO_CHARGE_PIN)
#define PIEZO_DISCHARGE_PIN_HIGH (1U << PIEZO_DISCHARGE_PIN)




/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

static void initGPIO(void);
static void chargePiezo(void);
static void dischargePiezo(void);



int main(void)
{

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();


  /* Configure the system clock */
  SystemClock_Config();

  initGPIO();

  while (1)
  {
    chargePiezo();
    HAL_Delay(1000);
    dischargePiezo();
    HAL_Delay(1000);


  }
}



static void initGPIO(void)
{
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
