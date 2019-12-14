/*
 * madgwick_v2.c
 *
 *  Created on: 16.09.2019
 *      Author: mnowak5
 */

//=====================================================================================================
// MadgwickAHRS.c
//=====================================================================================================
//
// Implementation of Madgwick's IMU and AHRS algorithms.
// See: http://www.x-io.co.uk/node/8#open_source_ahrs_and_imu_algorithms
//
// Date			Author          Notes
// 29/09/2011	SOH Madgwick    Initial release
// 02/10/2011	SOH Madgwick	Optimised for reduced CPU load
// 19/02/2012	SOH Madgwick	Magnetometer measurement is normalised
//
//=====================================================================================================

//---------------------------------------------------------------------------------------------------
// Header files

#include <madgwick.h>
#include <math.h>

//---------------------------------------------------------------------------------------------------
// Definitions
//#define betaDef		0.0001f		// 2 * proportional gain

//---------------------------------------------------------------------------------------------------
// Variable definitions

//volatile float beta = betaDef;								// 2 * proportional gain (Kp)
volatile float q0_m = 1.0f, q1_m = 0.0f, q2_m = 0.0f, q3_m = 0.0f;	// quaternion of sensor frame relative to auxiliary frame
volatile float q0 = 1.0f, q1 = 0.0f, q2 = 0.0f, q3 = 0.0f;	// quaternion of sensor frame relative to auxiliary frame

//---------------------------------------------------------------------------------------------------
// Function declarations

float invSqrt(float x);

//====================================================================================================
// Functions

//---------------------------------------------------------------------------------------------------
// AHRS algorithm update

void MadgwickAHRSupdate(float beta,
						float gx, float gy, float gz,
						float ax, float ay, float az,
						float mx, float my, float mz,
						float dt) {

	float sampleFreq = 1 / dt;
	float recipNorm;
	float s0, s1, s2, s3;
	float qDot1, qDot2, qDot3, qDot4;
	float hx, hy;
	float _2q0_mmx, _2q0_mmy, _2q0_mmz, _2q1_mmx, _2bx, _2bz, _4bx, _4bz, _2q0_m, _2q1_m, _2q2_m, _2q3_m, _2q0_mq2_m, _2q2_mq3_m, q0_mq0_m, q0_mq1_m, q0_mq2_m, q0_mq3_m, q1_mq1_m, q1_mq2_m, q1_mq3_m, q2_mq2_m, q2_mq3_m, q3_mq3_m;

	// Use IMU algorithm if magnetometer measurement invalid (avoids NaN in magnetometer normalisation)
	/*
	if((mx == 0.0f) && (my == 0.0f) && (mz == 0.0f)) {
		MadgwickAHRSupdateIMU(gx, gy, gz, ax, ay, az, dt);
		return;
	}
	*/

	// Rate of change of quaternion from gyroscope
	qDot1 = 0.5f * (-q1_m * gx - q2_m * gy - q3_m * gz);
	qDot2 = 0.5f * (q0_m * gx + q2_m * gz - q3_m * gy);
	qDot3 = 0.5f * (q0_m * gy - q1_m * gz + q3_m * gx);
	qDot4 = 0.5f * (q0_m * gz + q1_m * gy - q2_m * gx);

	// Compute feedback only if accelerometer measurement valid (avoids NaN in accelerometer normalisation)
	if(!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f))) {

		// Normalise accelerometer measurement
		recipNorm = invSqrt(ax * ax + ay * ay + az * az);
		ax *= recipNorm;
		ay *= recipNorm;
		az *= recipNorm;

		// Normalise magnetometer measurement
		recipNorm = invSqrt(mx * mx + my * my + mz * mz);
		mx *= recipNorm;
		my *= recipNorm;
		mz *= recipNorm;

		// Auxiliary variables to avoid repeated arithmetic
		_2q0_mmx = 2.0f * q0_m * mx;
		_2q0_mmy = 2.0f * q0_m * my;
		_2q0_mmz = 2.0f * q0_m * mz;
		_2q1_mmx = 2.0f * q1_m * mx;
		_2q0_m = 2.0f * q0_m;
		_2q1_m = 2.0f * q1_m;
		_2q2_m = 2.0f * q2_m;
		_2q3_m = 2.0f * q3_m;
		_2q0_mq2_m = 2.0f * q0_m * q2_m;
		_2q2_mq3_m = 2.0f * q2_m * q3_m;
		q0_mq0_m = q0_m * q0_m;
		q0_mq1_m = q0_m * q1_m;
		q0_mq2_m = q0_m * q2_m;
		q0_mq3_m = q0_m * q3_m;
		q1_mq1_m = q1_m * q1_m;
		q1_mq2_m = q1_m * q2_m;
		q1_mq3_m = q1_m * q3_m;
		q2_mq2_m = q2_m * q2_m;
		q2_mq3_m = q2_m * q3_m;
		q3_mq3_m = q3_m * q3_m;

		// Reference direction of Earth's magnetic field
		hx = mx * q0_mq0_m - _2q0_mmy * q3_m + _2q0_mmz * q2_m + mx * q1_mq1_m + _2q1_m * my * q2_m + _2q1_m * mz * q3_m - mx * q2_mq2_m - mx * q3_mq3_m;
		hy = _2q0_mmx * q3_m + my * q0_mq0_m - _2q0_mmz * q1_m + _2q1_mmx * q2_m - my * q1_mq1_m + my * q2_mq2_m + _2q2_m * mz * q3_m - my * q3_mq3_m;
		_2bx = sqrt(hx * hx + hy * hy);
		_2bz = -_2q0_mmx * q2_m + _2q0_mmy * q1_m + mz * q0_mq0_m + _2q1_mmx * q3_m - mz * q1_mq1_m + _2q2_m * my * q3_m - mz * q2_mq2_m + mz * q3_mq3_m;
		_4bx = 2.0f * _2bx;
		_4bz = 2.0f * _2bz;

		// Gradient decent algorithm corrective step
		s0 = -_2q2_m * (2.0f * q1_mq3_m - _2q0_mq2_m - ax) + _2q1_m * (2.0f * q0_mq1_m + _2q2_mq3_m - ay) - _2bz * q2_m * (_2bx * (0.5f - q2_mq2_m - q3_mq3_m) + _2bz * (q1_mq3_m - q0_mq2_m) - mx) + (-_2bx * q3_m + _2bz * q1_m) * (_2bx * (q1_mq2_m - q0_mq3_m) + _2bz * (q0_mq1_m + q2_mq3_m) - my) + _2bx * q2_m * (_2bx * (q0_mq2_m + q1_mq3_m) + _2bz * (0.5f - q1_mq1_m - q2_mq2_m) - mz);
		s1 = _2q3_m * (2.0f * q1_mq3_m - _2q0_mq2_m - ax) + _2q0_m * (2.0f * q0_mq1_m + _2q2_mq3_m - ay) - 4.0f * q1_m * (1 - 2.0f * q1_mq1_m - 2.0f * q2_mq2_m - az) + _2bz * q3_m * (_2bx * (0.5f - q2_mq2_m - q3_mq3_m) + _2bz * (q1_mq3_m - q0_mq2_m) - mx) + (_2bx * q2_m + _2bz * q0_m) * (_2bx * (q1_mq2_m - q0_mq3_m) + _2bz * (q0_mq1_m + q2_mq3_m) - my) + (_2bx * q3_m - _4bz * q1_m) * (_2bx * (q0_mq2_m + q1_mq3_m) + _2bz * (0.5f - q1_mq1_m - q2_mq2_m) - mz);
		s2 = -_2q0_m * (2.0f * q1_mq3_m - _2q0_mq2_m - ax) + _2q3_m * (2.0f * q0_mq1_m + _2q2_mq3_m - ay) - 4.0f * q2_m * (1 - 2.0f * q1_mq1_m - 2.0f * q2_mq2_m - az) + (-_4bx * q2_m - _2bz * q0_m) * (_2bx * (0.5f - q2_mq2_m - q3_mq3_m) + _2bz * (q1_mq3_m - q0_mq2_m) - mx) + (_2bx * q1_m + _2bz * q3_m) * (_2bx * (q1_mq2_m - q0_mq3_m) + _2bz * (q0_mq1_m + q2_mq3_m) - my) + (_2bx * q0_m - _4bz * q2_m) * (_2bx * (q0_mq2_m + q1_mq3_m) + _2bz * (0.5f - q1_mq1_m - q2_mq2_m) - mz);
		s3 = _2q1_m * (2.0f * q1_mq3_m - _2q0_mq2_m - ax) + _2q2_m * (2.0f * q0_mq1_m + _2q2_mq3_m - ay) + (-_4bx * q3_m + _2bz * q1_m) * (_2bx * (0.5f - q2_mq2_m - q3_mq3_m) + _2bz * (q1_mq3_m - q0_mq2_m) - mx) + (-_2bx * q0_m + _2bz * q2_m) * (_2bx * (q1_mq2_m - q0_mq3_m) + _2bz * (q0_mq1_m + q2_mq3_m) - my) + _2bx * q1_m * (_2bx * (q0_mq2_m + q1_mq3_m) + _2bz * (0.5f - q1_mq1_m - q2_mq2_m) - mz);
		recipNorm = invSqrt(s0 * s0 + s1 * s1 + s2 * s2 + s3 * s3); // normalise step magnitude
		s0 *= recipNorm;
		s1 *= recipNorm;
		s2 *= recipNorm;
		s3 *= recipNorm;

		// Apply feedback step
		qDot1 -= beta * s0;
		qDot2 -= beta * s1;
		qDot3 -= beta * s2;
		qDot4 -= beta * s3;
	}

	// Integrate rate of change of quaternion to yield quaternion
	q0_m += qDot1 * (1.0f / sampleFreq);
	q1_m += qDot2 * (1.0f / sampleFreq);
	q2_m += qDot3 * (1.0f / sampleFreq);
	q3_m += qDot4 * (1.0f / sampleFreq);

	// Normalise quaternion
	recipNorm = invSqrt(q0_m * q0_m + q1_m * q1_m + q2_m * q2_m + q3_m * q3_m);
	q0_m *= recipNorm;
	q1_m *= recipNorm;
	q2_m *= recipNorm;
	q3_m *= recipNorm;
}

//---------------------------------------------------------------------------------------------------
// IMU algorithm update
void MadgwickAHRSupdateIMU(float beta,
						   float gx, float gy, float gz,
						   float ax, float ay, float az,
						   float dt) {

	float sampleFreq = 1 / dt;
	float recipNorm;
	float s0, s1, s2, s3;
	float qDot1, qDot2, qDot3, qDot4;
	float _2q0_m, _2q1_m, _2q2_m, _2q3_m, _4q0_m, _4q1_m, _4q2_m ,_8q1_m, _8q2_m, q0_mq0_m, q1_mq1_m, q2_mq2_m, q3_mq3_m;

	// Rate of change of quaternion from gyroscope
	qDot1 = 0.5f * (-q1 * gx - q2 * gy - q3 * gz);
	qDot2 = 0.5f * (q0 * gx + q2 * gz - q3 * gy);
	qDot3 = 0.5f * (q0 * gy - q1 * gz + q3 * gx);
	qDot4 = 0.5f * (q0 * gz + q1 * gy - q2 * gx);

	// Compute feedback only if accelerometer measurement valid (avoids NaN in accelerometer normalisation)
	if(!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f))) {

		// Normalise accelerometer measurement
		recipNorm = invSqrt(ax * ax + ay * ay + az * az);
		ax *= recipNorm;
		ay *= recipNorm;
		az *= recipNorm;

		// Auxiliary variables to avoid repeated arithmetic
		_2q0_m = 2.0f * q0;
		_2q1_m = 2.0f * q1;
		_2q2_m = 2.0f * q2;
		_2q3_m = 2.0f * q3;
		_4q0_m = 4.0f * q0;
		_4q1_m = 4.0f * q1;
		_4q2_m = 4.0f * q2;
		_8q1_m = 8.0f * q1;
		_8q2_m = 8.0f * q2;
		q0_mq0_m = q0 * q0;
		q1_mq1_m = q1 * q1;
		q2_mq2_m = q2 * q2;
		q3_mq3_m = q3 * q3;

		// Gradient decent algorithm corrective step
		s0 = _4q0_m * q2_mq2_m + _2q2_m * ax + _4q0_m * q1_mq1_m - _2q1_m * ay;
		s1 = _4q1_m * q3_mq3_m - _2q3_m * ax + 4.0f * q0_mq0_m * q1 - _2q0_m * ay - _4q1_m + _8q1_m * q1_mq1_m + _8q1_m * q2_mq2_m + _4q1_m * az;
		s2 = 4.0f * q0_mq0_m * q2 + _2q0_m * ax + _4q2_m * q3_mq3_m - _2q3_m * ay - _4q2_m + _8q2_m * q1_mq1_m + _8q2_m * q2_mq2_m + _4q2_m * az;
		s3 = 4.0f * q1_mq1_m * q3 - _2q1_m * ax + 4.0f * q2_mq2_m * q3 - _2q2_m * ay;
		recipNorm = invSqrt(s0 * s0 + s1 * s1 + s2 * s2 + s3 * s3); // normalise step magnitude
		s0 *= recipNorm;
		s1 *= recipNorm;
		s2 *= recipNorm;
		s3 *= recipNorm;

		// Apply feedback step
		qDot1 -= beta * s0;
		qDot2 -= beta * s1;
		qDot3 -= beta * s2;
		qDot4 -= beta * s3;
	}

	// Integrate rate of change of quaternion to yield quaternion
	q0 += qDot1 * (1.0f / sampleFreq);
	q1 += qDot2 * (1.0f / sampleFreq);
	q2 += qDot3 * (1.0f / sampleFreq);
	q3 += qDot4 * (1.0f / sampleFreq);

	// Normalise quaternion
	recipNorm = invSqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
	q0 *= recipNorm;
	q1 *= recipNorm;
	q2 *= recipNorm;
	q3 *= recipNorm;
}

//---------------------------------------------------------------------------------------------------
// Fast inverse square-root
// See: http://en.wikipedia.org/wiki/Fast_inverse_square_root

float invSqrt(float x) {
	float halfx = 0.5f * x;
	float y = x;
	long i = *(long*)&y;
	i = 0x5f3759df - (i>>1);
	y = *(float*)&i;
	y = y * (1.5f - (halfx * y * y));
	return y;
}

//====================================================================================================
// END OF CODE
//====================================================================================================
