/*
 * controller_parser.c
 *
 *  Created on: Dec 1, 2023
 *      Author: miqix
 */
#include "stddef.h"
#include "controller_parser.h"
#include "klebot_commands.h"
#include "Programs/controller_programs.h"
#include "Programs/DiodeTest_Prog.h"
#include "Programs/MotorsDebug_Prog.h"


void Parser_Controller(uint8_t *command, uint8_t length)							//main parser funciton
{
	uint8_t *CurrentByte = command;
	uint8_t Length = length;
	Programs_Program_t* CurrentProgram = Programs_GetProgram();

	/* If the command header is currently running program's ID, then pass the rest fo the command to it's parser */
	if(NULL != CurrentProgram && *CurrentByte == CurrentProgram->ProgramID)
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
			/* Frame: [START_PROGRAM, ProgramID, Ack or Nack] */
			CurrentByte++;
			Programs_ProgramLaunchedACK(*CurrentByte, *(CurrentByte + 1) );
			break;

		case EXIT_PROGRAM:
			/* Frame: [EXIT_PROGRAM, Ack or Nack] */
			CurrentByte++;
			Programs_ProgramExitACK(*CurrentByte);
			break;

		default:
			break;
		}
	}
}



