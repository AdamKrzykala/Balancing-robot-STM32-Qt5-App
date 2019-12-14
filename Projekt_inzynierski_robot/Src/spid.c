/*
 * spid.c
 *
 *  Created on: 16.07.2019
 *      Author: mnowak5
 */

#include "spid.h"

/* ------------------------------------------------------------------------------------------------------------------------------------ */
void Speed_PID_Init(struct Speed_PID *pid) {

	pid->control = 0;
	pid->control_error = 0;
	pid->control_error_past = 0;

	pid->measured_point = 0;

	pid->integral = 0;
	pid->derivative = 0;
}

/* ------------------------------------------------------------------------------------------------------------------------------------ */
void Speed_PID_Set_parameters(struct Speed_PID *pid, double set_point, double Kp, double Ti, double Td) {

	pid->set_point = set_point;
	pid->Kp = Kp;
	pid->Ti = Ti;
	pid->Td = Td;
}

/* ------------------------------------------------------------------------------------------------------------------------------------ */
double Speed_PID_Calculate(struct Speed_PID *pid, double measured_point, long double I_Time_Start, long double I_Time_Stop) {

	pid->measured_point = measured_point;
	pid->control_error = pid->set_point - pid->measured_point;

	// K_I
	pid->integral = pid->integral + (0.5 * (pid->control_error + pid->control_error_past) * ((I_Time_Stop - I_Time_Start) / 1000));

	if (pid->integral > SPID_I_MAX) {

		pid->integral = SPID_I_MAX;

	}
	else if (pid->integral < SPID_I_MIN) {

		pid->integral = SPID_I_MIN;
	}

	// K_D
	pid->derivative = (pid->control_error - pid->control_error_past) / ( (I_Time_Stop - I_Time_Start ) / 1000 );

	pid->control = (pid->Kp * pid->control_error) +
				   (pid->Ti * pid->integral) +
				   (pid->Td * pid->derivative);

	if(pid->control > SPID_MAX_CONTROL) {

		pid->control = SPID_MAX_CONTROL;
	}
	else if(pid->control < SPID_MIN_CONTROL) {

		pid->control = SPID_MIN_CONTROL;
	}

	pid->control_error_past = pid->control_error;

	return pid->control_error;
}
/* ------------------------------------------------------------------------------------------------------------------------------------ */
