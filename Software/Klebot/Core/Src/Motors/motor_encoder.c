/*
 * motor_encoder.c
 *
 *  Created on: Dec 14, 2023
 *      Author: miqix
 */
#include "Motors/motor_encoder.h"


void MotorEnc_Init(MotorEncoder_t *encoder, TIM_HandleTypeDef *htim)
{
	encoder->htimEnc = htim;
	HAL_TIM_Encoder_Start(htim, TIM_CHANNEL_ALL);
}

void MotorEnc_Uptade(MotorEncoder_t *encoder)
{
	uint32_t NewCounter = encoder->htimEnc->Instance->CNT;
	int16_t TempPosition = encoder->Position;

	if(NewCounter == encoder->LastCounter)
	{
		encoder->Velocity = 0;
	}
	else if(NewCounter > encoder->LastCounter)
	{
		if(__HAL_TIM_IS_TIM_COUNTING_DOWN(encoder->htimEnc))	//overflow happened
		{
			encoder->Velocity = - ( encoder->LastCounter + (encoder->htimEnc->Instance->ARR - NewCounter) );
		}
		else
		{
			encoder->Velocity = NewCounter - encoder->LastCounter;
		}
	}
	else if(NewCounter < encoder->LastCounter)
	{
		if(__HAL_TIM_IS_TIM_COUNTING_DOWN(encoder->htimEnc))
		{
			encoder->Velocity = NewCounter - encoder->LastCounter;
		}
		else																//overflow happened
		{
			encoder->Velocity = NewCounter + (encoder->htimEnc->Instance->ARR + encoder->LastCounter);
		}
	}


	TempPosition = encoder->Position + encoder->Velocity;

	if(encoder->Velocity != 0)
	{
		if(TempPosition >= 0)
		{
			encoder->Position = (encoder->Position + encoder->Velocity) % PULSES_PER_ROTATION;
		}
		else
		{
			encoder->Position = PULSES_PER_ROTATION + encoder->Velocity;
		}
	}

	encoder->RPM = (encoder->Velocity * 6000) / 1400; //define constants
	encoder->LastCounter = NewCounter;

}
