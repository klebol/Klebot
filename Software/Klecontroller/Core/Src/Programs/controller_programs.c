/*
 * controller_programs.c
 *
 *  Created on: Nov 16, 2023
 *      Author: Michal Klebokowski
 */

#include "Programs/controller_programs.h"
#include "klebot_radio.h"
#include "klebot_commands.h"

/* Pointer to current running program struct */
Programs_Program_t *CurrentlyRunningProg;
/* Current program state */
Programs_status_t ProgramState = NO_PROGRAM_SET;
/* Var for counting communication timout during lauch/exit program */
uint16_t TimeoutStamp;

//
//	-- Sending programs start/exit commands --
//

static Programs_error_t Programs_SendProgramStartCommand(uint8_t ProgramID)
{
	uint8_t Buffer[2];
	Buffer[0] = START_PROGRAM;
	Buffer[1] = ProgramID;
	return Radio_TxBufferPut(Buffer, 2);
}

static Programs_error_t Programs_SendProgramExitCommand(void)
{
	uint8_t Buffer = EXIT_PROGRAM;
	return Radio_TxBufferPut(&Buffer, 1);
}

//
// -- General functions to manage programs --
//

/* Function starting a launch of specific program by setting current pointer
 * to program and sending start command to robot 				*/
Programs_error_t Programs_SetProgram(Programs_Program_t *ProgramToSet)
{
	if(NULL == ProgramToSet)
	{
		return PROGRAMS_ERROR;
	}

	if(NULL == CurrentlyRunningProg)
	{
		CurrentlyRunningProg = ProgramToSet;
		Programs_SendProgramStartCommand(ProgramToSet->ProgramID);
		TimeoutStamp = HAL_GetTick();
		ProgramState = PROGRAM_LAUNCHING;
		return PROGRAMS_OK;
	}
	else
	{
		return PROGRAMS_ERROR;
	}
}

/* Function starting a exit program process */
void Programs_ExitProgram(void)
{
	/* Call program DeInit function */
	CurrentlyRunningProg->ProgramExitFunction();
	/*Send exit program command to robot */
	Programs_SendProgramExitCommand();
	/*Start counting timeout for wainting to robot's ACK */
	TimeoutStamp = HAL_GetTick();
	ProgramState = PROGRAM_EXITING;

}

/* Function which returns current pointer to program */
Programs_Program_t* Programs_GetProgram(void)
{
	return CurrentlyRunningProg;
}

/* Clearing the program pointer and status variable */
void Programs_ClearProgram(void)
{
	CurrentlyRunningProg = NULL;
	ProgramState = NO_PROGRAM_SET;
}

/* Program performing function, made for being put in while loop */
Programs_status_t Programs_PerformProgram(void)
{
	switch(ProgramState)
	{
	case NO_PROGRAM_SET:
		/* No program set, no action */
		break;

	case PROGRAM_LAUNCHING:
		/* Waiting for program launch ACK from robot */
		if(HAL_GetTick() - TimeoutStamp > PROGRAM_START_TIMEOUT_MS)
		{
			ProgramState = PROGRAM_LAUNCH_ERROR;
		}
		break;

	case PROGRAM_IN_PROGRESS:
		/* Run the program */
		if(NULL != CurrentlyRunningProg->ProgramRoutine)
		{
			CurrentlyRunningProg->ProgramRoutine();
		}
		break;

	case PROGRAM_EXITING:
		/* Waiting for program exit ACK from robot */
		if(HAL_GetTick() - TimeoutStamp > PROGRAM_EXIT_TIMEOUT_MS)
		{
			ProgramState = PROGRAM_EXIT_ERROR;
		}
		break;

	case PROGRAM_COMPLETED:
		/* Clear the program after completing*/
		//Programs_ClearProgram();				//TODO: Think about this, can cause return problems
		break;

	case PROGRAM_LAUNCH_ERROR:
		/* Clear the program after launch error*/
		//Programs_ClearProgram();
		break;

	case PROGRAM_EXIT_ERROR:
		/* Clear the program after exit error*/
		//Programs_ClearProgram();
		break;

	default:
		break;
	}

	return ProgramState;
}

//
// -- Functions for parser to ACK launch/exit --
//

/* This functions are called by parser, when the robot acknowledges the proper program launch */

void Programs_ProgramLaunchedACK(uint8_t ProgramID, uint8_t ACKorNACK)
{
	switch(ACKorNACK)
	{
	case ACK:
		if(PROGRAM_LAUNCHING == ProgramState && ProgramID == CurrentlyRunningProg->ProgramID)
			{
				/* Call an init function for program which is being launched */
				CurrentlyRunningProg->ProgramInitFunction();
				/* Change the program state for program in progess state, which will allow the program itself to run */
				ProgramState = PROGRAM_IN_PROGRESS;
			}
		break;

	case NACK:
		//TODO: ADD NACK MANAGEMENT
		break;

	default:

		break;
	}
}

void Programs_ProgramExitACK(uint8_t ACKorNACK)
{
	switch(ACKorNACK)
	{
	case ACK:
		if(PROGRAM_EXITING == ProgramState)
		{
			ProgramState = PROGRAM_COMPLETED;
		}
		break;

	case NACK:
		//TODO: ADD NACK MANAGEMENT
		break;

	default:

		break;
	}

}
