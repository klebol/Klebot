/*
 * klebot_parser.c
 *
 *  Created on: 29 maj 2023
 *      Author: Michal Klebokowski
 */

#include "klebot_parser.h"
#include "klebot_commands.h"
#include "Programs/klebot_programs.h"
#include "Programs/DiodeTest_Prog.h"
#include "Programs/MotorsDebug_Prog.h"

void Parser_ParseProgramLaunchCommand(uint8_t ProgramID)
{
	uint8_t status;
	/* Launch proper program */
	/* When another program is currently running, launch function will return error */
	switch(ProgramID)
	{
	case DIODE_TEST:
		status = Prog_DiodeTest_Launch();
		break;

	case MOTORS_DEBUG:
		status = Prog_MotorsDebug_Launch();
		break;

	default:
		status = PROGRAMS_ERROR;
		break;
	}

	/* Send ACK to controller */
	if(status == PROGRAMS_OK)
	{
		Programs_SendProgramStartedACK(ProgramID, ACK);		//TODO: Maybe ACK should be sent after each program Init function ?
	}
	else
	{
		Programs_SendProgramStartedACK(ProgramID, NACK);
	}
}

void Parser_Klebot(uint8_t *command, uint8_t length)
{
	uint8_t *CurrentByte = command;
	uint8_t Length = length;
	Programs_Program_t* CurrentProgram = Programs_GetProgram();

	/* If the command header is currently running program's ID, then pass the rest fo the command to it's parser */
	if(*CurrentByte == CurrentProgram->ProgramID)
	{
		CurrentByte++;
		Length--;
		/* Frame: [ProgramID, Specific program commands...] */
		CurrentProgram->ProgramParser(CurrentByte, Length);
	}
	else
	/* If command header is different, check if it is launch/exit commands */
	{
		switch(*CurrentByte)
		{
		case START_PROGRAM:
			/* Frame: [START_PROGRAM, PROGRAM_ID] */
			uint8_t ProgramToLaunch = *(CurrentByte + 1);
			Parser_ParseProgramLaunchCommand(ProgramToLaunch);
			break;

		case EXIT_PROGRAM:
			/* Frame: [PROGRAM_EXIT] */
			Programs_ExitProgram();
			Programs_SendProgramExitACK(ACK);
			break;

		default:
			/* Incorrect command! */

			break;
		}
	}
}


