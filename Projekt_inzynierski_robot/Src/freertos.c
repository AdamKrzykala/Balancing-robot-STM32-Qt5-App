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
#include "tim.h"
#include "mpu9250.h"
#include "apid.h"
#include "spid.h"
#include "hc05.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define SETPOINT_ANGLE			0
#define HYSTERESIS_ANGLE		0
#define KP_ANGLE				10
#define KI_ANGLE				100
#define KD_ANGLE				0.1

#define SETPOINT_SPEED			0
#define HYSTERESIS_SPEED		0
#define KP_SPEED				20
#define KI_SPEED				15
#define KD_SPEED				0.1

#define FILTER_WEIGHT 			0.001
#define VARIANCE				10000

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* ------------> MPU9250 variables <------------- */
float a_x_g = 0, a_y_g = 0, a_z_g = 0;
float g_x_dgs = 0, g_y_dgs = 0, g_z_dgs = 0;
float m_x_uT = 0, m_y_uT = 0, m_z_uT = 0;

float a_roll_global = 0, a_pitch_global = 0;
float g_roll_global  = 0, g_pitch_global = 0, g_yaw_global   = 0;
float m_yaw_global = 0;

int16_t a_x_offset_global = 0, a_y_offset_global = 0, a_z_offset_global = 0;
int16_t g_x_offset_global = 0, g_y_offset_global = 0, g_z_offset_global = 0;

float Complementary_Roll_global = 0, Complementary_Pitch_global = 0, Complementary_Yaw_global = 0;
float Kalman_Roll_global = 0, Kalman_Pitch_global = 0, Kalman_Yaw_global = 0;
float Madgwick_Roll_global = 0, Madgwick_Pitch_global = 0, Madgwick_Yaw_global = 0;

float Filter_weight_global = FILTER_WEIGHT;
int16_t Kalman_filter_process_variance = VARIANCE;

float q1_test_global = 0, q2_test_global = 0, q3_test_global = 0, q4_test_global = 0;

/* -----------> Angle PID variables <------------- */
double Angle_Set_point_left_global  = SETPOINT_ANGLE;
double Angle_Set_point_right_global  = SETPOINT_ANGLE;

double Angle_Hysteresis_global = HYSTERESIS_ANGLE;

double Angle_KP_global = KP_ANGLE,
	   Angle_KI_global = KI_ANGLE,
	   Angle_KD_global = KD_ANGLE;

/* -----------> Speed PID variables <------------- */
double Speed_Set_point_left_global  = SETPOINT_SPEED;
double Speed_Set_point_right_global = SETPOINT_SPEED;

double Speed_Hysteresis_global = HYSTERESIS_SPEED;

double Speed_KP_global = KP_SPEED,
	   Speed_KI_global = KI_SPEED,
	   Speed_KD_global = KD_SPEED;

/* -----------> A4988 variables <----------- */
int16_t LeftEngineSpeed_global = 0;
int16_t RightEngineSpeed_global = 0;

int16_t LeftEngineSpeed_control_global = 0;
int16_t RightEngineSpeed_control_global = 0;

/* -----------> Communication variables <----------- */
UART_HandleTypeDef *HC05_handle = &huart1;

struct Data_frame_from_PC	DF_PC;
struct Data_frame_to_PC		DT_PC;

uint8_t Data_to_PC[DATA_FRAME_TO_PC_SIZE];
uint8_t Data_from_PC[DATA_FRAME_FROM_PC_SIZE];

/* -----------> 	LiPol variables 	<----------- */
int16_t LiPol_voltage_global = 0;

/* -----------> Additional variables    <----------- */
uint8_t Emergency_stop_global = 0;
uint8_t Robot_fell_over_global = 0;
uint8_t Which_filter_global = 0;

float dt = 0;

/* USER CODE END Variables */
osThreadId LiPol_TaskHandle;
osThreadId Engines_TaskHandle;
osThreadId IMU_TaskHandle;
osThreadId USART_TaskHandle;
osThreadId Control_TaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

void Start_LiPol_Task(void const * argument);
void Start_Engines_Task(void const * argument);
void Start_IMU_Task(void const * argument);
void Start_USART_Task(void const * argument);
void Start_Control_Task(void const * argument);

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
  /* definition and creation of LiPol_Task */
  osThreadDef(LiPol_Task, Start_LiPol_Task, osPriorityNormal, 0, 512);
  LiPol_TaskHandle = osThreadCreate(osThread(LiPol_Task), NULL);

  /* definition and creation of Engines_Task */
  osThreadDef(Engines_Task, Start_Engines_Task, osPriorityNormal, 0, 512);
  Engines_TaskHandle = osThreadCreate(osThread(Engines_Task), NULL);

  /* definition and creation of IMU_Task */
  osThreadDef(IMU_Task, Start_IMU_Task, osPriorityAboveNormal, 0, 512);
  IMU_TaskHandle = osThreadCreate(osThread(IMU_Task), NULL);

  /* definition and creation of USART_Task */
  osThreadDef(USART_Task, Start_USART_Task, osPriorityNormal, 0, 512);
  USART_TaskHandle = osThreadCreate(osThread(USART_Task), NULL);

  /* definition and creation of Control_Task */
  osThreadDef(Control_Task, Start_Control_Task, osPriorityNormal, 0, 512);
  Control_TaskHandle = osThreadCreate(osThread(Control_Task), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_Start_LiPol_Task */
/**
  * @brief  Function implementing the LiPol_Task thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_Start_LiPol_Task */
void Start_LiPol_Task(void const * argument)
{

  /* USER CODE BEGIN Start_LiPol_Task */

	/* LiPol_Task variables */
	ADC_HandleTypeDef *LiPol_adc_handle = &hadc1;

	uint32_t ADC_reading = 0;

	const float Supply_voltage = 3.3;
	const float ADC_resolution = 4096.0;
	const float Voltage_divider_ratio = 4.73725;

	float LiPol_voltage = 0;

	/* LiPol_Task init */
	HAL_ADC_Start_DMA(LiPol_adc_handle, &ADC_reading, 1);

	osDelay(100);

  /* Infinite loop */
  for(;;)
  {
	  /* Case 1: Measurement and conversion to voltage */
	  HAL_ADC_Start_DMA(LiPol_adc_handle, &ADC_reading, 1);

	  LiPol_voltage = (Supply_voltage * ADC_reading) / (ADC_resolution - 1);
	  LiPol_voltage *= Voltage_divider_ratio;
	  LiPol_voltage *= 100;

	  LiPol_voltage_global = LiPol_voltage;

	  /* Case 2: Voltage lower than 10.5 V */
	  if( LiPol_voltage < 1050 ) {

		  for(int i = 0; i < 10; i++) {

			  HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
			  osDelay(100);
		  }
	  }
	  /* Case 3: Voltage lower than 10.0 V */
	  if( LiPol_voltage < 1000 ) {

		  Emergency_stop_global = 0;
	  }

	  osDelay(20000);
  }
  /* USER CODE END Start_LiPol_Task */
}

/* USER CODE BEGIN Header_Start_Engines_Task */
/**
* @brief Function implementing the Engines_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_Engines_Task */
void Start_Engines_Task(void const * argument)
{
  /* USER CODE BEGIN Start_Engines_Task */

	osDelay(100);

	/* Engines task variables */
	struct A4988 A4988_1;
	struct A4988 A4988_2;

	/* Engines initialization */
	A4988_Init(&A4988_1,
			   &htim2, TIM_CHANNEL_1,
		  	   SD_EN1_GPIO_Port, SD_EN1_Pin,
			   SD_DIR1_GPIO_Port, SD_DIR1_Pin,
			   SD_MS1_GPIO_Port, SD_MS1_Pin,
			   SD_MS2_GPIO_Port, SD_MS2_Pin,
			   SD_MS3_GPIO_Port, SD_MS3_Pin);

	A4988_Init(&A4988_2,
			   &htim3, TIM_CHANNEL_1,
			   SD_EN2_GPIO_Port, SD_EN2_Pin,
			   SD_DIR2_GPIO_Port, SD_DIR2_Pin,
			   SD_MS1_GPIO_Port, SD_MS1_Pin,
			   SD_MS2_GPIO_Port, SD_MS2_Pin,
			   SD_MS3_GPIO_Port, SD_MS3_Pin);

  /* Infinite loop */
  for(;;)
  {
		if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET) {

			if (Emergency_stop_global == 0) {

				Emergency_stop_global = 1;

			} else {

				Emergency_stop_global = 0;
			}

			osDelay(250);
		}

	/* -----------------> A4988 <----------------- */
	/* 	Update engines speed and direction         */
	if (Emergency_stop_global == 1) {

		A4988_Power_on(&A4988_1);
		A4988_Power_on(&A4988_2);

		if( LeftEngineSpeed_control_global == RightEngineSpeed_control_global ) {

			A4988_Set_Speed(&A4988_1, LeftEngineSpeed_global);
			A4988_Set_Speed(&A4988_2, -RightEngineSpeed_global);
		}
		else if( LeftEngineSpeed_control_global > RightEngineSpeed_control_global ) {

			RightEngineSpeed_global *= 0.5;

			A4988_Set_Speed(&A4988_1, LeftEngineSpeed_global );
		    A4988_Set_Speed(&A4988_2, -RightEngineSpeed_global );
		}
		else if( LeftEngineSpeed_control_global < RightEngineSpeed_control_global ) {

			LeftEngineSpeed_global *= 0.5;

			A4988_Set_Speed(&A4988_1, LeftEngineSpeed_global );
			A4988_Set_Speed(&A4988_2, -RightEngineSpeed_global );
		}
	}
	else {

		A4988_Power_off(&A4988_1);
		A4988_Power_off(&A4988_2);
	}

	osDelay(5);
  }
  /* USER CODE END Start_Engines_Task */
}

/* USER CODE BEGIN Header_Start_IMU_Task */
/**
* @brief Function implementing the IMU_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_IMU_Task */
void Start_IMU_Task(void const * argument)
{
  /* USER CODE BEGIN Start_IMU_Task */

	/* IMU task variables */
	uint8_t mpu9250_correct_init_global = 0;

	struct MPU9250 mpu1;

	uint32_t I_Time_Stop = 0;
	uint32_t I_Time_Start = 0;

	/* IMU task initialization */

	HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	osDelay(100);

	if (MPU9250_Init(&hi2c1, &mpu1, MPU9250_Device_1, MPU9250_Acce_2G, MPU9250_Gyro_2000s) == MPU9250_Init_OK) {

		MPU9250_Set_Offsets(&hi2c1, &mpu1, 0, 0, 0, 0, 0, 0, 24, 146, -92.5);

		MPU9250_Calibration_Acce(&hi2c1, &mpu1);
		MPU9250_Calibration_Gyro(&hi2c1, &mpu1);
		//MPU9250_Calibration_Mag(&hi2c1, &mpu1);

		// set Q and R
		//Kalman_filter_init(0, 10000);

		for (int i = 0; i < 3; ++i) {

			HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
			osDelay(200);
			HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
			osDelay(200);
		}

		mpu9250_correct_init_global = 1;
	}
	else {

		mpu9250_correct_init_global = 0;
	}

	osDelay(100);
	HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);

  /* Infinite loop */
  for(;;)
  {
	  if( mpu9250_correct_init_global == 1 ) {

		  /* Case 1: Time measurement */
		  I_Time_Start = I_Time_Stop;
		  I_Time_Stop = HAL_GetTick();

		  dt = (float)( I_Time_Stop - I_Time_Start ) / 1000;

		  /* Case 2: RPY calculation */
		  MPU9250_Calculate_RPY(&hi2c1, &mpu1, dt);

		  a_x_g = mpu1.Accelerometer_X_g, a_y_g = mpu1.Accelerometer_Y_g, a_z_g = mpu1.Accelerometer_Z_g;
		  g_x_dgs = mpu1.Gyroscope_X_dgs, g_y_dgs = mpu1.Gyroscope_Y_dgs, g_z_dgs = mpu1.Gyroscope_Z_dgs;
		  m_x_uT = mpu1.Magnetometer_X_uT, m_y_uT = mpu1.Magnetometer_Y_uT, m_z_uT = mpu1.Magnetometer_Z_uT;

		  a_roll_global = mpu1.Accelerometer_Roll, a_pitch_global = mpu1.Accelerometer_Pitch;
		  g_roll_global = mpu1.Gyroscope_Roll, g_pitch_global = mpu1.Gyroscope_Pitch, g_yaw_global = mpu1.Gyroscope_Yaw;
		  m_yaw_global  = mpu1.Magnetometer_Yaw;

		  /* Case 3: Filters using */
		  //AlphaBeta_filter(&mpu1, 0.2, 0.05, 0, 0, 0, 0, dt);

		  /* Complementary filter */
		  Complementary_filter(&mpu1, Filter_weight_global, dt);

		  Complementary_Roll_global  = mpu1.Complementary_filter_Roll;
		  Complementary_Pitch_global = mpu1.Complementary_filter_Pitch;
		  Complementary_Yaw_global   = mpu1.Complementary_filter_Yaw;

		  /* Kalman filter */
		  Kalman_filter(&mpu1, 0.00001, Kalman_filter_process_variance, dt);

		  Kalman_Roll_global  = mpu1.Kalman_filter_Roll;
		  Kalman_Pitch_global = mpu1.Kalman_filter_Pitch;
		  Kalman_Yaw_global   = mpu1.Kalman_filter_Yaw;

		  /* Madgwick filter */
		  Madgwick_filter(&mpu1, dt);

		  Madgwick_Roll_global  = mpu1.Madgwick_filter_Roll;
		  Madgwick_Pitch_global = mpu1.Madgwick_filter_Pitch;
		  Madgwick_Yaw_global   = mpu1.Madgwick_filter_Yaw;
	  }

	  osDelay(5);
  }
  /* USER CODE END Start_IMU_Task */
}

/* USER CODE BEGIN Header_Start_USART_Task */
/**
* @brief Function implementing the USART_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_USART_Task */
void Start_USART_Task(void const * argument)
{
  /* USER CODE BEGIN Start_USART_Task */

	/* Start receiving */
	HAL_UART_Receive_DMA(HC05_handle, Data_from_PC, DATA_FRAME_FROM_PC_SIZE);

  /* Infinite loop */
  for(;;)
  {
	  HC05_Fill_Data_frame_to_PC(&DT_PC, Data_to_PC,
			  	  	  	   	     LiPol_voltage_global,
								 Complementary_Roll_global, Complementary_Pitch_global, Complementary_Yaw_global,
								 Kalman_Roll_global, Kalman_Pitch_global, Kalman_Yaw_global,
								 Madgwick_Roll_global, Madgwick_Pitch_global, Madgwick_Yaw_global,
								 LeftEngineSpeed_global, RightEngineSpeed_global);

	  HAL_UART_Transmit_DMA(HC05_handle, Data_to_PC, DATA_FRAME_TO_PC_SIZE);

	  osDelay(10);
  }
  /* USER CODE END Start_USART_Task */
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

	/* Control task variables */
	struct Angle_PID a_pid_left, a_pid_right;
	struct Speed_PID s_pid_left, s_pid_right;

	uint32_t I_Time_Stop = 0;
	uint32_t I_Time_Start = 0;

	/* PID regulators initialization */
	Angle_PID_Init(&a_pid_left);
	Angle_PID_Init(&a_pid_left);

	Speed_PID_Init(&s_pid_right);
	Speed_PID_Init(&s_pid_right);

	float Actual_angle = 0;

  /* Infinite loop */
  for(;;)
  {
		I_Time_Start = I_Time_Stop;
		I_Time_Stop = HAL_GetTick();

		Speed_Set_point_left_global = LeftEngineSpeed_control_global;
		Speed_Set_point_right_global = RightEngineSpeed_control_global;

		switch( Which_filter_global ) {

			case 0:
				Actual_angle = Complementary_Pitch_global;
				break;

			case 1:
				Actual_angle = Kalman_Pitch_global;
				break;

			case 2:
				Actual_angle = Madgwick_Pitch_global;
				break;
		}

		/* ---------------------------------> Speed PID <--------------------------------- */
		/* 					Update PID parameters and get PID output  	 				   */

		if (Speed_Set_point_left_global != LeftEngineSpeed_global
				|| Speed_Set_point_right_global != RightEngineSpeed_global) {

			if (Speed_Set_point_left_global == Speed_Set_point_right_global) {

				/* Left engine */
				Speed_PID_Set_parameters(&s_pid_left,
						Speed_Set_point_left_global, Speed_KP_global,
						Speed_KI_global, Speed_KD_global);
				Speed_PID_Calculate(&s_pid_left, a_pid_left.control,
						I_Time_Start, I_Time_Stop);

				/* Right engine */
				Speed_PID_Set_parameters(&s_pid_right,
						Speed_Set_point_right_global, Speed_KP_global,
						Speed_KI_global, Speed_KD_global);
				Speed_PID_Calculate(&s_pid_right, a_pid_right.control,
						I_Time_Start, I_Time_Stop);

				Angle_Set_point_left_global = -s_pid_left.control / 1000;
				Angle_Set_point_right_global = -s_pid_right.control / 1000;
			} else if (Speed_Set_point_left_global
					!= Speed_Set_point_right_global) {

				Speed_Set_point_left_global = -50;
				Speed_Set_point_right_global = -50;

				/* Left engine */
				Speed_PID_Set_parameters(&s_pid_left,
						Speed_Set_point_left_global, Speed_KP_global,
						Speed_KI_global, Speed_KD_global);
				Speed_PID_Calculate(&s_pid_left, a_pid_left.control,
						I_Time_Start, I_Time_Stop);

				/* Right engine */
				Speed_PID_Set_parameters(&s_pid_right,
						Speed_Set_point_right_global, Speed_KP_global,
						Speed_KI_global, Speed_KD_global);
				Speed_PID_Calculate(&s_pid_right, a_pid_right.control,
						I_Time_Start, I_Time_Stop);

				Angle_Set_point_left_global = -s_pid_left.control / 1000;
				Angle_Set_point_right_global = -s_pid_right.control / 1000;
			}
		}

		/* ---------------------------------> Angle PID <--------------------------------- */
		/* 					Update PID parameters and get PID output  	 				   */

		if (Angle_Set_point_left_global != Actual_angle
				|| Angle_Set_point_right_global != Complementary_Pitch_global) {

			/* Left engine */
			Angle_PID_Set_parameters(&a_pid_left, Angle_Set_point_left_global,
					Angle_KP_global, Angle_KI_global, Angle_KD_global);
			Angle_PID_Calculate(&a_pid_left, Actual_angle,
					I_Time_Start, I_Time_Stop);

			/* Right engine */
			Angle_PID_Set_parameters(&a_pid_right, Angle_Set_point_right_global,
					Angle_KP_global, Angle_KI_global, Angle_KD_global);
			Angle_PID_Calculate(&a_pid_right, Actual_angle,
					I_Time_Start, I_Time_Stop);

			if (fabs(Actual_angle) < 40 && Robot_fell_over_global != 1) {

				LeftEngineSpeed_global = a_pid_left.control;
				RightEngineSpeed_global = a_pid_right.control;

			} else {

				Robot_fell_over_global = 1;

				LeftEngineSpeed_global = 0;
				RightEngineSpeed_global = 0;

				a_pid_left.integral = 0;
				a_pid_right.integral = 0;

				s_pid_left.integral = 0;
				s_pid_right.integral = 0;

				if( fabs(Actual_angle) < 5 ) {

					Robot_fell_over_global = 0;
				}
			}
		}

		if( Emergency_stop_global == 0 ) {

			a_pid_left.integral = 0;
			a_pid_right.integral = 0;

			s_pid_left.integral = 0;
			s_pid_right.integral = 0;
		}

		osDelay(5);
  }
  /* USER CODE END Start_Control_Task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {

	if (huart->Instance == USART1) {

		HAL_UART_Receive_DMA(HC05_handle, Data_from_PC, DATA_FRAME_FROM_PC_SIZE);

		if( HC05_Parse_Data_frame(&DF_PC, Data_from_PC) == 0 ) {

			HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);

			/* Angle PID data from PC */
			Angle_KP_global = (double) DF_PC.Angle_KP / 100;
			Angle_KI_global = (double) DF_PC.Angle_KI / 100;
			Angle_KD_global = (double) DF_PC.Angle_KD / 100;

			/* Speed PID data from PC */
			Speed_KP_global = (double) DF_PC.Speed_KP / 100;
			Speed_KI_global = (double) DF_PC.Speed_KI / 100;
			Speed_KD_global = (double) DF_PC.Speed_KD / 100;

			/* Filters data from PC */
			Filter_weight_global = (double) DF_PC.Complementary_filter_weight / 1000;
			Kalman_filter_process_variance = DF_PC.Kalman_filter_process_variance;

			/* Engines speed data from PC */
			LeftEngineSpeed_control_global  = DF_PC.Left_engine_speed;
			RightEngineSpeed_control_global = DF_PC.Right_engine_speed;

			/* Additional data from PC */
			Emergency_stop_global = DF_PC.Emergency_stop;
			Which_filter_global = DF_PC.Which_filter;
		}
	}
}
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
