/*
 * FIRFilter.c
 *
 *  Created on: Jan 3, 2024
 *      Author: Michal Klebokowski
 */
#include "FIRFilter.h"

/* After many tests, the best solution for applied encoders is 100Hz sampling with moving average filter */
/* (25 elements and blackman windowing */
static float FIR_IMPULSE_RESPONSE[FIR_FILTER_LENGTH] =
{
		-0.000000000000000001,
		0.000626896741886996,
		0.002677311320216333,
		0.006591925536381568,
		0.012896825396825394,
		0.021955202891466723,
		0.033730158730158728,
		0.047631695461161243,
		0.062500000000000000,
		0.076741407796951766,
		0.088592529949624937,
		0.096452871572151710,
		0.099206349206349201,
		0.096452871572151724,
		0.088592529949624937,
		0.076741407796951794,
		0.062500000000000028,
		0.047631695461161243,
		0.033730158730158742,
		0.021955202891466741,
		0.012896825396825394,
		0.006591925536381577,
		0.002677311320216343,
		0.000626896741887000,
		-0.000000000000000001
 };




void FIRFilter_Init(FIRFilter *fir)
{
	/* Clear filter buffer */
	for (uint8_t n = 0; n < FIR_FILTER_LENGTH; n++)
	{
		fir->buf[n] = 0.0f;
	}

	/* Reset buffer index */
	fir->bufIndex = 0;

	/* Clear filter output */
	fir->out = 0.0f;
}

float FIRFilter_Update(FIRFilter *fir, float inp)
{
	/* Store latest sample in buffer */
	fir->buf[fir->bufIndex] = inp;

	/* Increment buffer index and wrap around if necessary */
	fir->bufIndex++;

	if(fir->bufIndex == FIR_FILTER_LENGTH)
	{
		fir->bufIndex = 0;
	}

	/* Compute new output sample (via convulation) */
	fir->out = 0.0f;

	uint8_t sumIndex = fir->bufIndex;

	for(uint8_t n = 0; n < FIR_FILTER_LENGTH; n++)
	{
		/* Decrement index and wrap if necessary */
		if (sumIndex > 0)
		{
			sumIndex--;
		}
		else
		{
			sumIndex = FIR_FILTER_LENGTH - 1;
		}

		/* Multiply impulse response with shifted input sample and add to output */
		fir->out += FIR_IMPULSE_RESPONSE[n] * fir->buf[sumIndex];
	}

	/* Return filtered output */
	return fir->out;
}
