/*
 * klebot_programs.c
 *
 *  Created on: Nov 29, 2023
 *      Author: Michal Klebokowski
 */
#include "Programs/klebot_programs.h"
#include "klebot_radio.h"
#include "klebot_commands.h"

/* Pointer to current running program struct */
Programs_Program_t *CurrentlyRunningProg;
/* Current program state */
Programs_status_t ProgramState = NO_PROGRAM_SET;
/* Var for counting communication timout during lauch/exit program */
uint16_t TimeoutStamp;


//
// -- General functions to manage programs --
//

/* Function starting a launch of specific program by setting current pointer
 * to program and calling it's init function				*/
Programs_error_t Programs_SetProgram(Programs_Program_t *ProgramToSet)
{
	if(NULL == ProgramToSet)
	{
		return PROGRAMS_ERROR;
	}

	if(NULL == CurrentlyRunningProg)
	{
		/* Set current program pointer */
		CurrentlyRunningProg = ProgramToSet;
		/* Call it's init function */
		CurrentlyRunningProg->ProgramInitFunction();
		/* Change state to program in progrss, it will allow it to run in perfom fun */
		ProgramState = PROGRAM_IN_PROGRESS;
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
	/* Change state to program completed */
	ProgramState = PROGRAM_COMPLETED;
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

	case PROGRAM_IN_PROGRESS:
		/* Run the program */
		if(NULL != CurrentlyRunningProg->ProgramRoutine)
		{
			CurrentlyRunningProg->ProgramRoutine();
		}
		break;

	case PROGRAM_COMPLETED:
		/* Clear the program after completing*/
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

/* This functions are called after program launch / exit. Sending it is needed for controller to proper functionality and sync with robot */

Programs_error_t Programs_SendProgramStartedACK(uint8_t ProgramID, uint8_t ACKorNACK)
{
	uint8_t Buffer[3];
	Buffer[0] = START_PROGRAM;
	Buffer[1] = ProgramID;
	Buffer[2] = ACKorNACK;
	return Radio_TxBufferPut(Buffer, 3);
}

Programs_error_t Programs_SendProgramExitACK(uint8_t ACKorNACK)
{
	uint8_t Buffer[2];
	Buffer[0] = EXIT_PROGRAM;
	Buffer[1] = ACKorNACK;
	return Radio_TxBufferPut(Buffer, 2);
}

