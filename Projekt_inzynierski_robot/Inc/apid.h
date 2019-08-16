/*
 * pid.h
 *
 *  Created on: 16.05.2019
 *  Author: Micha³
 */

#ifndef PID_H_
#define PID_H_

#include "math.h"

#define APID_MAX_CONTROL  250
#define APID_MIN_CONTROL -250

#define APID_I_MAX	 250
#define APID_I_MIN	-250

struct Angle_PID{

	double Kp, Ti, Td;

	double control;
	double control_error;
	double control_error_past;

	double set_point;
	double measured_point;

	double integral;
	double derivative;
};

void Angle_PID_Init(struct Angle_PID *pid);

void Angle_PID_Set_parameters(struct Angle_PID *pid, double set_point, double Kp, double Ti, double Td);

double Angle_PID_Calculate(struct Angle_PID *pid, double measured_point, long double I_Time_Start, long double I_Time_Stop);

#endif /* PID_H_ */
