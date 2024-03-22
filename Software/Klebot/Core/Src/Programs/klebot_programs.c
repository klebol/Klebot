/*
 * klebot_programs.c
 *
 *  Created on: Nov 29, 2023
 *      Author: Michal Klebokowski
 */
#include "Programs/klebot_programs.h"
/* FreeRTOS includes */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
/* Other */
#include "klebot_commands.h"
#include "radio_task.h"
#include "stdlib.h"


/* Programs task handler */
TaskHandle_t xTaskProgramsHandle;
/* Pointer to current running program struct */
Programs_Program_t *CurrentlyRunningProg;
/* Current program state */
Programs_status_t ProgramState = NO_PROGRAM_SET;



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
		/* another program is running */
		return PROGRAMS_ERROR;
	}
}

/* Function starting a exit program process */
Programs_error_t Programs_ExitProgram(void)
{
	if(NULL == CurrentlyRunningProg)
	{
		/* No currently running program to exit */
		return PROGRAMS_ERROR;
	}
	/* Call program DeInit function */
	CurrentlyRunningProg->ProgramExitFunction();
	/* Change state to program completed */
	ProgramState = PROGRAM_COMPLETED;
	return PROGRAMS_OK;
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

//
// Programs Task
//
void vTaskPrograms(void *pvParameters)
{

	for(;;)
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
			Programs_ClearProgram();
			break;

		default:
			break;
		}
	}
}

void Programs_TaskInit(void)
{
	xTaskCreate(vTaskPrograms, "Programs Task", 512, NULL, 1, &xTaskProgramsHandle);
}


//
// -- Functions for parser to ACK reponses --
//

/* These functions are called after program launch / exit. Sending it is needed for controller to proper functionality and sync with robot */

Programs_error_t Programs_SendProgramStartedACK(uint8_t ProgramID, uint8_t ACKorNACK)
{
	Radio_Frame_t Buffer;
	Buffer.data[0] = PROGRAM_FRAME;
	Buffer.data[1] = START_PROGRAM;
	Buffer.data[2] = ProgramID;
	Buffer.data[3] = ACKorNACK;
	Buffer.length = 4;
	return Radio_TxPutFrame(&Buffer);
}

Programs_error_t Programs_SendProgramExitACK(uint8_t ACKorNACK)
{
	Radio_Frame_t Buffer;
	Buffer.data[0] = PROGRAM_FRAME;
	Buffer.data[1] = EXIT_PROGRAM;
	Buffer.data[2] = ACKorNACK;
	Buffer.length = 3;
	return Radio_TxPutFrame(&Buffer);
}

/* Sends NACK after receiving a command for not currently running one */
Programs_error_t Programs_SendInvalidProgramNACK(uint8_t ProgramID)
{
	Radio_Frame_t Buffer;
	Buffer.data[0] = PROGRAM_FRAME;
	Buffer.data[1] = PROGRAM_COMMAND;
	Buffer.data[2] = ProgramID;
	Buffer.data[3] = NACK;
	Buffer.length = 4;
	return Radio_TxPutFrame(&Buffer);
}
