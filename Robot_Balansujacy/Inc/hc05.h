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

#define DATA_FRAME_TO_PC_SIZE		1
#define DATA_FRAME_FROM_PC_SIZE 	7


struct Data_frame_to_PC {

};

struct Data_frame_from_PC {

	int16_t Kp, Ki, Kd;
};

uint8_t HC05_Divide_int16(int16_t _data, uint8_t _which_byte);
int16_t HC05_Merge_bytes(uint8_t _lower_byte, uint8_t _higher_byte);

void HC05_Fill_Data_frame(struct Data_frame_to_PC *_frame,
						  int16_t _a_x, int16_t _a_y, int16_t _a_z,
						  int16_t _g_x, int16_t _g_y, int16_t _g_z,
						  int16_t _roll,
						  int16_t _LiPol_voltage,
						  int16_t _Kp, int16_t _Ti, int16_t _Td,
						  int16_t _Left_engine_speed, int16_t _Right_engine_speed);

void HC05_Send_Data_frame(struct Data_frame_to_PC *_frame, UART_HandleTypeDef *_huart);

void HC05_Receive_Data_frame(struct Data_frame_from_PC *_frame, UART_HandleTypeDef *_huart);

void HC05_Parse_Data_frame(struct Data_frame_from_PC *_data, uint8_t *_frame);

#endif /* HC05_H_ */
