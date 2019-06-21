/*
 * pid.c
 *
 *  Created on: 16.05.2019
 *      Author: Micha�
 */

#include "pid.h"

void PID_Set_parameters(struct PID_regulator *pid, double Kp, double Ti, double Td, double set_point) {

	pid->Kp = Kp;
	pid->Ti = Ti;
	pid->Td = Td;

	pid->control = 0;
	pid->control_error = 0;
	pid->control_error_past = 0;

	pid->set_point = set_point;
	pid->measured_point = 0;

	pid->integral = 0;
	pid->derivative = 0;
}

double PID_Calculate(struct PID_regulator *pid, double measured_point, long double I_Time_Start, long double I_Time_Stop) {

	pid->measured_point = measured_point;
	pid->control_error = pid->set_point - pid->measured_point;

	if( fabs(pid->control_error) > 0.01 ) { // 0.01 to anty windup ?

		pid->integral = pid->integral + ( 0.5 * (pid->control_error + pid->control_error_past) * ( (I_Time_Stop - I_Time_Start ) / 1000 ) );
	}

	pid->derivative = (pid->control_error - pid->control_error_past) / ( (I_Time_Stop - I_Time_Start ) / 1000 );

	pid->control = (pid->Kp * pid->control_error) +
				   (pid->Ti * pid->integral) +
				   (pid->Td * pid->derivative);

	if(pid->control > MAX_CONTROL) {

		pid->control = MAX_CONTROL;
	}
	else if(pid->control < MIN_CONTROL) {

		pid->control = MIN_CONTROL;
	}

	pid->control_error_past = pid->control_error;

	return pid->control_error;
}


