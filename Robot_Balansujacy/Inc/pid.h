/*
 * pid.h
 *
 *  Created on: 16.05.2019
 *  Author: Micha�
 */

#ifndef PID_H_
#define PID_H_

#include "math.h"

#define MAX_CONTROL  8000
#define MIN_CONTROL -8000

#define I_MAX	 900
#define I_MIN	-900

struct PID_regulator{

	double Kp, Ti, Td;

	double control;
	double control_error;
	double control_error_past;

	double set_point;
	double measured_point;

	double integral;
	double derivative;
};

void PID_Init(struct PID_regulator *pid);

void PID_Set_parameters(struct PID_regulator *pid, double set_point, double Kp, double Ti, double Td);

double PID_Calculate(struct PID_regulator *pid, double measured_point, long double I_Time_Start, long double I_Time_Stop);

#endif /* PID_H_ */
