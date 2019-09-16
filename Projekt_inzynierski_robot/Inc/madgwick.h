/*
 * madgwick_v2.h
 *
 *  Created on: 16.09.2019
 *      Author: mnowak5
 */

#ifndef MADGWICK_V2_H_
#define MADGWICK_V2_H_

//=====================================================================================================
// MadgwickAHRS.h
//=====================================================================================================
//
// Implementation of Madgwick's IMU and AHRS algorithms.
// See: http://www.x-io.co.uk/node/8#open_source_ahrs_and_imu_algorithms
//
// Date			Author          Notes
// 29/09/2011	SOH Madgwick    Initial release
// 02/10/2011	SOH Madgwick	Optimised for reduced CPU load
//
//=====================================================================================================

//----------------------------------------------------------------------------------------------------
// Variable declaration

//extern volatile float beta;				// algorithm gain
extern volatile float q0, q1, q2, q3;	// quaternion of sensor frame relative to auxiliary frame

//---------------------------------------------------------------------------------------------------
// Function declarations

void MadgwickAHRSupdate(float beta,
						float gx, float gy, float gz,
						float ax, float ay, float az,
						float mx, float my, float mz,
						float dt);
void MadgwickAHRSupdateIMU(float gx, float gy, float gz, float ax, float ay, float az, float dt);

//=====================================================================================================
// End of file
//=====================================================================================================

#endif /* MADGWICK_V2_H_ */
