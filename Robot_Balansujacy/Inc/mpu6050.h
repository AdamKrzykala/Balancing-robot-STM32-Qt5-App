/*
 * MPU6050.h
 */

/***********************************************************************************************
 *  Created on: 	31.03.2019
 *  Author: 		Micha³ Nowak
 *	University: 	Wroc³aw University of Science
 ***********************************************************************************************/

#ifndef MPU6050_H_
#define MPU6050_H_

#include "i2c.h"
#include "math.h"
#include "stdlib.h"


/***********************************************************************************************
 ***************** 						> REGISTER MAP <				       *****************
 *
 * Source: MPU-6000/MPU-6050 Register Map and Descriptions
 * Document Number: RM-MPU-6000A-00
 * Revision: 4.2
 * Release Date: 08/19/2013
 *
 ***********************************************************************************************/
#define MPU6050_I2C_ADDR				0xD0		/* <- Default I2C address */

#define MPU6050_SELF_TEST_X				0x0D
#define MPU6050_SELF_TEST_Y				0x0E
#define MPU6050_SELF_TEST_Z				0x0F
#define MPU6050_SELF_TEST_A				0x10
#define MPU6050_SMPLRT_DIV				0x19
#define MPU6050_CONFIG					0x1A
#define MPU6050_GYRO_CONFIG				0x1B
#define MPU6050_ACCEL_CONFIG			0x1C
#define MU6050_FIFO_EN					0x23
#define MPU6050_I2C_MST_CTRL			0x24
#define MPU6050_I2C_SLV0_ADDR			0x25
#define MPU6050_I2C_SLV0_REG			0x26
#define MPU6050_I2C_SLV0_CTRL			0x27
#define MPU6050_I2C_SLV1_ADDR			0x28
#define MPU6050_I2C_SLV1_REG			0x29
#define MPU6050_I2C_SLV1_CTRL			0x2A
#define MPU6050_I2C_SLV2_ADDR			0x2B
#define MPU6050_I2C_SLV2_REG			0x2C
#define MPU6050_I2C_SLV2_CTRL			0x2D
#define MPU6050_I2C_SLV3_ADDR			0x2E
#define MPU6050_I2C_SLV3_REG			0x2F
#define MPU6050_I2C_SLV3_CTRL			0x30
#define MPU6050_I2C_SLV4_ADDR			0x31
#define MPU6050_I2C_SLV4_REG			0x32
#define MPU6050_I2C_SLV4_DO				0x33
#define MPU6050_I2C_SLV4_CTRL			0x34
#define MPU6050_I2C_SLV4_DI				0x35
#define MPU6050_I2C_MST_STATUS			0x36
#define MPU6050_INT_PIN_CFG				0x37
#define MPU6050_INT_ENABLE				0x38
#define MPU6050_INT_STATUS				0x3A
#define MPU6050_ACCEL_XOUT_H			0x3B
#define MPU6050_ACCEL_XOUT_L			0x3C
#define MPU6050_ACCEL_YOUT_H			0x3D
#define MPU6050_ACCEL_YOUT_L			0x3E
#define MPU6050_ACCEL_ZOUT_H			0x3F
#define MPU6050_ACCEL_ZOUT_L			0x40
#define MPU6050_TEMP_OUT_H				0x41
#define MPU6050_TEMP_OUT_L				0x42
#define MPU6050_GYRO_XOUT_H				0x43
#define MPU6050_GYRO_XOUT_L				0x44
#define MPU6050_GYRO_YOUT_H				0x45
#define MPU6050_GYRO_YOUT_L				0x46
#define MPU6050_GYRO_ZOUT_H				0x47
#define MPU6050_GYRO_ZOUT_L				0x48
#define MPU6050_EXT_SENS_DATA_00		0x49
#define MPU6050_EXT_SENS_DATA_01		0x4A
#define MPU6050_EXT_SENS_DATA_02		0x4B
#define MPU6050_EXT_SENS_DATA_03		0x4C
#define MPU6050_EXT_SENS_DATA_04		0x4D
#define MPU6050_EXT_SENS_DATA_05		0x4E
#define MPU6050_EXT_SENS_DATA_06		0x4F
#define MPU6050_EXT_SENS_DATA_07		0x50
#define MPU6050_EXT_SENS_DATA_08		0x51
#define MPU6050_EXT_SENS_DATA_09		0x52
#define MPU6050_EXT_SENS_DATA_10		0x53
#define MPU6050_EXT_SENS_DATA_11		0x54
#define MPU6050_EXT_SENS_DATA_12		0x55
#define MPU6050_EXT_SENS_DATA_13		0x56
#define MPU6050_EXT_SENS_DATA_14		0x57
#define MPU6050_EXT_SENS_DATA_15		0x58
#define MPU6050_EXT_SENS_DATA_16		0x59
#define MPU6050_EXT_SENS_DATA_17		0x5A
#define MPU6050_EXT_SENS_DATA_18		0x5B
#define MPU6050_EXT_SENS_DATA_19		0x5C
#define MPU6050_EXT_SENS_DATA_20		0x5D
#define MPU6050_EXT_SENS_DATA_21		0x5E
#define MPU6050_EXT_SENS_DATA_22		0x5F
#define MPU6050_EXT_SENS_DATA_23		0x60
#define MPU6050_I2C_SLV0_DO				0x63
#define MPU6050_I2C_SLV1_DO				0x64
#define MPU6050_I2C_SLV2_DO				0x65
#define MPU6050_I2C_SLV3_DO				0x66
#define MPU6050_I2C_MST_DELAY_CT RL		0x67
#define MPU6050_SIGNAL_PATH_RES ET		0x68
#define MPU6050_USER_CTRL				0x6A
#define MPU6050_PWR_MGMT_1				0x6B
#define MPU6050_PWR_MGMT_2				0x6C
#define MPU6050_FIFO_COUNTH				0x72
#define MPU6050_FIFO_COUNTL				0x73
#define MPU6050_FIFO_R_W				0x74
#define MPU6050_WHO_AM_I				0x75

/***********************************************************************************************
 *****************				> Gyroscope sensitivities < 		   		   *****************
 ***********************************************************************************************/
#define MPU6050_GYRO_SENS_250		(float) 131
#define MPU6050_GYRO_SENS_500		(float) 65.5
#define MPU6050_GYRO_SENS_1000		(float) 32.8
#define MPU6050_GYRO_SENS_2000		(float) 16.4

/***********************************************************************************************
 *****************				> Accelerometer sensitivities <		   		   *****************
 ***********************************************************************************************/
#define MPU6050_ACCE_SENS_2			(float) 16384
#define MPU6050_ACCE_SENS_4			(float) 8192
#define MPU6050_ACCE_SENS_8			(float) 4096
#define MPU6050_ACCE_SENS_16		(float) 2048

/***********************************************************************************************
 *****************				> Data rates predefined constants <		 	   *****************
 ***********************************************************************************************/
#define MPU6050_DataRate_8KHz       0   		/* <- Sample rate set to 8 kHz  */
#define MPU6050_DataRate_4KHz       1   		/* <- Sample rate set to 4 kHz  */
#define MPU6050_DataRate_2KHz       3   		/* <- Sample rate set to 2 kHz  */
#define MPU6050_DataRate_1KHz       7   		/* <- Sample rate set to 1 kHz  */
#define MPU6050_DataRate_500Hz      15  		/* <- Sample rate set to 500 Hz */
#define MPU6050_DataRate_250Hz      31  		/* <- Sample rate set to 250 Hz */
#define MPU6050_DataRate_125Hz      63  		/* <- Sample rate set to 125 Hz */
#define MPU6050_DataRate_100Hz      79  		/* <- Sample rate set to 100 Hz */

/***********************************************************************************************
 * MPU6050 can have 2 different slave addresses, depends on it's input AD0 pin
 *         This feature allows you to use 2 different sensors with this library at the same time
 ***********************************************************************************************/
typedef enum  {

	MPU6050_Device_0 = 0x00, 					/* <- AD0 pin is set to low  */
	MPU6050_Device_1 = 0x02  					/* <- AD0 pin is set to high */

} MPU6050_Device;

/************************************************************************************************
 *****************			> Parameters for accelerometer range <				*****************
 ************************************************************************************************/
typedef enum  {

	MPU6050_Accelerometer_2G  = 0x00, 			/* <- Range is +- 2G  */
	MPU6050_Accelerometer_4G  = 0x01, 			/* <- Range is +- 4G  */
	MPU6050_Accelerometer_8G  = 0x02, 			/* <- Range is +- 8G  */
	MPU6050_Accelerometer_16G = 0x03  			/* <- Range is +- 16G */

} MPU6050_Accelerometer_Sensitivity;

/*************************************************************************************************
 ***************** 			> Parameters for gyroscope range < 					 *****************
 *************************************************************************************************/
typedef enum {

	MPU6050_Gyroscope_250s  = 0x00,  			/* <- Range is +- 250  degrees/s */
	MPU6050_Gyroscope_500s  = 0x01,  			/* <- Range is +- 500  degrees/s */
	MPU6050_Gyroscope_1000s = 0x02,  			/* <- Range is +- 1000 degrees/s */
	MPU6050_Gyroscope_2000s = 0x03   			/* <- Range is +- 2000 degrees/s */

} MPU6050_Gyroscope_Sensitivity;


/*************************************************************************************************
 *****************			> MPU6050_Result type definition <			         *****************
 *************************************************************************************************/
typedef enum {

	MPU6050_Result_Ok 				   = 0,		/* <- Everything OK */
	MPU6050_Result_Error			   = 1,     /* <- Unknown error */
	MPU6050_Result_DeviceNotConnected  = 2, 	/* <- There is no device with valid slave address  */
	MPU6050_Result_DeviceInvalid       = 3,  	/* <- Connected device with address is not MPU6050 */

} MPU6050_Result;


/*************************************************************************************************
 *****************					> MPU6050 structure <			         	 *****************
 *************************************************************************************************/
struct MPU6050 {

	uint8_t Address;         									/* <- I2C address of device */
	uint8_t DataRate;											/* <- Data sample rate */

	float Acce_Sensitivity;										/* <- Accelerometer sensitivity */
	float Gyro_Sensitivity;										/* <- Gyroscope sensitivity */

	double Acce_X, Acce_Y, Acce_Z; 								/* <- Accelerometer value XYZ axis */
	long double Acce_X_Offset, Acce_Y_Offset, Acce_Z_Offset;	/* <- Accelerometer XYZ values at point 0.0.0 (offset )*/
	double Acce_X_G, Acce_Y_G, Acce_Z_G;						/* <- Accelerometer XYZ in g(9.81 m/s^2) values */
	double Acce_Roll, Acce_Pitch;								/* <- Accelerometer Roll, Pitch values */

	double Gyro_X, Gyro_Y, Gyro_Z;     							/* <- Gyroscope value XYZ axis */
	long double Gyro_X_Offset, Gyro_Y_Offset, Gyro_Z_Offset;	/* <- Gyroscope XYZ values at point 0.0.0 (offset )*/
	double Gyro_X_DGS, Gyro_Y_DGS, Gyro_Z_DGS;					/* <- Gyroscope current XYZ in dg/s values */
	double Gyro_X_DGS_Past, Gyro_Y_DGS_Past, Gyro_Z_DGS_Past;	/* <- Gyroscope previous XYZ in dg/s values */
	double Gyro_Roll, Gyro_Pitch;								/* <- Gyroscope Roll, Pitch values */

};

/*************************************************************************************************
 *****************					> MPU6050 initialization <			         *****************
 *************************************************************************************************/
MPU6050_Result MPU6050_Init(I2C_HandleTypeDef* I2Cx,
							struct MPU6050* DataStruct,
							MPU6050_Device DeviceNumber,
							MPU6050_Accelerometer_Sensitivity AccelerometerSensitivity,
							MPU6050_Gyroscope_Sensitivity GyroscopeSensitivity,
							uint8_t DataRate);

/*************************************************************************************************
 *****************					> Configure gyroscope <					     *****************
 *************************************************************************************************/
MPU6050_Result MPU6050_Configure_Gyroscope(I2C_HandleTypeDef *I2Cx,
										  struct MPU6050 *DataStruct,
									      MPU6050_Gyroscope_Sensitivity GyroscopeSensitivity);

/*************************************************************************************************
 *****************				> Configure accelerometer <						 *****************
 *************************************************************************************************/
MPU6050_Result MPU6050_Configure_Accelerometer(I2C_HandleTypeDef *I2Cx,
											   struct MPU6050 *DataStruct,
										       MPU6050_Accelerometer_Sensitivity AccelerometerSensitivity);

/*************************************************************************************************
 *****************					> Set data sample rate <					 *****************
 *************************************************************************************************/
MPU6050_Result MPU6050_Set_DataRate(I2C_HandleTypeDef *I2Cx,
								    struct MPU6050 *DataStruct,
								    uint8_t rate);

/*************************************************************************************************
 *****************					> Read data from accelerometer < 			 *****************
 *************************************************************************************************/
MPU6050_Result MPU6050_Read_Accelerometer(I2C_HandleTypeDef *I2Cx,
										  struct MPU6050 *DataStruct);

/*************************************************************************************************
 *****************					> Read data from gyroscope <				 *****************
 *************************************************************************************************/
MPU6050_Result MPU6050_Read_Gyroscope(I2C_HandleTypeDef *I2Cx,
								      struct MPU6050 *DataStruct);


/*************************************************************************************************
 *****************					> Accelerometer calibration <				 *****************
 *************************************************************************************************/
MPU6050_Result MPU6050_Accelerometer_Calibration(I2C_HandleTypeDef *I2Cx,
												 struct MPU6050 *DataStruct);

/*************************************************************************************************
 *****************				> Accelerometer set offset manual       		 *****************
 *************************************************************************************************/
MPU6050_Result MPU6050_Accelerometer_Set_Offset(struct MPU6050 *DataStruct,
									 	 	 	long double x_offset,
												long double y_offset,
												long double z_offset);

/*************************************************************************************************
 *****************			> Accelerometer data to RPY transformation 	 		 *****************
 *************************************************************************************************/
MPU6050_Result MPU6050_Accelerometer_RPY(I2C_HandleTypeDef *I2Cx,
										 struct MPU6050* DataStruct);

/*************************************************************************************************
 *****************					> Gyroscope calibration <					 *****************
 *************************************************************************************************/
MPU6050_Result MPU6050_Gyroscope_Calibration(I2C_HandleTypeDef *I2Cx,
											 struct MPU6050 *DataStruct);

/*************************************************************************************************
 *****************				 > Gyroscope set offset manual       			 *****************
 *************************************************************************************************/
MPU6050_Result MPU6050_Gyroscope_Set_Offset(struct MPU6050 *DataStruct,
									 	 	long double x_offset,
											long double y_offset,
											long double z_offset);

/*************************************************************************************************
 *****************			> Gyroscope data to RPY transformation       		 *****************
 *************************************************************************************************/
MPU6050_Result MPU6050_Gyroscope_RPY(I2C_HandleTypeDef* I2Cx,
								     struct MPU6050 *DataStruct,
									 int32_t I_Time_Start,
									 int32_t I_Time_Stop);

#endif /* MPU6050_h */
