/*
 * motor_encoder.c
 *
 *  Created on: Dec 14, 2023
 *      Author: miqix
 */
#include "Motors/motor_encoder.h"

int16_t VelocityFilterBuffer[100];
int32_t FilterSum;
uint16_t OldestMember;


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

	encoder->RPM = (encoder->Velocity * (1000 / ENCODER_SAMPLING_TIME_MS) * 60 ) / PULSES_PER_ROTATION; //define constants
	encoder->LastCounter = NewCounter;
}

void MotorEnc_FilterVelocity(MotorEncoder_t *encoder)
{


	//static float VelocityIIR;


	float alpha = 0.1;
	encoder->VelocityFiltered = alpha * (float) encoder->Velocity + (1.0f - alpha) * encoder->VelocityFiltered;

//
//	FilterSum = FilterSum + VelocityIIR - VelocityFilterBuffer[OldestMember];
//	encoder->VelocityFiltered = FilterSum / 100;
//	VelocityFilterBuffer[OldestMember] = VelocityIIR;
//	OldestMember = (OldestMember + 1) % 100;



}
