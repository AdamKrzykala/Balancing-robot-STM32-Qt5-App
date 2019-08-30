/*
 * kalman.c
 *
 *  Created on: 29.08.2019
 *      Author: mnowak5
 */

#include "kalman.h"

/* ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

void matrix_2x2_mul_2x1(float * in1, float * in2, float * out)
{
   out[0] = in1[0] * in2[0] + in1[1] * in2[1];
   out[1] = in1[2] * in2[0] + in1[3] * in2[1];
}

void matrix_2x1_mul_1x1(float * in1, float * in2, float * out)
{
   out[0] = in1[0] * in2[0];
   out[1] = in1[1] * in2[0];
}

void matrix_2x1_add_2x1(float * in1, float * in2, float * out)
{
   out[0] = in1[0] + in2[0];
   out[1] = in1[1] + in2[1];
}

void matrix_2x2_mul_2x2(float * in1, float * in2, float * out)
{
   out[0] = in1[0] * in2[0] + in1[1] * in2[2];
   out[1] = in1[0] * in2[1] + in1[1] * in2[3];
   out[2] = in1[2] * in2[0] + in1[3] * in2[2];
   out[3] = in1[2] * in2[1] + in1[3] * in2[3];
}

void matrix_2x2_add_2x2(float * in1, float * in2, float * out)
{
   out[0] = in1[0] + in2[0];
   out[1] = in1[1] + in2[1];
   out[2] = in1[2] + in2[2];
   out[3] = in1[3] + in2[3];
}

void matrix_1x2_mul_2x1(float * in1, float * in2, float * out)
{
   out[0] = in1[0] * in2[0] + in1[1] * in2[1];
}

void matrix_1x2_mul_2x2(float * in1, float * in2, float * out)
{
   out[0] = in1[0] * in2[0] + in1[1] * in2[2];
   out[1] = in1[0] * in2[1] + in1[1] * in2[3];
}

void matrix_2x1_mul_1x2(float * in1, float * in2, float * out)
{
   out[0] = in1[0] * in2[0];
   out[1] = in1[0] * in2[1];
   out[2] = in1[1] * in2[0];
   out[3] = in1[1] * in2[1];
}

void matrix_2x2_sub_2x2(float * in1, float * in2, float * out)
{
   out[0] = in1[0] - in2[0];
   out[1] = in1[1] - in2[1];
   out[2] = in1[2] - in2[2];
   out[3] = in1[3] - in2[3];
}

void matrix_2x2_trans(float * in, float * out)
{
   out[0] = in[0];
   out[1] = in[2];
   out[2] = in[1];
   out[3] = in[3];
}

/* ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

void Kalman_filter_init(float dt, float Acce_pitch) {

	/* Inicjalizacja zmiennych */
	dt = 0.1;

	A[0] = 1;
	A[1] = -dt;
	A[2] = 0;
	A[3] = 1;

	B[0] = dt;
	B[1] = 0;

	C[0] = 1;
	C[1] = 0;

	std_dev_v = 1;
	std_dev_w = 2;
	V[0] = std_dev_v * std_dev_v * dt;
	V[1] = 0;
	V[2] = 0;
	V[3] = std_dev_v * std_dev_v * dt;
	W[0] = std_dev_w * std_dev_w;

	/* Wartosci poczatkowe filtru */
	P_post[0] = 1;
	P_post[1] = 0;
	P_post[2] = 0;
	P_post[3] = 1;

	//acc_x = sensor_acc_get_x();
	//acc_y = sensor_acc_get_y();
	x_post[0] = Acce_pitch;
	x_post[1] = 0;
}

/* ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

float Kalman_filter_calculate(float Acce_pitch, float Gyro_Z) {

	/* x(t+1|t) = Ax(t|t) + Bu(t) */
	u[0] = Gyro_Z;
	matrix_2x2_mul_2x1(A, x_post, Ax);
	matrix_2x1_mul_1x1(B, u, Bu);
	matrix_2x1_add_2x1(Ax, Bu, x_pri);

	/* P(t+1|t) = AP(t|t)A^T + V */
	matrix_2x2_mul_2x2(A, P_post, AP);
	matrix_2x2_trans(A, AT);
	matrix_2x2_mul_2x2(AP, AT, APAT);
	matrix_2x2_add_2x2(APAT, V, P_pri);

	/* eps(t) = y(t) - Cx(t|t-1) */
	//acc_x = sensor_acc_get_x();
	//acc_y = sensor_acc_get_y();
	y[0] = Acce_pitch;
	matrix_1x2_mul_2x1(C, x_pri, Cx);
	eps[0] = y[0] - Cx[0];

	/* S(t) = CP(t|t-1)C^T + W */
	matrix_1x2_mul_2x2(C, P_pri, CP);
	matrix_1x2_mul_2x1(C, C, CPCT);
	S[0] = CPCT[0] + W[0];

	/* K(t) = P(t|t-1)C^TS(t)^-1 */
	matrix_2x2_mul_2x1(P_pri, C, PCT);
	S1[0] = 1 / S[0];
	matrix_2x1_mul_1x1(PCT, S1, K);

	/* x(t|t) = x(t|t-1) + K(t)eps(t) */
	matrix_2x1_mul_1x1(K, eps, Keps);
	matrix_2x1_add_2x1(x_pri, Keps, x_post);

	/* P(t|t) = P(t|t-1) - K(t)S(t)K(t)^T */
	matrix_2x1_mul_1x1(K, S, KS);
	matrix_2x1_mul_1x2(KS, K, KSKT);
	matrix_2x2_sub_2x2(P_pri, KSKT, P_post);

	return x_post[0];
}

/* ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
