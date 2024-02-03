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
#include "math.h"
#include "PID.h"

DRV8836_t MotorDriver;
MotorEncoder_t MotorEncoderA;
MotorEncoder_t MotorEncoderB;

FIRFilter EncoderFilterA;
FIRFilter EncoderFilterB;

//
//pid test
//
int8_t Target;
float kp = 1;
int8_t error;
float u;

float ki = 1;
float eintegral;
//

PID_Controller_t MotorPID_B;


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
	FIRFilter_Init(&EncoderFilterB);
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
	MotorEnc_Update(&MotorEncoderA);
	MotorEnc_Update(&MotorEncoderB);
	//MotorEnc_FilterVelocity(&MotorEncoderA);
	//MotorEnc_FilterVelocity(&MotorEncoderB);

	MotorEncoderA.VelocityFiltered = FIRFilter_Update(&EncoderFilterA, MotorEncoderA.Velocity);
	MotorEncoderB.VelocityFiltered = FIRFilter_Update(&EncoderFilterB, MotorEncoderB.Velocity);

	MotorEncoderB.RPM = (MotorEncoderB.Velocity * 60 * (1000/ENCODER_SAMPLING_TIME_MS)) / PULSES_PER_ROTATION;

	//PID


	if(MotorPID_B.kp > 0)
	{
		PID_Update(&MotorPID_B, Target - MotorEncoderB.VelocityFiltered , 100);

		if(MotorPID_B.Output > 0)
		{
			Motors_SetMotor(Output_B, Reverse, 150 + MotorPID_B.Output);
		}
		else
		{
			Motors_SetMotor(Output_B, Forward, 150 + (-MotorPID_B.Output) );
		}
	}





	UartBufferLength = sprintf((char*) UartBuffer, "$%d %d;",(int16_t) MotorEncoderB.VelocityFiltered, MotorPID_B.Output );
	HAL_UART_Transmit(&huart2, UartBuffer, UartBufferLength, 500);

}

// PID TEST

void Motors_RoutinePID(void)
{

	DRV8836_Direction_t dir = Forward;
	float pwm;

	static uint16_t LastTick;
	uint16_t CurrentTick = HAL_GetTick();
	float DeltaT = ((float) (CurrentTick - LastTick))/1.0e6;
	LastTick = CurrentTick;
	CurrentTick = HAL_GetTick();



	error = MotorEncoderB.VelocityFiltered - Target;

	eintegral = eintegral + error*DeltaT;

	u = kp * error + ki*eintegral;



	if(error < 0)
	{
		dir = Reverse;
	}

	pwm = fabs(u);

	if(pwm > 255)
	{
		pwm = 255;
	}

	Motors_SetMotor(Output_B, dir, pwm);

}

void Motors_SetPIDTarget(int8_t target)
{
	Target = target;
}
