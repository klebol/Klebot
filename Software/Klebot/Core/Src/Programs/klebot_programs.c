/*
 * klebot_programs.c
 *
 *  Created on: Nov 29, 2023
 *      Author: miqix
 */
#include "Programs/klebot_programs.h"

DRV8836_t MotorDriver; // TEMPORARY FOR TEST!!!!

Programs_status_t (*ProgramToPerform)(void);	//pointer to program to execute

//
// --------------------- General functions to manage programs ---------------------
//

Programs_error_t Programs_SetProgram(uint8_t (*Program)(void))
{
	if(NULL == ProgramToPerform)
	{
		ProgramToPerform = Program;
		return PROGRAMS_OK;
	}
	else
	{
		return PROGRAMS_ERROR;
	}
}

Programs_status_t (*Programs_GetProgram(void))(void)	//super weird syntax function which returns out current pointer to program
{
	return ProgramToPerform;
}

void Programs_ClearProgram(void)
{
	ProgramToPerform = NULL;
}

Programs_status_t Programs_PerformProgram(void)
{
	Programs_status_t status;
	if(NULL != ProgramToPerform)		//if there is a program to perform
	{
		status = ProgramToPerform();	//perform it and return it's status
	}
	else
	{
		status = NO_PROGRAM_SET;
	}
	return status;
}

Programs_error_t Programs_SendProgramStartedACK(uint8_t ProgramID)
{
	uint8_t Buffer[3];
	Buffer[0] = ProgramID;
	Buffer[1] = START_PROGRAM;
	Buffer[2] = ACK;
	return Radio_TxBufferPut(Buffer, 3);
}

Programs_error_t Programs_SendProgramExitACK(uint8_t ProgramID)
{
	uint8_t Buffer[3];
	Buffer[0] = ProgramID;
	Buffer[1] = EXIT_PROGRAM;
	Buffer[2] = ACK;
	return Radio_TxBufferPut(Buffer, 3);
}

//
// --------------------- Specific programs ---------------------
//

//
//	--- Diode Test Program ---
//























//
// --- Free Ride Program ---
//
Programs_status_t FreeRide (void)
{
	static uint8_t StartupInitFlag = 0;
	if(0 == StartupInitFlag)
	{
		DRV8836_Init(&MotorDriver, &htim3, TIM_CHANNEL_1, TIM_CHANNEL_2, TIM_CHANNEL_3, TIM_CHANNEL_4);
		StartupInitFlag = 1;
	}
	return PROGRAM_IN_PROGRESS;
}

void FreeRide_Parser(uint8_t *command, uint8_t length)
{
	uint8_t *CurrentByte = command;
	//uint8_t Length = length;

	switch(*CurrentByte)
	{
	case START_PROGRAM:
		Programs_SetProgram(FreeRide);
		break;
	case EXIT_PROGRAM:

		break;
	case LEFT_MOTOR_SPEED:
		CurrentByte++;
		DRV8836_SetSpeed(&MotorDriver, Output_A, *CurrentByte);
		break;

	case RIGHT_MOTOR_SPEED:
		CurrentByte++;
		DRV8836_SetSpeed(&MotorDriver, Output_B, *CurrentByte);
		break;

	case LEFT_MOTOR_DIRECTION:
		CurrentByte++;
		DRV8836_SetDirection(&MotorDriver, Output_A, *CurrentByte);
		break;

	case RIGHT_MOTOR_DIRECTION:
		CurrentByte++;
		DRV8836_SetDirection(&MotorDriver, Output_B, *CurrentByte);
		break;

	default:
		break;
	}



}