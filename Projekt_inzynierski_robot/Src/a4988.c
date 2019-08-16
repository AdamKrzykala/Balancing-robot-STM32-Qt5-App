/*
 * a4988.c
 *
 *  Created on: 23.04.2019
 *      Author: Michal Nowak
 */

#include "a4988.h"

/* ************************************************************************************************************** */
void A4988_Init(struct A4988 *a4988,
						TIM_HandleTypeDef *htim, uint32_t tim_channel,
						GPIO_TypeDef *EN_Port,	 uint16_t EN_Pin,
						GPIO_TypeDef *DIR_Port,  uint16_t DIR_Pin,
						GPIO_TypeDef *MS1_port,  uint16_t MS1_Pin,
						GPIO_TypeDef *MS2_port,  uint16_t MS2_Pin,
						GPIO_TypeDef *MS3_port,  uint16_t MS3_Pin) {

	/* Case 1: GPIO configuration */
	a4988->EN_Port = EN_Port;
	a4988->EN_Pin  = EN_Pin;

	a4988->DIR_Port = DIR_Port;
	a4988->DIR_Pin  = DIR_Pin;

	a4988->MS1_Port = MS1_port;
	a4988->MS1_Pin  = MS1_Pin;

	a4988->MS2_Port = MS2_port;
	a4988->MS2_Pin  = MS2_Pin;

	a4988->MS3_Port = MS3_port;
	a4988->MS3_Pin  = MS3_Pin;

	/* Case 2: PWM configuration */
	a4988->htim = htim;
	a4988->tim_channel = tim_channel;

	HAL_TIM_PWM_Start(htim, tim_channel);

	htim->Instance->ARR  = 999;	/* <- ARR + 1 = 1000 duty levels (0%, 0.001%, ... ,100%) */
	htim->Instance->CCR1 = 500;	/* <- Set 50% duty */
	htim->Instance->PSC  = 0;	/* <- Set PSC value 0 */

	/* Case 3: Variables default value */
	a4988->Resolution = 0;
	a4988->Step_angle = 0;
	a4988->Steps_per_round = 0;
	a4988->Speed_RPM = 0;
	a4988->Step_delay = 0;

	A4988_Set_Resolution(a4988, A4988_One_8_step);
}

/* ************************************************************************************************************** */
void A4988_Power_on(struct A4988 *a4988) {

	HAL_GPIO_WritePin(a4988->EN_Port, a4988->EN_Pin, GPIO_PIN_RESET);
}

/* ************************************************************************************************************** */
void A4988_Power_off(struct A4988 *a4988) {

	HAL_GPIO_WritePin(a4988->EN_Port, a4988->EN_Pin, GPIO_PIN_SET);
}

/* ************************************************************************************************************** */
void A4988_Set_Resolution(struct A4988 *a4988, A4988_Resolution resolution) {

	if(resolution == A4988_Full_step) {

		a4988->Resolution = A4988_Full_step;

		HAL_GPIO_WritePin(a4988->MS1_Port, a4988->MS1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(a4988->MS2_Port, a4988->MS2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(a4988->MS3_Port, a4988->MS3_Pin, GPIO_PIN_RESET);
	}

	if(resolution == A4988_One_2_step) {

		a4988->Resolution = A4988_One_2_step;

		HAL_GPIO_WritePin(a4988->MS1_Port, a4988->MS1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(a4988->MS2_Port, a4988->MS2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(a4988->MS3_Port, a4988->MS3_Pin, GPIO_PIN_RESET);
	}

	if(resolution == A4988_One_4_step) {

		a4988->Resolution = A4988_One_4_step;

		HAL_GPIO_WritePin(a4988->MS1_Port, a4988->MS1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(a4988->MS2_Port, a4988->MS2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(a4988->MS3_Port, a4988->MS3_Pin, GPIO_PIN_RESET);
	}

	if(resolution == A4988_One_8_step) {

		a4988->Resolution = A4988_One_8_step;

		HAL_GPIO_WritePin(a4988->MS1_Port, a4988->MS1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(a4988->MS2_Port, a4988->MS2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(a4988->MS3_Port, a4988->MS3_Pin, GPIO_PIN_RESET);
	}

	if(resolution == A4988_One_16_step) {

		a4988->Resolution = A4988_One_16_step;

		HAL_GPIO_WritePin(a4988->MS1_Port, a4988->MS1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(a4988->MS2_Port, a4988->MS2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(a4988->MS3_Port, a4988->MS3_Pin, GPIO_PIN_SET);
	}
}

/* ************************************************************************************************************** */
void A4988_Set_Direction(struct A4988 *a4988, A4988_Direction direction) {

	if(direction == A4988_Left) {

		HAL_GPIO_WritePin(a4988->DIR_Port, a4988->DIR_Pin, GPIO_PIN_SET);
	}

	else if(direction == A4988_Right) {

		HAL_GPIO_WritePin(a4988->DIR_Port, a4988->DIR_Pin, GPIO_PIN_RESET);
	}
}

/* ************************************************************************************************************** */
uint32_t PSC_global_test = 0;
double Step_angle_global_test = 0;
long int Step_delay_global_test = 0;

void A4988_Set_Speed(struct A4988 *a4988, int speed_rpm) {

	const long int minute = 60000000;

	if( speed_rpm <= 0 ) {

		A4988_Set_Direction(a4988, A4988_Right);
	}
	else {

		A4988_Set_Direction(a4988, A4988_Left);
	}

	a4988->Step_angle = 0.9 / a4988->Resolution;
	a4988->Steps_per_round = (360 / a4988->Step_angle);
	a4988->Speed_RPM = fabs(speed_rpm) * a4988->Steps_per_round;
	a4988->Step_delay = (minute / a4988->Speed_RPM );

	if( speed_rpm != 0 ) {

		a4988->htim->Instance->CCR1 = 500;
		a4988->htim->Instance->PSC = ( ( 32 * a4988->Step_delay * 2 ) / ( a4988->htim->Instance->ARR + 1 ) ) - 1;
	}
	else {

		a4988->htim->Instance->CCR1 = 0;
	}
}

/* ************************************************************************************************************** */
