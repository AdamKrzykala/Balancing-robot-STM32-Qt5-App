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

#define ACCELEROMETER_DATA_FRAME_SIZE		11
#define GYROSCOPE_DATA_FRAME_SIZE			14

#define DATA_FRAME_FROM_PC_SIZE 	13


struct Data_frame_to_PC {

	/* Lipol data */
	int16_t Lipol_voltage;

	/* Accelerometer data */
	int8_t a_x_g, a_y_g, a_z_g;
	int16_t a_roll, a_pitch, a_yaw;

	/* Gyroscope data */
	int16_t g_x_dgs, g_y_dgs, g_z_dgs;
	int16_t g_roll, g_pitch, g_yaw;
};

struct Data_frame_from_PC {

	/* PID data */
	int16_t Set_point;
	int16_t Hysteresis;

	int16_t Kp, Ki, Kd;

	/* Filters data */
	int8_t Complementary_filter_weight;

	/* Additional data */
	int8_t Emergency_stop;
};

uint8_t HC05_Divide_int16(int16_t _data, uint8_t _which_byte);
int16_t HC05_Merge_bytes(uint8_t _lower_byte, uint8_t _higher_byte);

void HC05_Fill_Accelerometer_Data_frame(struct Data_frame_to_PC *_data, uint8_t *_frame,
						  	  	        double a_x_g, double a_y_g, double a_z_g,
										double a_roll, double a_pitch, double a_yaw);

void HC05_Fill_Gyroscope_Data_frame(struct Data_frame_to_PC *_data, uint8_t *_frame,
						  	  	    double g_x_dgs, double g_y_dgs, double a_z_dgs,
									double g_roll, double g_pitch, double g_yaw);

void HC05_Parse_Data_frame(struct Data_frame_from_PC *_data, uint8_t *_frame);

#endif /* HC05_H_ */
