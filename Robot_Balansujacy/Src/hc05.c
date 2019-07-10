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

void HC05_Fill_Data_frame(struct Data_frame_to_PC *_data, uint8_t *_frame,
		  	  	  	  	  int16_t _LiPol_voltage,
						  int16_t a_x, int16_t a_y, int16_t a_z) {

	_data->Lipol_voltage = _LiPol_voltage;
	_data->a_x = a_x; _data->a_y = a_y; _data->a_z = a_z;

	_frame[0] = 'S';
	/* Lipol data */
	_frame[1] = HC05_Divide_int16(_data->Lipol_voltage, 'L');
	_frame[2] = HC05_Divide_int16(_data->Lipol_voltage, 'H');
	/* Accelerometer data */
	_frame[3] = HC05_Divide_int16(_data->a_x, 'L');
	_frame[4] = HC05_Divide_int16(_data->a_x, 'H');
	_frame[5] = HC05_Divide_int16(_data->a_y, 'L');
	_frame[6] = HC05_Divide_int16(_data->a_y, 'H');
	_frame[7] = HC05_Divide_int16(_data->a_z, 'L');
	_frame[8] = HC05_Divide_int16(_data->a_z, 'H');
	/* CRC */
	_frame[9] = CRC8_DataArray(_frame, DATA_FRAME_TO_PC_SIZE - 1);
}

void HC05_Parse_Data_frame(struct Data_frame_from_PC *_data, uint8_t *_frame) {

	/* PID data */
	_data->Set_point  = HC05_Merge_bytes(_frame[1], _frame[2]);
	_data->Hysteresis = HC05_Merge_bytes(_frame[3], _frame[4]);

	_data->Kp = HC05_Merge_bytes(_frame[5], _frame[6]);
	_data->Ki = HC05_Merge_bytes(_frame[7], _frame[8]);
	_data->Kd = HC05_Merge_bytes(_frame[9], _frame[10]);

	/* Filters data */
	_data->Complementary_filter_weight = _frame[11];

	/* Additional data */
	_data->Emergency_stop = _frame[12];
}
