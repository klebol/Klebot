/*
 * motors.c
 *
 *  Created on: Dec 30, 2023
 *      Author: miqix
 */

#include "Motors/motors.h"

DRV8836_t MotorDriver;
MotorEncoder_t MotorEncoderA;
MotorEncoder_t MotorEncoderB;


void Motors_Init(void)
{
	DRV8836_Init(&MotorDriver, &htim3, TIM_CHANNEL_1, TIM_CHANNEL_2, TIM_CHANNEL_3, TIM_CHANNEL_4);
	MotorEnc_Init(&MotorEncoderA, &htim1);
	MotorEnc_Init(&MotorEncoderB, &htim4);
}

void Motors_SetMotor(DRV8836_Output_t motorAB, DRV8836_Direction_t direction, uint16_t speed)
{
	DRV8836_SetMotor(&MotorDriver, motorAB, direction, speed);
}

Motors_Error_t Motors_SetMotorSpeed(DRV8836_Output_t motorAB, uint16_t speed)
{
	switch(motorAB)
	{
	case Output_A:
		return DRV8836_SetMotor(&MotorDriver, motorAB, MotorDriver.a_direction, speed);
		break;

	case Output_B:
		return DRV8836_SetMotor(&MotorDriver, motorAB, MotorDriver.b_direction, speed);
		break;

	default:
		return MOTORS_ERROR;
		break;
	}
}

Motors_Error_t Motors_SetMotorDirection(DRV8836_Output_t motorAB, DRV8836_Direction_t direction)
{
	switch(motorAB)
	{
	case Output_A:
		return DRV8836_SetMotor(&MotorDriver, motorAB, direction, MotorDriver.a_speed);
		break;

	case Output_B:
		return DRV8836_SetMotor(&MotorDriver, motorAB, direction, MotorDriver.b_speed);
		break;

	default:
		return MOTORS_ERROR;
		break;
	}
}

Motors_Error_t Motors_SetMotorsOff(void)
{
	Motors_Error_t status = 0;
	status |= DRV8836_SetMotor(&MotorDriver, Output_A, Coast, 0);
	status |= DRV8836_SetMotor(&MotorDriver, Output_B, Coast, 0);
	return status;
}


void Motors_EncoderSample(void)						//call this function with encoder sampling frequency
{
	MotorEnc_Uptade(&MotorEncoderA);
	MotorEnc_Uptade(&MotorEncoderB);
	MotorEnc_FilterVelocity(&MotorEncoderA);
	MotorEnc_FilterVelocity(&MotorEncoderB);
}
