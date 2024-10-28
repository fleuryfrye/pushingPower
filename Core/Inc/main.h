/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

#define PIEZO_CHARGE_PIN 9U
#define PIEZO_DISCHARGE_PIN 10U
#define OUTPUT_MODE 1U
#define HIGH_SPEED_OUTPUT 0x03
#define PIEZO_CHARGE_PIN_HIGH (1U << PIEZO_CHARGE_PIN)
#define PIEZO_DISCHARGE_PIN_HIGH (1U << PIEZO_DISCHARGE_PIN)

#define ADC_PIN 0U
#define ADC_INPUT_MODE 3U
#define ADC_CLK_EN 28U


#define ADC_RDY 0U
#define ADC_EOC 2U

#define ADC1_SQR1_SQ1 6U // [4:0]
#define ADC1_CHANNEL_1 1U


#define ADC1_CFGR_CONT 13U
#define ADC1_CFGR_OVRMOD 12U

#define ADC1_CR_ADSTART 2U
#define ADC1_CR_EN 0U
#define ADC1_CR_CAL 31U
#define ADC1_CR_VREG_MSB 29U
#define ADC1_CR_VREG_LSB 28U

#define ADC1_CCR_CKMODE 16U

#define ADC_VREF 3.3



extern volatile int16_t adcData; //signed 12 bit data.
extern volatile uint8_t ADCRDY;



/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
