 /*
 * hc05.c
 *
 *  Created on: 23.03.2019
 *      Author: Micha³
 */

#include "hc05.h"

/* --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

uint8_t HC05_Divide_int16(int16_t _data, uint8_t _which_byte) {

	if(_which_byte == 'L') {

		return (_data & 0xFF); // return lower byte
	}
	else if(_which_byte == 'H'){

		return (_data >> 8);   // return higher byte
	}

	return 0;
}

/* --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

int16_t HC05_Merge_bytes(uint8_t _lower_byte, uint8_t _higher_byte) {

	int16_t uint16t_byte = ( (_higher_byte << 8) + _lower_byte );

	if(uint16t_byte >= 32767) {

		int16_t int_byte = uint16t_byte - ( 2 * 32768);
		return int_byte;
	}
	else  return uint16t_byte;

	return 0;
}

/* --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

void HC05_Fill_Accelerometer_Data_frame(struct Data_frame_to_PC *_data, uint8_t *_frame,
		  	  	  	  	  	  	  	    double a_x_g, double a_y_g, double a_z_g,
										double a_roll, double a_pitch, double a_yaw) {

	_data->a_x_g = a_x_g * 100;
	_data->a_y_g = a_y_g * 100;
	_data->a_z_g = a_z_g * 100;

	_data->a_roll  = a_roll  * 100;
	_data->a_pitch = a_pitch * 100;
	_data->a_yaw   = a_yaw   * 100;

	/* ACCELEROMETER DATA FRAME */
	_frame[0] = 'A';

	_frame[1] = _data->a_x_g;
	_frame[2] = _data->a_y_g;
	_frame[3] = _data->a_z_g;

	_frame[4] = HC05_Divide_int16(_data->a_roll, 'L');
	_frame[5] = HC05_Divide_int16(_data->a_roll, 'H');
	_frame[6] = HC05_Divide_int16(_data->a_pitch, 'L');
	_frame[7] = HC05_Divide_int16(_data->a_pitch, 'H');
	_frame[8] = HC05_Divide_int16(_data->a_yaw, 'L');
	_frame[9] = HC05_Divide_int16(_data->a_yaw, 'H');

	/* CRC */
	_frame[10] = CRC8_DataArray(_frame, ACCELEROMETER_DATA_FRAME_SIZE - 1);
}

/* --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

void HC05_Fill_Gyroscope_Data_frame(struct Data_frame_to_PC *_data, uint8_t *_frame,
						  	  	    double g_x_dgs, double g_y_dgs, double g_z_dgs,
									double g_roll, double g_pitch, double g_yaw) {

	_data->g_x_dgs = g_x_dgs * 100;
	_data->g_y_dgs = g_y_dgs * 100;
	_data->g_z_dgs = g_z_dgs * 100;

	_data->g_roll  = g_roll  * 100;
	_data->g_pitch = g_pitch * 100;
	_data->g_yaw   = g_yaw   * 100;

	/* GYROSCOPE DATA FRAME */
	_frame[0]  = 'G';
	_frame[1]  = HC05_Divide_int16(_data->g_x_dgs, 'L');
	_frame[2]  = HC05_Divide_int16(_data->g_x_dgs, 'H');
	_frame[3]  = HC05_Divide_int16(_data->g_y_dgs, 'L');
	_frame[4]  = HC05_Divide_int16(_data->g_y_dgs, 'H');
	_frame[5]  = HC05_Divide_int16(_data->g_z_dgs, 'L');
	_frame[6]  = HC05_Divide_int16(_data->g_z_dgs, 'H');

	_frame[7]  = HC05_Divide_int16(_data->g_roll, 'L');
	_frame[8]  = HC05_Divide_int16(_data->g_roll, 'H');
	_frame[9]  = HC05_Divide_int16(_data->g_pitch, 'L');
	_frame[10]  = HC05_Divide_int16(_data->g_pitch, 'H');
	_frame[11] = HC05_Divide_int16(_data->g_yaw, 'L');
	_frame[12] = HC05_Divide_int16(_data->g_yaw, 'H');

	/* CRC */
	_frame[13] = CRC8_DataArray(_frame, GYROSCOPE_DATA_FRAME_SIZE - 1);
}

/* --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

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

/* --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
