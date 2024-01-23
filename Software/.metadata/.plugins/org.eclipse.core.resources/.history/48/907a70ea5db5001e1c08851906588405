/*
 * FIRFilter.c
 *
 *  Created on: Jan 3, 2024
 *      Author: Michal Klebokowski
 */
#include "FIRFilter.h"

static float FIR_IMPULSE_RESPONSE[FIR_FILTER_LENGTH] = {        -0.000000000000000002,
	    0.001281030062831348,
	    0.005647692264795379,
	    0.014334622426885834,
	    0.028433503299884869,
	    0.047917389531823090,
	    0.071010675012083371,
	    0.094239904533218496,
	    0.113219640131959703,
	    0.123915542736517767,
	    0.123915542736517767,
	    0.113219640131959745,
	    0.094239904533218538,
	    0.071010675012083344,
	    0.047917389531823118,
	    0.028433503299884890,
	    0.014334622426885850,
	    0.005647692264795369,
	    0.001281030062831344,
	    -0.000000000000000002 };




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
