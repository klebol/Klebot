/*
 * motors.c
 *
 *  Created on: Dec 30, 2023
 *      Author: miqix
 */

#include "Motors/motors.h"
#include "Motors/motor_encoder.h"
#include "FIRFilter.h"
#include "stdio.h"
#include "usart.h"

DRV8836_t MotorDriver;
MotorEncoder_t MotorEncoderA;
MotorEncoder_t MotorEncoderB;

FIRFilter EncoderFilterA;

//
//
//

uint8_t UartBuffer[16];
uint8_t UartBufferLength;

//
// -- Init --
//

void Motors_Init(void)
{
	DRV8836_Init(&MotorDriver, &htim3, TIM_CHANNEL_1, TIM_CHANNEL_2, TIM_CHANNEL_3, TIM_CHANNEL_4);
	MotorEnc_Init(&MotorEncoderA, &htim1);
	MotorEnc_Init(&MotorEncoderB, &htim4);

	FIRFilter_Init(&EncoderFilterA);
}

//
// -- Setters --
//

void Motors_SetMotor(DRV8836_Output_t motorAB, DRV8836_Direction_t direction, uint16_t speed)
{
	DRV8836_SetMotor(&MotorDriver, motorAB, direction, speed);
}

Motors_Error_t Motors_SetMotorPWM(DRV8836_Output_t motorAB, uint16_t speed)
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

//
// -- Getters --
//

uint16_t Motors_GetMotorPWM(DRV8836_Output_t motorAB)
{
	switch(motorAB)
		{
		case Output_A:
			return MotorDriver.a_speed;
			break;

		case Output_B:
			return MotorDriver.b_speed;
			break;
		}
	return 0;
}

DRV8836_Direction_t Motors_GetMotorDirection(DRV8836_Output_t motorAB)
{
	switch(motorAB)
		{
		case Output_A:
			return MotorDriver.a_direction;
			break;

		case Output_B:
			return MotorDriver.b_direction;
			break;
		}
	return 0;
}

//
// -- Encoder routine --
//

void Motors_EncoderSample(void)						//call this function with encoder sampling frequency
{
	MotorEnc_Uptade(&MotorEncoderA);
	MotorEnc_Uptade(&MotorEncoderB);
	//MotorEnc_FilterVelocity(&MotorEncoderA);
	//MotorEnc_FilterVelocity(&MotorEncoderB);

	MotorEncoderA.VelocityFiltered = FIRFilter_Update(&EncoderFilterA, MotorEncoderA.Velocity);


	UartBufferLength = sprintf((char*) UartBuffer, "$%d %d;",(int16_t) MotorEncoderA.VelocityFiltered, MotorEncoderA.Velocity );
	HAL_UART_Transmit(&huart2, UartBuffer, UartBufferLength, 500);

}
