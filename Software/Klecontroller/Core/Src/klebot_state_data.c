/*
 * klebot_state_data.c
 *
 *  Created on: Jan 11, 2024
 *      Author: Michal Klebokowski
 */
#include "klebot_state_data.h"

Motor_Data_t LeftMotor;
Motor_Data_t RightMotor;

void StateData_Parser(uint8_t *command, uint8_t length)
{
	uint8_t *CurrentByte = command;

	switch(*CurrentByte)
	{
	case MOTOR_A:			//TODO ANOTHER MACRO NEEDED
		CurrentByte++;

		break;

	default:
		break;
	}
}

uint16_t StateData_Get_MotorPWM(uint8_t motorID)
{
	switch(motorID)
	{
	case MOTOR_A:
		return LeftMotor.PWM;

	case MOTOR_B:
		return RightMotor.PWM;

	default:
		return 0;

	}
}
