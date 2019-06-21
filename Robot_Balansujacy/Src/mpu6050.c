/*
 * MPU6050.c
 */

#include "MPU6050.h"


/* ************************************************************************************************************** */
MPU6050_Result MPU6050_Init(I2C_HandleTypeDef *I2Cx,
							struct MPU6050 *DataStruct,
						    MPU6050_Device DeviceNumber,
						    MPU6050_Accelerometer_Sensitivity AccelerometerSensitivity,
							MPU6050_Gyroscope_Sensitivity GyroscopeSensitivity,
							uint8_t DataRate) {

	/* Temporary variables */
	uint8_t MPU6050_address = 0x00;
	uint8_t WHO_AM_I = (uint8_t)MPU6050_WHO_AM_I;
	uint8_t Byte = 0x00;
	uint8_t Bytes[2] = {0};

	/* Format I2C address and save it to structure */
	DataStruct->Address = MPU6050_I2C_ADDR | DeviceNumber;
	MPU6050_address = DataStruct->Address;

	/* Check connection */
	if( HAL_I2C_IsDeviceReady(I2Cx, MPU6050_address, 1, 1000) != HAL_OK ) {
		return MPU6050_Result_DeviceNotConnected;
	}

	/*Check answer WHO_AM_I register */
	if( HAL_I2C_Master_Transmit(I2Cx, MPU6050_address, &WHO_AM_I, 1, 1000) != HAL_OK ) {
		return MPU6050_Result_Error;
	}

	if( HAL_I2C_Master_Receive(I2Cx, MPU6050_address, &Byte, 1, 1000) != HAL_OK ) {
		return MPU6050_Result_Error;
	}

	/* The right answer is 0x68 */
	if(Byte != 0x68) {
		return MPU6050_Result_DeviceInvalid;
	}

	/* Wake up MPU6050 */
	Bytes[0] = MPU6050_PWR_MGMT_1;
	Bytes[1] = 0x00;

	if(HAL_I2C_Master_Transmit(I2Cx,(uint16_t)MPU6050_address , (uint8_t *)Bytes, 2, 1000) != HAL_OK) {
		return MPU6050_Result_Error;
	}

	/* Set sample rate */
	if( MPU6050_Set_DataRate(I2Cx, DataStruct, DataRate) != MPU6050_Result_Ok) {
		return MPU6050_Result_Error;
	}

	/* Configure accelerometer */
	if( MPU6050_Configure_Accelerometer(I2Cx, DataStruct, AccelerometerSensitivity) != MPU6050_Result_Ok ) {
		return MPU6050_Result_Error;
	}

	/* Configure gyroscope */
	if( MPU6050_Configure_Gyroscope(I2Cx, DataStruct, GyroscopeSensitivity) != MPU6050_Result_Ok) {
		return MPU6050_Result_Error;
	}


	return MPU6050_Result_Ok;
}

/* ************************************************************************************************************** */
MPU6050_Result MPU6050_Set_DataRate(I2C_HandleTypeDef *I2Cx,
								    struct MPU6050 *DataStruct,
								    uint8_t rate) {

	/* Temporary variables */
	uint8_t MPU6050_address = DataStruct->Address;
	uint8_t Bytes[2];

	/* Set data sample rate */
	Bytes[0] = MPU6050_SMPLRT_DIV;
	Bytes[1] = rate;

	if( HAL_I2C_Master_Transmit(I2Cx, (uint16_t)MPU6050_address, (uint8_t *)Bytes, 2, 1000) != HAL_OK ) {
		return MPU6050_Result_Error;
	}

	/* Save data sample rate to structure */
	DataStruct->DataRate = rate;


	return MPU6050_Result_Ok;
}

/* ************************************************************************************************************** */
MPU6050_Result MPU6050_Configure_Accelerometer(I2C_HandleTypeDef *I2Cx,
									           struct MPU6050 *DataStruct,
									           MPU6050_Accelerometer_Sensitivity AccelerometerSensitivity) {

	/* Temporary variables */
	uint8_t MPU6050_address = DataStruct->Address;
	uint8_t ACCEL_CONFIG = (uint8_t )MPU6050_ACCEL_CONFIG;
	uint8_t Bytes[2] = {0};

	/* Send accelerometer sensitivity (AFS_SEL) to 3 and 4 bit of ACCEL_CONFIG register */
	Bytes[0] = ACCEL_CONFIG;
	Bytes[1] = (uint8_t)AccelerometerSensitivity << 3;

	if( HAL_I2C_Master_Transmit(I2Cx, (uint16_t)MPU6050_address, (uint8_t *)Bytes, 2, 1000) != HAL_OK ) {
		return MPU6050_Result_Error;
	}

	/* Save accelerometer sensitivity to structure */
	if( AccelerometerSensitivity == MPU6050_Accelerometer_2G ) {
		DataStruct->Acce_Sensitivity = MPU6050_ACCE_SENS_2;
	}
	else if( AccelerometerSensitivity == MPU6050_Accelerometer_4G ) {
		DataStruct->Acce_Sensitivity = MPU6050_ACCE_SENS_4;
	}
	else if( AccelerometerSensitivity == MPU6050_Accelerometer_8G ) {
		DataStruct->Acce_Sensitivity = MPU6050_ACCE_SENS_8;
	}
	else if( AccelerometerSensitivity == MPU6050_Accelerometer_16G ) {
		DataStruct->Acce_Sensitivity = MPU6050_ACCE_SENS_16;
	}


	return MPU6050_Result_Ok;
}

/* ************************************************************************************************************** */
MPU6050_Result MPU6050_Configure_Gyroscope(I2C_HandleTypeDef *I2Cx,
										   struct MPU6050 *DataStruct,
									       MPU6050_Gyroscope_Sensitivity GyroscopeSensitivity) {

	/* Temporary variables */
	uint8_t MPU6050_address = DataStruct->Address;
	uint8_t GYRO_CONFIG = (uint8_t )MPU6050_GYRO_CONFIG;
	uint8_t Bytes[2] = {0};

	/* Send gyroscope sensitivity (AFS_SEL) to 3 and 4 bit of GYRO_CONFIG register */
	Bytes[0] = GYRO_CONFIG;
	Bytes[1] = (uint8_t)GyroscopeSensitivity << 3;

	if( HAL_I2C_Master_Transmit(I2Cx, (uint16_t)MPU6050_address, (uint8_t *)Bytes, 2, 1000) != HAL_OK ) {
		return MPU6050_Result_Error;
	}

	/* Save gyroscope sensitivity to structure */
	if( GyroscopeSensitivity == MPU6050_Gyroscope_250s ) {
		DataStruct->Gyro_Sensitivity = MPU6050_GYRO_SENS_250;
	}
	else if( GyroscopeSensitivity == MPU6050_Gyroscope_500s ) {
		DataStruct->Gyro_Sensitivity = MPU6050_GYRO_SENS_500;
	}
	else if( GyroscopeSensitivity == MPU6050_Gyroscope_1000s ) {
		DataStruct->Gyro_Sensitivity = MPU6050_GYRO_SENS_1000;
	}
	else if( GyroscopeSensitivity == MPU6050_Gyroscope_2000s ) {
		DataStruct->Gyro_Sensitivity = MPU6050_GYRO_SENS_2000;
	}


	return MPU6050_Result_Ok;
}

/* ************************************************************************************************************** */
MPU6050_Result MPU6050_Read_Accelerometer(I2C_HandleTypeDef *I2Cx,
										  struct MPU6050 *DataStruct) {

	/* Temporary variables */
	uint8_t MPU6050_address = DataStruct->Address;
	uint8_t Bytes[2];

	uint8_t ACCEL_XOUT_H = MPU6050_ACCEL_XOUT_H;
	uint8_t ACCEL_XOUT_L = MPU6050_ACCEL_XOUT_L;

	uint8_t ACCEL_YOUT_H = (uint8_t)MPU6050_ACCEL_YOUT_H;
	uint8_t ACCEL_YOUT_L = (uint8_t)MPU6050_ACCEL_YOUT_L;

	uint8_t ACCEL_ZOUT_H = (uint8_t)MPU6050_ACCEL_ZOUT_H;
	uint8_t ACCEL_ZOUT_L = (uint8_t)MPU6050_ACCEL_ZOUT_L;


	/* Read and save to structure accelerometer X out*/
	if( HAL_I2C_Master_Transmit(I2Cx, (uint16_t)MPU6050_address, &ACCEL_XOUT_H, 1, 1000) != HAL_OK ) {
		return MPU6050_Result_Error;
	}
	if( HAL_I2C_Master_Receive(I2Cx, (uint16_t)MPU6050_address, &Bytes[0], 1, 1000) != HAL_OK ) {
		return MPU6050_Result_Error;
	}
	if( HAL_I2C_Master_Transmit(I2Cx, (uint16_t)MPU6050_address, &ACCEL_XOUT_L, 1, 1000) != HAL_OK ) {
		return MPU6050_Result_Error;
	}
	if( HAL_I2C_Master_Receive(I2Cx, (uint16_t)MPU6050_address, &Bytes[1], 1, 1000) != HAL_OK ) {
		return MPU6050_Result_Error;
	}

	DataStruct->Acce_X = (int16_t)(Bytes[0] << 8 | Bytes[1]);

	/* Read and save to structure accelerometer Y out*/
	if( HAL_I2C_Master_Transmit(I2Cx, (uint16_t)MPU6050_address, &ACCEL_YOUT_H, 1, 1000) != HAL_OK ) {
		return MPU6050_Result_Error;
	}
	if( HAL_I2C_Master_Receive(I2Cx, (uint16_t)MPU6050_address, &Bytes[0], 1, 1000) != HAL_OK ) {
		return MPU6050_Result_Error;
	}
	if( HAL_I2C_Master_Transmit(I2Cx, (uint16_t)MPU6050_address, &ACCEL_YOUT_L, 1, 1000) != HAL_OK ) {
		return MPU6050_Result_Error;
	}
	if( HAL_I2C_Master_Receive(I2Cx, (uint16_t)MPU6050_address, &Bytes[1], 1, 1000) != HAL_OK ) {
		return MPU6050_Result_Error;
	}

	DataStruct->Acce_Y = (int16_t)(Bytes[0] << 8 | Bytes[1]);

	/* Read and save to structure accelerometer Z out*/
	if( HAL_I2C_Master_Transmit(I2Cx, (uint16_t)MPU6050_address, &ACCEL_ZOUT_H, 1, 1000) != HAL_OK ) {
		return MPU6050_Result_Error;
	}
	if( HAL_I2C_Master_Receive(I2Cx, (uint16_t)MPU6050_address, &Bytes[0], 1, 1000) != HAL_OK ) {
		return MPU6050_Result_Error;
	}
	if( HAL_I2C_Master_Transmit(I2Cx, (uint16_t)MPU6050_address, &ACCEL_ZOUT_L, 1, 1000) != HAL_OK ) {
		return MPU6050_Result_Error;
	}
	if( HAL_I2C_Master_Receive(I2Cx, (uint16_t)MPU6050_address, &Bytes[1], 1, 1000) != HAL_OK ) {
		return MPU6050_Result_Error;
	}

	DataStruct->Acce_Z = (int16_t)(Bytes[0] << 8 | Bytes[1]);


	return MPU6050_Result_Ok;
}

/* ************************************************************************************************************** */
MPU6050_Result MPU6050_Read_Gyroscope(I2C_HandleTypeDef *I2Cx,
									  struct MPU6050 *DataStruct) {
	/* Temporary variables */
	uint8_t MPU6050_address = DataStruct->Address;
	uint8_t Bytes[2];

	uint8_t GYRO_XOUT_H = (uint8_t)MPU6050_GYRO_XOUT_H;
	uint8_t GYRO_XOUT_L = (uint8_t)MPU6050_GYRO_XOUT_L;

	uint8_t GYRO_YOUT_H = (uint8_t)MPU6050_GYRO_YOUT_H;
	uint8_t GYRO_YOUT_L = (uint8_t)MPU6050_GYRO_YOUT_L;

	uint8_t GYRO_ZOUT_H = (uint8_t)MPU6050_GYRO_ZOUT_H;
	uint8_t GYRO_ZOUT_L = (uint8_t)MPU6050_GYRO_ZOUT_L;


	/* Read and save to structure gyroscope X out*/
	if( HAL_I2C_Master_Transmit(I2Cx, (uint16_t)MPU6050_address, &GYRO_XOUT_H, 1, 1000) != HAL_OK ) {
		return MPU6050_Result_Error;
	}
	if( HAL_I2C_Master_Receive(I2Cx, (uint16_t)MPU6050_address, &Bytes[0], 1, 1000) != HAL_OK ) {
		return MPU6050_Result_Error;
	}
	if( HAL_I2C_Master_Transmit(I2Cx, (uint16_t)MPU6050_address, &GYRO_XOUT_L, 1, 1000) != HAL_OK ) {
		return MPU6050_Result_Error;
	}
	if( HAL_I2C_Master_Receive(I2Cx, (uint16_t)MPU6050_address, &Bytes[1], 1, 1000) != HAL_OK ) {
		return MPU6050_Result_Error;
	}

	DataStruct->Gyro_X = (int16_t)(Bytes[0] << 8 | Bytes[1]);

	/* Read and save to structure gyroscope Y out*/
	if( HAL_I2C_Master_Transmit(I2Cx, (uint16_t)MPU6050_address, &GYRO_YOUT_H, 1, 1000) != HAL_OK ) {
		return MPU6050_Result_Error;
	}
	if( HAL_I2C_Master_Receive(I2Cx, (uint16_t)MPU6050_address, &Bytes[0], 1, 1000) != HAL_OK ) {
		return MPU6050_Result_Error;
	}
	if( HAL_I2C_Master_Transmit(I2Cx, (uint16_t)MPU6050_address, &GYRO_YOUT_L, 1, 1000) != HAL_OK ) {
		return MPU6050_Result_Error;
	}
	if( HAL_I2C_Master_Receive(I2Cx, (uint16_t)MPU6050_address, &Bytes[1], 1, 1000) != HAL_OK ) {
		return MPU6050_Result_Error;
	}

	DataStruct->Gyro_Y = (int16_t)(Bytes[0] << 8 | Bytes[1]);

	/* Read and save to structure gyroscope Z out*/
	if( HAL_I2C_Master_Transmit(I2Cx, (uint16_t)MPU6050_address, &GYRO_ZOUT_H, 1, 1000) != HAL_OK ) {
		return MPU6050_Result_Error;
	}
	if( HAL_I2C_Master_Receive(I2Cx, (uint16_t)MPU6050_address, &Bytes[0], 1, 1000) != HAL_OK ) {
		return MPU6050_Result_Error;
	}
	if( HAL_I2C_Master_Transmit(I2Cx, (uint16_t)MPU6050_address, &GYRO_ZOUT_L, 1, 1000) != HAL_OK ) {
		return MPU6050_Result_Error;
	}
	if( HAL_I2C_Master_Receive(I2Cx, (uint16_t)MPU6050_address, &Bytes[1], 1, 1000) != HAL_OK ) {
		return MPU6050_Result_Error;
	}

	DataStruct->Gyro_Z = (int16_t)(Bytes[0] << 8 | Bytes[1]);


	return MPU6050_Result_Ok;
}

/* ************************************************************************************************************** */
MPU6050_Result MPU6050_Accelerometer_Calibration(I2C_HandleTypeDef *I2Cx,
												 struct MPU6050 *DataStruct) {
	/* Accelerometer calibration
	 * 16384 <- 1g (9.81 m/s^2)
	 * Correct reading after calibration:
	 * a_x = 0, a_x = 0, a_z = Acce_Sens
	 */

	float Acce_Sens = DataStruct->Acce_Sensitivity;

	/* Accelerometer offset averaging */
	for(int i = 0; i < 100; ++i) {

		MPU6050_Read_Accelerometer(I2Cx, DataStruct);
		DataStruct->Acce_X_Offset = DataStruct->Acce_X_Offset + DataStruct->Acce_X;
		DataStruct->Acce_Y_Offset = DataStruct->Acce_Y_Offset + DataStruct->Acce_Y;
		DataStruct->Acce_Z_Offset = DataStruct->Acce_Z_Offset + DataStruct->Acce_Z;
	}

	DataStruct->Acce_X_Offset /= 100;
	DataStruct->Acce_Y_Offset /= 100;
	DataStruct->Acce_Z_Offset = DataStruct->Acce_Z_Offset / 100 - Acce_Sens;


	return MPU6050_Result_Ok;
}

/* ************************************************************************************************************** */
MPU6050_Result MPU6050_Accelerometer_Set_Offset(struct MPU6050 *DataStruct,
									 	 	 	long double x_offset,
												long double y_offset,
												long double z_offset) {

	DataStruct->Acce_X_Offset = x_offset;
	DataStruct->Acce_Y_Offset = y_offset;
	DataStruct->Acce_Z_Offset = z_offset;

	return MPU6050_Result_Ok;
}

/* ************************************************************************************************************** */
MPU6050_Result MPU6050_Accelerometer_RPY(I2C_HandleTypeDef *I2Cx,
								         struct MPU6050 *DataStruct) {

	float Acce_Sens = DataStruct->Acce_Sensitivity;

	/******* Accelerometer measurement *******/
	MPU6050_Read_Accelerometer(I2Cx,DataStruct);

	DataStruct->Acce_X = DataStruct->Acce_X - DataStruct->Acce_X_Offset;
	DataStruct->Acce_Y = DataStruct->Acce_Y - DataStruct->Acce_Y_Offset;
	DataStruct->Acce_Z = DataStruct->Acce_Z - DataStruct->Acce_Z_Offset;

	DataStruct->Acce_X_G = DataStruct->Acce_X / Acce_Sens;
	DataStruct->Acce_Y_G = DataStruct->Acce_Y / Acce_Sens;
	DataStruct->Acce_Z_G = DataStruct->Acce_Z / Acce_Sens;

	/* Converting to RPY */
	DataStruct->Acce_Roll  = atan2(DataStruct->Acce_Y_G, DataStruct->Acce_Z_G) * (180 / M_PI);
	DataStruct->Acce_Pitch = atan2(DataStruct->Acce_X_G, DataStruct->Acce_Z_G) * (180 / M_PI);
	/* Yaw unused*/

	return MPU6050_Result_Ok;
}

/* ************************************************************************************************************** */
MPU6050_Result MPU6050_Gyroscope_Calibration(I2C_HandleTypeDef *I2Cx,
											 struct MPU6050 *DataStruct) {

	/* Gyroscope calibration
	 * 131 <- sensitivity scale factor for full scale range 250 dg/s
	 * Correct reading after calibration:
	 * g_x = 0, g_y = 0, g_z = 0
	 */

	/* Gyroscope offset averaging */
	for(int i = 0; i <= 100; ++i) {

		MPU6050_Read_Gyroscope(I2Cx,DataStruct);
		DataStruct->Gyro_X_Offset += DataStruct->Gyro_X;
		DataStruct->Gyro_Y_Offset += DataStruct->Gyro_Y;
		DataStruct->Gyro_Z_Offset += DataStruct->Gyro_Z;
	}

	DataStruct->Gyro_X_Offset /= 100;
	DataStruct->Gyro_Y_Offset /= 100;
	DataStruct->Gyro_Z_Offset /= 100;

	return MPU6050_Result_Ok;
}

/* ************************************************************************************************************** */
MPU6050_Result MPU6050_Gyroscope_Set_Offset(struct MPU6050 *DataStruct,
									 	 	long double x_offset,
											long double y_offset,
											long double z_offset) {

	DataStruct->Gyro_X_Offset = x_offset;
	DataStruct->Gyro_Y_Offset = y_offset;
	DataStruct->Gyro_Z_Offset = z_offset;

	return MPU6050_Result_Ok;
}

/* ************************************************************************************************************** */
MPU6050_Result MPU6050_Gyroscope_RPY(I2C_HandleTypeDef* I2Cx,
								     struct MPU6050* DataStruct,
									 int32_t I_Time_Start,
									 int32_t I_Time_Stop) {

	/******* Gyroscope measurement *******
	 * 131 <- sensitivity scale factor for full scale range 250 dg/s
	 */

	float Gyro_Sens = DataStruct->Gyro_Sensitivity;

	DataStruct->Gyro_X_DGS_Past = DataStruct->Gyro_X_DGS;
	DataStruct->Gyro_Y_DGS_Past = DataStruct->Gyro_Y_DGS;
	DataStruct->Gyro_Z_DGS_Past = DataStruct->Gyro_Z_DGS;

	/* Gyroscope measurment */
	MPU6050_Read_Gyroscope(I2Cx,DataStruct);

	DataStruct->Gyro_X = DataStruct->Gyro_X - DataStruct->Gyro_X_Offset;
	DataStruct->Gyro_Y = DataStruct->Gyro_Y - DataStruct->Gyro_Y_Offset;
	DataStruct->Gyro_Z = DataStruct->Gyro_Z - DataStruct->Gyro_Z_Offset;

	DataStruct->Gyro_X_DGS = (int16_t)( DataStruct->Gyro_X / Gyro_Sens);
	DataStruct->Gyro_Y_DGS = (int16_t)( DataStruct->Gyro_Y / Gyro_Sens);
	DataStruct->Gyro_Z_DGS = (int16_t)( DataStruct->Gyro_Z / Gyro_Sens);

	if( (DataStruct->Gyro_X_DGS == 1 || DataStruct->Gyro_X_DGS == -1) && DataStruct->Gyro_X_DGS_Past == 0)
		DataStruct->Gyro_X_DGS = 0;
	if( (DataStruct->Gyro_Y_DGS == 1 || DataStruct->Gyro_Y_DGS == -1) && DataStruct->Gyro_Y_DGS_Past == 0)
		DataStruct->Gyro_X_DGS = 0;
	if( (DataStruct->Gyro_Z_DGS == 1 || DataStruct->Gyro_Z_DGS == -1) && DataStruct->Gyro_Z_DGS_Past == 0)
		DataStruct->Gyro_X_DGS = 0;

	/* Converting to RPY */
	DataStruct->Gyro_Roll  = DataStruct->Gyro_Roll  + ( 0.5 * ( (long double)(I_Time_Stop - I_Time_Start) / 1000 )
												    * (DataStruct->Gyro_X_DGS + DataStruct->Gyro_X_DGS_Past) );

	DataStruct->Gyro_Pitch = DataStruct->Gyro_Pitch + ( 0.5 * ( (long double)(I_Time_Stop - I_Time_Start) / 1000 )
												    * (DataStruct->Gyro_Y_DGS + DataStruct->Gyro_Y_DGS_Past) );
	/* Yaw unused */


	return MPU6050_Result_Ok;
}

/* ************************************************************************************************************** */
