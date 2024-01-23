/*
 * FIRFilter.c
 *
 *  Created on: Jan 3, 2024
 *      Author: Michal Klebokowski
 */
#include "FIRFilter.h"

static float FIR_IMPULSE_RESPONSE[FIR_FILTER_LENGTH] =
{
	-0.001499855417445384,
	-0.000228126365317577,
	0.004581219159106590,
	-0.012188624969839882,
	0.017857570436562418,
	-0.010645028864524822,
	-0.020024146353593217,
	0.075503130263772034,
	-0.142894153073187063,
	0.198737431642011769,
	0.781601167084910120,
	0.198737431642011769,
	-0.142894153073187119,
	0.075503130263772048,
	-0.020024146353593224,
	-0.010645028864524824,
	0.017857570436562421,
	-0.012188624969839886,
	0.004581219159106592,
	-0.000228126365317577,
	-0.001499855417445384,
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
