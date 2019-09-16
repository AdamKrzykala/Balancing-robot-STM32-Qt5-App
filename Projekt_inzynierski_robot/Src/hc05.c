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

void HC05_Fill_Data_frame_to_PC(struct Data_frame_to_PC *_data, uint8_t *_frame,
								int16_t LiPol_voltage,
								float Complementary_Roll, float Complementary_Pitch, float Complementary_Yaw,
								float Kalman_Roll, float Kalman_Pitch, float Kalman_Yaw,
								float Madgwick_Roll, float Madgwick_Pitch, float Madgwick_Yaw,
								int16_t Left_engine_speed, int16_t Right_engine_speed) {

	_data->Lipol_voltage = LiPol_voltage;

	_data->Complementary_Roll  = Complementary_Roll  * 100;
	_data->Complementary_Pitch = Complementary_Pitch * 100;
	_data->Complementary_Yaw   = Complementary_Yaw   * 100;

	_data->Kalman_Roll  = Kalman_Roll  * 100;
	_data->Kalman_Pitch = Kalman_Pitch * 100;
	_data->Kalman_Yaw   = Kalman_Yaw   * 100;

	_data->Madgwick_Roll  = Madgwick_Roll  * 100;
	_data->Madgwick_Pitch = Madgwick_Pitch * 100;
	_data->Madgwick_Yaw   = Madgwick_Yaw   * 100;

	_data->Left_engine_speed  = Left_engine_speed;
	_data->Right_engine_speed = Right_engine_speed;

	/* LiPol data */
	_frame[0] = HC05_Divide_int16(_data->Lipol_voltage, 'L');
	_frame[1] = HC05_Divide_int16(_data->Lipol_voltage, 'H');

	/* Complementary filter data */
	_frame[2] = HC05_Divide_int16(_data->Complementary_Roll, 'L');
	_frame[3] = HC05_Divide_int16(_data->Complementary_Roll, 'H');

	_frame[4] = HC05_Divide_int16(_data->Complementary_Pitch, 'L');
	_frame[5] = HC05_Divide_int16(_data->Complementary_Pitch, 'H');

	_frame[6] = HC05_Divide_int16(_data->Complementary_Yaw, 'L');
	_frame[7] = HC05_Divide_int16(_data->Complementary_Yaw, 'H');

	/* Kalman filter data */
	_frame[8] = HC05_Divide_int16(_data->Kalman_Roll, 'L');
	_frame[9] = HC05_Divide_int16(_data->Kalman_Roll, 'H');

	_frame[10] = HC05_Divide_int16(_data->Kalman_Pitch, 'L');
	_frame[11] = HC05_Divide_int16(_data->Kalman_Pitch, 'H');

	_frame[12] = HC05_Divide_int16(_data->Kalman_Yaw, 'L');
	_frame[13] = HC05_Divide_int16(_data->Kalman_Yaw, 'H');

	/* Madgwick filter data */
	_frame[14] = HC05_Divide_int16(_data->Madgwick_Roll, 'L');
	_frame[15] = HC05_Divide_int16(_data->Madgwick_Roll, 'H');

	_frame[16] = HC05_Divide_int16(_data->Madgwick_Pitch, 'L');
	_frame[17] = HC05_Divide_int16(_data->Madgwick_Pitch, 'H');

	_frame[18] = HC05_Divide_int16(_data->Madgwick_Yaw, 'L');
	_frame[19] = HC05_Divide_int16(_data->Madgwick_Yaw, 'H');

	/* Engines data */
	_frame[20] = HC05_Divide_int16(_data->Left_engine_speed, 'L');
	_frame[21] = HC05_Divide_int16(_data->Left_engine_speed, 'H');

	_frame[22] = HC05_Divide_int16(_data->Right_engine_speed, 'L');
	_frame[23] = HC05_Divide_int16(_data->Right_engine_speed, 'H');

	/* CRC */
	_frame[24] = CRC8_DataArray(_frame, DATA_FRAME_TO_PC_SIZE - 1);
}

/* --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

int HC05_Parse_Data_frame(struct Data_frame_from_PC *_data, uint8_t *_frame) {

	uint8_t Actual_CRC = 0;
	uint8_t Received_CRC = 0;

	/* Angle PID data */
	_data->Angle_KP = HC05_Merge_bytes(_frame[1], _frame[2]);
	_data->Angle_KI = HC05_Merge_bytes(_frame[3], _frame[4]);
	_data->Angle_KD = HC05_Merge_bytes(_frame[5], _frame[6]);

	/* Speed PID data */
	_data->Speed_KP = HC05_Merge_bytes(_frame[7], _frame[8]);
	_data->Speed_KI = HC05_Merge_bytes(_frame[9], _frame[10]);
	_data->Speed_KD = HC05_Merge_bytes(_frame[11], _frame[12]);

	/* Filters data */
	_data->Complementary_filter_weight = _frame[13];
	_data->Kalman_filter_process_variance = HC05_Merge_bytes(_frame[14], _frame[15]);

	/* Engines data */
	_data->Left_engine_speed  = HC05_Merge_bytes(_frame[16], _frame[17]);
	_data->Right_engine_speed = HC05_Merge_bytes(_frame[18], _frame[19]);

	/* Additional data */
	_data->Emergency_stop = _frame[20];
	_data->Which_filter = _frame[21];

	/* CRC test */
	Received_CRC = _frame[22];
	Actual_CRC = CRC8_DataArray(_frame, DATA_FRAME_FROM_PC_SIZE - 1);

	if( Actual_CRC != Received_CRC ) {

		return -1;
	}

	return 0;
}

/* --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
