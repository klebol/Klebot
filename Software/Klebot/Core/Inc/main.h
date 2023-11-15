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
#include "stm32f1xx_hal.h"

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
#define DRV_MODE_Pin GPIO_PIN_13
#define DRV_MODE_GPIO_Port GPIOC
#define DRV_NSLEEP_Pin GPIO_PIN_14
#define DRV_NSLEEP_GPIO_Port GPIOC
#define LED_Pin GPIO_PIN_0
#define LED_GPIO_Port GPIOC
#define KEEP_ALIVE_Pin GPIO_PIN_1
#define KEEP_ALIVE_GPIO_Port GPIOC
#define DRV_AIN1_Pin GPIO_PIN_6
#define DRV_AIN1_GPIO_Port GPIOC
#define DRV_AIN2_Pin GPIO_PIN_7
#define DRV_AIN2_GPIO_Port GPIOC
#define DRV_BIN1_Pin GPIO_PIN_8
#define DRV_BIN1_GPIO_Port GPIOC
#define DRV_BIN2_Pin GPIO_PIN_9
#define DRV_BIN2_GPIO_Port GPIOC
#define ENC_A_1_Pin GPIO_PIN_8
#define ENC_A_1_GPIO_Port GPIOA
#define ENC_A_2_Pin GPIO_PIN_9
#define ENC_A_2_GPIO_Port GPIOA
#define BUTTON_PWR_Pin GPIO_PIN_10
#define BUTTON_PWR_GPIO_Port GPIOA
#define NRF24_IRQ_Pin GPIO_PIN_15
#define NRF24_IRQ_GPIO_Port GPIOA
#define NRF24_IRQ_EXTI_IRQn EXTI15_10_IRQn
#define NRF24_SCK_Pin GPIO_PIN_10
#define NRF24_SCK_GPIO_Port GPIOC
#define NRF24_MISO_Pin GPIO_PIN_11
#define NRF24_MISO_GPIO_Port GPIOC
#define NRF24_MOSI_Pin GPIO_PIN_12
#define NRF24_MOSI_GPIO_Port GPIOC
#define NRF24_CSN_Pin GPIO_PIN_2
#define NRF24_CSN_GPIO_Port GPIOD
#define NRF24_CE_Pin GPIO_PIN_4
#define NRF24_CE_GPIO_Port GPIOB
#define ENC_B_1_Pin GPIO_PIN_6
#define ENC_B_1_GPIO_Port GPIOB
#define ENC_B_2_Pin GPIO_PIN_7
#define ENC_B_2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
