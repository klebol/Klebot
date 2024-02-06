/*
 * PID.h
 *
 *  Created on: Feb 3, 2024
 *      Author: Michal Klebokowski
 */

#ifndef INC_PID_H_
#define INC_PID_H_

#include "stdint.h"

typedef struct
{
	/* PID gains */
	float kp;
	float ki;
	float kd;
	/* Errors */
	int16_t LastError;
	int32_t IntegralError;
	/* PID output */
	int16_t Output;
	/* Max values */
	int32_t MaxIntegralError;
	int16_t MaxOutput;

}PID_Controller_t;

void PID_SetGains(PID_Controller_t *instance, float p, float i, float d);
void PID_SetMaxValues(PID_Controller_t *instance, int32_t max_integral_error, int16_t max_output);
void PID_ResetGains(PID_Controller_t *instance);
int16_t PID_Update(PID_Controller_t *instance, int16_t input_error, uint16_t sampling_rate_hz);
void PID_ResetTemps(PID_Controller_t *instance);


#endif /* INC_PID_H_ */