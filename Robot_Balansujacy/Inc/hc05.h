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

#define DATA_FRAME_TO_PC_SIZE		10
#define DATA_FRAME_FROM_PC_SIZE 	13


struct Data_frame_to_PC {

	/* Lipol data */
	int16_t Lipol_voltage;

	/* Accelerometer data */
	int16_t a_x, a_y, a_z;
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

void HC05_Fill_Data_frame(struct Data_frame_to_PC *_data, uint8_t *_frame,
						  int16_t _LiPol_voltage,
						  int16_t a_x, int16_t a_y, int16_t a_z);

void HC05_Parse_Data_frame(struct Data_frame_from_PC *_data, uint8_t *_frame);

#endif /* HC05_H_ */
