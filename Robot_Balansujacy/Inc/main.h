/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
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
#define TIM3_PERIOD 63
#define TIM3_PRESCALER 0
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define B1_EXTI_IRQn EXTI15_10_IRQn
#define MS1_Pin GPIO_PIN_0
#define MS1_GPIO_Port GPIOC
#define MS2_Pin GPIO_PIN_1
#define MS2_GPIO_Port GPIOC
#define SD_EN2_Pin GPIO_PIN_0
#define SD_EN2_GPIO_Port GPIOA
#define SD_STEP2_Pin GPIO_PIN_1
#define SD_STEP2_GPIO_Port GPIOA
#define SD_DIR2_Pin GPIO_PIN_4
#define SD_DIR2_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define SD_EN1_Pin GPIO_PIN_4
#define SD_EN1_GPIO_Port GPIOC
#define ADC1_IN15_LiPol_Pin GPIO_PIN_5
#define ADC1_IN15_LiPol_GPIO_Port GPIOC
#define MS3_Pin GPIO_PIN_0
#define MS3_GPIO_Port GPIOB
#define SD_DIR1_Pin GPIO_PIN_8
#define SD_DIR1_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define SD_STEP1_Pin GPIO_PIN_4
#define SD_STEP1_GPIO_Port GPIOB
#define I2C1_SCL_MPU6050_Pin GPIO_PIN_6
#define I2C1_SCL_MPU6050_GPIO_Port GPIOB
#define I2C1_SDA_MPU6050_Pin GPIO_PIN_7
#define I2C1_SDA_MPU6050_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/