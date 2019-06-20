/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     

#include "adc.h"
#include "a4988.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

volatile uint32_t timer_global = 0;

int16_t LiPol_voltage_global = 0;

/* USER CODE END Variables */
osThreadId Engines_TaskHandle;
osThreadId LiPol_TaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

void Start_Engines_Task(void const * argument);
void Start_LiPol_Task(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of Engines_Task */
  osThreadDef(Engines_Task, Start_Engines_Task, osPriorityNormal, 0, 128);
  Engines_TaskHandle = osThreadCreate(osThread(Engines_Task), NULL);

  /* definition and creation of LiPol_Task */
  osThreadDef(LiPol_Task, Start_LiPol_Task, osPriorityNormal, 0, 128);
  LiPol_TaskHandle = osThreadCreate(osThread(LiPol_Task), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_Start_Engines_Task */
/**
  * @brief  Function implementing the Engines_Task thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_Start_Engines_Task */
void Start_Engines_Task(void const * argument)
{

  /* USER CODE BEGIN Start_Engines_Task */

	Micros_Init();

	struct A4988 A4988_1;
	struct A4988 A4988_2;

	A4988_Init(&A4988_1, SD_EN1_GPIO_Port, SD_EN1_Pin, SD_STEP1_GPIO_Port,
			SD_STEP1_Pin, SD_DIR1_GPIO_Port, SD_DIR1_Pin, MS1_GPIO_Port,
			MS1_Pin, MS2_GPIO_Port, MS2_Pin, MS3_GPIO_Port, MS3_Pin);

	A4988_Init(&A4988_2, SD_EN2_GPIO_Port, SD_EN2_Pin, SD_STEP2_GPIO_Port,
			SD_STEP2_Pin, SD_DIR2_GPIO_Port, SD_DIR2_Pin, MS1_GPIO_Port,
			MS1_Pin, MS2_GPIO_Port, MS2_Pin, MS3_GPIO_Port, MS3_Pin);

	A4988_Power_on(&A4988_1);
	A4988_Power_on(&A4988_2);

	A4988_1.previous_micros = Get_Micros();
	A4988_2.previous_micros = Get_Micros();

	/* Infinite loop */
  for(;;)
  {
	  A4988_Move(&A4988_1,  100);
	  A4988_Move(&A4988_2, -100);

	  //osDelay(1000);
  }
  /* USER CODE END Start_Engines_Task */
}

/* USER CODE BEGIN Header_Start_LiPol_Task */
/**
* @brief Function implementing the LiPol_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_LiPol_Task */
void Start_LiPol_Task(void const * argument)
{
  /* USER CODE BEGIN Start_LiPol_Task */

	const float Supply_voltage = 3.3;
	const float ADC_resolution = 4096.0;
	const float Voltage_divider_ratio = 4.7; // uwzgledniono tez spadki napiecia

	uint16_t ADC_value = 0;
	float LiPol_voltage = 0;

  /* Infinite loop */
  for(;;)
  {
		HAL_ADC_Start(&hadc1);

		HAL_StatusTypeDef status = HAL_ADC_PollForConversion(&hadc1, 10);

		if (status == HAL_OK) {

			ADC_value = HAL_ADC_GetValue(&hadc1);
			LiPol_voltage = (Supply_voltage * ADC_value) / (ADC_resolution - 1);
			LiPol_voltage *= Voltage_divider_ratio;
		}

		HAL_ADC_Start(&hadc1);

		LiPol_voltage_global = LiPol_voltage * 100; // zmienna tymczasowa

		if (LiPol_voltage_global <= 1100) {

			/* Debug LED LD2 fast blink */
			for (int i = 0; i <= 101; i++) {

				HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
				osDelay(50);
			}

			//EXIT_FAILURE;
		}

		osDelay(20000);
  }
  /* USER CODE END Start_LiPol_Task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
