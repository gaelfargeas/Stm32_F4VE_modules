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
#define PB3_K1_Pin GPIO_PIN_3
#define PB3_K1_GPIO_Port GPIOE
#define BP2_K0_Pin GPIO_PIN_4
#define BP2_K0_GPIO_Port GPIOE
#define BP1_Pin GPIO_PIN_0
#define BP1_GPIO_Port GPIOA
#define LED1_Pin GPIO_PIN_6
#define LED1_GPIO_Port GPIOA
#define LED2_Pin GPIO_PIN_7
#define LED2_GPIO_Port GPIOA
#define LCD_BL_Pin GPIO_PIN_1
#define LCD_BL_GPIO_Port GPIOB
#define BOOT1_jumper_Pin GPIO_PIN_2
#define BOOT1_jumper_GPIO_Port GPIOB
#define WIRELESS_CS_Pin GPIO_PIN_12
#define WIRELESS_CS_GPIO_Port GPIOB
#define WIRELESS_SCK_Pin GPIO_PIN_13
#define WIRELESS_SCK_GPIO_Port GPIOB
#define WIRELESS_MISO_Pin GPIO_PIN_14
#define WIRELESS_MISO_GPIO_Port GPIOB
#define WIRELESS_MOSI_Pin GPIO_PIN_15
#define WIRELESS_MOSI_GPIO_Port GPIOB
#define BP_SELECT_Pin GPIO_PIN_5
#define BP_SELECT_GPIO_Port GPIOB
#define BP_SELECT_EXTI_IRQn EXTI9_5_IRQn

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
