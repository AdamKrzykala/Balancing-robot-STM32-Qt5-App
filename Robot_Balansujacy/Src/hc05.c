 /*
 * hc05.c
 *
 *  Created on: 23.03.2019
 *      Author: Micha³
 */

#include "hc05.h"

uint8_t HC05_Divide_int16(int16_t _data, uint8_t _which_byte) {

	if(_which_byte == 'L') {
		return (_data & 0xFF); // return lower byte
	}
	else if(_which_byte == 'H'){
		return (_data >> 8);   // return higher byte
	}

	return 0;
}

int16_t HC05_Merge_bytes(uint8_t _lower_byte, uint8_t _higher_byte) {

	int16_t uint16t_byte = ( (_higher_byte << 8) + _lower_byte );

	if(uint16t_byte >= 32767) {

		int16_t int_byte = uint16t_byte - ( 2 * 32768);
		return int_byte;
	}
	else  return uint16t_byte;

	return 0;
}

void HC05_Fill_Data_frame(struct Data_frame_to_PC *_frame,
						  int16_t _a_x, int16_t _a_y, int16_t _a_z,
						  int16_t _g_x, int16_t _g_y, int16_t _g_z,
						  int16_t _roll,
						  int16_t _LiPol_voltage,
						  int16_t _Kp, int16_t _Ti, int16_t _Td,
						  int16_t _Left_engine_speed, int16_t _Right_engine_speed) {

}

void HC05_Send_Data_frame(struct Data_frame_to_PC *_frame, UART_HandleTypeDef *_huart) {


}

uint8_t Test_byte1 = 0;
uint8_t Test_byte2 = 0;
uint8_t Test_byte3 = 0;
uint8_t Test_byte4 = 0;
uint8_t Test_byte5 = 0;
uint8_t Test_byte6 = 0;

void HC05_Parse_Data_frame(struct Data_frame_from_PC *_data, uint8_t *_frame) {

	Test_byte1 = _frame[1];
	Test_byte2 = _frame[2];
	Test_byte3 = _frame[3];
	Test_byte4  = _frame[4];
	Test_byte5 = _frame[5];
	Test_byte6 = _frame[6];

	_data->Kp = HC05_Merge_bytes(_frame[1], _frame[2]);
	_data->Ki = HC05_Merge_bytes(_frame[3], _frame[4]);
	_data->Kd = HC05_Merge_bytes(_frame[5], _frame[6]);
}
