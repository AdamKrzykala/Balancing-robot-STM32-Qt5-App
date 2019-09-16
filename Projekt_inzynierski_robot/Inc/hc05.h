/*
 * hc05.h
 *
 *  Created on: 23.03.2019
 *  Author: Michal
 */

#ifndef HC05_H_
#define HC05_H_

#include "usart.h"
#include "crc.h"

#define DATA_FRAME_FROM_PC_SIZE 	26
#define DATA_FRAME_TO_PC_SIZE 		25

/* --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
struct Data_frame_to_PC {

	/* LiPol data */
	int16_t Lipol_voltage;

	/* Complementary filter data */
	int16_t Complementary_Roll, Complementary_Pitch, Complementary_Yaw;

	/* Kalman filter data */
	int16_t Kalman_Roll, Kalman_Pitch, Kalman_Yaw;

	/* Madgwick filter data */
	int16_t Madgwick_Roll, Madgwick_Pitch, Madgwick_Yaw;

	/* Engines data */
	int16_t Left_engine_speed, Right_engine_speed;
};

/* --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
struct Data_frame_from_PC {

	/* PID data */
	int16_t Angle_KP, Angle_KI, Angle_KD;
	int16_t Speed_KP, Speed_KI, Speed_KD;

	/* Filters data */
	int16_t Complementary_filter_weight;
	int16_t Kalman_filter_process_variance;
	int16_t Madgwick_filter_beta;

	/* Engines data */
	int16_t Left_engine_speed, Right_engine_speed;

	/* Additional data */
	int8_t Emergency_stop;
	int8_t Which_filter;
};

/* --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
uint8_t HC05_Divide_int16(int16_t _data, uint8_t _which_byte);

/* --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
int16_t HC05_Merge_bytes(uint8_t _lower_byte, uint8_t _higher_byte);

/* --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
void HC05_Fill_Data_frame_to_PC(struct Data_frame_to_PC *_data, uint8_t *_frame,
								int16_t LiPol_voltage,
				   			    float Complementary_Roll, float Complementary_Pitch, float Complementary_Yaw,
								float Kalman_Roll, float Kalman_Pitch, float Kalman_Yaw,
								float Madgwick_Roll, float Madgwick_Pitch, float Madgwick_Yaw,
								int16_t Left_engine_speed, int16_t Right_engine_speed);

/* --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
int HC05_Parse_Data_frame(struct Data_frame_from_PC *_data, uint8_t *_frame);

/* --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

#endif /* HC05_H_ */
