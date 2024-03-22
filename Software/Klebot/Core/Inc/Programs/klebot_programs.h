/*
 * klebot_programs.h
 *
 *  Created on: Nov 29, 2023
 *      Author: miqix
 */

#ifndef INC_KLEBOT_PROGRAMS_H_
#define INC_KLEBOT_PROGRAMS_H_

#include "stdint.h"

#define PROGRAM_START_TIMEOUT_MS 1000
#define PROGRAM_EXIT_TIMEOUT_MS 1000

typedef enum
{
	NO_PROGRAM_SET,
	//PROGRAM_LAUNCHING,		//NOT USED ON ROBOTS SIDE
	PROGRAM_IN_PROGRESS,
	//PROGRAM_EXITING,			//NOT USED ON ROBOTS SIDE
	PROGRAM_COMPLETED
	//PROGRAM_LAUNCH_ERROR,		//NOT USED ON ROBOTS SIDE
	//PROGRAM_EXIT_ERROR		//NOT USED ON ROBOTS SIDE
}Programs_status_t;

typedef enum
{
	PROGRAMS_OK,
	PROGRAMS_ERROR,
	PROGRAMS_BUSY
}Programs_error_t;

typedef struct
{
	Programs_error_t (*ProgramInitFunction)(void);				//Init function for each program
	Programs_error_t (*ProgramExitFunction)(void);				//Deinit function, exit funcion
	Programs_error_t (*ProgramRoutine)(void);					//Program funcion itself
	void (*ProgramParser)(uint8_t *command, uint8_t length);	//Program parser
	uint8_t ProgramID;
}Programs_Program_t;
//
// -- Public functions --
//

/* Task init */
void Programs_TaskInit(void);
/* Set program to launch */
Programs_error_t Programs_SetProgram(Programs_Program_t *ProgramToSet);

/* Exit current running program */
Programs_error_t Programs_ExitProgram(void);

/* Get pointer to curent running program */
Programs_Program_t* Programs_GetProgram(void);

/* Clear pointer to current running program */
void Programs_ClearProgram(void);

/* Infinite loop program routine */
Programs_status_t Programs_PerformProgram(void);

/* Function for sending ACK to controller about program launch result */
Programs_error_t Programs_SendProgramStartedACK(uint8_t ProgramID, uint8_t ACKorNACK);

/* Function for sending ACK to controller about program exit result */
Programs_error_t Programs_SendProgramExitACK(uint8_t ACKorNACK);

/* Sends NACK after receiving a command for not currently running one */
Programs_error_t Programs_SendInvalidProgramNACK(uint8_t ProgramID);




#endif /* INC_KLEBOT_PROGRAMS_H_ */
