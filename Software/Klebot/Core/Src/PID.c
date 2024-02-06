/*
 * PID.c
 *
 *  Created on: Feb 3, 2024
 *      Author: Michal Klebokowski
 */

#include "PID.h"

void PID_SetGains(PID_Controller_t *instance, float p, float i, float d)
{
	instance->kp = p;
	instance->ki = i;
	instance->kp = p;
}

void PID_SetMaxValues(PID_Controller_t *instance, int32_t max_integral_error, int16_t max_output)
{
	instance->MaxIntegralError = max_integral_error;
	instance->MaxOutput = max_output;
}

void PID_ResetGains(PID_Controller_t *instance)
{
	instance->kp = 0;
	instance->ki = 0;
	instance->kp = 0;
	instance->IntegralError = 0;
}

void PID_ResetTemps(PID_Controller_t *instance)
{
	instance->Output = 0;
	instance->LastError = 0;
	instance->IntegralError = 0;
}


int16_t PID_Update(PID_Controller_t *instance, int16_t input_error, uint16_t sampling_rate_hz)
{
	/* Update integral error */
	if(instance->ki > 0)
	{
		instance->IntegralError += input_error;
	}
	/* Secure integral error */
	if(instance->IntegralError > instance->MaxIntegralError)
	{
		instance->IntegralError = instance->MaxIntegralError;
	}
	else if(instance->IntegralError < -instance->MaxIntegralError)
	{
		instance->IntegralError = -instance->MaxIntegralError;
	}

	/*Calculate the PID output */
	instance->Output = (instance->kp * input_error) +
			(instance->ki * (instance->IntegralError) / sampling_rate_hz) +
			(instance->kd * sampling_rate_hz * (input_error - instance->LastError) );


	/* Secure output */
	if(instance->Output >= instance->MaxOutput)
	{
		instance->Output = instance->MaxOutput;
	}
	else if(instance->Output <= -instance->MaxOutput)
	{
		instance->Output = -instance->MaxOutput;
	}

	/* Save error */
	instance->LastError = input_error;

	return instance->Output;
}
