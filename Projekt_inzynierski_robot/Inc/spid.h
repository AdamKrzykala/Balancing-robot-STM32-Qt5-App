/*
 * spid.h
 *
 *  Created on: 16.07.2019
 *      Author: mnowak5
 */

#ifndef SPID_H_
#define SPID_H_

#include "math.h"

#define SPID_MAX_CONTROL  2000
#define SPID_MIN_CONTROL -2000

#define SPID_I_MAX	 2000
#define SPID_I_MIN	-2000

struct Speed_PID{

	double Kp, Ti, Td;

	double control;
	double control_error;
	double control_error_past;

	double set_point;
	double measured_point;

	double integral;
	double derivative;
};

void Speed_PID_Init(struct Speed_PID *pid);

void Speed_PID_Set_parameters(struct Speed_PID *pid, double set_point, double Kp, double Ti, double Td);

double Speed_PID_Calculate(struct Speed_PID *pid, double measured_point, long double I_Time_Start, long double I_Time_Stop);

#endif /* SPID_H_ */
