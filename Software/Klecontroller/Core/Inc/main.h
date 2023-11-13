/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BUTTON_JOY1_Pin GPIO_PIN_0
#define BUTTON_JOY1_GPIO_Port GPIOC
#define JOY1_ADC_Y_Pin GPIO_PIN_1
#define JOY1_ADC_Y_GPIO_Port GPIOC
#define JOY1_ADC_X_Pin GPIO_PIN_2
#define JOY1_ADC_X_GPIO_Port GPIOC
#define BUTTON_JOY2_Pin GPIO_PIN_0
#define BUTTON_JOY2_GPIO_Port GPIOA
#define JOY2_ADC_Y_Pin GPIO_PIN_1
#define JOY2_ADC_Y_GPIO_Port GPIOA
#define JOY2_ADC_X_Pin GPIO_PIN_2
#define JOY2_ADC_X_GPIO_Port GPIOA
#define BUTTON_ENC_Pin GPIO_PIN_5
#define BUTTON_ENC_GPIO_Port GPIOA
#define ENC_A_Pin GPIO_PIN_6
#define ENC_A_GPIO_Port GPIOA
#define ENC_B_Pin GPIO_PIN_7
#define ENC_B_GPIO_Port GPIOA
#define LED_Pin GPIO_PIN_2
#define LED_GPIO_Port GPIOB
#define NRF24_IRQ_Pin GPIO_PIN_12
#define NRF24_IRQ_GPIO_Port GPIOB
#define NRF24_IRQ_EXTI_IRQn EXTI15_10_IRQn
#define NRF24_CSN_Pin GPIO_PIN_6
#define NRF24_CSN_GPIO_Port GPIOC
#define NRF24_CE_Pin GPIO_PIN_7
#define NRF24_CE_GPIO_Port GPIOC
#define BUTTON_UP_Pin GPIO_PIN_10
#define BUTTON_UP_GPIO_Port GPIOC
#define BUTTON_DOWN_Pin GPIO_PIN_2
#define BUTTON_DOWN_GPIO_Port GPIOD
#define KEEP_ALIVE_Pin GPIO_PIN_5
#define KEEP_ALIVE_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
