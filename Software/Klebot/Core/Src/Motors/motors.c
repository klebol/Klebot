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

uint8_t MotorsSwitch;

DRV8836_t MotorDriver;
MotorEncoder_t MotorEncoderA;
MotorEncoder_t MotorEncoderB;

FIRFilter EncoderFilterA;
FIRFilter EncoderFilterB;


int16_t TargetVelocityA;
int16_t TargetVelocityB;
PID_Controller_t MotorPID_A;
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
	case MOTOR_A:
		return DRV8836_SetMotor(&MotorDriver, motorAB, MotorDriver.a_direction, speed);
		break;

	case MOTOR_B:
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
	case MOTOR_A:
		return DRV8836_SetMotor(&MotorDriver, motorAB, direction, MotorDriver.a_speed);
		break;

	case MOTOR_B:
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
	status |= DRV8836_SetMotor(&MotorDriver, MOTOR_A, Coast, 0);
	status |= DRV8836_SetMotor(&MotorDriver, MOTOR_B, Coast, 0);
	return status;
}

//
// -- Getters --
//

uint16_t Motors_GetMotorPWM(DRV8836_Output_t motorAB)
{
	switch(motorAB)
		{
		case MOTOR_A:
			return MotorDriver.a_speed;
			break;

		case MOTOR_B:
			return MotorDriver.b_speed;
			break;

		default:
			return 0;
		}
}

DRV8836_Direction_t Motors_GetMotorDirection(DRV8836_Output_t motorAB)
{
	switch(motorAB)
		{
		case MOTOR_A:
			return MotorDriver.a_direction;

		case MOTOR_B:
			return MotorDriver.b_direction;

		default:
			return 0;
		}
}

//
// -- Encoder routine --
//

void Motors_EncoderSample(void)						//call this function with encoder sampling frequency
{
	/* Read encoder values and calculate velocity */
	MotorEnc_Update(&MotorEncoderA);
	MotorEnc_Update(&MotorEncoderB);

	/* Filter velocity values */
	MotorEncoderA.VelocityFiltered = FIRFilter_Update(&EncoderFilterA, MotorEncoderA.Velocity);
	MotorEncoderB.VelocityFiltered = FIRFilter_Update(&EncoderFilterB, MotorEncoderB.Velocity);

	/* Calculate RPM */
	//MotorEncoderB.RPM = (MotorEncoderB.Velocity * 60 * (1000/ENCODER_SAMPLING_TIME_MS)) / PULSES_PER_ROTATION;

	if(MotorsSwitch == 1)
	{
		/* Uptade motor's A PID if any of its gains its greater than 0 */
		if(MotorPID_A.kp > 0 || MotorPID_A.ki > 0|| MotorPID_A.kd > 0)
		{
			PID_Update(&MotorPID_A, TargetVelocityA - MotorEncoderA.VelocityFiltered , 1000 / ENCODER_SAMPLING_TIME_MS);

			if(MotorPID_A.Output > 0)
			{
				Motors_SetMotor(MOTOR_A, Reverse, DEAD_PWM_OFFSET + MotorPID_A.Output);
			}
			else
			{
				Motors_SetMotor(MOTOR_A, Forward, DEAD_PWM_OFFSET + (-MotorPID_A.Output) );
			}
		}
		/* Same for motor B */
		if(MotorPID_B.kp > 0 || MotorPID_B.ki > 0|| MotorPID_B.kd > 0)
		{
			PID_Update(&MotorPID_B, TargetVelocityB - MotorEncoderB.VelocityFiltered , 1000 / ENCODER_SAMPLING_TIME_MS);

			if(MotorPID_B.Output > 0)
			{
				Motors_SetMotor(MOTOR_B, Reverse, DEAD_PWM_OFFSET + MotorPID_B.Output);
			}
			else
			{
				Motors_SetMotor(MOTOR_B, Forward, DEAD_PWM_OFFSET + (-MotorPID_B.Output) );
			}
		}
	}



	/* Debug UART print */
	UartBufferLength = sprintf((char*) UartBuffer, "$%d %d;",(int16_t) MotorEncoderB.VelocityFiltered, MotorPID_B.Output );
	HAL_UART_Transmit(&huart2, UartBuffer, UartBufferLength, 500);

}

Motors_Error_t Motors_SetPIDTarget(DRV8836_Output_t motorAB, int16_t Target)
{
	if(Target > MAX_VELOCITY_VALUE || Target < -MAX_VELOCITY_VALUE)
	{
		return MOTORS_ERROR;
	}

	switch(motorAB)
	{
	case MOTOR_A:
		TargetVelocityA = Target;
		return MOTORS_OK;

	case MOTOR_B:
		TargetVelocityB = Target;
		return MOTORS_OK;

	case MOTOR_ALL:
		TargetVelocityA = Target;
		TargetVelocityB = Target;
		return MOTORS_OK;

	default:
		return MOTORS_ERROR;
	}
}

Motors_Error_t Motors_SetKP(DRV8836_Output_t motorAB, float p)
{
	switch(motorAB)
	{
	case MOTOR_A:
		PID_SetGains(&MotorPID_A, p, MotorPID_A.ki, MotorPID_A.kd);
		return MOTORS_OK;

	case MOTOR_B:
		PID_SetGains(&MotorPID_B, p, MotorPID_B.ki, MotorPID_B.kd);
		return MOTORS_OK;

	case MOTOR_ALL:
		PID_SetGains(&MotorPID_A, p, MotorPID_A.ki, MotorPID_A.kd);
		PID_SetGains(&MotorPID_B, p, MotorPID_B.ki, MotorPID_B.kd);
		return MOTORS_OK;

	default:
		return MOTORS_ERROR;
	}
}

Motors_Error_t Motors_SetKI(DRV8836_Output_t motorAB, float i)
{
	switch(motorAB)
	{
	case MOTOR_A:
		PID_SetGains(&MotorPID_A, MotorPID_A.kp, i, MotorPID_A.kd);
		return MOTORS_OK;

	case MOTOR_B:
		PID_SetGains(&MotorPID_B, MotorPID_B.kp, i, MotorPID_B.kd);
		return MOTORS_OK;

	case MOTOR_ALL:
		PID_SetGains(&MotorPID_A, MotorPID_A.kp, i, MotorPID_A.kd);
		PID_SetGains(&MotorPID_B, MotorPID_B.kp, i, MotorPID_B.kd);
		return MOTORS_OK;

	default:
		return MOTORS_ERROR;
	}
}

Motors_Error_t Motors_SetKD(DRV8836_Output_t motorAB, float d)
{
	switch(motorAB)
	{
	case MOTOR_A:
		PID_SetGains(&MotorPID_A, MotorPID_A.kp, MotorPID_A.ki, d);
		return MOTORS_OK;

	case MOTOR_B:
		PID_SetGains(&MotorPID_B, MotorPID_B.kp, MotorPID_B.ki, d);
		return MOTORS_OK;

	case MOTOR_ALL:
		PID_SetGains(&MotorPID_A, MotorPID_A.kp, MotorPID_A.ki, d);
		PID_SetGains(&MotorPID_B, MotorPID_B.kp, MotorPID_B.ki, d);
		return MOTORS_OK;

	default:
		return MOTORS_ERROR;
	}
}

Motors_Error_t Motors_ResetPIDGains(DRV8836_Output_t motorAB)
{
	switch(motorAB)
	{
	case MOTOR_A:
		PID_ResetGains(&MotorPID_A);
		return MOTORS_OK;

	case MOTOR_B:
		PID_ResetGains(&MotorPID_B);
		return MOTORS_OK;

	case MOTOR_ALL:
		PID_ResetGains(&MotorPID_A);
		PID_ResetGains(&MotorPID_B);
		return MOTORS_OK;

	default:
		return MOTORS_ERROR;
	}
}

Motors_Error_t Motors_ResetTemps(DRV8836_Output_t motorAB)
{
	switch(motorAB)
	{
	case MOTOR_A:
		PID_ResetTemps(&MotorPID_A);
		return MOTORS_OK;

	case MOTOR_B:
		PID_ResetTemps(&MotorPID_B);
		return MOTORS_OK;

	case MOTOR_ALL:
		PID_ResetTemps(&MotorPID_A);
		PID_ResetTemps(&MotorPID_B);
		return MOTORS_OK;

	default:
		return MOTORS_ERROR;
	}
}

void Motors_SetSwitch(uint8_t ONOFF)
{
	MotorsSwitch = ONOFF;
}

