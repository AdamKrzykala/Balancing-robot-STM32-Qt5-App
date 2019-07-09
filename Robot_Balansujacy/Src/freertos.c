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
#include "mpu6050.h"
#include "pid.h"
#include "hc05.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define SETPOINT	0
#define OFFSET		0
#define HYSTERESIS	0.5

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

struct Data_frame_from_PC	DF_PC;

int8_t Data_from_PC[DATA_FRAME_FROM_PC_SIZE];
uint8_t Data_to_PC[DATA_FRAME_TO_PC_SIZE];

double Filter_weight = 0.05;

int16_t LiPol_voltage_global = 0;
uint8_t LiPol_voltage_too_low = 0;

I2C_HandleTypeDef  *mpu6050_i2c_handle = &hi2c1;
UART_HandleTypeDef *hc05_uart_handle   = &huart1;

int16_t Roll_filtered_global = 0;
double  Roll_filtered_pid = 0;

int16_t a_x_global = 0, a_y_global = 0, a_z_global = 0;
int16_t g_x_global = 0, g_y_global = 0, g_z_global = 0;

int16_t a_x_offset_global = 0, a_y_offset_global = 0, a_z_offset_global = 0;
int16_t g_x_offset_global = 0, g_y_offset_global = 0, g_z_offset_global = 0;

int16_t Kp_global = 6000, Ti_global = 0, Td_global = 0;

int16_t LeftEngineSpeed_global = 0;
int16_t RightEngineSpeed_global = 0;

uint8_t mpu6050_correct_init_global = 0;

/* USER CODE END Variables */
osThreadId Engines_TaskHandle;
osThreadId LiPol_TaskHandle;
osThreadId Control_TaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

/* USER CODE END FunctionPrototypes */

void Start_Engines_Task(void const * argument);
void Start_LiPol_Task(void const * argument);
void Start_Control_Task(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
	HAL_UART_Receive_DMA(hc05_uart_handle, Data_from_PC, DATA_FRAME_FROM_PC_SIZE);

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
  osThreadDef(Engines_Task, Start_Engines_Task, osPriorityNormal, 0, 512);
  Engines_TaskHandle = osThreadCreate(osThread(Engines_Task), NULL);

  /* definition and creation of LiPol_Task */
  osThreadDef(LiPol_Task, Start_LiPol_Task, osPriorityNormal, 0, 512);
  LiPol_TaskHandle = osThreadCreate(osThread(LiPol_Task), NULL);

  /* definition and creation of Control_Task */
  osThreadDef(Control_Task, Start_Control_Task, osPriorityNormal, 0, 512);
  Control_TaskHandle = osThreadCreate(osThread(Control_Task), NULL);

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

	struct A4988 A4988_1;
	struct A4988 A4988_2;

	A4988_Init(&A4988_1, SD_EN1_GPIO_Port, SD_EN1_Pin, SD_STEP1_GPIO_Port,
			SD_STEP1_Pin, SD_DIR1_GPIO_Port, SD_DIR1_Pin, MS1_GPIO_Port,
			MS1_Pin, MS2_GPIO_Port, MS2_Pin, MS3_GPIO_Port, MS3_Pin);

	A4988_Init(&A4988_2, SD_EN2_GPIO_Port, SD_EN2_Pin, SD_STEP2_GPIO_Port,
			SD_STEP2_Pin, SD_DIR2_GPIO_Port, SD_DIR2_Pin, MS1_GPIO_Port,
			MS1_Pin, MS2_GPIO_Port, MS2_Pin, MS3_GPIO_Port, MS3_Pin);

	A4988_Power_off(&A4988_1);
	A4988_Power_off(&A4988_2);

	Micros_Init();

	A4988_1.previous_micros = Get_Micros();
	A4988_2.previous_micros = Get_Micros();

	/* Infinite loop */
  for(;;)
  {
	  if( LiPol_voltage_too_low != 1 ) {

		  A4988_Move(&A4988_1,  LeftEngineSpeed_global);
		  A4988_Move(&A4988_2, -RightEngineSpeed_global);
	  }
	  else {

		  A4988_Power_off(&A4988_1);
		  A4988_Power_off(&A4988_2);
	  }
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
	const float Voltage_divider_ratio = 4.7;

	uint16_t ADC_value = 0;
	float LiPol_voltage = 0;

	HAL_StatusTypeDef status = HAL_ERROR;

  /* Infinite loop */
  for (;;) {

		status = HAL_ADC_Start(&hadc1);

		if (status == HAL_OK) {

			status = HAL_ADC_PollForConversion(&hadc1, 10);

			if (status == HAL_OK) {

				ADC_value = HAL_ADC_GetValue(&hadc1);
				LiPol_voltage = (Supply_voltage * ADC_value) / (ADC_resolution - 1);
				LiPol_voltage *= Voltage_divider_ratio;
			}

			LiPol_voltage_global = LiPol_voltage * 100;

			if (LiPol_voltage_global <= 1100) {
			//if (LiPol_voltage_global <= 650) {

				for(int i = 0; i < 100; i++) {

					HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
					osDelay(100);
				}

				if(LiPol_voltage_global <= 1050) {
				//if(LiPol_voltage_global <= 620) {

					LiPol_voltage_too_low = 1;
				}

			}
			else {

				LiPol_voltage_too_low = 0;
			}
		}

		osDelay(20000);
	}
  /* USER CODE END Start_LiPol_Task */
}

/* USER CODE BEGIN Header_Start_Control_Task */
/**
* @brief Function implementing the Control_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_Control_Task */
void Start_Control_Task(void const * argument)
{
  /* USER CODE BEGIN Start_Control_Task */

	int32_t Timer_start = HAL_GetTick();

	/* IMU variables */
	struct MPU6050 mpu1;

	int32_t I_Time_Stop = HAL_GetTick();
	int32_t I_Time_Start = 0;

	double Roll_filtered_temp = 0;

	/* PID variables */
	struct PID_regulator pid;

	PID_Init(&pid, SETPOINT);

	double Kp = Kp_global;
	double Ti = Ti_global;
	double Td = Td_global;

	/******* MPU6050 Initialization and connection ******/
	osDelay(1500);

	MPU6050_Result connected = MPU6050_Init(mpu6050_i2c_handle, &mpu1,
			MPU6050_Device_0, MPU6050_Accelerometer_2G, MPU6050_Gyroscope_2000s,
			MPU6050_DataRate_100Hz);

	/****** MPU6050 Calibration *******/

	if (connected == MPU6050_Result_Ok) {

		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		osDelay(100);
		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);

		MPU6050_Accelerometer_Calibration(mpu6050_i2c_handle, &mpu1);
		MPU6050_Gyroscope_Calibration(mpu6050_i2c_handle, &mpu1);

		//a_x_offset_global = mpu1.Acce_X_Offset, a_y_offset_global = mpu1.Acce_Y_Offset, a_z_offset_global = mpu1.Acce_Z_Offset;
		//g_x_offset_global = mpu1.Gyro_X_Offset, g_y_offset_global = mpu1.Gyro_Y_Offset, g_z_offset_global = mpu1.Gyro_Z_Offset;

		//MPU6050_Accelerometer_Set_Offset(&mpu1, 761, -302, -2869);
		//MPU6050_Gyroscope_Set_Offset(&mpu1, 2933, -35, 101);

		mpu6050_correct_init_global = 1;
	}
	else {

		mpu6050_correct_init_global = 0;
	}


  /* Infinite loop */
  for (;;) {

		if (mpu6050_correct_init_global == 1) {

			I_Time_Start = I_Time_Stop;
			I_Time_Stop = HAL_GetTick();

			MPU6050_Accelerometer_RPY(mpu6050_i2c_handle, &mpu1);
			MPU6050_Gyroscope_RPY(mpu6050_i2c_handle, &mpu1, I_Time_Start,
					I_Time_Stop);

			/***** Complementary filter *****/
			Roll_filtered_temp = ((1-Filter_weight)
					* (Roll_filtered_temp
							+ (mpu1.Gyro_Pitch
									* ((I_Time_Start - I_Time_Stop) / 1000)))
					+ (Filter_weight * mpu1.Acce_Pitch));

			a_x_global = mpu1.Acce_X;
			a_y_global = mpu1.Acce_Y;
			a_z_global = mpu1.Acce_Z;
			g_x_global = mpu1.Gyro_X;
			g_y_global = mpu1.Gyro_Y;
			g_z_global = mpu1.Gyro_Z;

			Roll_filtered_global = Roll_filtered_temp + OFFSET;
			Roll_filtered_pid = Roll_filtered_temp + OFFSET;

			if (HAL_GetTick() - Timer_start >= 4) {

				Kp = Kp_global;
				Ti = Ti_global;
				Td = Td_global;

				PID_Set_parameters(&pid, Kp / 100, Ti / 100, Td/ 100);
				PID_Calculate(&pid, Roll_filtered_pid, I_Time_Start, I_Time_Stop);

				if ( (Roll_filtered_pid < SETPOINT - HYSTERESIS  ||
					  Roll_filtered_pid > SETPOINT + HYSTERESIS) &&
					  fabs(Roll_filtered_pid) < 80) {

					LeftEngineSpeed_global = pid.control;
					RightEngineSpeed_global = pid.control;

				} else {

					LeftEngineSpeed_global = 0;
					RightEngineSpeed_global = 0;
				}

				Timer_start = HAL_GetTick();
			}
		}
  }
  /* USER CODE END Start_Control_Task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
	void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {

		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);

		HAL_UART_Receive_DMA(hc05_uart_handle, Data_from_PC, DATA_FRAME_FROM_PC_SIZE);
		HC05_Parse_Data_frame(&DF_PC, Data_from_PC);

		Kp_global = DF_PC.Kp;
		Ti_global = DF_PC.Ki;
		Td_global = DF_PC.Kd;
	}

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
